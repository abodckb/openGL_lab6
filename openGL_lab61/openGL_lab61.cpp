#include <windows.h>	
// ������������ ���� ��� Windows
#include <gl\gl.h>		
	// ������������ ���� ��� ���������� OpenGL32 
#include <gl\glu.h>		
	// ������������ ���� ��� ���������� GLu32 
//#include <gl\glaux.h>		
	// ������������ ���� ��� ���������� GLaux 
#include <gl\glut.h>	


#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <fstream>

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
float _zoom = 30.0;

GLvoid InitGL(GLsizei Width, GLsizei Height)	//������� ����� �������� ���� GL
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	// ������� ������ � ����� ����
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


void DrawWheels()
{
	GLUquadricObj* quadricObj = gluNewQuadric();
	//glClear(GL_COLOR_BUFFER_BIT);

	glPushMatrix();
	//glRotatef(30, 0, 1, 0);
	//glTranslatef(0, -0.1, -0.2);
	glColor3f(1, 0, 0);
	//gluQuadricDrawStyle(quadricObj, GLU_LINE);
	gluQuadricDrawStyle(quadricObj, GLU_FILL);
	gluCylinder(quadricObj, 0.1, 0.1, 0.1, 30, 3);
	glPopMatrix();

	glPushMatrix();
	//glRotatef(90, 1, 0, 0);
	//glTranslatef(0.0, 0.0, -0.2);
	glColor3f(1, 0, 1);
	//gluQuadricDrawStyle(quadricObj, GLU_LINE);
	gluQuadricDrawStyle(quadricObj, GLU_FILL);
	gluCylinder(quadricObj, 0.3, 0.3, 0.1, 30, 3);
	glPopMatrix();

	GLUquadricObj* quadricObjDisk = gluNewQuadric();
	glPushMatrix();
	//glRotatef(60, 0, 1, 0);
	//glTranslatef(0.0, 0.0, 0.0);
	glColor3f(0, 0, 1);
	//gluQuadricDrawStyle(quadricObjDisk, GLU_LINE);
	gluQuadricDrawStyle(quadricObjDisk, GLU_FILL);
	gluDisk(quadricObjDisk, 0.1, 0.3, 10, 3);
	glPopMatrix();

	//GLUquadricObj* quadricObjDisk = gluNewQuadric();
	glPushMatrix();
	//glRotatef(60, 0, 1, 0);
	glTranslatef(0.0, 0.0, 0.1);
	glColor3f(0, 0, 0);
	//gluQuadricDrawStyle(quadricObjDisk, GLU_LINE);
	gluQuadricDrawStyle(quadricObjDisk, GLU_FILL);
	gluDisk(quadricObjDisk, 0.1, 0.3, 10, 3);
	glPopMatrix();

	gluDeleteQuadric(quadricObj);
	gluDeleteQuadric(quadricObjDisk);
}

void DrawLine() {
	glBegin(GL_LINES);
	glVertex3f(-1, 0, 0);
	glVertex3f(1, 0, 0);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(-0.05, 0, 0);
	glVertex3f(-0.05, 0.05, 0);
	glVertex3f(0.05, 0.05, 0);
	glVertex3f(0.05, 0, 0);
	glEnd();
	float pos = -0.5;
	glBegin(GL_POLYGON);
	glVertex3f(pos - 0.05, 0, 0);
	glVertex3f(pos - 0.05, 0.05, 0);
	glVertex3f(pos + 0.05, 0.05, 0);
	glVertex3f(pos + 0.05, 0, 0);
	glEnd();
	pos = 0.5;
	glBegin(GL_POLYGON);
	glVertex3f(pos - 0.05, 0, 0);
	glVertex3f(pos - 0.05, 0.05, 0);
	glVertex3f(pos + 0.05, 0.05, 0);
	glVertex3f(pos + 0.05, 0, 0);
	glEnd();
}

