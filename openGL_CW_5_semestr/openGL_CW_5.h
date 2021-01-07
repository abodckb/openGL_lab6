#pragma once
#include <windows.h>	
// Заголовочный файл для Windows
#include <gl\gl.h>		
#include <gl\glut.h>
	// Заголовочный файл для библиотеки OpenGL32 
#include <gl\glu.h>		
	// Заголовочный файл для библиотеки GLu32 
#include <gl\glaux.h>		
	// Заголовочный файл для библиотеки GLaux 
#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <fstream>

extern  GLuint TextNames[100];
extern  AUX_RGBImageRec* TextureMass[100];
extern AUX_RGBImageRec* ImRect1;

#define PI 3.14159265

//#define BRIKS 0x00
//#define SPACE 0x01
//#define CARBOTTON 0x02
//#define PROTECTOR 0x03
//#define HEADLIGHT 0x04
//#define ROOF 0x05
//#define SKY 0x06
//#define SAND 0x07
//#define BRIKS1 0x08
//#define WOOD 0x09
//#define ROAD 0x0A
//#define RAIN 0x0B
//#define RAIN1 0x0C
#define BRIKS 0
#define SPACE 1
#define CARBOTTON 2
#define PROTECTOR 3
#define HEADLIGHT 4
#define ROOF 5
#define SKY 6
#define SAND 7
#define BRIKS1 8
#define WOOD 9
#define ROAD 10
#define RAIN 11
#define RAIN1 12
#define WINDOW1 13
