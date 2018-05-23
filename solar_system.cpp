///////////////////////////////////////////////////////////////////////////////
//solar_system.cpp
//Code by Grant Hill and Jayson Kjenstad
//The code in this file is responisble for drawing the planets in the solar
//system.  The draw style is specified in this file (wireframe, flat, smooth
//texture). Labels for each planet is made in this file.  And finally the 
//planets themselves are drawn here with the needed gl translate/rotate/ect
//functions. The speeds of rotation and orbit are also specified
///////////////////////////////////////////////////////////////////////////////
#include <GL/freeglut.h>
#include "readPlanets.h"
#include "solar_system.h"

//Helper functon to draw each drawable object (I know, "planet" isn't 
//technically correct, since we also have the moon and Saturn's rings)
void HandleDrawStyle(GLUquadric* planet, PlanetTexture tex,	DrawStyle style)
{
	GLenum toDraw = GLU_FILL;

	switch (style)
	{
		case Wireframe:
			toDraw = GLU_LINE;

		case Flat:
			gluQuadricNormals(planet, GLU_FLAT);
			break;

		case Smooth:
			gluQuadricNormals(planet, GLU_SMOOTH);
			break;

		case TextureMapped:
			getPlanetTexture(tex);
			gluQuadricTexture(planet, GLU_TRUE);
			break;
	}

	gluQuadricDrawStyle(planet, toDraw);
}

//This functinon draws a label showing the planets name
void EmissiveLabel(const char* label)
{
	float emission_color[4] = {1.0, 1.0, 1.0, 1.0 };
	glMaterialfv(GL_FRONT, GL_EMISSION, emission_color);

	glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)label);

	float turn_off_emission[4] = {0.0, 0.0, 0.0, 0.0 };
	glMaterialfv(GL_FRONT, GL_EMISSION, turn_off_emission);
}

//All these planet ones are the same. Draw the planet at the 
//given location.
void sun(float HourOfDay, float DayOfYear, DrawStyle style)
{
	// Clear the current matrix (Modelview)
	glLoadIdentity();

	// Back off eight units to be able to view from the origin.
	glTranslatef ( 0.0, 0.0, -8.0 );

	//Rotate the sun 90 degrees so its axis is vertical.
	glRotatef(90, 1, 0, 0);

	float emission_color[4] = {1.0, 1.0, .5, 0.0 };
	glMaterialfv(GL_FRONT, GL_EMISSION, emission_color);

	//Set the sun's color- it should be yellow.
	glColor3f(1, 1, 0);

	//Make and draw the sun.
	GLUquadricObj* sun = gluNewQuadric();
	HandleDrawStyle(sun, PlanetTexture::Sun, style);
	gluSphere(sun, 1.0, 15, 15);
	gluDeleteQuadric(sun);

	//Nothing else should emit.
	float turn_off_emission[4] = {0.0, 0.0, 0.0, 0.0 };
	glMaterialfv(GL_FRONT, GL_EMISSION, turn_off_emission);

	glRasterPos3f(0, 0, -1.25);
	EmissiveLabel("Sun");
    
}

void mercury(float HourOfDay, float DayOfYear, DrawStyle style)
{
	glLoadIdentity();
	glColor3f(.6, 0.6, 0.6);

	//handle all texture mapping for mercury
	GLUquadricObj* mercury = gluNewQuadric();

	gluQuadricOrientation(mercury, GLU_OUTSIDE);
	HandleDrawStyle(mercury, PlanetTexture::Mercury, style);

	GLUquadricObj* quadratic;
	quadratic = gluNewQuadric();
	gluQuadricNormals(quadratic, GLU_SMOOTH);
	glPushMatrix();
	glTranslatef(0,0.0,-8.0);
	glRotatef( -75.0, 1.0, 0.0, 0.0 );

	gluDisk(quadratic, 1.99, 2.01, 50, 5);
	glPopMatrix(); 


	// Back off eight units to be able to view from the origin.
	glTranslatef ( 0.0, 0.0, -8.0 );

	// Rotate the plane of the elliptic
	// (rotate the model's plane about the x axis by fifteen degrees)
	glRotatef( 15.0, 1.0, 0.0, 0.0 );

	// First position it around the sun. Use DayOfYear to determine its position.
	glRotatef( 360.0 * DayOfYear / 88.0, 0.0, 1.0, 0.0 );
	glTranslatef( 2.0, 0.0, 0.0 );

	glPushMatrix();						// Save matrix state

	// Second, rotate mercury on its axis. Use HourOfDay to determine its rotation.
	glRotatef( 360.0 * HourOfDay / 1416.0, 0.0, 1.0, 0.0 );

	glRotatef(90, 1, 0, 0);
	
	//draw mercury
	gluSphere(mercury, .15, 10, 10);
	gluDeleteQuadric(mercury);
	glPopMatrix();	
	glRasterPos2f(0, -.75);
	EmissiveLabel("Mercury");

	glPopMatrix();

}