void drawQube()
{
	float size = 1.f;
	glBegin(GL_QUADS);

	//glColor3f(randomFlt(), randomFlt(), randomFlt());
	//float _cred = randomFlt();
	//float _cgreen = randomFlt();
	//float _cblue = randomFlt();
	//glColor3f(_cred, _cgreen, _cblue);
	glColor3f(1.0, 0.0, 0.0);


	//front
	glVertex3f(-size, -size, size);
	glVertex3f(size, -size, size);
	glVertex3f(size, size, size);
	glVertex3f(-size, size, size);
	glEnd();

	glBegin(GL_QUADS);
	//glColor3f(randomFlt(), randomFlt(), randomFlt());
	glColor3f(0.0, 0.0, 0.0);
	//back
	glVertex3f(-size, -size, -size);
	glVertex3f(-size, size, -size);
	glVertex3f(size, size, -size);
	glVertex3f(size, -size, -size);
	glEnd();


	glBegin(GL_QUADS);
	//glColor3f(randomFlt(), randomFlt(), randomFlt());
	glColor3f(0.0, 1.0, 0.0);
	//left
	glVertex3f(-size, -size, size);
	glVertex3f(-size, -size, -size);
	glVertex3f(-size, size, -size);
	glVertex3f(-size, size, size);
	glEnd();


	glBegin(GL_QUADS);
	//glColor3f(randomFlt(), randomFlt(), randomFlt());
	glColor3f(0.6, 0.6, 0.0);
	//right
	glVertex3f(size, -size, -size);
	glVertex3f(size, -size, size);
	glVertex3f(size, size, size);
	glVertex3f(size, size, -size);
	glEnd();


	glBegin(GL_QUADS);
	//glColor3f(randomFlt(), randomFlt(), randomFlt());
	glColor3f(0.4, 0.4, 0.0);
	//bottom
	glVertex3f(-size, -size, size);
	glVertex3f(size, -size, size);
	glVertex3f(size, -size, -size);
	glVertex3f(-size, -size, -size);
	glEnd();


	glBegin(GL_QUADS);
	//glColor3f(randomFlt(), randomFlt(), randomFlt());
	glColor3f(0.2, 0.2, 0.2);
	//top  		
	glVertex3f(-size, size, -size);
	glVertex3f(size, size, -size);
	glVertex3f(size, size, size);
	glVertex3f(-size, size, size);
	glEnd();
}


void DrawLight(void)
{
	int w = 1366;
	int h = 768;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluPerspective(30.0f, (float)1366 / 768, 6.f, 12.0f);
	//glTranslatef(0.0, 0.0, -1.);
	glOrtho(-1.5 * (GLfloat)w / (GLfloat)h, 1.5 * (GLfloat)w / (GLfloat)h, -1.5, 1.5, -10.0, 10.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//LIGHT0
	GLfloat light_ambient[] = { 0.0,0.0,1.0,1.0 };
	GLfloat light_diffuse[] = { 1.0,1.0,1.0,1.0 };
	GLfloat light_specular[] = { 1.0,1.0,1.0,1.0 };
	GLfloat light_position[] = { 1.0,1.0,1.0,0.0 };

	GLfloat mat_specular[] = { 1.0,1.0,1.0,1.0 };
	GLfloat mat_shininess[] = { 80.0 };
	//GLfloat white_light[] = { 1.0,1.0,1.0,1.0 };

	glClearColor(0.0, 0.0, 0.0, 0.0);

	glShadeModel(GL_SMOOTH);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	//glEnable(GL_LIGHT1);
	glEnable(GL_DEPTH_TEST);

	glutSolidSphere(1.0, 40, 16);
}

void DrawLight1(void)
{
	int w = 1366;
	int h = 768;
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluPerspective(30.0f, (float)1366 / 768, 6.f, 12.0f);
	//glTranslatef(0.0, 0.0, -8.);
	glOrtho(-1.5 * (GLfloat)w / (GLfloat)h, 1.5 * (GLfloat)w / (GLfloat)h, -1.5, 1.5, -10.0, 10.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//LIGHT1
	GLfloat light_ambient[] = { 0.2,0.2,0.2,1.0 };
	GLfloat light_diffuse[] = { 1.0,1.0,1.0,1.0 };
	GLfloat light_specular[] = { 1.0,1.0,1.0,1.0 };
	//GLfloat light_position[] = { -2.0,2.0,-1.0,1.0 };
	GLfloat light_position[] = { .0,.0,2.0,1.0 };
	//GLfloat spot_direction[] = { -1.0,1.0,0.0 };
	GLfloat spot_direction[] = { 0.0,0.0,-1.0 };

	//GLfloat mat_specular[] = { 1.0,1.0,1.0,1.0 };
	//GLfloat mat_shininess[] = { 80.0 };

	//glShadeModel(GL_SMOOTH);
	//glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	//glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT1);
	glEnable(GL_DEPTH_TEST);

	glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT1, GL_POSITION, light_position);
	glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1.5);
	glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.5);
	glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.2);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 20.0);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 2.0);

	GLfloat mat_specular[] = { 1.0,1.0,1.0,1.0 };
	GLfloat no_shininess[] = { 0.0 };
	GLfloat low_shininess[] = { 5.0 };
	GLfloat high_shininess[] = { 100.0 };

	//glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
	//glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	//glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	//glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
	//glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

	glutSolidSphere(1., 40, 16);
}

