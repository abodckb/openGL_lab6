
//#include <windows.h>	
//// Заголовочный файл для Windows
//#include <gl\gl.h>		
//#include <gl\glut.h>
//	// Заголовочный файл для библиотеки OpenGL32 
//#include <gl\glu.h>		
//	// Заголовочный файл для библиотеки GLu32 
////#include <gl\glaux.h>		
//	// Заголовочный файл для библиотеки GLaux 
//#define _USE_MATH_DEFINES
//#include <cmath>
//#include <iostream>
//#include <fstream>

#include "openGL_CW_5.h"

static HGLRC hRC;
// Постоянный контекст рендеринга
static HDC hDC;
// Приватный контекст устройства GDI

BOOL	keys[256];
// Массив для процедуры обработки клавиатуры
float h_angle = 0.0;
float v_angle = 0.0;
float h_cam = 0.0;
float v_cam = 0.0;
float r_object = 0.0; //rotate left
float r_right = 0.0;//rotate right
float _zoom = 30.0;
float stepman = 0.0;

GLuint TextNames[100];
AUX_RGBImageRec* TextureMass[100];
AUX_RGBImageRec* ImRect1;
//char* TextureFiles[] = {"Bricks.bmp"};
const char* TextureFiles[] = { "Bricks.bmp","space.bmp","CarBotton.bmp","protectorbump_010.bmp","headlights_001.bmp","metals_004.bmp","Statue.bmp","WallPaint.bmp" };

GLvoid InitGL(GLsizei Width, GLsizei Height)	//Вызвать после создания окна GL
{
	glClearColor(.0f, .0f, .0f, 1.0f);
	//glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	// Очистка экрана в черный цвет
}

GLvoid ReSizeGLScene(GLsizei Width, GLsizei Height)
{
	if (Height == 0)
		// Предотвращение деления на ноль, 
		//если окно слишком мало
		Height = 1;
	glViewport(0, 0, Width, Height);
	// Сброс текущей области вывода и
	//перспективных преобразований
}


void DrawWheels()
{
	GLUquadricObj* quadricObj = gluNewQuadric();
	//GLfloat no_mat_specular[] = { 0.0,0.0,0.0,1.0 };
	//glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat_specular);
	//glClear(GL_COLOR_BUFFER_BIT);

	glPushMatrix(); //малый цилиндр (внутренний)
	//glRotatef(30, 0, 1, 0);
	//glTranslatef(0, -0.1, -0.2);
	//glColor3f(1, 0, 0);
	GLfloat color_mat1[] = { 1.0,0.0,0.0,1.0 };
	//glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color_mat1);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color_mat1);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, color_mat1);
	//gluQuadricDrawStyle(quadricObj, GLU_LINE);
	gluQuadricDrawStyle(quadricObj, GLU_FILL);
	gluCylinder(quadricObj, 0.1, 0.1, 0.1, 30, 3);
	glPopMatrix();




	glPushMatrix(); //большой цилиндр (внешний)

		gluQuadricTexture(quadricObj, GL_TRUE);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, TextNames[PROTECTOR]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_LINEAR_MIPMAP_LINEAR);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		glColor3f(0, 0, 0);

		//glRotatef(90, 1, 0, 0);
		//glTranslatef(0.0, 0.0, -0.2);
		//glColor3f(1, 0, 1);
		GLfloat color_mat2[] = { 1.0,0.0,1.0,1.0 };
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color_mat2);
		//glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color_mat2);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, color_mat2);
		//gluQuadricDrawStyle(quadricObj, GLU_LINE);
		gluQuadricDrawStyle(quadricObj, GLU_FILL);
		gluCylinder(quadricObj, 0.3, 0.3, 0.1, 30, 3);

		glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	GLUquadricObj* quadricObjDisk = gluNewQuadric();
	glPushMatrix();//диск колеса (внутренний)
		//glRotatef(60, 0, 1, 0);
		//glTranslatef(0.0, 0.0, 0.0);
		//glColor3f(0, 0, 1);
		GLfloat color_mat3[] = { 0.0,0.0,1.0,1.0 };
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color_mat3);
		//glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color_mat3);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, color_mat3);
		//gluQuadricDrawStyle(quadricObjDisk, GLU_LINE);
		gluQuadricDrawStyle(quadricObjDisk, GLU_FILL);
		gluDisk(quadricObjDisk, 0.1, 0.3, 10, 3);
	glPopMatrix();

	//GLUquadricObj* quadricObjDisk = gluNewQuadric();
	glPushMatrix();
		//glRotatef(60, 0, 1, 0);
		glTranslatef(0.0, 0.0, 0.1);
		glColor3f(0, 0, 0);
		//GLfloat color_mat4[] = { 0.0,0.0,0.0,1.0 };
		//glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color_mat4);
		//glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, color_mat4);
		//gluQuadricDrawStyle(quadricObjDisk, GLU_LINE);
		gluQuadricDrawStyle(quadricObjDisk, GLU_FILL);
		gluDisk(quadricObjDisk, 0.1, 0.3, 10, 3);
	glPopMatrix();

	gluDeleteQuadric(quadricObj);
	gluDeleteQuadric(quadricObjDisk);
}


