//solar_system.h
//Header file for solar_system.cpp
//Defines enums for draw style and prototypes for planets.
#ifndef SOLAR_SYSTEM
#define SOLAR_SYSTEM

//The four different ways to draw something.
//Wireframe: Just lines- a colored wirefram of the object.
//Flat: Solid objects with non-interpolated sides.
//Smooth: Like flat, but the surface normals are interpolated
//to make the lighting look "smoother".
//TextureMapped: Wrap textures around the planets.
enum DrawStyle {Wireframe, Flat, Smooth, TextureMapped};

//All these do the same thing, more or less. Draw the named planet
//at the given rotation and position around the sun with the specified style.
void sun(float HourOfDay, float DayOfYear, DrawStyle style);
void mercury(float HourOfDay, float DayOfYear, DrawStyle style);
void venus(float HourOfDay, float DayOfYear, DrawStyle style);
void earth(float HourOfDay, float DayOfYear, DrawStyle style);
void mars(float HourOfDay, float DayOfYear, DrawStyle style);
void jupiter(float HourOfDay, float DayOfYear, DrawStyle style);
void saturn(float HourOfDay, float DayOfYear, DrawStyle style);
void uranus(float HourOfDay, float DayOfYear, DrawStyle style);
void neptune(float HourOfDay, float DayOfYear, DrawStyle style);

#endif