void venus(float HourOfDay, float DayOfYear, DrawStyle style)
{
	glLoadIdentity();
	glColor3f(1, .5, 0);

	//handle all texture mapping for vebus
	GLUquadricObj* venus = gluNewQuadric();
	HandleDrawStyle(venus, PlanetTexture::Venus, style);
	GLUquadricObj* quadratic;
	quadratic = gluNewQuadric();
	gluQuadricNormals(quadratic, GLU_SMOOTH);
	glPushMatrix();
	glTranslatef(0,0.0,-8.0);
	glRotatef( -75.0, 1.0, 0.0, 0.0 );

	gluDisk(quadratic, 3.71, 3.73, 50, 5);
	gluDeleteQuadric(quadratic);
	glPopMatrix(); 

	// Back off eight units to be able to view from the origin.
	glTranslatef ( 0.0, 0.0, -8.0 );

	// Rotate the plane of the elliptic
	// (rotate the model's plane about the x axis by fifteen degrees)
	glRotatef( 15.0, 1.0, 0.0, 0.0 );


	// First position it around the sun. Use DayOfYear to determine its position.
	glRotatef( 360.0 * DayOfYear / 225.0, 0.0, 1.0, 0.0 );
	glTranslatef( 3.72, 0.0, 0.0 );
	glPushMatrix();						// Save matrix state
	// Second, rotate venus on its axis. Use HourOfDay to determine its rotation.
	glRotatef( 360.0 * HourOfDay / 5832.0, 0.0, 1.0, 0.0 );

	//draw Venus
	glRotatef(90, 1, 0, 0);
	gluSphere(venus, .38, 10, 10);
	gluDeleteQuadric(venus);
	glPopMatrix();	
	glRasterPos2f(0, -.75);
	EmissiveLabel("Venus");
}

void earth(float HourOfDay, float DayOfYear, DrawStyle style)
{
	glLoadIdentity();
	glColor3f(0, 0, 1);

	//handle the texture mapping
	GLUquadricObj* earth = gluNewQuadric();
	HandleDrawStyle(earth, PlanetTexture::Earth, style);

	GLUquadricObj* quadratic;
	quadratic = gluNewQuadric();
	gluQuadricNormals(quadratic, GLU_SMOOTH);
	glPushMatrix();
	glTranslatef(0,0.0,-8.0);
	glRotatef( -75.0, 1.0, 0.0, 0.0 );

	gluDisk(quadratic, 5.16, 5.18, 100, 5);
	glPopMatrix(); 


	// Back off eight units to be able to view from the origin.
	glTranslatef ( 0.0, 0.0, -8.0 );

	// Rotate the plane of the elliptic
	// (rotate the model's plane about the x axis by fifteen degrees)
	glRotatef( 15.0, 1.0, 0.0, 0.0 );

	// Draw the Earth
	// First position it around the sun. Use DayOfYear to determine its position.
	glRotatef( 360.0 * DayOfYear / 365.0, 0.0, 1.0, 0.0 );
	glTranslatef( 5.17, 0.0, 0.0 );
	glPushMatrix();						// Save matrix state
	// Second, rotate the earth on its axis. Use HourOfDay to determine its rotation.
	glRotatef( 360.0 * HourOfDay / 24.0, 0.0, 1.0, 0.0 );

	//Turn the planet right side up.
	glRotatef(-100, 1.0, 0.0, .5);

	gluSphere(earth, .4, 10, 10);
	gluDeleteQuadric(earth);
	glPopMatrix();						// Restore matrix state
	glRasterPos2f(0, -1);
	EmissiveLabel("Earth");

	// Draw the moon. Use DayOfYear to control its rotation around the earth
	glColor3f(.8, .8, .8);
	glRotatef( 360.0 * 12.0 * DayOfYear / 365.0, 0.0, 1.0, 0.0 );
	glTranslatef( 0.7, 0.0, 0.0 );
	GLUquadricObj* moon = gluNewQuadric();
	HandleDrawStyle(moon, PlanetTexture::Moon, style);
	gluSphere(moon, .1, 5, 5);
	gluDeleteQuadric(moon);

}