void drawQube()
{
	float size = 1.f;

	//texture material modifications
	GLfloat glTexAmbientFlore[] = { 0,0,0,1 };
	GLfloat glTexDiffuseFlore[] = { 1.0,1,1.0,1 };
	GLfloat glTexShineFlore[] = { 1.0,1.0,1.0,1 };
	//GLfloat glTexDiffuseFlore[] = { 0.3,0,0.8,1 };
	//GLfloat glTexShineFlore[] = { 0.2,0.2,0.2,1 };

	glBindTexture(GL_TEXTURE_2D, TextNames[BRIKS]);
	glMaterialfv(GL_FRONT, GL_AMBIENT, glTexAmbientFlore);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, glTexDiffuseFlore);
	glMaterialfv(GL_FRONT, GL_SPECULAR, glTexShineFlore);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_LINEAR_MIPMAP_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glColor3f(0, 0, 0);

	glBegin(GL_QUADS);
		//glColor3f(0.652, 0.566, 0.727);
		//front
		glTexCoord2f(0, 0);
		glVertex3f(-size, -size, size);
		glTexCoord2f(1, 0);
		glVertex3f(size, -size, size);
		glTexCoord2f(1, 1);
		glVertex3f(size, 0.*size, size);
		glTexCoord2f(0, 1);
		glVertex3f(-size, 0. *size, size);
	glEnd();

	glBegin(GL_QUADS);
		//glColor3f(randomFlt(), randomFlt(), randomFlt());
		//glColor3f(0.699, 0.699, 0.762);
		glColor3f(0.652, 0.566, 0.727);
		//back
		glVertex3f(-size, -size, -size);
		glVertex3f(-size, 0*size, -size);
		glVertex3f(size, 0* size, -size);
		glVertex3f(size, -size, -size);
	glEnd();


	glBegin(GL_QUADS);
		//glColor3f(randomFlt(), randomFlt(), randomFlt());
		//glColor3f(0.773, 0.648, 0.715);
		glColor3f(0.652, 0.566, 0.727);
		//left
		glVertex3f(-size, -size, size);
		glVertex3f(-size, -size, -size);
		glVertex3f(-size, 0.0 * size, -size);
		glVertex3f(-size, 0.0 * size, size);
	glEnd();


	glBegin(GL_QUADS);
		//glColor3f(randomFlt(), randomFlt(), randomFlt());
		//glColor3f(0.746, 0.832, 0.797);
		glColor3f(0.652, 0.566, 0.727);
		//right
		glVertex3f(size, -size, -size);
		glVertex3f(size, -size, size);
		glVertex3f(size, 0.0 * size, size);
		glVertex3f(size, 0.0 * size, -size);
	glEnd();


	glBindTexture(GL_TEXTURE_2D, TextNames[CARBOTTON]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_LINEAR_MIPMAP_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glColor3f(0, 0, 0);

	glBegin(GL_QUADS);
		//glColor3f(randomFlt(), randomFlt(), randomFlt());
		//glColor3f(0.891, 0.726, 0.703);
		//glColor3f(0.652, 0.566, 0.727);
		//bottom
		glTexCoord2f(0, 0);
		glVertex3f(-size, -size, size);
		glTexCoord2f(1, 0);
		glVertex3f(size, -size, size);
		glTexCoord2f(1, 1);
		glVertex3f(size, -size, -size);
		glTexCoord2f(0, 1);
		glVertex3f(-size, -size, -size);
	glEnd();


	glBegin(GL_QUADS);
		//glColor3f(randomFlt(), randomFlt(), randomFlt());
		//glColor3f(0.855, 0.914, 0.859);
		glColor3f(0.652, 0.566, 0.727);
		//top  		
		glVertex3f(-size, 0.*size, -size);
		glVertex3f(size, 0. * size, -size);
		glVertex3f(size, 0. * size, size);
		glVertex3f(-size, 0. * size, size);
	glEnd();

	//-------------------------------------------------------------kabine
	glBegin(GL_QUADS);
		glColor3f(0.652, 0.566, 0.727);
		//front
		glVertex3f(-size, 0.*size, size);
		glVertex3f(0.2 * size, 0.* size, size);
		glVertex3f(0.2*size, 0.7*size, size);
		glVertex3f(-size, 0.7 * size, size);
	glEnd();

	glBegin(GL_QUADS);
		//glColor3f(randomFlt(), randomFlt(), randomFlt());
		//glColor3f(0.699, 0.699, 0.762);
		glColor3f(0.652, 0.566, 0.727);
		//back
		glVertex3f(-size, -0. * size, -size);
		glVertex3f(-size, 0.7 * size, -size);
		glVertex3f(0.2 * size, 0.7 * size, -size);
		glVertex3f(0.2 * size, -0. * size, -size);
	glEnd();


	glBegin(GL_QUADS);
		//glColor3f(randomFlt(), randomFlt(), randomFlt());
		//glColor3f(0.773, 0.648, 0.715);
		glColor3f(0.652, 0.566, 0.727);
		//left
		glVertex3f(-size, -0*size, size);
		glVertex3f(-size, -0*size, -size);
		glVertex3f(-size, 0.7 * size, -size);
		glVertex3f(-size, 0.7 * size, size);
	glEnd();


	glBegin(GL_QUADS);
		//glColor3f(randomFlt(), randomFlt(), randomFlt());
		glColor3f(0.5, 0.5, 0.5);
		//right
		glVertex3f(0.2*size, -0*size, -size);
		glVertex3f(0.2 * size, -0*size, size);
		glVertex3f(0.2 * size, 0.7 * size, size);
		glVertex3f(0.2 * size, 0.7 * size, -size);
	glEnd();


	glBegin(GL_QUADS);
		//glColor3f(randomFlt(), randomFlt(), randomFlt());
		//glColor3f(0.891, 0.726, 0.703);
		glColor3f(0.652, 0.566, 0.727);
		//bottom
		glVertex3f(-size, -0*size, size);
		glVertex3f(0.2 * size, -0*size, size);
		glVertex3f(0.2 * size, -0*size, -size);
		glVertex3f(-size, -0*size, -size);
	glEnd();


	glBegin(GL_QUADS);
		//glColor3f(randomFlt(), randomFlt(), randomFlt());
		//glColor3f(0.855, 0.914, 0.859);
		glColor3f(0.652, 0.566, 0.727);
		//top  		
		glVertex3f(-size, 0.7 * size, -size);
		glVertex3f(0.2 * size, 0.7 * size, -size);
		glVertex3f(0.2 * size, 0.7 * size, size);
		glVertex3f(-size, 0.7 * size, size);
	glEnd();
}

