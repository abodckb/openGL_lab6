
//#include <windows.h>	
//// ������������ ���� ��� Windows
//#include <gl\gl.h>		
//#include <gl\glut.h>
//	// ������������ ���� ��� ���������� OpenGL32 
//#include <gl\glu.h>		
//	// ������������ ���� ��� ���������� GLu32 
////#include <gl\glaux.h>		
//	// ������������ ���� ��� ���������� GLaux 
//#define _USE_MATH_DEFINES
//#include <cmath>
//#include <iostream>
//#include <fstream>

#include "openGL_CW_5.h"

static HGLRC hRC;
// ���������� �������� ����������
static HDC hDC;
// ��������� �������� ���������� GDI

BOOL	keys[256];
// ������ ��� ��������� ��������� ����������
float h_angle = 0.0;
float v_angle = 0.0;
float h_cam = 0.0;
float v_cam = 0.0;
float r_object = 0.0; //rotate left
float r_right = 0.0;//rotate right
float _zoom = 45.0;
float stepman = 0.0;

bool flag = false;
GLfloat deltaCar = 0.0;
std::ofstream myfile;

bool flag_GL_LIGHT1 = false;
bool flag_GL_LIGHT2 = false;
bool flag_GL_LIGHT3 = false;


float xCar = 0.0;
float zCar = 0.0;
float prevCar = 0.0;// ���������� ���� �������� ������
float curCar = 0.0;// ������� ���� �������� ������

GLuint TextNames[100];
AUX_RGBImageRec* TextureMass[100];
AUX_RGBImageRec* ImRect1;
//char* TextureFiles[] = {"Bricks.bmp"};
const char* TextureFiles[] = { "Bricks.bmp","space.bmp","CarBotton.bmp","protectorbump_010.bmp","headlights_001.bmp","metals_004.bmp","skies_031.bmp","sand_35.bmp","bricks_039.bmp","woods_023.bmp", "street2.bmp", "headGlass.bmp", "rain1.bmp", "window.bmp" };

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


GLvoid InitGL(GLsizei Width, GLsizei Height)	//������� ����� �������� ���� GL
{
	glClearColor(.0f, .0f, .0f, 1.0f);
	//glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	// ������� ������ � ������ ����
}

//const int N = 20;
GLvoid drawObj(GLfloat texW, GLfloat texH, GLfloat objW, GLfloat objH, int n, GLfloat offsetX)
{
	int N = n+1;
	//GLfloat arrTexW[N], arrTexH[const N],arrObjW[const N],arrObjH[const N];
	GLfloat *arrTexW= new GLfloat[N];
	GLfloat* arrTexH = new GLfloat[N];
	GLfloat* arrObjW = new GLfloat[N];
	GLfloat* arrObjH = new GLfloat[N];

	GLfloat delta=0.0;
	delta = texW / n;


	arrTexW[0] = 0.0;
	for (int i = 1; i < N ; i++)
		arrTexW[i] = arrTexW[i-1]+delta;
	arrTexW[N -1] = texW;

	delta = texH / n;
	arrTexH[0] = 0.0;
	for (int i = 1; i < N; i++)
		arrTexH[i] = arrTexH[i - 1] + delta;
	arrTexH[N-1] = texH;

	delta = objW / n;
	arrObjW[0] = 0.0;
	int p=0;
	for (int i = 1; i < N; i++) {
		arrObjW[i] = arrObjW[i - 1] + delta;
		p++;
	}
	arrObjW[N-1 ] = objW;

	delta = objH / n;
	arrObjH[0] = 0.0;
	for (int i = 1; i < N ; i++)
		arrObjH[i] = arrObjH[i - 1] + delta;
	arrObjH[N-1] = objH;

	glBegin(GL_QUADS);
	for (int j = 0; j < n; j++) {
		for (int i = 0; i < n; i++) {
			glTexCoord2f(arrTexW[i], arrTexH[j]); glVertex3f(offsetX, arrObjH[j], arrObjW[i]);
			glTexCoord2f(arrTexW[i], arrTexH[++j]); glVertex3f(offsetX, arrObjH[j], arrObjW[i]);
			glTexCoord2f(arrTexW[++i], arrTexH[j]); glVertex3f(offsetX, arrObjH[j], arrObjW[i]);
			glTexCoord2f(arrTexW[i], arrTexH[--j]); glVertex3f(offsetX, arrObjH[j], arrObjW[i]);
			i--;
		}
	}
	glEnd();
	delete arrTexW;
	delete arrTexH;
	delete arrObjW;
	delete arrObjH;
}

GLvoid ReSizeGLScene(GLsizei Width, GLsizei Height)
{
	if (Height == 0)
		// �������������� ������� �� ����, 
		//���� ���� ������� ����
		Height = 1;
	glViewport(0, 0, Width, Height);
	// ����� ������� ������� ������ �
	//������������� ��������������
}


void DrawWheels(float size)
{
	GLUquadricObj* quadricObj = gluNewQuadric();
	//GLfloat no_mat_specular[] = { 0.0,0.0,0.0,1.0 };
	//glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat_specular);
	//glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
		//glTranslatef(0.0, 0.3, 0.0);

		glPushMatrix(); //����� ������� (����������)
			//glRotatef(30, 0, 1, 0);
			//glTranslatef(0, -0.1, -0.2);
			//glColor3f(1, 0, 0);
			GLfloat color_mat1[] = { 1.0,0.0,0.0,1.0 };
			//glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color_mat1);
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color_mat1);
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, color_mat1);
			//gluQuadricDrawStyle(quadricObj, GLU_LINE);
			gluQuadricDrawStyle(quadricObj, GLU_FILL);
			gluCylinder(quadricObj, 0.1 * size, 0.1 * size, 0.1 * size, 30, 3);
		glPopMatrix();




		glPushMatrix(); //������� ������� (�������)

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
			gluCylinder(quadricObj, 0.3 * size, 0.3 * size, 0.1 * size, 30, 3);

			glDisable(GL_TEXTURE_2D);
		glPopMatrix();

		GLUquadricObj* quadricObjDisk = gluNewQuadric();
		glPushMatrix();//���� ������ (����������)
			//glRotatef(60, 0, 1, 0);
			//glTranslatef(0.0, 0.0, 0.0);
			//glColor3f(0, 0, 1);
			GLfloat color_mat3[] = { 0.0,0.0,1.0,1.0 };
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color_mat3);
			//glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color_mat3);
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, color_mat3);
			//gluQuadricDrawStyle(quadricObjDisk, GLU_LINE);
			gluQuadricDrawStyle(quadricObjDisk, GLU_FILL);
			gluDisk(quadricObjDisk, 0.1 * size, 0.3 * size, 10, 3);
		glPopMatrix();

		//GLUquadricObj* quadricObjDisk = gluNewQuadric();
		glPushMatrix();
			//glRotatef(60, 0, 1, 0);
			glTranslatef(0.0, 0.0, 0.1 * size);
			glColor3f(0, 0, 0);
			//GLfloat color_mat4[] = { 0.0,0.0,0.0,1.0 };
			//glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color_mat4);
			//glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, color_mat4);
			//gluQuadricDrawStyle(quadricObjDisk, GLU_LINE);
			gluQuadricDrawStyle(quadricObjDisk, GLU_FILL);
			gluDisk(quadricObjDisk, 0.1 * size, 0.3 * size, 10, 3);
		glPopMatrix();
	glPopMatrix();

	gluDeleteQuadric(quadricObj);
	gluDeleteQuadric(quadricObjDisk);
}

void drawHeadLight(float size) // �������� ����
{
	GLfloat color_white[] = { 1.0,1.0,1.0,1.0 };
	GLfloat color_red[] = { 1.0,0.0,0.0,1.0 };
	GLfloat color_black[] = { 0.0,0.0,0.0,1.0 };

	GLUquadricObj* quadricObj = gluNewQuadric();

	glPushMatrix();
		gluQuadricTexture(quadricObj, GL_TRUE);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, TextNames[HEADLIGHT]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_LINEAR_MIPMAP_LINEAR);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

		//glTranslatef(1.0, -0.5, -0.7);		//���� 1
		glColor3f(1, 1, 0);
		GLfloat color_mat4[] = { 1.0,1.0,0.0,1.0 };
		glMaterialfv(GL_FRONT, GL_DIFFUSE, color_mat4);
		glMaterialfv(GL_FRONT, GL_SPECULAR, color_mat4);
		//glutSolidSphere(0.2, 99, 99);
		glPushMatrix();
			glRotated(-90, 1, 0, 0);
			gluSphere(quadricObj, 0.2*size, 16, 16);
		glPopMatrix();

		glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	//glPushMatrix();
	//	glTranslatef(1.0, -0.5, 0.7);		//���� 2
	//	glColor3f(1, 1, 0);
	//	//glutSolidSphere(0.2, 99, 99);
	//	glPushMatrix();
	//	glRotated(-90, 1, 0, 0);
	//	gluSphere(quadricObj, 0.2, 16, 16);
	//	glPopMatrix();
	//	glDisable(GL_TEXTURE_2D);
	//glPopMatrix();

}