void mars(float HourOfDay, float DayOfYear, DrawStyle style)
{
	glLoadIdentity();
	glColor3f(1.0, 0, 0);

	//handle the texture mapping
	GLUquadricObj* mars = gluNewQuadric();
	HandleDrawStyle(mars, PlanetTexture::Mars, style);

	GLUquadricObj* quadratic;
	quadratic = gluNewQuadric();
	gluQuadricNormals(quadratic, GLU_SMOOTH);
	glPushMatrix();
	glTranslatef(0,0.0,-8.0);
	glRotatef( -75.0, 1.0, 0.0, 0.0 );

	gluDisk(quadratic, 7.85, 7.87, 100, 5);
	glPopMatrix(); 


	// Back off eight units to be able to view from the origin.
	glTranslatef ( 0.0, 0.0, -8.0 );

	// Rotate the plane of the elliptic
	// (rotate the model's plane about the x axis by fifteen degrees)
	glRotatef( 15.0, 1.0, 0.0, 0.0 );

	
	// First position it around the sun. Use DayOfYear to determine its position.
	glRotatef( 360.0 * DayOfYear / 687.0, 0.0, 1.0, 0.0 );
	glTranslatef( 7.86, 0.0, 0.0 );
	glPushMatrix();						// Save matrix state
	// Second, rotate the earth on its axis. Use HourOfDay to determine its rotation.
	glRotatef( 360.0 * HourOfDay / 24.6, 0.0, 1.0, 0.0 );
	// Third, draw the earth as a wireframe sphere.

	//draw Mars
	//Turn the planet right side up.
	glRotatef(-100, 1.0, 0.0, .5);
	gluSphere(mars, .21, 10, 10);
	gluDeleteQuadric(mars);
	glPopMatrix();	
	glRasterPos2f(0, -1);
	EmissiveLabel("Mars");
}

void jupiter(float HourOfDay, float DayOfYear, DrawStyle style)
{
	glLoadIdentity();
	glColor3f(.627, .392, .325);

	//handle texture mapping
	GLUquadricObj* jupiter = gluNewQuadric();
	HandleDrawStyle(jupiter, PlanetTexture::Jupiter, style);

	GLUquadricObj* quadratic;
	quadratic = gluNewQuadric();
	gluQuadricNormals(quadratic, GLU_SMOOTH);
	glPushMatrix();
	glTranslatef(0,0.0,-8.0);
	glRotatef( -75.0, 1.0, 0.0, 0.0 );

	gluDisk(quadratic, 26.85, 26.87, 100000, 5);
	glPopMatrix(); 

	// Back off eight units to be able to view from the origin.
	glTranslatef ( 0.0, 0.0, -8.0 );

	// Rotate the plane of the elliptic
	// (rotate the model's plane about the x axis by fifteen degrees)
	glRotatef( 15.0, 1.0, 0.0, 0.0 );

	// Draw the Jupiter
	// First position it around the sun. Use DayOfYear to determine its position.
	glRotatef( 360.0 * DayOfYear / 4332.0, 0.0, 1.0, 0.0 );
	glTranslatef( 26.86, 0.0, 0.0 );
	glPushMatrix();						// Save matrix state
	// Second, rotate the earth on its axis. Use HourOfDay to determine its rotation.
	glRotatef( 360.0 * HourOfDay / 9.8, 0.0, 1.0, 0.0 );
	// Third, draw the earth as a wireframe sphere.

	//Turn the planet right side up.
	glRotatef(90, 1.0, 0.0, 0.0);
	gluSphere(jupiter, 4.48, 10, 10);
	gluDeleteQuadric(jupiter);
	glPopMatrix();
	glRasterPos2f(-1, -6);
	EmissiveLabel("Jupiter");
}

void saturn(float HourOfDay, float DayOfYear, DrawStyle style)
{
	glLoadIdentity();
	glColor3f(.8, .6, .5);
	
	//handle texture mapping
	GLUquadricObj* quadratic;
	quadratic = gluNewQuadric();
	gluQuadricNormals(quadratic, GLU_SMOOTH);
	glPushMatrix();
	glTranslatef(0,0.0,-8.0);
	glRotatef( -75.0, 1.0, 0.0, 0.0 );

	gluDisk(quadratic, 49.09, 49.11, 100000, 5);
	glPopMatrix();

	// Back off eight units to be able to view from the origin.
	glTranslatef ( 0.0, 0.0, -8.0 );

	// Rotate the plane of the elliptic
	// (rotate the model's plane about the x axis by fifteen degrees)
	glRotatef( 15.0, 1.0, 0.0, 0.0 );

	// First position it around the sun. Use DayOfYear to determine its position.
	glRotatef( 360.0 * DayOfYear / 10761.0, 0.0, 1.0, 0.0 );
	glTranslatef( 49.10, 0.0, 0.0 );

	//Draw Saturn's rings
	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	GLUquadricObj* rings = gluNewQuadric();
	HandleDrawStyle(rings, PlanetTexture::SaturnRings, style);
	gluQuadricOrientation(rings, GLU_OUTSIDE);
	gluCylinder(rings, 7.56, 4.73, .38, 20, 20);		
	gluDeleteQuadric(rings);
	glPopMatrix();
	glPushMatrix();						// Save matrix state
		
	//Draw Saturn
	// Second, rotate Saturn on its axis. Use HourOfDay to determine its rotation.
	glRotatef( 360.0 * HourOfDay / 10.2, 0.0, 1.0, 0.0 );

	//Turn the planet right side up.
	glRotatef(90, 1.0, 0.0, 0.0);
    GLUquadricObj* saturn = gluNewQuadric();
	HandleDrawStyle(saturn, PlanetTexture::Saturn, style);
	gluSphere(saturn, 3.78, 10, 10);
	gluDeleteQuadric(saturn);
	glPopMatrix();
	glRasterPos2f(-2, -5);
	EmissiveLabel("Saturn");

}

