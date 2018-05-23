//bmpRead.h
//Code for reading .BMP files into memory. 
//Header file by Grant Hill. bmpRead code provided by John Weiss.
#ifndef BMP_READ
#define BMP_READ
bool LoadBmpFile( const char* filename, int &NumRows, int &NumCols, unsigned char* &ImagePtr );
#endif
