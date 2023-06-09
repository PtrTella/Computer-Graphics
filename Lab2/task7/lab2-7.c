
#include "MicroGlut.h"
#include "GL_utilities.h"
#include <math.h>
#include <stdio.h>
#include "../common/LittleOBJLoader.h"
#include "../common/LoadTGA.h"
#include "../common/VectorUtils3.h"


#define near 1.0

#define far 30.0

#define right 0.5

#define left -0.5

#define top 0.5

#define bottom -0.5

GLfloat color[] = 
{
	1.0f,0.0f,0.0f,
	0.0f,1.0f,0.0f,
	0.0f,0.0f,1.0f

	
};


GLfloat projectionMatrix[] = {
	2.0f*near/(right-left), 0.0f, (right+left)/(right-left), 0.0f, 
	0.0f, 2.0f*near/(top-bottom), (top+bottom)/(top-bottom), 0.0f,
	0.0f, 0.0f, -(far + near)/(far - near), -2*far*near/(far - near),
	0.0f, 0.0f, -1.0f, 0.0f 
};


mat4 cameraMatrix;


mat4 transform, rot, trans, total, complete, mod1Transform, mod2Transform;
//Maek teh madelz!
Model *bunnyPlanet;
Model *bunnyMoon;


// vertex array object
GLfloat t;
GLuint program;



void init(void)
{
	// Load objects for bunnehs
	unsigned int myTex;

	LoadTGATextureSimple("../texture/maskros512.tga", &myTex);

	transform = IdentityMatrix();
	//Load teh banny
	bunnyPlanet = LoadModelPlus("../model/bunnyplus.obj");
	bunnyMoon = LoadModelPlus("../model/bunnyplus.obj");
	dumpInfo();
	
	//LoadTGATextureSimple("maskros512.tga", &myTex);
	

	// GL inits
	glClearColor(0.3,0.3,0.3,0);
	//glDisable(GL_DEPTH_TEST);
	printError("GL inits");
	
	
	
	// Load and compile shader
	program = loadShaders("lab2-7.vert", "lab2-7.frag");
	printError("init shader");
	
	glUniformMatrix4fv(glGetUniformLocation(program, "uniProjection"), 1, GL_TRUE, projectionMatrix);
	
	glBindTexture(GL_TEXTURE_2D, myTex);
	printError("init arrays");

	

}


void display(void)
{
	printError("pre display");

	// clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	GLfloat mod1Color[] = {0.0f, 0.4f, 0.8f, 0.0f};
	GLfloat mod2Color[] = {0.4f, 0.4f, 0.4f, 0.0f};
	
	//Projection
	vec3 p, l, v;
	//p = SetVector(0,1.0f,5.0f);
	p = SetVector(5.0f*sin(t/4.0f),1.0f,5.0f*cos(t/4.0f));
	l = SetVector(0,0,0);
	v = SetVector(0,1,0);
	cameraMatrix = lookAtv(p,l,v);
	

	//Model 1
	//Move object to camera
	trans = T(0, 0, 0.0f);
	rot = Ry(0);
	total = Mult(rot, trans);
	complete = Mult(cameraMatrix,Mult(total,mod1Transform));
	glUniformMatrix4fv(glGetUniformLocation(program, "uniTotal"), 1, GL_TRUE, complete.m);
	glUniform4fv(glGetUniformLocation(program, "inColor"), 1, mod1Color);
	DrawModel(bunnyPlanet, program, "in_Position", "in_Normal", "inTexCoord");
	

	//Model 2
	//Move object to camera
	trans = T(-1.0f, 0, 0.0f);
	rot = Ry(t);
	mat4 scale = S(0.3f,0.3f,0.3f);
	total = Mult(rot, Mult(trans, scale));
	complete = Mult(cameraMatrix,Mult(total,mod2Transform));
	glUniformMatrix4fv(glGetUniformLocation(program, "uniTotal"), 1, GL_TRUE, complete.m);
	glUniform4fv(glGetUniformLocation(program, "inColor"), 1, mod2Color);
	DrawModel(bunnyMoon, program, "in_Position", "in_Normal", "inTexCoord");
	

	printError("display");
	
	glutSwapBuffers();
}
//uniProjection * uniCamera * uniTotal * uniTransform

void onTimer(int value)
{
	
	t = (GLfloat)glutGet(GLUT_ELAPSED_TIME) * M_PI / (2*1000);
	glUniform1f(glGetUniformLocation(program, "uniTime"), t*10);
	mod1Transform = Mult(Rz((-23.0f/180.0f)*M_PI),Ry(t));
	mod2Transform = Mult(Rz((0)*M_PI),Ry(-t/2.0f));
	glutPostRedisplay();	
	glutTimerFunc(20, &onTimer, value); //50 FPS
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitContextVersion(3, 2);
	glutInitWindowSize(800, 600);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow ("Magical BunnyMoon orbiting magical BunnyPlanet");
	glEnable(GL_DEPTH_TEST);
	glutDisplayFunc(display);
	glutTimerFunc(20, &onTimer, 0); 
	init ();
	glutMainLoop();
	return 0;
}
