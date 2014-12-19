#include <windows.h>
#include <iostream>
#include <time.h>
//#include <stdlib.h>
#include <GL/GLU.h>
#include <gl/GL.h>
#include "glut.h"



using namespace std;

double z = 0, v = 0;
float ofx = 0, enemyof = 0;
bool deathray;
bool enemtab[5];
bool defeat = false;
int enemyLeft = 6;

int updateTime = 100;

float Xmovement = 0;
float xofc = 0, yofc = 0;

void EraseDeathRay(int x)
{
	deathray = false;
}

void Display(void)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

	// Changes the seed for the random number generator 
	// based on a specific number (number of seconds since 1/1/1970)
   	srand(time(NULL));
	
	// 2 loops that render the map starting on the top left corner of the screen
	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100 ; j++)
		{
			// Generates a number in [0,5]
			int temp_int = rand() % 6;
			//cout << ("int = ") << temp_int << endl;
			if (temp_int == 0) 
			{	// dark blue
				glColor3f(0.05f,0.05,0.30f);
			}else if (temp_int == 1) 
			{	// green
				glColor3f(0.5f, 1.0f, 0.5f);
			}else if (temp_int == 2)
			{	// blue
				glColor3f(0.5f, 0.5f, 1.0f);
			}else if (temp_int == 3) 
			{	// cyan-ish
				glColor3f(0.7f, 1.0f, 0.9f);
			}else if (temp_int == 4)
			{	// gray
				glColor3f(0.5f, 0.5f, 0.5f);
			}else if (temp_int == 5)
			{	// green-ish
				glColor3f(0.3f, 1.0f, 0.34f);
			}
			// Renders each square
			glBegin(GL_POLYGON);
				glVertex2f( -1.0   + xofc   ,   0.98  + yofc );
				glVertex2f( -1.0   + xofc   ,   1.0   + yofc );
				glVertex2f( -0.98  + xofc   ,   1.0   + yofc );
				glVertex2f( -0.98  + xofc   ,   0.98  + yofc );
			glEnd();
			// Changes the position of the next square
			xofc += 0.02;

		}
		xofc = 0;
		yofc -= 0.02;
	}
	yofc = 0;

   if (deathray == true)
   {
	   glBegin(GL_POLYGON);
		   glColor3f (1, 1, 0);
		   glVertex2f( z-0.05   , 1 );
		   glVertex2f( z-0.05   , -0.8 + v );
		   glVertex2f( z+0.05   , 1 );
		   glVertex2f( z+0.05   , -0.8 + v );
	   glEnd();

	   glutTimerFunc(500, EraseDeathRay, 1);
   }

   // enemies
   glColor3f (1, 0, 0);

   for (int i=0; i<6 ; i++)
   {
	   glBegin(GL_POLYGON);

	   if(enemtab[i]==false)
	   {
		   glVertex2f( -0.9 + ofx + Xmovement , 0.9 + enemyof );
		   glVertex2f( -0.7 + ofx + Xmovement  , 0.9 + enemyof );
		   glVertex2f( -0.7 + ofx + Xmovement  , 0.7 + enemyof );
		   glVertex2f( -0.9 + ofx + Xmovement  , 0.7 + enemyof );
	   }


		glEnd();
		ofx+= 0.3;
	}

   // player
   glBegin(GL_TRIANGLES);

   glColor3f (1.0f, 1.0f, 1.0f);
   glVertex2f( -0.1 + z  , -0.9 + v);
   glVertex2f( 0 + z   , -0.6 + v);
   glVertex2f( 0.1 + z   , -0.9 + v);

   glEnd();

   if (defeat)
   {
		glutSetWindowTitle("YOU ARE DEFEATED!");
   }

   glutSwapBuffers();
   ofx = 0;

   glutPostRedisplay();
}

void Keyboard(unsigned char key, int x, int y)
//Note: because there is an Idle-func, we don't have to call Display here
{	
	switch(key)
	{
	case 'q':	//ESC
		exit(0);
		break;
	case 's':		//a
	    //movedown
		v -= 0.05;
		break;
	case 'w':		//d
	    //moveup
		v += 0.05;
        break;
 	case 'a':		//a
	    //moveleft
		z -= 0.05;
		break;
	case 'd':		//d
	    //moveRight
		z +=0.05;
        break;
	case ' ':
		if ((z >= -0.9 + Xmovement) && (z <= -0.7 + Xmovement) && !(enemyof + 0.9 < v -0.6))
		{
			if (enemtab[0] == false)
			{
				enemtab[0]=true;
				enemyLeft--;
			}
		}
		if ((z >= -0.6 + Xmovement) && (z <= -0.4 + Xmovement ) && !(enemyof + 0.9 < v -0.6))
			if (enemtab[1] == false)
			{
				enemtab[1]=true;
				enemyLeft--;
			}
		if ((z >= -0.3 + Xmovement) && (z <= -0.1 + Xmovement) && !(enemyof + 0.9 < v -0.6))
			if (enemtab[2] == false)
			{
				enemtab[2]=true;
				enemyLeft--;
			}
		if ((z >= 0 + Xmovement) && (z <= 0.2 + Xmovement) && !(enemyof + 0.9  < v -0.6))
			if (enemtab[3] == false)
			{
				enemtab[3]=true;
				enemyLeft--;
			}
		if ((z >= 0.3 + Xmovement) && (z <= 0.5 + Xmovement) && !(enemyof + 0.9 < v -0.6))
			if (enemtab[4] == false)
			{
				enemtab[4]=true;
				enemyLeft--;
			}
		if ((z >= 0.6 + Xmovement) && (z <= 0.8 + Xmovement) && !(enemyof + 0.9 < v -0.6))
			if (enemtab[5] == false)
			{
				enemtab[5]=true;
				enemyLeft--;
			}
		deathray=true;
		break;

	}
	if(z>0.9)
		z=0.9;
	else if (z<-0.9)
		z=-0.9;
	if(v>1.6)
		v=1.6;
	else if (v<-0.1)
		v=-0.1;

	Display();
}

void update(int x)
{
	enemyof -= 0.01;
	static int direction = -1;
	Xmovement += 0.03 * direction;
	if (Xmovement < -0.2)
	{
		direction = 1;
	}
	else if (Xmovement > 0.3)
	{
		direction = -1;
	}
	if (enemyof > -1.3)
	{
		glutTimerFunc(updateTime, update, 1);
	}
	else
	{
		if (enemyLeft > 0)
		{
			defeat = true;
		}
	}

	if (enemyLeft == 0)
	{
		glutSetWindowTitle("Victory!");
	}
}

int main (int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA| GLUT_DOUBLE);
	glutInitWindowPosition(400,40);
	glutInitWindowSize(800,600);
	glutCreateWindow("Demo"); 
	glutDisplayFunc(Display);
    glutKeyboardFunc(Keyboard);
	glutTimerFunc(updateTime, update, 1);
	glutMainLoop();
	return 0;
}