void DrawLight2(void) {
	int w = 1366;
	int h = 768;
	GLdouble spin = 10.0;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluPerspective(30.0f, (float)1366 / 768, 6.f, 12.0f);
//glTranslatef(0.0, 0.0, -1.);
	glOrtho(-1.5 * (GLfloat)w / (GLfloat)h, 1.5 * (GLfloat)w / (GLfloat)h, -1.5, 1.5, 0.01, 10.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//glTranslatef(0.0, 0.0, -9.0);
	//glColor3f(1.0, 0.0, 0.0);

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);

	GLfloat position[] = { 0.0,0.0,1.5,1.0 };

	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
		glTranslatef(0.0, 0.0, -5.0);
		glPushMatrix();
			glRotated((GLdouble)spin, 1.0, 0.0, 0.0);
			glLightfv(GL_LIGHT0, GL_POSITION, position);
			glTranslated(0.0, 0.0, 1.5);
			glDisable(GL_LIGHTING);
			glColor3f(1.0, 1.0, 1.0);
			glutWireCube(0.3);
			//glEnable(GL_LIGHTING);
		glPopMatrix();
		glutSolidTorus(0.275, 0.85, 40, 40);
	glPopMatrix();
}

void DrawLight3(void) {
	int w = 1366;
	int h = 768;
	GLdouble spin = 10.0;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluPerspective(60.0f, (float)1366 / 768, -6.f, 12.0f);
	//glTranslatef(0.0, 0.0, -1.);
	//glOrtho(-1.5 * (GLfloat)w / (GLfloat)h, 1.5 * (GLfloat)w / (GLfloat)h, -1.5, 1.5, -10.0, 10.0);
	glOrtho(-4. * (GLfloat)w / (GLfloat)h, 4. * (GLfloat)w / (GLfloat)h, -4., 4., -1., 10.0);


	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	GLfloat no_mat[] = { 0.0,0.0,0.0,1.0 };
	GLfloat mat_ambient[] = { 0.7,0.7,0.7,1.0 };
	GLfloat mat_ambient_color[] = { 0.8,0.8,0.2,1.0 };
	GLfloat mat_diffuse[] = { 0.1,0.5,0.8,1.0 };
	GLfloat mat_specular[] = { 1.0,1.0,1.0,1.0 };
	GLfloat no_shininess[] = { 0.0 };
	GLfloat low_shininess[] = { 5.0 };
	GLfloat high_shininess[] = { 100.0 };
	GLfloat mat_emission[] = { 0.3,0.2,0.2,0.0 };
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//���������� ������ ����� �����
	glPushMatrix();
		glTranslated(-3.75, 0.0, 0.0);
		glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
		glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
		glutSolidSphere(1.0, 16, 16);
	glPopMatrix();
	//���������� ������ ����� ������ ������
	glPushMatrix();
		glTranslated(-1.25, 0.0, 0.0);
		glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);
		glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
		glutSolidSphere(1.0, 16, 16);
	glPopMatrix();
	//���������� ������ ����� ������ ������ ����
	glPushMatrix();
		glTranslated(1.25, 0.0, 0.0);
		glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
		glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
		glutSolidSphere(1.0, 16, 16);
	glPopMatrix();
	//���������� ��������� ����� ������
	glPushMatrix();
	glTranslated(3.75, 0.0, 0.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
	glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	glutSolidSphere(1.0, 16, 16);
	glPopMatrix();
}


