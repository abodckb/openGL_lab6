#pragma once
#include <windows.h>	
// ������������ ���� ��� Windows
#include <gl\gl.h>		
#include <gl\glut.h>
	// ������������ ���� ��� ���������� OpenGL32 
#include <gl\glu.h>		
	// ������������ ���� ��� ���������� GLu32 
#include <gl\glaux.h>		
	// ������������ ���� ��� ���������� GLaux 
#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <fstream>

extern  GLuint TextNames[100];
extern  AUX_RGBImageRec* TextureMass[100];
extern AUX_RGBImageRec* ImRect1;


#define BRIKS 0x00
#define SPACE 0x01
#define CARBOTTON 0x02
#define PROTECTOR 0x03
#define HEADLIGHT 0x04
#define ROOF 0x05
#define FACE 0x06
#define STATUE 0x07
#define WALLPAINT 0x08