void drawBackLight(float size) // ������ ����
{
	GLfloat color_white[] = { 1.0,1.0,1.0,1.0 };
	GLfloat color_red[] = { 1.0,0.0,0.0,1.0 };
	GLfloat color_black[] = { 0.0,0.0,0.0,1.0 };

	GLUquadricObj* quadricObj = gluNewQuadric();

//---START-----������ ������
		glPushMatrix();
			//glTranslatef(-1.00, -0.5, 0.7);		//������ ������ 1
			glColor3f(1, 0, 0);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, color_red);
			glMaterialfv(GL_FRONT, GL_SPECULAR, color_red);
			gluQuadricDrawStyle(quadricObj, GLU_FILL);
			gluCylinder(quadricObj, 0.05 * size, 0.05 * size, 0.18 * size, 99, 99);
		//glPopMatrix();

		//glPushMatrix();
		float theta;
		glBegin(GL_POLYGON);
			for (int i = 0; i < 360; i++) {
				theta = i * M_PI / 180;
				glVertex3f(0.05 * size * cos(theta), 0.05 * size * sin(theta), 0.18 * size);
			}
		glEnd();
		//glPopMatrix();

		//glPushMatrix();
		glBegin(GL_POLYGON);
			for (int i = 0; i < 360; i++) {
				theta = i * M_PI / 180;
				glVertex3f(0.05 * size * cos(theta), 0.05 * size * sin(theta), 0.0);
			}
		glEnd();
		glPopMatrix();

		//glPushMatrix();
		//	glTranslatef(-1.00, -0.5, -0.88);		//������ ������ 2 
		//	glColor3f(1, 0, 0);
		//	gluQuadricDrawStyle(quadricObj, GLU_FILL);
		//	gluCylinder(quadricObj, 0.05, 0.05, 0.18, 99, 99);
		//glPopMatrix();
//---END-----������ ������

}


void drawQube(float size)
{
	//float size = 1.f;

	//texture material modifications
	GLfloat glTexAmbientFlore[] = { 0,0,0,1 };
	GLfloat glTexDiffuseFlore[] = { 1.0,1,1.0,1 };
	GLfloat glTexShineFlore[] = { 1.0,1.0,1.0,1 };
	//GLfloat glTexDiffuseFlore[] = { 0.3,0,0.8,1 };
	//GLfloat glTexShineFlore[] = { 0.2,0.2,0.2,1 };

	glBindTexture(GL_TEXTURE_2D, TextNames[BRIKS]);
	//glMaterialfv(GL_FRONT, GL_AMBIENT, glTexAmbientFlore);
	//glMaterialfv(GL_FRONT, GL_DIFFUSE, glTexDiffuseFlore);
	//glMaterialfv(GL_FRONT, GL_SPECULAR, glTexShineFlore);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_LINEAR_MIPMAP_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glColor3f(0, 0, 0);

	glPushMatrix();
		glTranslatef(0.0,size,0.0);

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

		glEnable(GL_TEXTURE_2D);
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
		glDisable(GL_TEXTURE_2D);


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


		glBindTexture(GL_TEXTURE_2D, TextNames[RAIN1]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_LINEAR_MIPMAP_LINEAR);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glColor3f(0, 0, 0);

		glEnable(GL_TEXTURE_2D);
		glBegin(GL_QUADS);
			//glColor3f(randomFlt(), randomFlt(), randomFlt());
			//glColor3f(0.773, 0.648, 0.715);
			glColor3f(0.652, 0.566, 0.727);
			//left
			glTexCoord2f(0, 0);
			glVertex3f(-size, -0*size, size);
			glTexCoord2f(1, 0);
			glVertex3f(-size, -0*size, -size);
			glTexCoord2f(1, 1);
			glVertex3f(-size, 0.7 * size, -size);
			glTexCoord2f(0, 1);
			glVertex3f(-size, 0.7 * size, size);
		glEnd();
		//glDisable(GL_TEXTURE_2D);

		//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

		glBegin(GL_QUADS);
			//glColor3f(randomFlt(), randomFlt(), randomFlt());
			glColor3f(0.5, 0.5, 0.5);
			//right
			glTexCoord2f(1, 0);
			glVertex3f(0.2*size, -0*size, -size);
			glTexCoord2f(0, 0);
			glVertex3f(0.2 * size, -0*size, size);
			glTexCoord2f(1, 0);
			glVertex3f(0.2 * size, 0.7 * size, size);
			glTexCoord2f(1, 1);
			glVertex3f(0.2 * size, 0.7 * size, -size);
		glEnd();
		glDisable(GL_TEXTURE_2D);


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
	glPopMatrix();
}

void drawQube1(float size)
{
	//float size = 1.f;

	//texture material modifications
	//GLfloat glTexAmbientFlore[] = { 0,0,0,1 };
	//GLfloat glTexDiffuseFlore[] = { 1.0,1,1.0,1 };
	//GLfloat glTexShineFlore[] = { 1.0,1.0,1.0,1 };
	//GLfloat glTexDiffuseFlore[] = { 0.3,0,0.8,1 };
	//GLfloat glTexShineFlore[] = { 0.2,0.2,0.2,1 };

	//glBindTexture(GL_TEXTURE_2D, TextNames[BRIKS]);
	//glMaterialfv(GL_FRONT, GL_AMBIENT, glTexAmbientFlore);
	//glMaterialfv(GL_FRONT, GL_DIFFUSE, glTexDiffuseFlore);
	//glMaterialfv(GL_FRONT, GL_SPECULAR, glTexShineFlore);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_LINEAR_MIPMAP_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_LINEAR_MIPMAP_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	//glColor3f(0, 0, 0);

	//glPushMatrix();
	//glTranslatef(0.0, size, 0.0);

	//glEnable(GL_TEXTURE_2D);
	//glBindTexture(GL_TEXTURE_2D, TextNames[RAIN1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_LINEAR_MIPMAP_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glColor3f(0, 0, 0);

//-----START--------korpus car---------------------------
	glPushMatrix();
		//glColor3f(1, 1, 1);
		glPushMatrix();
		glTranslatef(0.0, 0.0, -size);
			drawObj(1, 1, 2 * size, size, 20, -size);//back
			drawObj(1, 1, 2 * size, size, 20, size);//front
		glPopMatrix();

		glPushMatrix();
			glRotatef(90, 0, 1, 0);
			glTranslatef(0.0, 0.0, -size);
			drawObj(1, 1, 2 * size, size, 20, size);//right
			drawObj(1, 1, 2 * size, size, 20, -size);//left/"
		glPopMatrix();

		glPushMatrix();
			glTranslatef(size, size/2, -size);
			glRotatef(90, 0, 0, 1);
			drawObj(1, 1, 2 * size, 2*size, 20, size/2);//top	
			drawObj(1, 1, 2 * size, 2*size, 20, -size/2);//botton
		glPopMatrix();
	glPopMatrix();
//-----END--------korpus car---------------------------


//-----START--------kabine car---------------------------
	glPushMatrix();
		//glColor3f(1, 1, 1);
		glTranslatef(0.0*size, size, 0);


		glPushMatrix();
			glRotatef(90, 0, 1, 0);
			glTranslatef(0.0, 0.0, -size);
			drawObj(1, 1, 1.3 * size, size, 20, size);//right
			drawObj(1, 1, 1.3 * size, size, 20, -size);//left
		glPopMatrix();

		glPushMatrix();
			glTranslatef(0.3 * size, size / 2, -size);
			glRotatef(90, 0, 0, 1);
			drawObj(1, 1, 2 * size, 1.3 * size, 20, size / 2);//top	
			//drawObj(1, 1, 2 * size, size, 20, -size / 2);//botton
		glPopMatrix();

		glPushMatrix();
			glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_def);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse_def);
			//glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse_white);
			glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular_def);
			//glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular_white);
			glMaterialf(GL_FRONT, GL_SHININESS, 90);
			glBindTexture(GL_TEXTURE_2D, TextNames[RAIN1]);
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
			glEnable(GL_TEXTURE_2D);
			{
				glTranslatef(0.0, 0.0, -size);
				drawObj(1, 1, 2 * size, size, 20, -size);//back
				drawObj(1, 1, 2 * size, size, 20, 0.3 * size);//front
			}
			glDisable(GL_TEXTURE_2D);
		glPopMatrix();
	glPopMatrix();
