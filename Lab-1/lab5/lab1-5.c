// Lab 1-1.
// This is the same as the first simple example in the course book,
// but with a few error checks.
// Remember to copy your file to a new on appropriate places during the lab so you keep old results.
// Note that the files "lab1-1.frag", "lab1-1.vert" are required.

#include "GL_utilities.h"
#include "MicroGlut.h"
#include "math.h"
#include "stdio.h"
// uses framework OpenGL
// uses framework Cocoa

// Globals
// Data would normally be read from files
GLfloat vertices[] =
	{
		// Pyramid

		// Front
		0.0f,
		0.5f,
		0.0f,
		-0.5f,
		-0.5f,
		0.5f,
		0.5f,
		-0.5f,
		0.5f,

		// Right
		0.0f,
		0.5f,
		0.0f,
		0.5f,
		-0.5f,
		0.5f,
		0.5f,
		-0.5f,
		-0.5f,

		// Back
		0.0f,
		0.5f,
		0.0f,
		0.5f,
		-0.5f,
		-0.5f,
		-0.5f,
		-0.5f,
		-0.5f,

		// Left
		0.0f,
		0.5f,
		0.0f,
		-0.5f,
		-0.5f,
		-0.5f,
		-0.5f,
		-0.5f,
		0.5f,

		// Bottom
		-0.5f,
		-0.5f,
		0.5f,
		0.5f,
		-0.5f,
		0.5f,
		0.5f,
		-0.5f,
		-0.5f,

		-0.5f,
		-0.5f,
		0.5f,
		0.5f,
		-0.5f,
		-0.5f,
		-0.5f,
		-0.5f,
		-0.5f,

};

GLfloat color[] =
	{
		// Front
		0.0f,
		0.5f,
		0.0f,
		-0.5f,
		-0.5f,
		0.5f,
		0.5f,
		-0.5f,
		0.5f,

		// Right
		0.0f,
		0.5f,
		0.0f,
		0.5f,
		-0.5f,
		0.5f,
		0.5f,
		-0.5f,
		-0.5f,

		// Back
		0.0f,
		0.5f,
		0.0f,
		0.5f,
		-0.5f,
		-0.5f,
		-0.5f,
		-0.5f,
		-0.5f,

		// Left
		0.0f,
		0.5f,
		0.0f,
		-0.5f,
		-0.5f,
		-0.5f,
		-0.5f,
		-0.5f,
		0.5f,

		// Bottom
		-0.5f,
		-0.5f,
		0.5f,
		0.5f,
		-0.5f,
		0.5f,
		0.5f,
		-0.5f,
		-0.5f,

		-0.5f,
		-0.5f,
		0.5f,
		0.5f,
		-0.5f,
		-0.5f,
		-0.5f,
		-0.5f,
		-0.5f,
};

GLfloat Rotx[] =
	{
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f};

GLfloat Roty[] =
	{
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f};

GLfloat Rotz[] =
	{
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f};

// vertex array object
unsigned int vertexArrayObjID;
// Reference to shader program
GLuint program;

void init(void)
{
	// vertex buffer object, used for uploading the geometry
	unsigned int vertexBufferObjID;
	unsigned int colorBufferObjID;

	dumpInfo();

	// GL inits
	glClearColor(0.2, 0.2, 0.2, 0);
	glDisable(GL_DEPTH_TEST);
	printError("GL inits");

	// Load and compile shader
	program = loadShaders("lab1-5.vert", "lab1-5.frag");
	printError("init shader");

	// Upload geometry to the GPU:

	// Allocate and activate Vertex Array Object
	glGenVertexArrays(1, &vertexArrayObjID);
	glBindVertexArray(vertexArrayObjID);

	// Allocate Vertex Buffer Objects
	glGenBuffers(1, &vertexBufferObjID);

	// VBO for vertex data
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObjID);
	glBufferData(GL_ARRAY_BUFFER, 6 * 9 * sizeof(GLfloat), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(glGetAttribLocation(program, "in_Position"), 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(glGetAttribLocation(program, "in_Position"));

	// Allocate Vertex Buffer Objects
	glGenBuffers(1, &colorBufferObjID);

	// VB0 for color data
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObjID);
	glBufferData(GL_ARRAY_BUFFER, 6 * 9 * sizeof(GLfloat), color, GL_STATIC_DRAW);
	glVertexAttribPointer(glGetAttribLocation(program, "in_Color"), 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(glGetAttribLocation(program, "in_Color"));

	// Matrix application
	// glUniformMatrix4fv(glGetUniformLocation(program, "myMatrix"), 1, GL_TRUE, myMatrixDUO);

	// End of upload of geometry
	printError("init arrays");
}

void display(void)
{
	printError("pre display");

	// clear the screen
	glClear(GL_COLOR_BUFFER_BIT);

	glBindVertexArray(vertexArrayObjID);  // Select VAO
	glDrawArrays(GL_TRIANGLES, 0, 6 * 3); // draw object

	glUniformMatrix4fv(glGetUniformLocation(program, "Rotx"), 1, GL_TRUE, Rotx);
	glUniformMatrix4fv(glGetUniformLocation(program, "Roty"), 1, GL_TRUE, Roty);
	glUniformMatrix4fv(glGetUniformLocation(program, "Rotz"), 1, GL_TRUE, Rotz);
	
	glutPostRedisplay();

	printError("display");

	glutSwapBuffers();
}

void updateMatrix()
{

	// Rotation on y
	GLfloat time = (GLfloat)glutGet(GLUT_ELAPSED_TIME) * M_PI / (2 * 1000);

	Rotx[5] = cos(time);
	Rotx[6] = -sin(time);
	Rotx[9] = sin(time);
	Rotx[10] = cos(time);
	Roty[0] = cos(time);
	Roty[3] = sin(time);
	Roty[8] = -sin(time);
	Roty[10] = cos(time);
	Rotz[0] = cos(time);
	Rotz[4] = sin(time);
	Rotz[1] = -sin(time);
	Rotz[5] = cos(time);

	glutTimerFunc(20, &updateMatrix, 0);
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitContextVersion(3, 2);
	glutInitWindowSize(600, 600);
	glutCreateWindow("GL3 white triangle example LAB 3");
	// glutRepeatingTimer(20);
	glutDisplayFunc(display);
	glutTimerFunc(20, &updateMatrix, 0);
	init();
	glutMainLoop();
	return 0;
}
