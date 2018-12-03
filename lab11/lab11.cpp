#include "soil.h"
#include "GL/glew.h"
#include "GL/freeglut.h"

#include <iostream>

static int w = 0, h = 0;

GLuint floor_texture_id;
GLuint car_texture_id;
GLuint knuckles_texture_id;
GLuint uganda_texture_id;

GLfloat dist_x = 0, dist_y = 0;
GLfloat angle = 0;

GLfloat cam_dist = 20;
GLfloat ang_hor = 0, ang_vert = -60;

GLfloat no_light[] = { 0, 0, 0, 1 };
GLfloat light[] = { 1, 1, 1, 0 };

double cam_x = 0;
double cam_y = 0;
double cam_z = 0;

float amb[] = { 0.8, 0.8, 0.8 };
float dif[] = { 0.2, 0.2, 0.2 };

const double step = 1;

void loadTextures() {


    floor_texture_id = SOIL_load_OGL_texture("world.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
            SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	car_texture_id = SOIL_load_OGL_texture("ussr.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	knuckles_texture_id = SOIL_load_OGL_texture("knuckles.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	uganda_texture_id = SOIL_load_OGL_texture("uganda.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}

void init() {
    glClearColor(0, 0, 0, 1);

    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

    const GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    const GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };

    loadTextures();

    glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT2, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT3, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT3, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT4, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT5, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT5, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT6, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT6, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT7, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT7, GL_DIFFUSE, light_diffuse);


    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}

void drawFloor() {
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, amb);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, dif);
    glBindTexture(GL_TEXTURE_2D, floor_texture_id);

    glBegin(GL_QUADS);
		glTexCoord2f(0, 0); glNormal3f(0, 0, 1); glVertex3f(-10, -10, 0);
		glTexCoord2f(0, 1); glNormal3f(0, 0, 1); glVertex3f(-10, 10, 0);
		glTexCoord2f(1, 1); glNormal3f(0, 0, 1); glVertex3f(10, 10, 0);
		glTexCoord2f(1, 0); glNormal3f(0, 0, 1); glVertex3f(10, -10, 0);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

void drawLamps() {
    const GLfloat light_pos[] = {0.f, 0.f, 4.6f, 1.f};

    glColor3f(0.5f, 0.5f, 0.5f);
    glPushMatrix();
    glTranslatef(-4, -4, 0);
    glutSolidCylinder(0.1, 4, 10, 10);
	glPushMatrix();
	glTranslatef(0, 0, 4.1);
	if (glIsEnabled(GL_LIGHT1))
		glMaterialfv(GL_FRONT, GL_EMISSION, light);
	else
		glMaterialfv(GL_FRONT, GL_EMISSION, no_light);
	glutSolidSphere(0.5, 10, 10);
	glPopMatrix();
    glLightfv(GL_LIGHT1, GL_POSITION, light_pos);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-4, 4, 0);
    glutSolidCylinder(0.1, 4, 10, 10);
	glPushMatrix();
	glTranslatef(0, 0, 4.1);
	if (glIsEnabled(GL_LIGHT2))
		glMaterialfv(GL_FRONT, GL_EMISSION, light);
	else
		glMaterialfv(GL_FRONT, GL_EMISSION, no_light);
	glutSolidSphere(0.5, 10, 10);
	glPopMatrix();
	glLightfv(GL_LIGHT2, GL_POSITION, light_pos);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(4, 4, 0);
    glutSolidCylinder(0.1, 4, 10, 10);
	glPushMatrix();
	glTranslatef(0, 0, 4.1);
	if (glIsEnabled(GL_LIGHT3))
		glMaterialfv(GL_FRONT, GL_EMISSION, light);
	else
		glMaterialfv(GL_FRONT, GL_EMISSION, no_light);
	glutSolidSphere(0.5, 10, 10);
	glPopMatrix();
    glLightfv(GL_LIGHT3, GL_POSITION, light_pos);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(4, -4, 0);
    glutSolidCylinder(0.1, 4, 10, 10);
	glPushMatrix();
	glTranslatef(0, 0, 4.1);
	if (glIsEnabled(GL_LIGHT4))
		glMaterialfv(GL_FRONT, GL_EMISSION, light);
	else
		glMaterialfv(GL_FRONT, GL_EMISSION, no_light);
	glutSolidSphere(0.5, 10, 10);
	glPopMatrix();
	glMaterialfv(GL_FRONT, GL_EMISSION, no_light);
    glLightfv(GL_LIGHT4, GL_POSITION, light_pos);
    glPopMatrix();


	glPushMatrix();
	glTranslatef(dist_x, dist_y, 0);
	glRotatef(angle, 0, 0, 1);
	glRotatef(-90, 0, 0, 1);
	float dir[] = { 0, 1, 0, 1 };
	float pos[] = { 2, -0.4,0.6 };
	glLightfv(GL_LIGHT5, GL_POSITION, pos);
	glLightf(GL_LIGHT5, GL_SPOT_CUTOFF, 60);
	glLightfv(GL_LIGHT5, GL_SPOT_DIRECTION, dir);
	pos[1] += 1.8;
	glLightfv(GL_LIGHT6, GL_POSITION, pos);
	glLightf(GL_LIGHT6, GL_SPOT_CUTOFF, 60);
	glLightfv(GL_LIGHT6, GL_SPOT_DIRECTION, dir);
	glPopMatrix();

	float cam_dir[] = { -cam_x, -cam_y, -cam_z };
	pos[0] = cam_x; pos[1] = cam_y; pos[2] = cam_z;
	glLightfv(GL_LIGHT7, GL_POSITION, pos);
	glLightf(GL_LIGHT7, GL_SPOT_CUTOFF, 60);
	glLightfv(GL_LIGHT7, GL_SPOT_DIRECTION, cam_dir);
}