//-----END--------kabine car---------------------------
	glDisable(GL_TEXTURE_2D);

}



void drawCar(float size)
{
	GLfloat color_white[] = { 1.0,1.0,1.0,1.0 };
	GLfloat color_red[] = { 1.0,0.0,0.0,1.0 };
	GLfloat color_black[] = { 0.0,0.0,0.0,1.0 };

	GLUquadricObj* quadricObj = gluNewQuadric();

	glPushMatrix();
		glTranslatef(0, 0.3 * size, 0.0);

		//glDisable(GL_TEXTURE_2D);
		//glEnable(GL_TEXTURE_2D);
		drawQube(size);
		//glDisable(GL_TEXTURE_2D);

		glPushMatrix();
			glTranslatef(1.0*size, 0.5 * size, -0.7 * size); //�������� ����
			drawHeadLight(size);
			glTranslatef(0.0, 0.0, 1.4 * size);
			drawHeadLight(size);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-1.00 * size, 0.5 * size, -0.7 * size);//������ ����
			drawBackLight(size);
			glTranslatef(0.0, 0.0, 1.2 * size);
			drawBackLight(size);
		glPopMatrix();

		

		glPushMatrix();
			glTranslatef(-1.0 * size, 0.0, 1.0 * size);		//��������� ����� 
			DrawWheels(size);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(1.0 * size, 0.0, 1.0 * size);		//��������� ����� 
			DrawWheels(size);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-1.0 * size, 0.0, -1.0 * size);		//��������� ����� 
			glRotatef(180, 0, 1, 0);
			DrawWheels(size);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(1.0 * size, 0.0, -1.0 * size);		//��������� ����� 
			glRotatef(180, 0, 1, 0);
			DrawWheels(size);
		glPopMatrix();

		gluDeleteQuadric(quadricObj);
	glPopMatrix();
	//gluDeleteQuadric(quadricObj);
	//---END---telega------------------

}

void drawCar1(float size)
{
	GLfloat color_white[] = { 1.0,1.0,1.0,1.0 };
	GLfloat color_red[] = { 1.0,0.0,0.0,1.0 };
	GLfloat color_black[] = { 0.0,0.0,0.0,1.0 };

	GLUquadricObj* quadricObj = gluNewQuadric();

	glPushMatrix();
	glTranslatef(0, 0.3 * size, 0.0);

	//glDisable(GL_TEXTURE_2D);
	//glEnable(GL_TEXTURE_2D);
	drawQube1(size);
	//glDisable(GL_TEXTURE_2D);

	glPushMatrix();
	glTranslatef(1.0 * size, 0.5 * size, -0.7 * size); //�������� ����
	drawHeadLight(size);
	glTranslatef(0.0, 0.0, 1.4 * size);
	drawHeadLight(size);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.00 * size, 0.5 * size, -0.7 * size);//������ ����
	drawBackLight(size);
	glTranslatef(0.0, 0.0, 1.2 * size);
	drawBackLight(size);
	glPopMatrix();



	glPushMatrix();
	glTranslatef(-1.0 * size, 0.0, 1.0 * size);		//��������� ����� 
	DrawWheels(size);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.0 * size, 0.0, 1.0 * size);		//��������� ����� 
	DrawWheels(size);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.0 * size, 0.0, -1.0 * size);		//��������� ����� 
	glRotatef(180, 0, 1, 0);
	DrawWheels(size);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.0 * size, 0.0, -1.0 * size);		//��������� ����� 
	glRotatef(180, 0, 1, 0);
	DrawWheels(size);
	glPopMatrix();

	gluDeleteQuadric(quadricObj);
	glPopMatrix();
	//gluDeleteQuadric(quadricObj);
	//---END---telega------------------

}

void drawWindow(int size)
{
	//----START----window----
	glBegin(GL_QUADS);
	glVertex3f(-size / 2, -size / 2, size + 0.001);
	glVertex3f(size / 2, -size / 2, size + 0.001);
	glVertex3f(size / 2, size / 2, size + 0.001);
	glVertex3f(-size / 2, size / 2, size + 0.001);
	glEnd();
	//----END----window----

}


void drawHome()
{
	float size = 1.f;

	GLfloat color_white[] = { 1.0,1.0,1.0,1.0 };
	GLfloat color_red[] = { 1.0,0.0,0.0,1.0 };
	GLfloat color_black[] = { 0.0,0.0,0.0,1.0 };

	GLUquadricObj* quadricObj = gluNewQuadric();

	//glPushMatrix();
	gluQuadricTexture(quadricObj, GL_TRUE);
	//glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, TextNames[BRIKS1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_LINEAR_MIPMAP_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	
	GLfloat color_mat4[] = { 1.0,1.0,1.0,1.0 };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color_mat4);
	glMaterialfv(GL_FRONT, GL_SPECULAR, color_mat4);

	glPushMatrix();
		glTranslatef(0.0, size, 0.0);

//----START----window----
		//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		color_mat4[0] = 1.0;
		color_mat4[1] = 1.0;
		color_mat4[2] = 0.0;

		//glBegin(GL_QUADS);
		//	glMaterialfv(GL_FRONT, GL_DIFFUSE, color_black);
		//	glMaterialfv(GL_FRONT, GL_SPECULAR, color_black);
		//	glVertex3f(-0.01, -size / 2, size + 0.003);
		//	glVertex3f(0.01, -size / 2, size + 0.003);
		//	glVertex3f(0.01, size / 2, size + 0.003);
		//	glVertex3f(-0.01, size / 2, size + 0.003);

		//	glVertex3f(-size / 2, -0.01, size + 0.003);
		//	glVertex3f(size / 2, -0.01, size + 0.003);
		//	glVertex3f(size / 2, 0.01, size + 0.003);
		//	glVertex3f(-size / 2, 0.01, size + 0.003);
		//glEnd();

		//color_mat4[0] = 1.0;
		//color_mat4[1] = 1.0;
		//color_mat4[2] = 0.0;
		//glMaterialfv(GL_FRONT, GL_DIFFUSE, color_mat4);
		//glMaterialfv(GL_FRONT, GL_SPECULAR, color_mat4);

		//glBegin(GL_QUADS);
		//	glVertex3f(-size / 2 + 0.1, -size / 2 + 0.1, size + 0.002);
		//	glVertex3f(size / 2 - 0.1, -size / 2 + 0.1, size + 0.002);
		//	glVertex3f(size / 2 - 0.1, size / 2 - 0.1, size + 0.002);
		//	glVertex3f(-size / 2 + 0.1, size / 2 - 0.1, size + 0.002);
		//glEnd();

		//glBegin(GL_QUADS);
		//	glMaterialfv(GL_FRONT, GL_DIFFUSE, color_black);
		//	glMaterialfv(GL_FRONT, GL_SPECULAR, color_black);
		//	glVertex3f(-size / 2, -size / 2, size + 0.001);
		//	glVertex3f(size / 2, -size / 2, size + 0.001);
		//	glVertex3f(size / 2, size / 2, size + 0.001);
		//	glVertex3f(-size / 2, size / 2, size + 0.001);
		//glEnd();
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, TextNames[WINDOW1]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_LINEAR_MIPMAP_LINEAR);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		glColor3f(0, 0, 0);

		glBegin(GL_QUADS);
		//glMaterialfv(GL_FRONT, GL_DIFFUSE, color_black);
		//glMaterialfv(GL_FRONT, GL_SPECULAR, color_black);
		glColor3f(0, 1, 1);
		glTexCoord2f(0, 0);
		glVertex3f(-size / 2, -size / 2, size + 0.005);
		glTexCoord2f(1, 0);
		glVertex3f(size / 2, -size / 2, size + 0.005);
		glTexCoord2f(1, 1);
		glVertex3f(size / 2, size / 2, size + 0.005);
		glTexCoord2f(0, 1);
		glVertex3f(-size / 2, size / 2, size + 0.005);
		glEnd();
		glDisable(GL_TEXTURE_2D);