void drawHome()
{
	float size = 1.f;
	glBegin(GL_QUADS);

	//glColor3f(randomFlt(), randomFlt(), randomFlt());
	//float _cred = randomFlt();
	//float _cgreen = randomFlt();
	//float _cblue = randomFlt();
	//glColor3f(_cred, _cgreen, _cblue);
	glColor3f(0.652, 0.566, 0.727);


	//front
	glVertex3f(-size, -size, size);
	glVertex3f(size, -size, size);
	glVertex3f(size, size, size);
	glVertex3f(-size, size, size);
	glEnd();

	glBegin(GL_QUADS);
	//glColor3f(randomFlt(), randomFlt(), randomFlt());
	glColor3f(0.699, 0.699, 0.762);
	//back
	glVertex3f(-size, -size, -size);
	glVertex3f(-size, size, -size);
	glVertex3f(size, size, -size);
	glVertex3f(size, -size, -size);
	glEnd();


	glBegin(GL_QUADS);
	//glColor3f(randomFlt(), randomFlt(), randomFlt());
	glColor3f(0.773, 0.648, 0.715);
	//left
	glVertex3f(-size, -size, size);
	glVertex3f(-size, -size, -size);
	glVertex3f(-size, size, -size);
	glVertex3f(-size, size, size);
	glEnd();


	glBegin(GL_QUADS);
	//glColor3f(randomFlt(), randomFlt(), randomFlt());
	glColor3f(0.746, 0.832, 0.797);
	//right
	glVertex3f(size, -size, -size);
	glVertex3f(size, -size, size);
	glVertex3f(size, size, size);
	glVertex3f(size, size, -size);
	glEnd();


	glBegin(GL_QUADS);
	//glColor3f(randomFlt(), randomFlt(), randomFlt());
	glColor3f(0.891, 0.726, 0.703);
	//bottom
	glVertex3f(-size, -size, size);
	glVertex3f(size, -size, size);
	glVertex3f(size, -size, -size);
	glVertex3f(-size, -size, -size);
	glEnd();


	glBegin(GL_QUADS);
	//glColor3f(randomFlt(), randomFlt(), randomFlt());
	glColor3f(0.855, 0.914, 0.859);
	//top  		
	glVertex3f(-size, size, -size);
	glVertex3f(size, size, -size);
	glVertex3f(size, size, size);
	glVertex3f(-size, size, size);
	glEnd();

	glBegin(GL_TRIANGLES);
	//glColor3f(randomFlt(), randomFlt(), randomFlt());
	glColor3f(1, 1, 0.);
	//top  		
	glVertex3f(-size, size, size);
	glVertex3f(size, size, size);
	glVertex3f(0*size, 1.8*size, size);
	glEnd();

	glBegin(GL_TRIANGLES);
	//glColor3f(randomFlt(), randomFlt(), randomFlt());
	glColor3f(1, 0, 0.);
	//top  		
	glVertex3f(-size, size, -size);
	glVertex3f(size, size, -size);
	glVertex3f(0 * size, 1.8 * size, -size);
	glEnd();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, TextNames[ROOF]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_LINEAR_MIPMAP_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glColor3f(0, 0, 0);

	glBegin(GL_QUADS);
	//glColor3f(randomFlt(), randomFlt(), randomFlt());
	glColor3f(0, 1, 1);
	//top  
	glTexCoord2f(0, 0);
	glVertex3f(size+0.375, size-0.3, size);
	glTexCoord2f(0, 1);
	glVertex3f(0 * size, 1.8 * size, size);
	glTexCoord2f(1, 1);
	glVertex3f(0 *size, 1.8 * size, -size);
	glTexCoord2f(1, 0);
	glVertex3f(size + 0.375, size - 0.3, -size);
	glEnd();

	glBegin(GL_QUADS);
	//glColor3f(randomFlt(), randomFlt(), randomFlt());
	glColor3f(0, 1, 1);
	//top 
	glTexCoord2f(0, 0);
	glVertex3f(-size - 0.375, size - 0.3, size);
	glTexCoord2f(0, 1);
	glVertex3f(0 * size, 1.8 * size, size);
	glTexCoord2f(1, 1);
	glVertex3f(0 * size, 1.8 * size, -size);
	glTexCoord2f(1, 0);
	glVertex3f(-size - 0.375, size - 0.3, -size);
	glEnd();

	glDisable(GL_TEXTURE_2D);

}