void DrawLight4(void) {
	int w = 1366;
	int h = 768;
	GLdouble spin = 10.0;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluPerspective(60.0f, (float)1366 / 768, -6.f, 12.0f);
	//glTranslatef(0.0, 0.0, -1.);
	//glOrtho(-1.5 * (GLfloat)w / (GLfloat)h, 1.5 * (GLfloat)w / (GLfloat)h, -1.5, 1.5, -10.0, 10.0);
	glOrtho(-15.0 * (GLfloat)w / (GLfloat)h, 15.0 * (GLfloat)w / (GLfloat)h, -15.0, 15.0, -15.0, 15.0);


	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//��������� ����� (���������)
	//GLfloat light_ambient[] = { 0.5,0.3,0.5,1.0 };
	GLfloat light_ambient[] = { 0.0,0.0,0.0,1.0 };
	GLfloat light_diffuse[] = { 1.0,1.0,1.0,1.0 };
	GLfloat light_specular[] = { 1.0,1.0,1.0,1.0 };
	//GLfloat light_position[] = { 8.0,0.0,10.0,0.0 };
	GLfloat light_position[] = { -5.0,0.0,10.0,0.0 };
	//GLfloat spot_direction[] = { 0.0,0.0,-1.0 };

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT1);
	glEnable(GL_DEPTH_TEST);

	//glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT1, GL_POSITION, light_position);
	//glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1.5);
	//glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.5);
	//glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.2);
	//glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 20.0);
	//glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction);
	//glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 2.0);


	//��������� ���������
	GLfloat no_mat[] = { 0.0,0.0,0.0,1.0 };
	GLfloat mat_ambient[] = { 0.7,0.7,0.7,1.0 };
	GLfloat mat_ambient_color[] = { 0.8,0.8,0.2,1.0 };
	GLfloat mat_diffuse_default[] = { 0.8,0.8,0.8,1.0 };	//�������� �� ��������� ��� ���������
	GLfloat mat_diffuse[] = { 1.0,1.0,0.0,1.0 };
	GLfloat no_mat_specular[] = { 0.0,0.0,0.0,1.0 };
	GLfloat mat_specular[] = { 1.0,1.0,1.0,1.0 };
	GLfloat mat_shininess[] = { 93.0 };
	GLfloat no_shininess[] = { 0.0 };	//�������� �� ��������� ��� ���������
	GLfloat low_shininess[] = { 5.0 };
	GLfloat high_shininess[] = { 100.0 };
	GLfloat mat_emission[] = { 0.3,0.2,0.2,0.0 };
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//���������� ������ ����� �����
	glPushMatrix();
	glTranslated(9.0, 4.0, 10.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat_specular);
	//glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
	//glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	glutSolidSphere(2.9, 16, 16);
	glPopMatrix();
	//���������� ������ ����� ������ ������
	glPushMatrix();
	glTranslated(9.0, -4.0, 10.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse_default);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_diffuse_default);
	//glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glutSolidSphere(2.9, 16, 16);
	glPopMatrix();
	
}