//----END----window----

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, TextNames[BRIKS1]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_LINEAR_MIPMAP_LINEAR);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glColor3f(0, 0, 0);
		color_mat4[0] = 0.5;
		color_mat4[1] = 0.5;
		color_mat4[2] = 0.5;
		glMaterialfv(GL_FRONT, GL_DIFFUSE, color_mat4);
		glMaterialfv(GL_FRONT, GL_SPECULAR, color_mat4);


	//glPushMatrix();
	//	glTranslatef(0.0, size, 0.0);

		glBegin(GL_QUADS);
			//glColor3f(1, 1, 1);
			//front
			glTexCoord2f(0, 0);
			glVertex3f(-size, -size, size);
			glTexCoord2f(2, 0);
			glVertex3f(size, -size, size);
			glTexCoord2f(2, 2);
			glVertex3f(size, size, size);
			glTexCoord2f(0, 2);
			glVertex3f(-size, size, size);
		glEnd();



		glBegin(GL_QUADS);
			//glColor3f(randomFlt(), randomFlt(), randomFlt());
			glColor3f(0.699, 0.699, 0.762);
			//back
			glTexCoord2f(0, 0);
			glVertex3f(-size, -size, -size);
			glTexCoord2f(0, 2);
			glVertex3f(-size, size, -size);
			glTexCoord2f(2, 2);
			glVertex3f(size, size, -size);
			glTexCoord2f(2, 0);
			glVertex3f(size, -size, -size);
		glEnd();


		glBegin(GL_QUADS);
			//glColor3f(randomFlt(), randomFlt(), randomFlt());
			glColor3f(0.773, 0.648, 0.715);
			//left
			glTexCoord2f(0, 0);
			glVertex3f(-size, -size, size);
			glTexCoord2f(1, 0);
			glVertex3f(-size, -size, -size);
			glTexCoord2f(1, 1);
			glVertex3f(-size, size, -size);
			glTexCoord2f(0, 1);
			glVertex3f(-size, size, size);
		glEnd();


		glBegin(GL_QUADS);
			//glColor3f(randomFlt(), randomFlt(), randomFlt());
			glColor3f(0.746, 0.832, 0.797);
			//right
			glTexCoord2f(0, 0);
			glVertex3f(size, -size, -size);
			glTexCoord2f(1, 0);
			glVertex3f(size, -size, size);
			glTexCoord2f(1, 1);
			glVertex3f(size, size, size);
			glTexCoord2f(0, 1);
			glVertex3f(size, size, -size);
		glEnd();


		//glBegin(GL_QUADS);
		//	//glColor3f(randomFlt(), randomFlt(), randomFlt());
		//	glColor3f(0.891, 0.726, 0.703);
		//	//bottom
		//	glVertex3f(-size, -size, size);
		//	glVertex3f(size, -size, size);
		//	glVertex3f(size, -size, -size);
		//	glVertex3f(-size, -size, -size);
		//glEnd();


		//glBegin(GL_QUADS);
		//	//glColor3f(randomFlt(), randomFlt(), randomFlt());
		//	glColor3f(0.855, 0.914, 0.859);
		//	//top  		
		//	glVertex3f(-size, size, -size);
		//	glVertex3f(size, size, -size);
		//	glVertex3f(size, size, size);
		//	glVertex3f(-size, size, size);
		//glEnd();
//----START----cherdak-----
		glBindTexture(GL_TEXTURE_2D, TextNames[WOOD]);

		glBegin(GL_TRIANGLES);
			//glColor3f(randomFlt(), randomFlt(), randomFlt());
			glColor3f(1, 1, 0.);
			//top  		
			glTexCoord2f(0, 0);
			glVertex3f(-size, size, size);
			glTexCoord2f(1, 0);
			glVertex3f(size, size, size);
			glTexCoord2f(0.5, 1);
			glVertex3f(0*size, 1.8*size, size);
		glEnd();

		glBegin(GL_TRIANGLES);
			//glColor3f(randomFlt(), randomFlt(), randomFlt());
			glColor3f(1, 0, 0.);
			//top  		
			glTexCoord2f(0, 0);
			glVertex3f(-size, size, -size);
			glTexCoord2f(1, 0);
			glVertex3f(size, size, -size);
			glTexCoord2f(0.5, 1);
			glVertex3f(0 * size, 1.8 * size, -size);
		glEnd();
//----END----cherdak-----

//----START----roof-----

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
			glVertex3f(size+0.375, size-0.3, size + 0.375);
			glTexCoord2f(0, 1);
			glVertex3f(0 * size, 1.8 * size, size + 0.375);
			glTexCoord2f(1, 1);
			glVertex3f(0 *size, 1.8 * size, -size - 0.375);
			glTexCoord2f(1, 0);
			glVertex3f(size + 0.375, size - 0.3, -size - 0.375);
		glEnd();

		glBegin(GL_QUADS);
			//glColor3f(randomFlt(), randomFlt(), randomFlt());
			glColor3f(0, 1, 1);
			//top 
			glTexCoord2f(0, 0);
			glVertex3f(-size - 0.375, size - 0.3, size + 0.375);
			glTexCoord2f(0, 1);
			glVertex3f(0 * size, 1.8 * size, size + 0.375);
			glTexCoord2f(1, 1);
			glVertex3f(0 * size, 1.8 * size, -size- 0.375);
			glTexCoord2f(1, 0);
			glVertex3f(-size - 0.375, size - 0.3, -size- 0.375);
		glEnd();

//----END----roof-----
		glDisable(GL_TEXTURE_2D);

////----START----window----
//		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
//		color_mat4[0] = 1.0;
//		color_mat4[1] = 1.0;
//		color_mat4[2] = 0.0;
//		glMaterialfv(GL_FRONT, GL_DIFFUSE, color_mat4);
//		glMaterialfv(GL_FRONT, GL_SPECULAR, color_mat4);
//		glBegin(GL_QUADS);
//			glMaterialfv(GL_FRONT, GL_DIFFUSE, color_black);
//			glMaterialfv(GL_FRONT, GL_SPECULAR, color_black);
//			glVertex3f(-size / 2, -size / 2, size + 0.001);
//			glVertex3f(size / 2, -size / 2, size + 0.001);
//			glVertex3f(size / 2, size / 2, size + 0.001);
//			glVertex3f(-size / 2, size / 2, size + 0.001);
//		glEnd();
//
//		//GLfloat color_mat4[] = { 1.0,1.0,0.0,1.0 };
//		glMaterialfv(GL_FRONT, GL_DIFFUSE, color_mat4);
//		glMaterialfv(GL_FRONT, GL_SPECULAR, color_mat4);
//
//		glBegin(GL_QUADS);
//			glVertex3f(-size / 2+0.1, -size / 2 + 0.1, size + 0.002);
//			glVertex3f(size / 2 - 0.1, -size / 2 + 0.1, size + 0.002);
//			glVertex3f(size / 2 - 0.1, size / 2 - 0.1, size + 0.002);
//			glVertex3f(-size / 2 + 0.1, size / 2 - 0.1, size + 0.002);
//		glEnd();
//
//		glBegin(GL_QUADS);
//			glMaterialfv(GL_FRONT, GL_DIFFUSE, color_black);
//			glMaterialfv(GL_FRONT, GL_SPECULAR, color_black);
//			glVertex3f(-0.01, -size / 2, size + 0.003);
//			glVertex3f(0.01, -size / 2, size + 0.003);
//			glVertex3f(0.01, size / 2, size + 0.003);
//			glVertex3f(-0.01, size / 2, size + 0.003);
//
//			glVertex3f(-size/2, -0.01, size + 0.003);
//			glVertex3f(size/2, -0.01, size + 0.003);
//			glVertex3f(size/2, 0.01, size + 0.003);
//			glVertex3f(-size/2, 0.01, size + 0.003);
//		glEnd();

		//glEnable(GL_TEXTURE_2D);
		//glBindTexture(GL_TEXTURE_2D, TextNames[WINDOW1]);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_LINEAR_MIPMAP_LINEAR);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_LINEAR_MIPMAP_LINEAR);
		////glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		////glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		//glColor3f(0, 0, 0);

		//glBegin(GL_QUADS);
		////glMaterialfv(GL_FRONT, GL_DIFFUSE, color_black);
		////glMaterialfv(GL_FRONT, GL_SPECULAR, color_black);
		//glColor3f(0, 1, 1);
		//	glTexCoord2f(0, 0);
		//	glVertex3f(-size / 2, -size / 2, size + 0.005);
		//	glTexCoord2f(1, 0);
		//	glVertex3f(size / 2, -size / 2, size + 0.005);
		//	glTexCoord2f(1, 1);
		//	glVertex3f(size / 2, size / 2, size + 0.005);
		//	glTexCoord2f(0, 1);
		//	glVertex3f(-size / 2, size / 2, size + 0.005);
		//glEnd();
		//glDisable(GL_TEXTURE_2D);
