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
	-0.5f,-0.5f,0.0f,
	-0.5f,0.5f,0.0f,
	0.5f,-0.5f,0.0f
};

GLfloat myMatrix[] = {    1.0f, 0.0f, 0.0f, 0.5f,

                        0.0f, 1.0f, 0.0f, 0.0f,

                        0.0f, 0.0f, 1.0f, 0.0f,

                        0.0f, 0.0f, 0.0f, 1.0f };

GLfloat myMatrixDUO[] = { 	cos(1), -sin(1), 0.0f, 0.0f,
                       		sin(1), cos(1),  0.0f, 0.0f,
                       		0.0f,         0.0f,          1.0f, 0.0f,
                       		0.0f,         0.0f,          0.0f, 1.0f };

// vertex array object
unsigned int vertexArrayObjID;
// Reference to shader program
GLuint program;

void init(void)
{
	// vertex buffer object, used for uploading the geometry
	unsigned int vertexBufferObjID;

	dumpInfo();

	// GL inits
	glClearColor(0.2,0.2,0.2,0);
	glDisable(GL_DEPTH_TEST);
	printError("GL inits");

	// Load and compile shader
	program = loadShaders("lab1-3.vert", "lab1-3.frag");
	printError("init shader");
	
	// Upload geometry to the GPU:
	
	// Allocate and activate Vertex Array Object
	glGenVertexArrays(1, &vertexArrayObjID);
	glBindVertexArray(vertexArrayObjID);
	// Allocate Vertex Buffer Objects
	glGenBuffers(1, &vertexBufferObjID);
	
	// VBO for vertex data
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObjID);
	glBufferData(GL_ARRAY_BUFFER, 9*sizeof(GLfloat), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(glGetAttribLocation(program, "in_Position"), 3, GL_FLOAT, GL_FALSE, 0, 0); 
	glEnableVertexAttribArray(glGetAttribLocation(program, "in_Position"));

	//Matrix application
	//TODO:: IN DISPLAY MULTIPLY THIS MATRIX FOR T AND FIN AN METHOD TO SEND IT TO VER INTO UNIFORM 
	glUniformMatrix4fv(glGetUniformLocation(program, "myMatrixDUO"), 1, GL_TRUE, myMatrixDUO);


	//COlor change
	int vertexColorLocation = glGetUniformLocation(program, "in_frag_color");
    glUniform4f(vertexColorLocation, 0.796,0.196,0.204, 1.0);
	
	// End of upload of geometry
	
	printError("init arrays");
}


void display(void)
{

	printError("pre display");
	//
	GLfloat t = (GLfloat)glutGet(GLUT_ELAPSED_TIME);
	t = fmod(t, 360);
	GLfloat radiants = t * (3.14159f / 180.0f);

	myMatrixDUO[0] = cos(radiants);
	myMatrixDUO[1] = -sin(radiants);
	myMatrixDUO[4] = sin(radiants);
	myMatrixDUO[5] = cos(radiants);

	glUniformMatrix4fv(glGetUniformLocation(program, "myMatrixDUO"), 1, GL_TRUE, myMatrixDUO);

	// clear the screen
	glClear(GL_COLOR_BUFFER_BIT);

	glBindVertexArray(vertexArrayObjID);	// Select VAO
	glDrawArrays(GL_TRIANGLES, 0, 3);	// draw object

	printError("display");
	
	glutSwapBuffers();
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitContextVersion(3, 2);
	glutInitWindowSize(600, 600);
	glutCreateWindow ("GL3 white triangle example LAB 3");
	glutRepeatingTimer(20);
	glutDisplayFunc(display); 
	init ();
	glutMainLoop();
	return 0;
}