GLvoid DrawGLScene(float h_angle, float v_angle, float h_cam, float v_cam, float stepman)
{
	GLUquadricObj* quadricObj = gluNewQuadric();

	GLfloat no_mat[] = { 0.0,0.0,0.0,1.0 };
	GLfloat mat_ambient_def[] = { 0.2, 0.2, 0.2, 1.0 };
	GLfloat mat_ambient[] = { 0.8,0.8,0.2,1.0 };

	GLfloat mat_diffuse_def[] = { 0.8, 0.8, 0.8, 1.0 };
	GLfloat mat_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_diffuse_white[] = { 1.0,1.0,1.0,1.0 };
	GLfloat mat_diffuse_red[] = { 1.0,0.0,0.0,1.0 };
	GLfloat mat_diffuse_black[] = { 0.0,0.0,0.0,1.0 };
	
	GLfloat no_shininess[] = { 0.0 };
	GLfloat low_shininess[] = { 5.0 };
	GLfloat high_shininess[] = { 100.0 };

	GLfloat mat_emission[] = { 0.3,0.2,0.2,0.0 };

	GLfloat no_mat_specular[] = { 0.0,0.0,0.0,1.0 };
	GLfloat mat_specular_def[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat mat_specular_white[] = { 1.0,1.0,1.0,1.0 };
	GLfloat mat_specular_red[] = { 1.0,0.0,0.0,1.0 };
	GLfloat mat_specular_black[] = { 0.0,0.0,0.0,1.0 };

	GLfloat color_white[] = { 1.0,1.0,1.0,1.0 };
	GLfloat color_red[] = { 1.0,0.0,0.0,1.0 };
	GLfloat color_black[] = { 0.0,0.0,0.0,1.0 };

	glClearColor(0.0, 0.0, 0.0, 0.0);

	//glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_def);
	//glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse_def);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse_white);
	//glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular_def);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular_white);



	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);


	//Light0 modes
	GLfloat glLight0_ambient[] = { 0.0,0.0,0.0,1.0 };
	GLfloat glLight0_diffuse[] = { 1,1,1,1 };
	GLfloat glLight0_specular[] = { 1,1,1,1 };
	GLfloat glLight0_position[] = { 0,0,1,0 };
	//GLfloat glLight0_position[] = { 0,2,1,1 };
	//set light0------------------------------
	glEnable(GL_LIGHT0);
	//glLightfv(GL_LIGHT0, GL_AMBIENT, glLight0_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, glLight0_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, glLight0_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, glLight0_position);

	//set light2
	GLfloat glLight2_ambient[] = { 0.2,0.2,0.2,1.0 };
	GLfloat glLight2_diffuse[] = { 1,1,1,1 };
	GLfloat glLight2_specular[] = { 1,1,1,1 };
	GLfloat glLight2_position[] = { 2,5,-5,1 };
	glEnable(GL_LIGHT2);
	//glLightfv(GL_LIGHT2, GL_AMBIENT, glLight2_ambient);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, glLight2_diffuse);
	glLightfv(GL_LIGHT2, GL_SPECULAR, glLight2_specular);
	glLightfv(GL_LIGHT2, GL_POSITION, glLight2_position);




	glMatrixMode(GL_PROJECTION);
	glLoadIdentity(); 			//Сброс всех матриц в 1
	gluPerspective(_zoom, (float)1366 / 768, 7.f, 18.0f);
	//glRotatef(r_object, 0, 1, 0);
	//glRotatef(v_cam, 1, 0, 0);
	////glFrustum(-1, 1, -1, 1, 1, 5);	//видовые параметры
	////glFrustum(-0.85, 0.85, -0.7, 0.7, 3, 12);	//видовые параметр

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	//glRasterPos2d(0, 0);
	//glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	//glPixelZoom(1.0, 1.0);
	//glDrawPixels(TextureMass[1]->sizeX, TextureMass[1]->sizeY,GL_RGB, GL_UNSIGNED_BYTE, TextureMass[1]->data);

	////gluLookAt(-1.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	//glTranslatef(0.0, -1.0, -9.0);		//начальный сдвиг 
	////--------------------------
	//glRotatef(h_angle, 0, 1, 0);
	//glRotatef(v_angle, 1, 0, 0);
	////--------------------------
	//drawQube();


	//------------------------snowman
	glPushMatrix();
		glTranslatef(-2.5, -1.0, -9.0);		//начальный сдвиг 
		glRotatef(stepman, 0, 1, 0);
		
		glTranslatef(1.0, -0.0, -0.0);		//начальный сдвиг 
		//glTranslatef(1 * sin(stepman), -1.0*1 * cos(stepman), -9.0);		//начальный сдвиг 
		glColor3f(0.746, 0.832, 0.797);
		//GLfloat color_mat1[] = { 0.746, 0.832, 0.797,1.0 };
		GLfloat color_mat1[] = { 0.5, 0.5, 0.5,1.0 };
		glMaterialfv(GL_FRONT, GL_DIFFUSE, color_mat1);
		//glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat_specular);
		glMaterialfv(GL_FRONT, GL_SPECULAR, color_mat1);

		gluQuadricTexture(quadricObj, GL_TRUE);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, TextNames[SPACE]);
		//glMaterialfv(GL_FRONT, GL_AMBIENT, glTexAmbientFlore);
		//glMaterialfv(GL_FRONT, GL_DIFFUSE, glTexDiffuseFlore);
		//glMaterialfv(GL_FRONT, GL_SPECULAR, glTexShineFlore);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_LINEAR_MIPMAP_LINEAR);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

		//glutSolidSphere(0.7, 99, 99);
		glPushMatrix();
			glRotated(-90, 1, 0, 0);
			gluSphere(quadricObj, 0.7, 16, 16);
		glPopMatrix();
		
		glDisable(GL_TEXTURE_2D);
		
		glPushMatrix();
			glTranslatef(0.0, 1.15, 0.0);		//начальный сдвиг 
			glColor3f(0.746, 0.832, 0.797);
			glutSolidSphere(0.45, 99, 99);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(0.0, 1.9, 0.0);		//начальный сдвиг 
			glColor3f(0.746, 0.832, 0.797);
			glutSolidSphere(0.3, 99, 99);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(0.09, 1.95, 0.24);		//начальный сдвиг 
			//glColor3f(0, 0, 0);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse_black);
			glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular_black);
			glutSolidSphere(0.05, 99, 99);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-0.09, 1.95, 0.24);		//начальный сдвиг 
			glColor3f(0, 0, 0);
			glutSolidSphere(0.05, 99, 99);
		glPopMatrix();

		glPushMatrix();
			//glScalef(TYPE kx, TYPE ky, TYPE kz);
			glTranslatef(0.00, 1.85, 0.28);		//начальный сдвиг 
			glColor3f(1, 0.549, 0);
			GLfloat color_mat3[] = { 1.0,0.0,0.0,1.0 };
			glMaterialfv(GL_FRONT, GL_DIFFUSE, color_mat3);
			glMaterialfv(GL_FRONT, GL_SPECULAR, color_mat3);
			gluQuadricDrawStyle(quadricObj, GLU_FILL);
			gluCylinder(quadricObj, 0.05, 0, 0.15, 99, 99);
		glPopMatrix();
		//glRotatef(-stepman, 0, 1, 0);
	glPopMatrix();
		//gluDeleteQuadric(quadricObj);