void uranus(float HourOfDay, float DayOfYear, DrawStyle style)
{
	glLoadIdentity();

	glColor3f(0, 0, .5);

	//texture mapping
	GLUquadricObj* uranus = gluNewQuadric();
	HandleDrawStyle(uranus, PlanetTexture::Uranus, style);

	GLUquadricObj* quadratic;
	quadratic = gluNewQuadric();
	gluQuadricNormals(quadratic, GLU_SMOOTH);
	glPushMatrix();
	glTranslatef(0,0.0,-8.0);
	glRotatef( -75.0, 1.0, 0.0, 0.0 );

	gluDisk(quadratic, 98.85, 98.87, 100000, 5);
	glPopMatrix();


	// Back off eight units to be able to view from the origin.
	glTranslatef ( 0.0, 0.0, -8.0 );

	// Rotate the plane of the elliptic
	// (rotate the model's plane about the x axis by fifteen degrees)
	glRotatef( 15.0, 1.0, 0.0, 0.0 );


	// First position it around the sun. Use DayOfYear to determine its position.
	glRotatef( 360.0 * DayOfYear / 30682.0, 0.0, 1.0, 0.0 );
	glTranslatef( 98.86, 0.0, 0.0 );
	glPushMatrix();						// Save matrix state
	// Second, rotate the Uranus on its axis. Use HourOfDay to determine its rotation.
	glRotatef( 360.0 * HourOfDay / 15.5, 0.0, 1.0, 0.0 );
	// Third, draw the earth as a wireframe sphere.

	//Turn the planet right side up.
	glRotatef(-100, 1.0, 0.0, .5);
	gluSphere(uranus, 1.60, 10, 10);
	gluDeleteQuadric(uranus);
	glPopMatrix();

	glRasterPos2f(-1, -3);
	EmissiveLabel("Uranus");
}

void neptune(float HourOfDay, float DayOfYear, DrawStyle style)
{
	glLoadIdentity();

	glColor3f(0, 0, .4);

	//texture mapping
	GLUquadricObj* neptune = gluNewQuadric();
	HandleDrawStyle(neptune, PlanetTexture::Neptune, style);

	GLUquadricObj* quadratic;
	quadratic = gluNewQuadric();
	gluQuadricNormals(quadratic, GLU_SMOOTH);
	glPushMatrix();
	glTranslatef(0,0.0,-8.0);
	glRotatef( -75.0, 1.0, 0.0, 0.0 );
	gluDisk(quadratic, 154.89, 154.91, 100000, 5);
	glPopMatrix();


	// Back off eight units to be able to view from the origin.
	glTranslatef ( 0.0, 0.0, -8.0 );

	// Rotate the plane of the elliptic
	// (rotate the model's plane about the x axis by fifteen degrees)
	glRotatef( 15.0, 1.0, 0.0, 0.0 );

	// Draw the Earth
	// First position it around the sun. Use DayOfYear to determine its position.
	glRotatef( 360.0 * DayOfYear / 60195.0, 0.0, 1.0, 0.0 );
	glTranslatef( 154.90, 0.0, 0.0 );
	glPushMatrix();						// Save matrix state
	// Second, rotate Nekptune on its axis. Use HourOfDay to determine its rotation.
	glRotatef( 360.0 * HourOfDay / 15.8, 0.0, 1.0, 0.0 );
	// Third, draw the earth as a wireframe sphere.

	//Turn the planet right side up.
	glRotatef(-100, 1.0, 0.0, .5);
	gluSphere(neptune, .4, 10, 10);
	gluDeleteQuadric(neptune);
	glPopMatrix();

	glRasterPos2f(-1, -1);
	EmissiveLabel("Neptune");
}


