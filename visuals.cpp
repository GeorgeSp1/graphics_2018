#include <stdio.h>     // - Just for some ASCII messages
#include <string.h>
#include <math.h>
#include <ctime>
#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "gl/glut.h"   // - An interface and windows 
//   management library
#include "visuals.h"   // Header file for our OpenGL functions



#define SUN_RADIUS 13.0
#define STAR_COUNT 700
#define STARS_RADIUS 0.05

using namespace std;

model *md;

static bool animate = true;
bool x_flag = true;
bool z_flag = true;

point *stars[STAR_COUNT];
static float sun_radius_now = SUN_RADIUS;
static float sun_flickering_speed = 0.05;

static float stars_radius_now = STARS_RADIUS;
static float stars_flickering_speed = 0.00;

float earth_x = 100;
float earth_y = 0;
float earth_z = 0;

float earth_start_x = earth_x;
float earth_start_y = earth_y;
float earth_start_z = earth_z;

float moon_x = earth_x;
float moon_y = earth_y + 50;
float moon_z = earth_z-50;

// planets
static float planet_rotx = 0.0;
static float planet_roty = 0.0;
static float rotating_speed = 1.5;

// camera movement
static float tx = 0.0;
static float ty = 0.0;
static float tz = 0.0;

void star_positions()
{
	srand(time(NULL));

	for (int i = 0; i < STAR_COUNT; i++) {
		stars[i] = (point *)malloc(sizeof(point));
		float LO = -70.0;
		float HI = 70.0;
		stars[i]->x = LO + static_cast<float>(rand()) /
			(static_cast<float>(RAND_MAX / (HI - LO)));
		stars[i]->y = LO + static_cast<float>(rand()) /
			(static_cast<float>(RAND_MAX / (HI - LO)));
		stars[i]->z = LO + static_cast<float>(rand()) /
			(static_cast<float>(RAND_MAX / (HI - LO)));
	}
}

void Render()
{
	//CLEARS FRAME BUFFER ie COLOR BUFFER& DEPTH BUFFER (1.0)
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // Clean up the colour of the window
														 // and the depth buffer
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//glTranslatef(0.0f, 0.0f, tz);
	/*glTranslatef(0,0,-50);*/

	glTranslatef(0.0, 0.0, -150);
	glRotatef(tx, 1.0, 0.0, 0.0);
	glRotatef(ty, 0.0, 1.0, 0.0);
	glRotatef(tz, 0.0, 0.0, 1.0);

	/* Render planet (Earth)*/
	glPushMatrix();
	glColor3f(0.0, 0.0, 1.0);
	glRotatef(planet_rotx, 0.0, 0.5, 0.0);
	glTranslatef(earth_x, earth_y, earth_z);
	glScalef(0.01, 0.0087, 0.01);

	DisplayModel(md);
	glPopMatrix();

	/* Render another planet (Moon)*/
	glPushMatrix();
	glColor3f(0.5, 0.5, 0.5);
	glRotatef(planet_rotx, 0.0, 0.5, 0.0);
	glRotatef(planet_roty, 0.8, 0.0, 0.0);
	glTranslatef(earth_x, (earth_y + 20.0), (earth_z + 20.0));
	glScalef(0.005, 0.0045, 0.005);

	DisplayModel(md);
	glPopMatrix();
	
	
	//GLfloat light_position[] = { 0.0, 0.0, -500.0, 1.0 };
	//glLightfv(GL_LIGHT0, GL_POSITION, light_position);


	/* Render Sun*/
	glPushMatrix();

	glColor3f(1.0, 1.0, 0.0);
	glTranslatef(0.0, 0.0, 0.0);
	glutSolidSphere(SUN_RADIUS, 30, 24);

	glColor4f(1.0, 1.0, 0.0, 0.2);
	glutSolidSphere(sun_radius_now+2.1, 30, 24);
	
	glPopMatrix();

	for (int i = 0; i != STAR_COUNT; i++) {
		glPushMatrix();
		glTranslatef(stars[i]->x, stars[i]->y, stars[i]->z);
		glColor3f(1, 1, 1);
		glutSolidSphere(STARS_RADIUS, 30, 24);
		glColor4f(1, 1, 1, 0.5);
		glutSolidSphere(stars_radius_now, 30, 24);
		glPopMatrix();
	}


	glutSwapBuffers();             // All drawing commands applied to the 
								   // hidden buffer, so now, bring forward
								   // the hidden buffer and hide the visible one
}

void Keyboard(unsigned char key, int x, int y) {
	if (key == 'a')
		ty += 0.5; // move y (-)
	if (key == 'd')
		ty -= 0.5; // move y (-)
	if (key == 'w')
		tx += 0.5; // move x (-)
	if (key == 's')
		tx -= 0.5; // move x (+)
	if (key == '=')
		tz += 0.5; // move z (+)
	if (key == '-')
		tz -= 0.5; // move z (-)
	if (key == 'q')
		exit(EXIT_SUCCESS); // quit program
	if (key == '\'')
		rotating_speed += 0.2;
	if (key == ';')
		rotating_speed -= 0.2;
	if (key == 'p') { // stop or start animation
		if (animate)
			animate = false;
		else
			animate = true;
	}
	glutPostRedisplay();
}

