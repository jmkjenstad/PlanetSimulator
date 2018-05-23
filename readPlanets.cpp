//*******************************
//readPlanets.cpp
//Code by Grant Hill
//Responsible for reading in .bmp textures from the files listed in
//planetFiles[], then providing those textures to OpenGL and the program.
//
//readPlanets() should be called at the start of the program, before
//getPlanetTexture(). getPlanetTexture should be called in place of
//glBindTexture or any other way to get the planet textures from OpenGL.
//That is, it sets the specified texture globally until another one is
//called for. Note the use of constants and enums defined in readPlanets.h.


#include "bmpRead.h"
#include "readPlanets.h"
#include <GL/freeglut.h>

const int numFiles = 11;
const char* planetFiles[] =
{
	"textures/earth.bmp",
	"textures/jupiter.bmp",
	"textures/mars.bmp",
	"textures/mercury.bmp",
	"textures/moon.bmp",
	"textures/neptune.bmp",
	"textures/saturn.bmp",
	"textures/saturnrings.bmp",
	"textures/sun.bmp",
	"textures/uranus.bmp",
	"textures/venus.bmp"
};


typedef unsigned char* imagePtr;

//This array maps enum values (from PlanetTexture) to openGL texture IDs (from glGenTextures). That is, textureIds[PlanetTexture::anything] returns a value that you should give to glBindTexture.
GLuint textureIds[numFiles];

//Reads planet textures from the files listed in planetFiles. Call this before calling getPlanetTexture.
void readPlanets()
{
	GLuint nextTexture;
	imagePtr thisImage;
	for (int i = 0; i < numFiles; i++)
	{
		int numRows, numCols;
		glGenTextures(1, &nextTexture);
		LoadBmpFile(planetFiles[i], numRows, numCols, thisImage);
		glBindTexture(GL_TEXTURE_2D, nextTexture);
		gluBuild2DMipmaps( GL_TEXTURE_2D, GL_RGB, numCols, numRows, GL_RGB, GL_UNSIGNED_BYTE, thisImage);
		textureIds[i] = nextTexture;
		delete [] thisImage;
	}
}

//Sets the planet texture for OpenGL.
void getPlanetTexture(PlanetTexture tex)
{
	glBindTexture(GL_TEXTURE_2D, textureIds[tex]);
}