void draw_car()
{
	glPushMatrix();
	glTranslatef(dist_x, dist_y, 0);
	glRotatef(angle, 0, 0, 1);

	glColor3f(1, 1, 1);
	glBindTexture(GL_TEXTURE_2D, car_texture_id);
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);

		//Днище
		glNormal3f(0, 0, 1); glTexCoord2f(0.0, 0.0); glVertex3f(-2, -1, 0.4);
		glNormal3f(0, 0, 1); glTexCoord2f(0.0, 1.0); glVertex3f(-2, 2, 0.4);
		glNormal3f(0, 0, 1); glTexCoord2f(1.0, 1.0); glVertex3f(2, 2, 0.4);
		glNormal3f(0, 0, 1); glTexCoord2f(1.0, 0.0); glVertex3f(2, -1, 0.4);

		//Потолок
		glNormal3f(0, 0, 1); glTexCoord2f(0.0, 0.0); glVertex3f(-2, -1, 1.5);
		glNormal3f(0, 0, 1); glTexCoord2f(0.0, 1.0); glVertex3f(-2, 2, 1.5);
		glNormal3f(0, 0, 1); glTexCoord2f(1.0, 1.0); glVertex3f(2, 2, 1.5);
		glNormal3f(0, 0, 1); glTexCoord2f(1.0, 0.0); glVertex3f(2, -1, 1.5);

		//Передний квадрат
		glNormal3f(0, 0, 1); glTexCoord2f(0.0, 0.0); glVertex3f(-2, -1, 0.4);
		glNormal3f(0, 0, 1); glTexCoord2f(0.0, 1.0); glVertex3f(-2, 2, 0.4);
		glNormal3f(0, 0, 1); glTexCoord2f(1.0, 1.0); glVertex3f(-2, 2, 1.5);
		glNormal3f(0, 0, 1); glTexCoord2f(1.0, 0.0); glVertex3f(-2, -1, 1.5);

		//Задний квадрат
		glNormal3f(0, 0, 1); glTexCoord2f(0.0, 0.0); glVertex3f(2, -1, 0.4);
		glNormal3f(0, 0, 1); glTexCoord2f(0.0, 1.0); glVertex3f(2, 2, 0.4);
		glNormal3f(0, 0, 1); glTexCoord2f(1.0, 1.0); glVertex3f(2, 2, 1.5);
		glNormal3f(0, 0, 1); glTexCoord2f(1.0, 0.0); glVertex3f(2, -1, 1.5);

		//Левый бок
		glNormal3f(0, 0, 1); glTexCoord2f(0.0, 0.0); glVertex3f(-2, 2, 0.4);
		glNormal3f(0, 0, 1); glTexCoord2f(0.0, 1.0); glVertex3f(2, 2, 0.4);
		glNormal3f(0, 0, 1); glTexCoord2f(1.0, 1.0); glVertex3f(2, 2, 1.5);
		glNormal3f(0, 0, 1); glTexCoord2f(1.0, 0.0); glVertex3f(-2, 2, 1.5);

		//Правый бок
		glNormal3f(0, 0, 1); glTexCoord2f(0.0, 0.0); glVertex3f(-2, -1, 0.4);
		glNormal3f(0, 0, 1); glTexCoord2f(0.0, 1.0); glVertex3f(2, -1, 0.4);
		glNormal3f(0, 0, 1); glTexCoord2f(1.0, 1.0); glVertex3f(2, -1, 1.5);
		glNormal3f(0, 0, 1); glTexCoord2f(1.0, 0.0); glVertex3f(-2, -1, 1.5);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, knuckles_texture_id);
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
		//крыша башни
		glNormal3f(0, 0, 1); glTexCoord2f(0.0, 0.0); glVertex3f(1, -0.25, 2.3);
		glNormal3f(0, 0, 1); glTexCoord2f(0.0, 1.0); glVertex3f(1, 1.25, 2.3);
		glNormal3f(0, 0, 1); glTexCoord2f(1.0, 1.0); glVertex3f(-1, 1.25, 2.3);
		glNormal3f(0, 0, 1); glTexCoord2f(1.0, 0.0); glVertex3f(-1, -0.25, 2.3);

		//Задняя часть башни
		glNormal3f(0, 0, 1); glTexCoord2f(0.0, 0.0); glVertex3f(1, -0.25, 1.5);
		glNormal3f(0, 0, 1); glTexCoord2f(0.0, 1.0); glVertex3f(1, 1.25, 1.5);
		glNormal3f(0, 0, 1); glTexCoord2f(1.0, 0.0); glVertex3f(1, 1.25, 2.3);
		glNormal3f(0, 0, 1); glTexCoord2f(1.0, 1.0); glVertex3f(1, -0.25, 2.3);


		//Передняя часть башни
		glNormal3f(0, 0, 1); glTexCoord2f(0.0, 0.0); glVertex3f(-1, -0.25, 1.5);
		glNormal3f(0, 0, 1); glTexCoord2f(0.0, 1.0); glVertex3f(-1, 1.25, 1.5);
		glNormal3f(0, 0, 1); glTexCoord2f(1.0, 0.0); glVertex3f(-1, 1.25, 2.3);
		glNormal3f(0, 0, 1); glTexCoord2f(1.0, 1.0); glVertex3f(-1, -0.25, 2.3);

		//Боковая часть башни
		glNormal3f(0, 0, 1); glTexCoord2f(0.0, 0.0); glVertex3f(-1, 1.25, 1.5);
		glNormal3f(0, 0, 1); glTexCoord2f(0.0, 1.0); glVertex3f(-1, 1.25, 2.3);
		glNormal3f(0, 0, 1); glTexCoord2f(1.0, 0.0); glVertex3f(1, 1.25, 2.3);
		glNormal3f(0, 0, 1); glTexCoord2f(1.0, 1.0); glVertex3f(1, 1.25, 1.5);

		//Боковая часть башни
		glNormal3f(0, 0, 1); glTexCoord2f(0.0, 0.0); glVertex3f(-1, -0.25, 1.5);
		glNormal3f(0, 0, 1); glTexCoord2f(0.0, 1.0); glVertex3f(-1, -0.25, 2.3);
		glNormal3f(0, 0, 1); glTexCoord2f(1.0, 0.0); glVertex3f(1, -0.25, 2.3);
		glNormal3f(0, 0, 1); glTexCoord2f(1.0, 1.0); glVertex3f(1, -0.25, 1.5);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, uganda_texture_id);
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
		//Флаг
		glNormal3f(0, 0, 1); glTexCoord2f(0.0, 0.0); glVertex3f(5, 0.5, 2);
		glNormal3f(0, 0, 1); glTexCoord2f(0.0, 1.0); glVertex3f(5, 0.5, 0.5);
		glNormal3f(0, 0, 1); glTexCoord2f(1.0, 0.0); glVertex3f(3.5, 0.5, 0.5);
		glNormal3f(0, 0, 1); glTexCoord2f(1.0, 1.0); glVertex3f(3.5, 0.5, 2);
	glEnd();
	glDisable(GL_TEXTURE_2D);



	glPushMatrix();
	glTranslatef(0, 0.5, 2);
	glRotatef(90, 0, 1, 0);
	glutSolidCylinder(0.1, 5, 10, 10);
	glPopMatrix();

	//Гусеницы
	glPushMatrix();
	glTranslatef(2, -1, 0.4);
	glRotatef(90, 1, 0, 0);
	glutSolidTorus(0.1, 0.2, 10, 10);
	for (int i = 0; i < 10; ++i)
	{
		glTranslatef(-0.4, 0, 0);
		glutSolidTorus(0.1, 0.2, 10, 10);
	}

	glTranslatef(0, 0, -3);
	glutSolidTorus(0.1, 0.2, 10, 10);
	for (int i = 0; i < 10; ++i)
	{
		glTranslatef(0.4, 0, 0);
		glutSolidTorus(0.1, 0.2, 10, 10);
	}
	glPopMatrix();

	// фары
	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslatef(2, -0.4, 0.6);
	if (glIsEnabled(GL_LIGHT5))
		glMaterialfv(GL_FRONT, GL_EMISSION, light);
	else
		glMaterialfv(GL_FRONT, GL_EMISSION, no_light);

	glutSolidSphere(0.5, 5, 5);
	glTranslatef(0, 1.8, 0);
	glutSolidSphere(0.5, 5, 5);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_light);
	glPopMatrix();
	glPopMatrix();
}