//
//
////----END----window----
	glPopMatrix();

}

void drawHome1()
{
	float size = 1.f;

	GLfloat color_white[] = { 1.0,1.0,1.0,1.0 };
	GLfloat color_red[] = { 1.0,0.0,0.0,1.0 };
	GLfloat color_black[] = { 0.0,0.0,0.0,1.0 };

	GLUquadricObj* quadricObj = gluNewQuadric();

	//glPushMatrix();
	gluQuadricTexture(quadricObj, GL_TRUE);
	//glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, TextNames[BRIKS1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_LINEAR_MIPMAP_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);


	GLfloat color_mat4[] = { 1.0,1.0,1.0,1.0 };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color_mat4);
	glMaterialfv(GL_FRONT, GL_SPECULAR, color_mat4);


//----START----window----
	//color_mat4[0] = 1.0;
	//color_mat4[1] = 1.0;
	//color_mat4[2] = 0.0;
	////	glMaterialfv(GL_FRONT, GL_DIFFUSE, color_black);
	////	glMaterialfv(GL_FRONT, GL_SPECULAR, color_black);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, TextNames[WINDOW1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_LINEAR_MIPMAP_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glColor3f(0, 0, 0);

	glPushMatrix();
		glRotatef(-90, 0, 1, 0);
		glTranslatef(0.0, size / 2, -size/2);
		drawObj(1, 1, size, size, 10, size);//left
		//drawObj(1, 1, 2 * size, 2 * size, 20, size);//right
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
//----END----window----



//----START----korobka doma----
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, TextNames[BRIKS1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_LINEAR_MIPMAP_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glColor3f(0, 0, 0);
	color_mat4[0] = 0.5;
	color_mat4[1] = 0.5;
	color_mat4[2] = 0.5;
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color_mat4);
	glMaterialfv(GL_FRONT, GL_SPECULAR, color_mat4);

	glPushMatrix();
	//glColor3f(1, 1, 1);
		glPushMatrix();
			glTranslatef(0.0, 0.0, -size);
			drawObj(1, 1, 2 * size, 2 * size, 20, -size);//left
			drawObj(1, 1, 2 * size, 2 * size, 20, size);//right
		glPopMatrix();

		glPushMatrix();
			glRotatef(90, 0, 1, 0);
			glTranslatef(0.0, 0.0, -size);
			drawObj(1, 1, 2 * size, 2 * size, 20, size);//front
			drawObj(1, 1, 2 * size, 2 * size, 20, -size);//back
		glPopMatrix();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
//----END----korobka doma----


//----START----cherdak-----
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, TextNames[WOOD]);

	glPushMatrix();

		//glTranslatef(-size, 2* size, size);
	//
		glBegin(GL_TRIANGLES);
		//glColor3f(randomFlt(), randomFlt(), randomFlt());
		glColor3f(0, 0, 0);
		//top  		
		glTexCoord2f(0, 0); glVertex3f(-size, 2 * size, -size);
		glTexCoord2f(1, 0);	glVertex3f(size, 2 * size, -size);
		glTexCoord2f(0.5, 1); glVertex3f(0 * size, 3 * size, -size);
		glEnd();
	//
		glBegin(GL_TRIANGLES);
			glColor3f(0, 0, 0);
			//top  		
			glTexCoord2f(0, 0);	glVertex3f(-size, 2*size, size);
			glTexCoord2f(1, 0); glVertex3f(size, 2*size, size);
			glTexCoord2f(0.5, 1);glVertex3f(0 * size, 3 * size, size);
		glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
//----END----cherdak-----



//----START----roof-----
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, TextNames[ROOF]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_LINEAR_MIPMAP_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glColor3f(0, 0, 0);

	glPushMatrix();
		glTranslatef(size+0.3, 2 * size-0.3, 2.5 * (-size)/2);
		glRotatef(45, 0, 0, 1);
		drawObj(1, 1, 2.5 * size, 1.84 * size, 20, 0);
	glPopMatrix();

	glPushMatrix();
		glRotatef(180, 0, 1, 0);
		glTranslatef(size + 0.3, 2 * size - 0.3, 2.5 * (-size) / 2);
		glRotatef(45, 0, 0, 1);
		drawObj(1, 1, 2.5 * size, 1.84 * size, 20, 0);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
//----END----roof-----
}

void drawRoad(int gsize, float size)
{
	//float size = 1.f;
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, TextNames[ROAD]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_LINEAR_MIPMAP_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// ��������� �������� ������������ ���������� ������� �� �������
	//glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);
	//glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);
	//��� ��������� ������-�� ������ �� ������������...

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glColor3f(0, 0, 0);

	//glBegin(GL_QUADS);
	//	//glColor3f(randomFlt(), randomFlt(), randomFlt());
	//	glColor3f(0, 0, 0);
	//	//top  
	//	glTexCoord2f(0, 0);
	//	glVertex3f(0, 0,0);
	//	glTexCoord2f(1, 0);
	//	glVertex3f(size, 0, 0);
	//	glTexCoord2f(1, 5);
	//	glVertex3f(size, 0, -2*gsize);//gsize
	//	glTexCoord2f(0, 5);
	//	glVertex3f(0, 0, -2*gsize);
	//glEnd();
	glPushMatrix();
		glRotatef(90, 0, 1, 0);
		glRotatef(90, 0, 0, 1);
		glTranslatef(0, -gsize, 0);
		
		drawObj(1, 5, size, 2 * gsize, 40, 0);//left
		//drawObj(1, 1, 2 * gsize, 2 * gsize, 20, -size);//right
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

}


void drawSnowman(float size)
{
	GLUquadricObj* quadricObj = gluNewQuadric();

	GLfloat mat_diffuse_white[] = { 1.0,1.0,1.0,1.0 };
	GLfloat mat_diffuse_red[] = { 1.0,0.0,0.0,1.0 };
	GLfloat mat_diffuse_black[] = { 0.0,0.0,0.0,1.0 };

	GLfloat mat_specular_white[] = { 1.0,1.0,1.0,1.0 };
	GLfloat mat_specular_red[] = { 1.0,0.0,0.0,1.0 };
	GLfloat mat_specular_black[] = { 0.0,0.0,0.0,1.0 };

	GLfloat color_white[] = { 1.0,1.0,1.0,1.0 };
	GLfloat color_red[] = { 1.0,0.0,0.0,1.0 };
	GLfloat color_black[] = { 0.0,0.0,0.0,1.0 };

// ----START----snowman------------------
	glPushMatrix();
	glTranslatef(0, 0.7*size, 0);		//��������� ����� 
	//glRotatef(stepman, 0, 1, 0);

	//glTranslatef(1.0, -0.0, -0.0);		//��������� ����� 
	//glTranslatef(1 * sin(stepman), -1.0*1 * cos(stepman), -9.0);		//��������� ����� 
	glColor3f(0.746, 0.832, 0.797);
	//GLfloat color_mat1[] = { 0.746, 0.832, 0.797,1.0 };
	GLfloat color_mat1[] = { 0.5, 0.5, 0.5,1.0 };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color_white);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_def);
	//glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat_specular);
	glMaterialfv(GL_FRONT, GL_SPECULAR, color_white);

	//gluQuadricTexture(quadricObj, GL_TRUE);
	//glEnable(GL_TEXTURE_2D);
	//glBindTexture(GL_TEXTURE_2D, TextNames[SPACE]);
	////glMaterialfv(GL_FRONT, GL_AMBIENT, glTexAmbientFlore);
	////glMaterialfv(GL_FRONT, GL_DIFFUSE, glTexDiffuseFlore);
	////glMaterialfv(GL_FRONT, GL_SPECULAR, glTexShineFlore);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_LINEAR_MIPMAP_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_LINEAR_MIPMAP_LINEAR);
	////glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	////glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	//glutSolidSphere(0.7, 99, 99);
	glPushMatrix();
		glRotated(-90, 1, 0, 0);
		gluSphere(quadricObj, 0.7*size, 16, 16);
	glPopMatrix();

	//glDisable(GL_TEXTURE_2D);

	glPushMatrix();
	glTranslatef(0.0, 1.15 * size, 0.0);		//��������� ����� 
	glColor3f(0.746, 0.832, 0.797);
	glutSolidSphere(0.45 * size, 99, 99);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 1.9 * size, 0.0);		//��������� ����� 
	glColor3f(0.746, 0.832, 0.797);
	glutSolidSphere(0.3 * size, 99, 99);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0.09 * size, 1.95 * size, 0.24 * size);		//��������� ����� 
		//glColor3f(0, 0, 0);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse_black);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular_black);
		glutSolidSphere(0.05 * size, 99, 99);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.09 * size, 1.95 * size, 0.24 * size);		//��������� ����� 
	glColor3f(0, 0, 0);
	glutSolidSphere(0.05 * size, 99, 99);
	glPopMatrix();

	glPushMatrix();
	//glScalef(TYPE kx, TYPE ky, TYPE kz);
	glTranslatef(0.00, 1.85 * size, 0.28 * size);		//��������� ����� 
	glColor3f(1, 0.549, 0);
	GLfloat color_mat3[] = { 1.0,0.0,0.0,1.0 };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color_mat3);
	glMaterialfv(GL_FRONT, GL_SPECULAR, color_mat3);
	gluQuadricDrawStyle(quadricObj, GLU_FILL);
	gluCylinder(quadricObj, 0.05 * size, 0, 0.15 * size, 99, 99);
	glPopMatrix();
	//glRotatef(-stepman, 0, 1, 0);
	glPopMatrix();
	//gluDeleteQuadric(quadricObj);