void DisplayModel(model *md)
{

	glPushMatrix();
	glBegin(GL_TRIANGLES);

	for (int i = 0; i < md->faces; i++)
	{
		glVertex3f(md->obj_points[md->obj_faces[i].vtx[0] - 1].x, md->obj_points[md->obj_faces[i].vtx[0] - 1].y, md->obj_points[md->obj_faces[i].vtx[0] - 1].z);
		glVertex3f(md->obj_points[md->obj_faces[i].vtx[1] - 1].x, md->obj_points[md->obj_faces[i].vtx[1] - 1].y, md->obj_points[md->obj_faces[i].vtx[1] - 1].z);
		glVertex3f(md->obj_points[md->obj_faces[i].vtx[2] - 1].x, md->obj_points[md->obj_faces[i].vtx[2] - 1].y, md->obj_points[md->obj_faces[i].vtx[2] - 1].z);

		glNormal3f(md->obj_normals[md->obj_faces[i].vtn[0] - 1].x, md->obj_normals[md->obj_faces[i].vtn[0] - 1].y, md->obj_normals[md->obj_faces[i].vtn[0] - 1].z);
		glNormal3f(md->obj_normals[md->obj_faces[i].vtn[1] - 1].x, md->obj_normals[md->obj_faces[i].vtn[1] - 1].y, md->obj_normals[md->obj_faces[i].vtn[1] - 1].z);
		glNormal3f(md->obj_normals[md->obj_faces[i].vtn[2] - 1].x, md->obj_normals[md->obj_faces[i].vtn[2] - 1].y, md->obj_normals[md->obj_faces[i].vtn[2] - 1].z);
		
	}

	glEnd();
	glPopMatrix();

}

//-----------------------------------------------------------

void Resize(int w, int h)
{
	// define the visible area of the window ( in pixels )
	if (h == 0) h = 1;
	glViewport(0, 0, w, h);

	// Setup viewing volume

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (float)w / (float)h, 1.0, 500.0);
}

void Idle() {

	if (animate) {
		// sun flickering
		if (sun_radius_now < SUN_RADIUS)
			sun_flickering_speed = -sun_flickering_speed;
		if (sun_radius_now > SUN_RADIUS+2)
			sun_flickering_speed = -sun_flickering_speed;
		sun_radius_now += sun_flickering_speed;

		// stars flickering
		if (stars_radius_now < STARS_RADIUS)
			stars_flickering_speed = -stars_flickering_speed;
		if (stars_radius_now > 0.1)
			stars_flickering_speed = -stars_flickering_speed;
		stars_radius_now += stars_flickering_speed;

		// planets rotating
		planet_rotx += rotating_speed;
		planet_roty += rotating_speed + 1.0;


	}
	glutPostRedisplay();
}

void Setup()  // TOUCH IT !! 
{
	initModel(&md);
	ReadFile(md);


	//enable extra light -- have to enable GL_LIGHTING GL_LIGHT0
	/*GLfloat light_position[] = { 0.0, 0.0, -70.0, 1 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	GLfloat diffuseLight[] = { 0.5, 0.5, 0.5, 1.0 };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);*/

	// Parameter handling
	glShadeModel(GL_SMOOTH);


	//enable if we want lighting
	//glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);


	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glClearDepth(1);

	star_positions();

	// polygon rendering mode
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glEnable(GL_CULL_FACE);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);



	// Black background
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

}

void initModel(model **md) {

	ifstream fp("planet.obj");

	if (fp.fail()) {
		exit(1);
	}

	string line;
	int no_of_vertices = 0;
	int no_of_normals = 0;
	int no_of_faces = 0;

	while (getline(fp, line)) {
		string temp = line.substr(0, 2);
		if (temp == "v ") {
			no_of_vertices++;
		}
		else if (temp == "vn") {
			no_of_normals++;
		}
		else if (temp == "f ") {
			no_of_faces++;
		}
	}

	cout << no_of_vertices << " " << no_of_normals << " " << no_of_faces << endl;
	(*md) = new model(no_of_vertices, no_of_normals, no_of_faces);
	fp.close();
}

void ReadFile(model *md) {

	ifstream fp("planet.obj");

	if (fp.fail()) {
		exit(1);
	}

	string line;

	int no_of_vertices = 0;
	int no_of_normals = 0;
	int no_of_faces = 0;

	while (getline(fp, line)) {
		string temp = line.substr(0, 2);
		//		cout << line << endl;
		if (temp == "v ") {
			istringstream string_stream(line.substr(2));
			string_stream >> md->obj_points[no_of_vertices].x;
			string_stream >> md->obj_points[no_of_vertices].y;
			string_stream >> md->obj_points[no_of_vertices].z;
			no_of_vertices++;
		}
		else if (temp == "vn") {
			istringstream string_stream(line.substr(3));
			string_stream >> md->obj_normals[no_of_normals].x;
			string_stream >> md->obj_normals[no_of_normals].y;
			string_stream >> md->obj_normals[no_of_normals].z;
			no_of_normals++;
		}
		else if (temp == "f ") {
			istringstream string_stream(line.substr(2));
			for (int i = 0; i < 3; i++) {
				string_stream >> md->obj_faces[no_of_faces].vtx[i];
				string_stream.ignore(2);
				string_stream >> md->obj_faces[no_of_faces].vtn[i];
				if (i == 2) break;
				string_stream.ignore(1);
			}
			no_of_faces++;
		}
	}
	fp.close();
}