//---------------------------------------------------telega
	//glTranslatef(-1.0, -0.0, -0.0);
	glPushMatrix();
		//glTranslatef(0.0, -0.0, -0.0);		//начальный сдвиг
		//glRotatef(r_object, 0, 1, 0);
		//glRotatef(v_cam, 1, 0, 0);
		glTranslatef(2, 0.0, -9.0);		//начальный сдвиг 
		glRotatef(h_angle, 0, 1, 0);
		glRotatef(v_angle, 1, 0, 0);
		glRotatef(-180, 0, 1, 0);

		glEnable(GL_TEXTURE_2D);
		drawQube();
		glDisable(GL_TEXTURE_2D);

		glPushMatrix();
			glTranslatef(-1.0, -1.0, 1.0);		//начальный сдвиг 
			DrawWheels();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(1.0, -1.0, 1.0);		//начальный сдвиг 
			DrawWheels();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-1.0, -1.0, -1.0);		//начальный сдвиг 
			glRotatef(180, 0, 1, 0);
			DrawWheels();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(1.0, -1.0, -1.0);		//начальный сдвиг 
			glRotatef(180, 0, 1, 0);
			DrawWheels();
		glPopMatrix();

		glPushMatrix();
			gluQuadricTexture(quadricObj, GL_TRUE);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, TextNames[HEADLIGHT]);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_LINEAR_MIPMAP_LINEAR);
			//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

			glTranslatef(1.0, -0.5, -0.7);		//фара 1
			glColor3f(1, 1, 0);
			GLfloat color_mat4[] = { 1.0,1.0,0.0,1.0 };
			glMaterialfv(GL_FRONT, GL_DIFFUSE, color_mat4);
			glMaterialfv(GL_FRONT, GL_SPECULAR, color_mat4);
			//glutSolidSphere(0.2, 99, 99);
			glPushMatrix();
				glRotated(-90, 1, 0, 0);
				gluSphere(quadricObj, 0.2, 16, 16);
			glPopMatrix();

			//glDisable(GL_TEXTURE_2D);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(1.0, -0.5, 0.7);		//фара 2
			glColor3f(1, 1, 0);
			//glutSolidSphere(0.2, 99, 99);
			glPushMatrix();
				glRotated(-90, 1, 0, 0);
				gluSphere(quadricObj, 0.2, 16, 16);
			glPopMatrix();
			glDisable(GL_TEXTURE_2D);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-1.00, -0.5, 0.7);		//задний фонарь 1
			glColor3f(1, 0, 0);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, color_red);
			glMaterialfv(GL_FRONT, GL_SPECULAR, color_red);
			gluQuadricDrawStyle(quadricObj, GLU_FILL);
			gluCylinder(quadricObj, 0.05, 0.05, 0.18, 99, 99);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-1.00, -0.5, -0.88);		//задний фонарь 2 
			glColor3f(1, 0, 0);
			gluQuadricDrawStyle(quadricObj, GLU_FILL);
			gluCylinder(quadricObj, 0.05, 0.05, 0.18, 99, 99);
		glPopMatrix();

		glPushMatrix();
			float theta;
			glBegin(GL_POLYGON);
			for (int i = 0; i < 360; i++) {
				theta = i * M_PI / 180;
				glVertex3f(-1 + 0.05 * cos(theta), -0.5 + 0.05 * sin(theta),0.88);
			}
			glEnd();
		glPopMatrix();

		glPushMatrix();
			glBegin(GL_POLYGON);
			for (int i = 0; i < 360; i++) {
				theta = i * M_PI / 180;
				glVertex3f(-1 + 0.05 * cos(theta), -0.5 + 0.05 * sin(theta), 0.7);
			}
			glEnd();
		glPopMatrix();

		glPushMatrix();
			glBegin(GL_POLYGON);
			for (int i = 0; i < 360; i++) {
				theta = i * M_PI / 180;
				glVertex3f(-1 + 0.05 * cos(theta), -0.5 + 0.05 * sin(theta), -0.88);
			}
			glEnd();
		glPopMatrix();

		glPushMatrix();
			glBegin(GL_POLYGON);
				for (int i = 0; i < 360; i++) {
					theta = i * M_PI / 180;
					glVertex3f(-1 + 0.05 * cos(theta), -0.5 + 0.05 * sin(theta), -0.7);
				}
			glEnd();
		glPopMatrix();
		gluDeleteQuadric(quadricObj);
	glPopMatrix();