//---END---snowman------------------
}

GLvoid DrawGLScene(float h_angle, float v_angle, float h_cam, float v_cam, float stepman)
{
	/*float size = 1.0f;*/
	float size = 0.5f;
	GLUquadricObj* quadricObj = gluNewQuadric();

	//GLfloat no_mat[] = { 0.0,0.0,0.0,1.0 };
	//GLfloat mat_ambient_def[] = { 0.2, 0.2, 0.2, 1.0 };
	//GLfloat mat_ambient[] = { 0.8,0.8,0.2,1.0 };

	//GLfloat mat_diffuse_def[] = { 0.8, 0.8, 0.8, 1.0 };
	//GLfloat mat_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	//GLfloat mat_diffuse_white[] = { 1.0,1.0,1.0,1.0 };
	//GLfloat mat_diffuse_red[] = { 1.0,0.0,0.0,1.0 };
	//GLfloat mat_diffuse_black[] = { 0.0,0.0,0.0,1.0 };
	//
	//GLfloat no_shininess[] = { 0.0 };
	//GLfloat low_shininess[] = { 5.0 };
	//GLfloat high_shininess[] = { 100.0 };

	//GLfloat mat_emission[] = { 0.3,0.2,0.2,0.0 };

	//GLfloat no_mat_specular[] = { 0.0,0.0,0.0,1.0 };
	//GLfloat mat_specular_def[] = { 0.0, 0.0, 0.0, 1.0 };
	//GLfloat mat_specular_white[] = { 1.0,1.0,1.0,1.0 };
	//GLfloat mat_specular_red[] = { 1.0,0.0,0.0,1.0 };
	//GLfloat mat_specular_black[] = { 0.0,0.0,0.0,1.0 };


	//GLfloat color_white[] = { 1.0,1.0,1.0,1.0 };
	//GLfloat color_red[] = { 1.0,0.0,0.0,1.0 };
	//GLfloat color_black[] = { 0.0,0.0,0.0,1.0 };

	glClearColor(0.0, 0.0, 0.0, 0.0);

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_def);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse_def);
	//glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse_white);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular_def);
	//glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular_white);
	glMaterialf(GL_FRONT, GL_SHININESS, 90);

	//glMaterialfv(GL_BACK, GL_AMBIENT_AND_DIFFUSE, color_black);




	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);


	//Light0 modes
	GLfloat glLight0_ambient[] = { 0.0,0.0,0.0,1.0 };
	//GLfloat glLight0_ambient[] = { 0.5,0.5,0.5,1.0 };
	GLfloat glLight0_diffuse[] = { 1,1,1,1 };
	GLfloat glLight0_specular[] = { 1,1,1,1 };
	GLfloat glLight0_position[] = { 0,0,1,0 };
	//GLfloat glLight0_position[] = { 0,2,1,1 };
	//set light0------------------------------
	//glEnable(GL_LIGHT0);
	//glLightfv(GL_LIGHT0, GL_AMBIENT, glLight0_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, glLight0_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, glLight0_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, glLight0_position);

	//set light1
	GLfloat glLight1_ambient[] = { 0.2,0.2,0.2,1.0 };
	GLfloat glLight1_diffuse[] = { 0.8,0.8,0.8,1 };
	GLfloat glLight1_specular[] = { 0.8,0.8,0.8,1 };
	//GLfloat glLight1_position[] = { 0, 15, 7, 1 };
	GLfloat glLight1_position[] = { 5, 5, 5, 1 };
	if (flag_GL_LIGHT1)
		glEnable(GL_LIGHT1);
	else
		glDisable(GL_LIGHT1);
	//glEnable(GL_LIGHT1);
	glLightfv(GL_LIGHT1, GL_AMBIENT, glLight1_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, glLight1_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, glLight1_specular);
	glLightfv(GL_LIGHT1, GL_POSITION, glLight1_position);

	//set light2
	GLfloat glLight2_ambient[] = { 0.2,0.2,0.2,1.0 };
	GLfloat glLight2_diffuse[] = { 1,1,1,1 };
	GLfloat glLight2_specular[] = { 1,1,1,1 };
	GLfloat glLight2_position[] = { 2,2,-12,1 };
	if (flag_GL_LIGHT2)
		glEnable(GL_LIGHT2);
	else
		glDisable(GL_LIGHT2);
	glLightfv(GL_LIGHT2, GL_AMBIENT, glLight2_ambient);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, glLight2_diffuse);
	glLightfv(GL_LIGHT2, GL_SPECULAR, glLight2_specular);
	glLightfv(GL_LIGHT2, GL_POSITION, glLight2_position);

	//set light3
	GLfloat glLight3_ambient[] = { 0.2,0.2,0.2,1.0 };
	GLfloat glLight3_diffuse[] = { 1,1,1,1 };
	GLfloat glLight3_specular[] = { 1,1,1,1 };
	GLfloat glLight3_position[] = { 0,5,5,1 };
	GLfloat spot_direction3[] = { 0, -1.0, 0.0 };
	glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 45.0);
	glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, spot_direction3);
	glLightf(GL_LIGHT3, GL_SPOT_EXPONENT, 2.0);
	//glEnable(GL_LIGHT3);
	if (flag_GL_LIGHT3)
		glEnable(GL_LIGHT3);
	else
		glDisable(GL_LIGHT3);
	glLightfv(GL_LIGHT3, GL_AMBIENT, glLight3_ambient);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, glLight3_diffuse);
	glLightfv(GL_LIGHT3, GL_SPECULAR, glLight3_specular);
	glLightfv(GL_LIGHT3, GL_POSITION, glLight3_position);
	

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity(); 			//����� ���� ������ � 1
	gluPerspective(_zoom, (float)1366 / 768, 0.1f, 40.0f);
	//glRotatef(r_object, 0, 1, 0);
	//glRotatef(v_cam, 1, 0, 0);
	////glFrustum(-1, 1, -1, 1, 1, 5);	//������� ���������
	////glFrustum(-0.85, 0.85, -0.7, 0.7, 3, 12);	//������� ��������

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(0.0, -1.0, 0.0);
	//�������� ����� � �������������� � ������������ ���������
	
	//glRotatef(v_cam, 1, 0, 0);
	//glRotatef(r_object, 0, 1, 0);
	//glTranslatef(0.0, 0.0, -9.0);
	//glTranslatef(0.0, 0.0, 9.0);
	

	//glRasterPos2d(0, 0);
	//glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	//glPixelZoom(1.0, 1.0);
	//glDrawPixels(TextureMass[1]->sizeX, TextureMass[1]->sizeY,GL_RGB, GL_UNSIGNED_BYTE, TextureMass[1]->data);

	GLfloat gsize = 20.0;
	float x = (gsize-1) * cos(v_cam * PI / 180) * sin(r_object * PI / 180);
	float y = (gsize - 1) * sin(v_cam * PI / 180);
	float z = (gsize - 1) * cos(v_cam * PI / 180) * cos(r_object * PI / 180);
	gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	//glTranslatef(-x, -y, -z);

	//gluLookAt(-1.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	//glTranslatef(0.0, -1.0, -9.0);		//��������� ����� 
	////--------------------------
	//glRotatef(h_angle, 0, 1, 0);
	//glRotatef(v_angle, 1, 0, 0);
	////--------------------------
	//drawQube();