void update() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

	double ang_vert_r = ang_vert / 180 * 3.1416;
	double ang_hor_r = ang_hor / 180 * 3.1416;
	cam_x = cam_dist * std::sin(ang_vert_r) * std::cos(ang_hor_r);
	cam_y = cam_dist * std::sin(ang_vert_r) * std::sin(ang_hor_r);
	cam_z = cam_dist * std::cos(ang_vert_r);

	gluLookAt(cam_x, cam_y, cam_z, 0., 0., 0., 0., 0., 1.);
    drawLamps();
    drawFloor();
	draw_car();


    glFlush();
    glutSwapBuffers();
}

void updateCamera() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.f, (float)w / h, 1.0f, 1000.f);
    glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
	case 'w':
		ang_vert += 5;
		break;
	case 's':
		ang_vert -= 5;
		break;
	case 'a':
		ang_hor -= 5;
		break;
	case 'd':
		ang_hor += 5;
		break;
	case 'q':
		cam_dist--;
		break;
	case 'z':
		cam_dist++;
		break;
    case '1':
        if (glIsEnabled(GL_LIGHT1))
            glDisable(GL_LIGHT1);
        else
            glEnable(GL_LIGHT1);
        break;
    case '2':
        if (glIsEnabled(GL_LIGHT2))
            glDisable(GL_LIGHT2);
        else
            glEnable(GL_LIGHT2);
        break;
    case '3':
        if (glIsEnabled(GL_LIGHT3))
            glDisable(GL_LIGHT3);
        else
            glEnable(GL_LIGHT3);
        break;
    case '4':
        if (glIsEnabled(GL_LIGHT4))
            glDisable(GL_LIGHT4);
        else
            glEnable(GL_LIGHT4);
        break;
	case '5':
		if (glIsEnabled(GL_LIGHT5))
		{
			glDisable(GL_LIGHT5);
			glDisable(GL_LIGHT6);
		}
		else
		{
			glEnable(GL_LIGHT5);
			glEnable(GL_LIGHT6);
		}
		break;
    default:
        break;
	case '6':
		if (glIsEnabled(GL_LIGHT7))
			glDisable(GL_LIGHT7);
		else
			glEnable(GL_LIGHT7);
		break;
    }
    glutPostRedisplay();
}

void reshape(int width, int height) {
    w = width;
    h = height;
    
    glViewport(0, 0, w, h);
    updateCamera();
}

void SpecialKeys(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		dist_x += std::cos(angle / 180 * 3.1416) * 0.3;
		dist_y += std::sin(angle / 180 * 3.1416) * 0.3;
		break;
	case GLUT_KEY_DOWN:
		dist_x -= std::cos(angle / 180 * 3.1416) * 0.3;
		dist_y -= std::sin(angle / 180 * 3.1416) * 0.3;
		break;
	case GLUT_KEY_LEFT:
		angle -= 5;
		break;
	case GLUT_KEY_RIGHT:
		angle += 5;
		break;
	}
	glutPostRedisplay();
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 800);
    glutCreateWindow("texture and lighting");

    init();

    glutReshapeFunc(reshape);
    glutDisplayFunc(update);
    glutKeyboardFunc(keyboard);
	glutSpecialFunc(SpecialKeys);

    glutMainLoop();

    return 0;
}