//gluDeleteQuadric(quadricObj);

//----------------------------------------HOME
		glPushMatrix();
			//glTranslatef(0.0, -0.0, -0.0);		//начальный сдвиг
			//glRotatef(r_object, 0, 1, 0);
			//glRotatef(v_cam, 1, 0, 0);
			glTranslatef(0.0, 0.0, -18.0);		//начальный сдвиг 
			//glRotatef(h_angle, 0, 1, 0);
			//glRotatef(v_angle, 1, 0, 0);
			glRotatef(-20, 0, 1, 0);

			drawHome();

		glPopMatrix();
}

LRESULT CALLBACK WndProc(HWND	hWnd,
	UINT	message,
	WPARAM	wParam,
	LPARAM	lParam)
{
	RECT	Screen;
	// используется позднее для размеров окна
	GLuint	PixelFormat;
	static	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		// Размер этой структуры
		1,			// Номер версии 
		PFD_DRAW_TO_WINDOW |	// Формат для Окна
		PFD_SUPPORT_OPENGL |	// Формат для OpenGL
		PFD_DOUBLEBUFFER,	// Формат для двойного буфера
		PFD_TYPE_RGBA,		// Требуется RGBA формат
		16,			// Выбор 16 бит глубины цвета
		0, 0, 0, 0, 0, 0,   // Игнорирование цветовых битов 
		0,			// нет буфера прозрачности
		0,			// Сдвиговый бит игнорируется 
		0,			// Нет буфера аккумуляции
		0, 0, 0, 0,	// Биты аккумуляции игнорируются 
		16,		// 16 битный Z-буфер (буфер глубины)  
		0,			// Нет буфера трафарета
		0,		// Нет вспомогательных буферов 
		PFD_MAIN_PLANE,		// Главный слой рисования
		0,			// Резерв 
		0, 0, 0			// Маски слоя игнорируются 
	};

	switch (message)	// Тип сообщения
	{
	case WM_CREATE:
		hDC = GetDC(hWnd);
		// Получить контекст устройства для окна
		PixelFormat = ChoosePixelFormat(hDC, &pfd);
		// Найти ближайшее совпадение для формата пикселей
		if (!PixelFormat)
		{
			MessageBox(0, "Не найден подходящий формат пикселя.",
				"Ошибка", MB_OK | MB_ICONERROR);
			PostQuitMessage(0);
			// Это сообщение говорит, что
			// программа должна завершиться
			break;		// Предотвращение повтора кода
		}

		if (!SetPixelFormat(hDC, PixelFormat, &pfd))
		{
			MessageBox(0, "Формат пикселя не установлен.",
				"Ошибка", MB_OK | MB_ICONERROR);
			PostQuitMessage(0);
			break;
		}

		hRC = wglCreateContext(hDC);
		if (!hRC)
		{
			MessageBox(0, "Контекст воспроизведения не создан.",
				"Ошибка", MB_OK | MB_ICONERROR);
			PostQuitMessage(0);
			break;
		}

		if (!wglMakeCurrent(hDC, hRC))
		{
			MessageBox(0, "Невозможно активизировать GLRC.",
				"Ошибка", MB_OK | MB_ICONERROR);
			PostQuitMessage(0);
			break;
		}

		//Generating names for textures
		glGenTextures(10, TextNames);

		//Load Flore texture
		for (int i = 0; i < 8; i++)
		{
			ImRect1 = auxDIBImageLoad(TextureFiles[i]);
			glBindTexture(GL_TEXTURE_2D, TextNames[i]);
			gluBuild2DMipmaps(GL_TEXTURE_2D, 3, ImRect1->sizeX, ImRect1->sizeY, GL_RGB, GL_UNSIGNED_BYTE, ImRect1->data);
			TextureMass[i] = ImRect1;
		}


		GetClientRect(hWnd, &Screen);
		InitGL(Screen.right, Screen.bottom);
		break;

	case WM_DESTROY:
	case WM_CLOSE:
		ChangeDisplaySettings(NULL, 0);
		wglMakeCurrent(hDC, NULL);
		wglDeleteContext(hRC);
		ReleaseDC(hWnd, hDC);
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			//keys[wParam] = TRUE;
			SendMessage(hWnd, WM_CLOSE, 0, 0);
			break;
		case VK_LEFT:
			h_angle += 10.0;
			break;
		case VK_RIGHT:
			h_angle -= 10.0;
			break;
		case VK_UP:
			v_angle += 10.0;
			break;
		case VK_DOWN:
			v_angle -= 10.0;
			break;
		case 0x41: //key A
			r_object += 10.0;
			break;
		case 0x44: //key D
			r_object -= 10.0;
			break;
			//case 0x57: //key W
			//	v_angle += 10.0;
			//	break;
			//case 0x53: //key S
			//	v_angle -= 10.0;
			//	break;
		case VK_OEM_PLUS:
			_zoom -= 10.0;
			if (_zoom < 10) _zoom = 10;
			break;
		case VK_OEM_MINUS:
			_zoom += 10.0;
			if (_zoom > 170) _zoom = 170;
			break;
		default:
			break;
		}
		//keys[wParam] = TRUE;
		//if (keys[VK_UP]) v_angle -= 10.0;
		//if (keys[VK_DOWN]) v_angle += 10.0;
		//if (keys[VK_LEFT]) h_angle -= 10.0;
		//if (keys[VK_RIGHT]) h_angle += 10.0;

		//if (keys[VK_UP]) v_angle -= 10.0;
		//if (keys[VK_DOWN]) v_angle += 10.0;
		//if (keys[VK_LEFT]) h_angle -= 10.0;
		//if (keys[VK_RIGHT]) h_angle += 10.0;
		//break;

	case WM_KEYUP:
		keys[wParam] = FALSE;
		break;

	case WM_SIZE:
		ReSizeGLScene(LOWORD(lParam), HIWORD(lParam));
		break;

	default:
		return (DefWindowProc(hWnd, message,
			wParam, lParam));
	}
	return (0);
}

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	MSG		msg;	// Структура сообщения Windows
	WNDCLASS	wc; 	// Структура класса Windows 
				// для установки типа окна
	HWND	hWnd;	// Сохранение дескриптора окна
	//float _angle=0.0;


	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = (WNDPROC)WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = NULL;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = "OpenGL WinClass";

	if (!RegisterClass(&wc))
	{
		MessageBox(0, "Ошибка регистрации класса окна.",
			"Ошибка", MB_OK | MB_ICONERROR);
		return FALSE;
	}

	hWnd = CreateWindow(
		"OpenGL WinClass",
		"Это минимальная программа OpenGL",
		// Заголовок вверху окна
		WS_POPUP |
		WS_CLIPCHILDREN |
		WS_CLIPSIBLINGS,
		0, 0,		// Позиция окна на экране
		1366, 768,		// Ширина и высота окна
		NULL,
		NULL,
		hInstance,
		NULL);

	if (!hWnd)
	{
		MessageBox(0, "Ошибка создания окна.",
			"Ошибка", MB_OK | MB_ICONERROR);
		return FALSE;
	}
	DEVMODE dmScreenSettings;	// Режим работы
	memset(&dmScreenSettings, 0, sizeof(DEVMODE));
	// Очистка для хранения установок
	dmScreenSettings.dmSize = sizeof(DEVMODE);
	// Размер структуры Devmode
	dmScreenSettings.dmPelsWidth = 1366;
	// Ширина экрана
	dmScreenSettings.dmPelsHeight = 768;
	// Высота экрана
	dmScreenSettings.dmFields = DM_PELSWIDTH |
		DM_PELSHEIGHT;
	// Режим Пикселя
	ChangeDisplaySettings(&dmScreenSettings,
		CDS_FULLSCREEN);
	// Переключение в полный экран
	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);
	SetFocus(hWnd);

	while (1)
	{
		// Обработка всех сообщений
		while (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
		{
			if (GetMessage(&msg, NULL, 0, 0))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else
			{
				return TRUE;
			}
		}
		if (h_angle == 360) h_angle = 0;
		if (v_angle == 360) v_angle = 0;
		//if (keys[VK_UP]) _angle = 10.0;
		//if (keys[VK_DOWN]) _angle = -10.0;
		//if (keys[VK_SPACE]) _angle+=1.0 ;
		//myfile << "_angle=" << _angle << std::endl;
		stepman +=15* M_PI / 180;
		DrawGLScene(h_angle, v_angle, h_cam, v_cam,stepman);  // Нарисовать сцену
		SwapBuffers(hDC);	// Переключить буфер экрана
		if (keys[VK_ESCAPE]) SendMessage(hWnd, WM_CLOSE, 0, 0);
		// Если ESC - выйти
	}
}


