//readPlanets.h
//Header file for readPlanets.cpp
//File by Grant Hill

#ifndef READ_PLANETS
#define READ_PLANETS

//I know, "planet" isn't exactly right. Enumerated values for each drawable celestial body. These are used to look up which texture we want for texture mapping.
enum PlanetTexture
{
	Earth, Jupiter, Mars, Mercury, Moon, Neptune, Saturn, SaturnRings, Sun, Uranus, Venus
};

//This guy reads all the planet textures in from the textures folder. Call him early on, before you call getPlanetTexture.
void readPlanets();

//Map the current planet texture. 
void getPlanetTexture(PlanetTexture tex);

#endif
