/*
 * orbit.cpp
 *
 * Program to demonstrate how to use a local
 * coordinate method to position parts of a
 * model in relation to other model parts.
 *
 * Draws a simple solar system, with a sun, planet and moon.
 * Based on sample code from the OpenGL programming guide
 * by Woo, Neider, Davis.  Addison-Wesley.
 *
 * Author: Samuel R. Buss
 *
 * Software accompanying the book
 * 3D Computer Graphics: A Mathematical Introduction with OpenGL,
 * by S. Buss, Cambridge University Press, 2003.
 *
 * Software is "as-is" and carries no warranty.  It may be used without
 * restriction, but if you modify it, please change the filenames to
 * prevent confusion between different versions.
 *
 * Bug reports: Sam Buss, sbuss@ucsd.edu.
 * Web page: http://math.ucsd.edu/~sbuss/MathCG
 *
 * USAGE:
 *    Press the "r" key to toggle (off and on) running the animation
 *    Press the "t" key to single-sTep animation
 *    Press the "f" key to go to the next draw style.
 *			 Texture mapped -> Wireframe -> Flat -> Smooth
 *		Press the "c" key to toggle the Camera mode.
 *				Translate <-> Rotate	
 *
 *		Q and A increase and decrease the X direction in the current camera direction.
 *		Q moves you in the positive X direction in translate mode.
 *		Q rotates you around the X axis in the positive direction in rotate mode.
 *
 *		W/S does the same in the Y direction. E/D does the same in the Z direction.
 *		Note that moving in the Z direction is the same as zooming.
 *
 *		Press the space bar to reset the camera to its starting position.
 *
 *    The up and down array keys control the time step used in the animation rate.
 *    Each key press multiplies or divides the times by a factor of two.
 *    Press ESCAPE to exit.
 */

// JMW: Minor modifications for CSC433/533 Computer Graphics, Fall 2016.
// Grant Hill and Jayson Kjenstad: Major modifications for above computer graphics course.

#include <cstdlib>
#include <GL/freeglut.h>
#include "readPlanets.h"
#include "solar_system.h"

// function prototypes
void OpenGLInit( void );
void Animate( void );
void Key_r( void );
void Key_t( void );
void Key_up( void );
void Key_down( void );
void Cycle_draw( void );
void ResizeWindow( int w, int h );
void KeyPressFunc( unsigned char Key, int x, int y );
void ResetCamera();
void SpecialKeyFunc( int Key, int x, int y );

// global variables
GLenum spinMode = GL_TRUE;
GLenum singleStep = GL_FALSE;

// these three variables control the animation's state and speed.
float HourOfDay = 0.0;
float DayOfYear = 0.0;
float AnimateIncrement = 24.0;  // Time step for animation (hours)

DrawStyle currentStyle = TextureMapped;

enum CameraMode {Translate, Rotate};

//How far to step the camera when the user presses a key.
const float cameraStep = .05;

//Which way to move the camera when the user clicks and drags.
CameraMode currentCamera = Translate;

//Store the current transformation state.
float cameraTransforms[2][3] = {{0}};

// glutKeyboardFunc is called to set this function to handle normal key presses.
void KeyPressFunc( unsigned char Key, int x, int y )
{
	switch ( Key )
	{
		//Press the "r" key to toggle (off and on) running the animation
		case 'R':
		case 'r':
			Key_r();
			break;
		
		//Press the "t" key to single-sTep animation
		case 't':
		case 'T':
			Key_t();
			break;
		
		//Press the "f" key to go to the next draw style.
		//Texture mapped -> Wireframe -> Flat -> Smooth
		case 'f':
		case 'F':
			//Go to the "next" draw style.
			//See the DrawStyle enum in solar_system.h.
			currentStyle = DrawStyle((currentStyle + 1) % 4);

			//So, this guy in the secret sauce to getting the wire frame and
			//other shading options working. Turns out, if you have texture_2D
			//enabled, it disables regular colors and materials. Weird, right?
			if (currentStyle == TextureMapped)
				glEnable(GL_TEXTURE_2D);
			else
				glDisable(GL_TEXTURE_2D);
			break;

		//Go to the "next" camera mode. 
		//translate -> rotate -> zoom
		case 'c':
		case 'C':
			currentCamera = CameraMode((currentCamera + 1) % 2);
			break;


		//These guys are responsible for moving the camera.
		case 'q':
		case 'Q':
			cameraTransforms[currentCamera][0] += cameraStep;
			break;
		case 'w':
		case 'W':
			cameraTransforms[currentCamera][1] -= cameraStep;
			break;
		case 'e':
		case 'E':
			cameraTransforms[currentCamera][2] += cameraStep;
			break;

		case 'a':
		case 'A':
			cameraTransforms[currentCamera][0] -= cameraStep;
			break;
		case 's':
		case 'S':
			cameraTransforms[currentCamera][1] += cameraStep;
			break;
		case 'd':
		case 'D':
			cameraTransforms[currentCamera][2] -= cameraStep;
			break;
		case 'o':
		case 'O':
			AnimateIncrement *= 2.0;
			break;
		case 'p':
		case 'P':
			AnimateIncrement /= 2.0;
			break;

		//Move the camera back to the start.
		case ' ':
			ResetCamera();
			break;

		case 27: 	// Escape key
			exit( 1 );
	}
}

// glutSpecialFunc is called to set this function to handle all special key presses
// See glut.h for the names of special keys.
void SpecialKeyFunc( int Key, int x, int y )
{
	switch ( Key )
	{
		case GLUT_KEY_UP:
			Key_up();
			break;
		case GLUT_KEY_DOWN:
			Key_down();
			break;
	}
}