//---START---XYZ------------------
	glDisable(GL_LIGHTING);
	glLineWidth(3);       // ������ ����� ������������� 1

	glPushMatrix();
		//glTranslatef(0.0, 0.0, -9.0);
		glBegin(GL_LINES);
			glColor3d(1, 0, 0);     // ������� ����
			glVertex3d(0, 0, 0);
			glVertex3d(10, 0, 0); // ������ �����

			glColor3d(0, 1, 0);     // �������
			glVertex3d(0, 0, 0); // ������ �����
			glVertex3d(0, 10, 0);
		glEnd();
	glPopMatrix();
	glEnable(GL_LIGHTING);
//---END---XYZ------------------


//---START---sky	
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_def);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse_def);
	//glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse_white);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular_def);
	//glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular_white);
	glMaterialf(GL_FRONT, GL_SHININESS, 90);

	//glMaterialfv(GL_BACK, GL_AMBIENT_AND_DIFFUSE, color_black);


	gluQuadricTexture(quadricObj, GL_TRUE);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, TextNames[SKY]);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_LINEAR_MIPMAP_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	GLdouble equation[4] = { 0,1,0,0.1 };

	glEnable(GL_CLIP_PLANE0);
	glClipPlane(GL_CLIP_PLANE0, equation);
	glPushMatrix();
		//glTranslatef(0.0, 0.0, -9.0);
		glRotated(-90, 0, 0, 1);
		gluSphere(quadricObj, gsize, 99, 99);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
//---END---sky------------------

//---START---road------------------
	static GLfloat xyzRoad[] = { 4, 0.005, 0 };
	glPushMatrix();
		glTranslatef(xyzRoad[0], xyzRoad[1], xyzRoad[2]);
		drawRoad(gsize, 5*size);
	glPopMatrix();

//---END---road------------------

//---START---ground------------------

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_def);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse_def);
	//glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse_white);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular_def);
	//glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular_white);
	glMaterialf(GL_FRONT, GL_SHININESS, 90);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, TextNames[SAND]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_LINEAR_MIPMAP_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glColor3f(0, 0, 0);

	glPushMatrix();
		glTranslatef(gsize, 0.0, -gsize);
		glRotatef(90, 0, 0, 1);
		drawObj(1, 1, 2 * gsize, 2 * gsize, 40, 0);//left
		//drawObj(1, 1, 2 * gsize, 2 * gsize, 20, -size);//right
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
//---END---ground------------------

////---START---road------------------
//	static GLfloat xyzRoad[] = { 4, 0.05, gsize };
//	glPushMatrix();
//		glTranslatef(xyzRoad[0], xyzRoad[1], xyzRoad[2]);
//		drawRoad(gsize, size);
//	glPopMatrix();
//
////---END---road------------------

//---START---car1----drive-----
	GLfloat color_matCar[] = { 1.0,0.0,0.0,1.0 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_def);
	//glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color_matCar);
	glMaterialfv(GL_FRONT, GL_SPECULAR, color_matCar);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_def);
	glMaterialfv(GL_BACK, GL_AMBIENT_AND_DIFFUSE, color_black);

	static GLfloat xyzCar1[] = { 0,0,gsize };
	glPushMatrix();

		if (xyzCar1[2] < -gsize)
			xyzCar1[2] = gsize;

		xyzCar1[2] -= 0.05;
		glTranslatef(xyzRoad[0] + size*5*3/4 , 0.0, 0.0);		//��������� ����� 
		glTranslatef(xyzCar1[0], xyzCar1[1], xyzCar1[2]);		//���������� ������
		glRotatef(90, 0, 1, 0);
		drawCar1(size);
	glPopMatrix();
//---END---car1----drive-----

//---START---car2----drive-----
	static GLfloat xyzCar2[] = { 0,0,-gsize };

	color_matCar[0] = 1.0;
	color_matCar[1] = 1.0;
	color_matCar[2] = 0.0;
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color_matCar);
	glMaterialfv(GL_FRONT, GL_SPECULAR, color_matCar);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_def);
	glMaterialfv(GL_BACK, GL_AMBIENT_AND_DIFFUSE, color_black);

	glPushMatrix();
		if (xyzCar2[2] > gsize)
			xyzCar2[2] = -gsize;

		xyzCar2[2] += 0.05;
		glTranslatef(xyzRoad[0] + size *5/ 4, 0.0, 0.0);		//��������� ����� 
		glTranslatef(xyzCar2[0], xyzCar2[1], xyzCar2[2]);		//���������� ������
		glRotatef(-90, 0, 1, 0);
		drawCar1(size);
	glPopMatrix();
//---END---car2----drive-----


//---START---car3----drive-----
	//static GLfloat xyzCar3[] = { 0,0,0 };
	color_matCar[0] = 1.0;
	color_matCar[1] = 0.0;
	color_matCar[2] = 1.0;
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color_matCar);
	glMaterialfv(GL_FRONT, GL_SPECULAR, color_matCar);

	if (xCar > gsize-2)
		xCar = gsize-2;

	if (xCar < -gsize + 2)
		xCar = -gsize + 2;

	if (zCar > gsize - 2)
		zCar = gsize - 2;

	if (zCar < -gsize + 2)
		zCar = -gsize + 2;

	glPushMatrix();
		//xyzCar2[2] += 0.01;
	//glTranslatef(0, 0.0, 0);
		//glTranslatef(xCar* cos(h_angle * PI / 180), 0.0, xCar* sin(h_angle * PI / 180));		//��������� ����� 

		//if (prevCar==curCar)
		//	glRotatef(prevCar, 0, 1, 0);
		//else
		//	glRotatef(curCar-prevCar, 0, 1, 0);


		xCar += deltaCar * cos(h_angle * PI / 180);
		zCar += deltaCar * sin(h_angle * PI / 180);
		//myfile << "xCar " << xCar <<"zCar " << zCar << "h_angle"<< h_angle<<std::endl;


		//glRotatef(h_angle, 0, 1, 0);
		//glTranslatef(xCar*cos(h_angle *PI/180), 0.0, xCar * sin(h_angle * PI / 180));
		glTranslatef(xCar, 0.0, zCar);
		glRotatef(-h_angle, 0, 1, 0);
		//glRotatef(v_angle, 1, 0, 0);
		//drawCar1(size);
		deltaCar = 0.0;
		//prevCar = curCar;
	glPopMatrix();

//---END---car3----drive-----

////---START---car4----drive-----
	static GLfloat xyzCar4[] = { 0,0,-gsize };

	color_matCar[0] = 1.0;
	color_matCar[1] = 0.0;
	color_matCar[2] = 0.0;
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color_matCar);
	glMaterialfv(GL_FRONT, GL_SPECULAR, color_matCar);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_def);
	glMaterialfv(GL_BACK, GL_AMBIENT_AND_DIFFUSE, color_black);

	if (xCar > gsize - 2)
		xCar = gsize - 2;

	if (xCar < -gsize + 2)
		xCar = -gsize + 2;

	if (zCar > gsize - 2)
		zCar = gsize - 2;

	if (zCar < -gsize + 2)
		zCar = -gsize + 2;

	xCar += deltaCar * cos(h_angle * PI / 180);
	zCar += deltaCar * sin(h_angle * PI / 180);




	glPushMatrix();
		glTranslatef(xCar, 0.0, zCar);
		glRotatef(-h_angle, 0, 1, 0);
		drawCar1(2*size);
		deltaCar = 0.0;
	glPopMatrix();
////---END---car4----drive-----

////---START---snowman------------------

	glPushMatrix();
		glTranslatef(-4.5, 0.0, 4.0);		//��������� ����� 
		glRotatef(stepman, 0, 1, 0);
		glTranslatef(1.0, -0.0, -0.0);
		drawSnowman(size);

	glPopMatrix();
////---END---snowman------------------

////---START---telega----from-----function---------
//		//glTranslatef(-1.0, -0.0, -0.0);
//	glPushMatrix();
//		//glTranslatef(0.0, -0.0, -0.0);		//��������� �����
//		//glRotatef(r_object, 0, 1, 0);
//		//glRotatef(v_cam, 1, 0, 0);
//		glTranslatef(2, 0.0, -9.0);		//��������� ����� 
//		glRotatef(h_angle, 0, 1, 0);
//		glRotatef(v_angle, 1, 0, 0);
//		glRotatef(-180, 0, 1, 0);
//		drawCar(size);
//	glPopMatrix();
////---END---telega----from-----function---------