//GLvoid DrawGLScene(GLvoid)
GLvoid DrawGLScene(float h_angle, float v_angle, float h_cam, float v_cam)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity(); 			//����� ���� ������ � 1
	//glOrtho(-1, 1, -1, 1, 1, 5);	//������� ���������
	//gluPerspective(30.0f, (float)1366 / 768, 6.f, 12.0f);
	gluPerspective(_zoom, (float)1366 / 768, 6.f, 12.0f);
	glRotatef(r_object, 0, 1, 0);
	glRotatef(v_cam, 1, 0, 0);
	//glFrustum(-1, 1, -1, 1, 1, 5);	//������� ���������
	//glFrustum(-0.85, 0.85, -0.7, 0.7, 3, 12);	//������� ��������

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	//gluLookAt(-1.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glTranslatef(0.0, 0.0, -9.0);		//��������� ����� 
	glRotatef(h_angle, 0, 1, 0);
	glRotatef(v_angle, 1, 0, 0);



	drawQube();

	glPushMatrix();
	glTranslatef(-1.0, -1.0, 1.0);		//��������� ����� 
	DrawWheels();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.0, -1.0, 1.0);		//��������� ����� 
	DrawWheels();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.0, -1.0, -1.0 - 0.1);		//��������� ����� 
	DrawWheels();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.0, -1.0, -1.0 - 0.1);		//��������� ����� 
	DrawWheels();
	glPopMatrix();

	//GLUquadricObj* quadricObj = gluNewQuadric();
	//glClear(GL_COLOR_BUFFER_BIT);

	////glLoadIdentity();
	//
	//glPushMatrix();
	//	//glRotatef(30, 0, 1, 0);
	//	//glTranslatef(0, -0.1, -0.2);
	//	glColor3f(1, 0, 0);
	//		//gluQuadricDrawStyle(quadricObj, GLU_LINE);
	//		gluQuadricDrawStyle(quadricObj, GLU_FILL);
	//		gluCylinder(quadricObj, 0.1, 0.1, 0.1, 30, 3);
	//glPopMatrix();

	//glPushMatrix();
	//	//glRotatef(90, 1, 0, 0);
	//	//glTranslatef(0.0, 0.0, -0.2);
	//	glColor3f(1, 0, 1);
	//		//gluQuadricDrawStyle(quadricObj, GLU_LINE);
	//		gluQuadricDrawStyle(quadricObj, GLU_FILL);
	//		gluCylinder(quadricObj, 0.3, 0.3, 0.1, 30, 3);
	//glPopMatrix();

	//GLUquadricObj* quadricObjDisk = gluNewQuadric();
	//glPushMatrix();
	//	//glRotatef(60, 0, 1, 0);
	//	//glTranslatef(0.0, 0.0, 0.0);
	//	glColor3f(0, 0, 1);
	//		//gluQuadricDrawStyle(quadricObjDisk, GLU_LINE);
	//		gluQuadricDrawStyle(quadricObjDisk, GLU_FILL);
	//		gluDisk(quadricObjDisk, 0.1, 0.3, 10, 3);
	//glPopMatrix();

	////GLUquadricObj* quadricObjDisk = gluNewQuadric();
	//glPushMatrix();
	//	//glRotatef(60, 0, 1, 0);
	//	glTranslatef(0.0, 0.0, 0.1);
	//	glColor3f(0, 0, 0);
	//		//gluQuadricDrawStyle(quadricObjDisk, GLU_LINE);
	//		gluQuadricDrawStyle(quadricObjDisk, GLU_FILL);
	//		gluDisk(quadricObjDisk, 0.1, 0.3, 10, 3);
	//glPopMatrix();
	//glTranslatef(0, 0.1, 0.2);

	//gluDeleteQuadric(quadricObj);
	//gluDeleteQuadric(quadricObjDisk);

//----------------------------------------------------------------------------------------------

	//glDisableClientState(GL_COLOR_ARRAY);
	//glDisableClientState(GL_VERTEX_ARRAY);
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
			if (_zoom > 170) _zoom = 170;
			break;
		case VK_OEM_MINUS:
			_zoom += 10.0;
			if (_zoom < 10) _zoom = 10;
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

	//std::ofstream myfile;
	//myfile.open("example.txt");
	//myfile << "Writing this to a file.\n";

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
		//DrawGLScene(h_angle, v_angle, h_cam, v_cam);  // ���������� �����
		DrawLight4();
		SwapBuffers(hDC);	// ����������� ����� ������
		if (keys[VK_ESCAPE]) SendMessage(hWnd, WM_CLOSE, 0, 0);
		// ���� ESC - �����
	}
	//myfile.close(); //close file
}