// restart animation
void Key_r( void )
{
	if ( singleStep )
	{			// If ending single step mode
		singleStep = GL_FALSE;
		spinMode = GL_TRUE;		// Restart animation
	}
	else
	{
		spinMode = !spinMode;	// Toggle animation on and off.
	}
}

// single step animation
void Key_t( void )
{
	singleStep = GL_TRUE;
	spinMode = GL_TRUE;
}

// animation speed
void Key_up( void )
{
	AnimateIncrement *= 2.0;			// Double the animation time step
}

// animation speed
void Key_down( void )
{
	AnimateIncrement /= 2.0;			// Halve the animation time step
}

//Reset the camera to its starting position.
void ResetCamera()
{
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 3; j++)
		{
			cameraTransforms[i][j] = 0;
		}
}

// Animate() handles the animation and the redrawing of the graphics window contents.
void Animate( void )
{

	// Clear the redering window
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	if ( spinMode )
	{
		// Update the animation state
		HourOfDay += AnimateIncrement;
		DayOfYear += AnimateIncrement / 24.0;
	}

	glMatrixMode( GL_PROJECTION );

	glLoadIdentity();
	//Move the "back" far enough that we can see all the planets.
	gluPerspective(55, 1.333, 1, 1000); 

	//Translate the camera according to the user's wishes.
	glTranslatef(cameraTransforms[Translate][0],cameraTransforms[Translate][1], cameraTransforms[Translate][2]);

	//Rotate the view appropriately.
	glRotatef(cameraTransforms[Rotate][0], 1, 0, 0);
	glRotatef(cameraTransforms[Rotate][1], 0, 1, 0);
	glRotatef(cameraTransforms[Rotate][2], 0, 0, 1);

	glMatrixMode( GL_MODELVIEW );

	//Draw the planets!
	sun(HourOfDay, DayOfYear, currentStyle);
	mercury(HourOfDay, DayOfYear, currentStyle);
	venus(HourOfDay, DayOfYear, currentStyle);
	earth(HourOfDay, DayOfYear, currentStyle);
	mars(HourOfDay, DayOfYear, currentStyle);
	jupiter(HourOfDay, DayOfYear, currentStyle);
	saturn(HourOfDay, DayOfYear, currentStyle);
	uranus(HourOfDay, DayOfYear, currentStyle);
	neptune(HourOfDay, DayOfYear, currentStyle);

	// Flush the pipeline, and swap the buffers
	glutSwapBuffers();

	if ( singleStep )
	{
		spinMode = GL_FALSE;
	}


	glutPostRedisplay();		// Request a re-draw for animation purposes
}

// Initialize OpenGL's rendering modes
void OpenGLInit( void )
{
	glShadeModel( GL_SMOOTH );
	glClearColor( 0.0, 0.0, 0.0, 0.0 );
	glClearDepth( 1.0 );

	glEnable( GL_DEPTH_TEST );
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 1);


	//This guy lets us use glColor for our wireframes.
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);

	//Gotta have lights.
	glEnable(GL_LIGHT0);
}

// ResizeWindow is called when the window is resized
void ResizeWindow( int w, int h )
{
	float aspectRatio;
	h = ( h == 0 ) ? 1 : h;
	w = ( w == 0 ) ? 1 : w;
	glViewport( 0, 0, w, h );	// View port uses whole window
	aspectRatio = ( float ) w / ( float ) h;

	// Set up the projection view matrix (not very well!)
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	gluPerspective( 60.0, aspectRatio, 1.0, 30.0 );

	// Select the Modelview matrix
	glMatrixMode( GL_MODELVIEW );
}

//menu selections go to this function
void menu(int menu)
{
	KeyPressFunc(menu, 0, 0 );

	glutPostRedisplay();

	return;
}

//creates a clickable menu showing all of the different controls
void MenuSetting()
{
 
	glutCreateMenu(menu);
	glutAddMenuEntry("C - Toggle camera controls between translation and rotation", 'c');
	glutAddMenuEntry("Q - Move camera left / Rotate along x axis", 'q');
	glutAddMenuEntry("A - Move camera right / Rotate along x axis", 'a');
	glutAddMenuEntry("W - Move camera up / Rotate along y axis", 'w');
	glutAddMenuEntry("S - Move camera down / Rotate along y axis", 's');
	glutAddMenuEntry("E - Zoom in / Rotate along z axis",'e');
	glutAddMenuEntry("D - Zoom out / Rotate along z axis", 'd');
	glutAddMenuEntry("T - Single step mode", 't');
	glutAddMenuEntry("R - Restart animation", 'r');
	glutAddMenuEntry("F - Cycle through draw styles", 'f');
	glutAddMenuEntry("Up arrow - Animation speed up", 'o');
	glutAddMenuEntry("Down arrow - Animation speed down", 'p');
	glutAddMenuEntry("Space - Reset camera", ' ');


	glutAttachMenu(GLUT_RIGHT_BUTTON);
}


// Main routine
// Set up OpenGL, hook up callbacks, and start the main loop
int main( int argc, char** argv )
{
	// Need to double buffer for animation
	glutInit( &argc, argv );
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH );

	// Create and position the graphics window
	glutInitWindowPosition( 0, 0 );
	glutInitWindowSize( 600, 360 );
	glutCreateWindow( "Solar System!" );

	// Initialize OpenGL.
	OpenGLInit();

	MenuSetting();

	// Set up callback functions for key presses
	glutKeyboardFunc( KeyPressFunc );
	glutSpecialFunc( SpecialKeyFunc );

	// Set up the callback function for resizing windows
	glutReshapeFunc( ResizeWindow );

	// Callback for graphics image redrawing
	glutDisplayFunc( Animate );

	readPlanets();

	// Start the main loop.  glutMainLoop never returns.
	glutMainLoop( );

	return 0;
}