//---START---HOME------------------
		glPushMatrix();
			//glTranslatef(0.0, -0.0, -0.0);		//��������� �����
			//glRotatef(r_object, 0, 1, 0);
			//glRotatef(v_cam, 1, 0, 0);
			glTranslatef(2.0, 0.0, -13.0);		//��������� ����� 
			//glRotatef(h_angle, 0, 1, 0);
			//glRotatef(v_angle, 1, 0, 0);
			glRotatef(-20, 0, 1, 0);

			drawHome();

		glPopMatrix();
//---END---HOME------------------
		
//---START---HOME1------------------
		glPushMatrix();
		//glTranslatef(0.0, -0.0, -0.0);		//��������� �����
		//glRotatef(r_object, 0, 1, 0);
		//glRotatef(v_cam, 1, 0, 0);
		glTranslatef(-2.0, 0.0, -13.0);		//��������� ����� 
		//glRotatef(h_angle, 0, 1, 0);
		//glRotatef(v_angle, 1, 0, 0);
		//glRotatef(-20, 0, 1, 0);

		drawHome1();

		glPopMatrix();
//---END---HOME------------------
}

LRESULT CALLBACK WndProc(HWND	hWnd,
	UINT	message,
	WPARAM	wParam,
	LPARAM	lParam)
{
	RECT	Screen;
	// ������������ ������� ��� �������� ����
	GLuint	PixelFormat;
	static	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		// ������ ���� ���������
		1,			// ����� ������ 
		PFD_DRAW_TO_WINDOW |	// ������ ��� ����
		PFD_SUPPORT_OPENGL |	// ������ ��� OpenGL
		PFD_DOUBLEBUFFER,	// ������ ��� �������� ������
		PFD_TYPE_RGBA,		// ��������� RGBA ������
		16,			// ����� 16 ��� ������� �����
		0, 0, 0, 0, 0, 0,   // ������������� �������� ����� 
		0,			// ��� ������ ������������
		0,			// ��������� ��� ������������ 
		0,			// ��� ������ �����������
		0, 0, 0, 0,	// ���� ����������� ������������ 
		16,		// 16 ������ Z-����� (����� �������)  
		0,			// ��� ������ ���������
		0,		// ��� ��������������� ������� 
		PFD_MAIN_PLANE,		// ������� ���� ���������
		0,			// ������ 
		0, 0, 0			// ����� ���� ������������ 
	};

	switch (message)	// ��� ���������
	{
	case WM_CREATE:
		hDC = GetDC(hWnd);
		// �������� �������� ���������� ��� ����
		PixelFormat = ChoosePixelFormat(hDC, &pfd);
		// ����� ��������� ���������� ��� ������� ��������
		if (!PixelFormat)
		{
			MessageBox(0, "�� ������ ���������� ������ �������.",
				"������", MB_OK | MB_ICONERROR);
			PostQuitMessage(0);
			// ��� ��������� �������, ���
			// ��������� ������ �����������
			break;		// �������������� ������� ����
		}

		if (!SetPixelFormat(hDC, PixelFormat, &pfd))
		{
			MessageBox(0, "������ ������� �� ����������.",
				"������", MB_OK | MB_ICONERROR);
			PostQuitMessage(0);
			break;
		}

		hRC = wglCreateContext(hDC);
		if (!hRC)
		{
			MessageBox(0, "�������� ��������������� �� ������.",
				"������", MB_OK | MB_ICONERROR);
			PostQuitMessage(0);
			break;
		}

		if (!wglMakeCurrent(hDC, hRC))
		{
			MessageBox(0, "���������� �������������� GLRC.",
				"������", MB_OK | MB_ICONERROR);
			PostQuitMessage(0);
			break;
		}

		//Generating names for textures
		glGenTextures(20, TextNames);

		//Load Flore texture
		for (int i = 0; i < 14; i++)
		{
			ImRect1 = auxDIBImageLoad(TextureFiles[i]);
			glBindTexture(GL_TEXTURE_2D, TextNames[i]);
			gluBuild2DMipmaps(GL_TEXTURE_2D, 3, ImRect1->sizeX, ImRect1->sizeY, GL_RGB, GL_UNSIGNED_BYTE, ImRect1->data);
			TextureMass[i] = ImRect1;
		}


		GetClientRect(hWnd, &Screen);
		InitGL(Screen.right, Screen.bottom);
		myfile.open("log.txt");
		myfile << "Writing this to a file.\n";
		break;

	case WM_DESTROY:
	case WM_CLOSE:
		myfile.close();
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
		//case VK_LEFT:
		//	h_angle += 10.0;
		//	break;
		//case VK_RIGHT:
		//	h_angle -= 10.0;
		//	break;
		//case VK_UP:
		//	v_angle += 10.0;
		//	break;
		//case VK_DOWN:
		//	v_angle -= 10.0;
		//	break;

		case VK_LEFT:
			h_angle -= 1.0;
			break;
		case VK_RIGHT:
			h_angle += 1.0;
			break;
		case VK_UP:
			//xCar += 0.1;
			deltaCar = 0.1;
			break;
		case VK_DOWN:
			//xCar -= 0.1;
			deltaCar = -0.1;
			break;

		case 0x41: //key A
			r_object -= 2.0;
			break;
		case 0x44: //key D
			r_object += 2.0;
		break;
		case 0x57: //key W
			v_cam += 2.0;
			break;
		case 0x53: //key S
			v_cam -= 2.0;
			break;

		case 0x50: //key P
			v_angle += 10.0;
			zCar -= 0.1;
			curCar = 90;
			break;
		case VK_OEM_1: //key  ';:'
			v_angle -= 10.0;
			zCar += 0.1;
			curCar = 270;
			break;
		case 0x4C: //key L
			xCar -= 0.1;
			curCar = 180;
			break;
		case VK_OEM_7: //key ' " '
			xCar += 0.1;
			curCar = 0;
			break;

		case VK_OEM_PLUS:
			_zoom -= 5.0;
			if (_zoom < 5) _zoom = 5;
			break;
		case VK_OEM_MINUS:
			_zoom += 5.0;
			if (_zoom > 175) _zoom = 175;
			break;
		case 0x31:
			flag_GL_LIGHT1 = !flag_GL_LIGHT1;
			break;
		case 0x32:
			flag_GL_LIGHT2 = !flag_GL_LIGHT2;
			break;
		case 0x33:
			flag_GL_LIGHT3 = !flag_GL_LIGHT3;
			break;
		default:
			break;
		}

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
	MSG		msg;	// ��������� ��������� Windows
	WNDCLASS	wc; 	// ��������� ������ Windows 
				// ��� ��������� ���� ����
	HWND	hWnd;	// ���������� ����������� ����
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
		MessageBox(0, "������ ����������� ������ ����.",
			"������", MB_OK | MB_ICONERROR);
		return FALSE;
	}

	hWnd = CreateWindow(
		"OpenGL WinClass",
		"��� ����������� ��������� OpenGL",
		// ��������� ������ ����
		WS_POPUP |
		WS_CLIPCHILDREN |
		WS_CLIPSIBLINGS,
		0, 0,		// ������� ���� �� ������
		1366, 768,		// ������ � ������ ����
		NULL,
		NULL,
		hInstance,
		NULL);

	if (!hWnd)
	{
		MessageBox(0, "������ �������� ����.",
			"������", MB_OK | MB_ICONERROR);
		return FALSE;
	}
	DEVMODE dmScreenSettings;	// ����� ������
	memset(&dmScreenSettings, 0, sizeof(DEVMODE));
	// ������� ��� �������� ���������
	dmScreenSettings.dmSize = sizeof(DEVMODE);
	// ������ ��������� Devmode
	dmScreenSettings.dmPelsWidth = 1366;
	// ������ ������
	dmScreenSettings.dmPelsHeight = 768;
	// ������ ������
	dmScreenSettings.dmFields = DM_PELSWIDTH |
		DM_PELSHEIGHT;
	// ����� �������
	ChangeDisplaySettings(&dmScreenSettings,
		CDS_FULLSCREEN);
	// ������������ � ������ �����
	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);
	SetFocus(hWnd);

	while (1)
	{
		// ��������� ���� ���������
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
		DrawGLScene(h_angle, v_angle, h_cam, v_cam,stepman);  // ���������� �����
		SwapBuffers(hDC);	// ����������� ����� ������
		if (keys[VK_ESCAPE]) SendMessage(hWnd, WM_CLOSE, 0, 0);
		// ���� ESC - �����
	}
}


