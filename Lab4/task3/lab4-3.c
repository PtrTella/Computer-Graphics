// Lab 4, terrain generation

#ifdef __APPLE__
	#include <OpenGL/gl3.h>
	// Linking hint for Lightweight IDE
	// uses framework Cocoa
#endif
#include "MicroGlut.h"
#include "GL_utilities.h"
#include "VectorUtils3.h"
#include "LittleOBJLoader.h"
#include "LoadTGA.h"


mat4 projectionMatrix;

float sphereSpeed;

vec3 calculateNormal(int x, int z, int zLen, GLfloat *vertex){
	vec3 returnVector;
	vec3 a, b, c;
	
	if(x != 0){
		if(z != 0){
			a = SetVector(vertex[((x-1) + z * zLen)*3 + 0], vertex[((x-1) + z * zLen)*3 + 1], vertex[((x-1) + z * zLen)*3 + 2]);
			b = SetVector(vertex[(x + (z-1) * zLen)*3 + 0], vertex[(x + (z-1) * zLen)*3 + 1], vertex[(x + (z-1) * zLen)*3 + 2]);
			c = SetVector(vertex[((x-1) + (z-1) * zLen)*3 + 0], vertex[((x-1) + (z-1) * zLen)*3 + 1], vertex[((x-1) + (z-1) * zLen)*3 + 2]);
		} else {
			a = SetVector(vertex[((x-1) + z * zLen)*3 + 0], vertex[((x-1) + z * zLen)*3 + 1], vertex[((x-1) + z * zLen)*3 + 2]);
			b = SetVector(vertex[(x + (z+1) * zLen)*3 + 0], vertex[(x + (z+1) * zLen)*3 + 1], vertex[(x + (z+1) * zLen)*3 + 2]);
			c = SetVector(vertex[((x-1) + (z+1) * zLen)*3 + 0], vertex[((x-1) + (z+1) * zLen)*3 + 1], vertex[((x-1) + (z+1) * zLen)*3 + 2]);
		}
	} else {
		if(z != 0){
			a = SetVector(vertex[((x+1) + z * zLen)*3 + 0], vertex[((x+1) + z * zLen)*3 + 1], vertex[((x+1) + z * zLen)*3 + 2]);
			b = SetVector(vertex[(x + (z-1) * zLen)*3 + 0], vertex[(x + (z-1) * zLen)*3 + 1], vertex[(x + (z-1) * zLen)*3 + 2]);
			c = SetVector(vertex[((x+1) + (z-1) * zLen)*3 + 0], vertex[((x+1) + (z-1) * zLen)*3 + 1], vertex[((x+1) + (z-1) * zLen)*3 + 2]);
		} else {
			a = SetVector(vertex[((x+1) + z * zLen)*3 + 0], vertex[((x+1) + z * zLen)*3 + 1], vertex[((x+1) + z * zLen)*3 + 2]);
			b = SetVector(vertex[(x + (z+1) * zLen)*3 + 0], vertex[(x + (z+1) * zLen)*3 + 1], vertex[(x + (z+1) * zLen)*3 + 2]);
			c = SetVector(vertex[((x+1) + (z+1) * zLen)*3 + 0], vertex[((x+1) + (z+1) * zLen)*3 + 1], vertex[((x+1) + (z+1) * zLen)*3 + 2]);
		}		
	}
	returnVector = CalcNormalVector(a,b,c);
	return returnVector;
} 

Model* GenerateTerrain(TextureData *tex)
{
	int vertexCount = tex->width * tex->height;
	int triangleCount = (tex->width-1) * (tex->height-1) * 2;
	int x, z;
	
	GLfloat *vertexArray = malloc(sizeof(GLfloat) * 3 * vertexCount);
	GLfloat *normalArray = malloc(sizeof(GLfloat) * 3 * vertexCount);
	GLfloat *texCoordArray = malloc(sizeof(GLfloat) * 2 * vertexCount);
	GLuint *indexArray = malloc(sizeof(GLuint) * triangleCount*3);
	
	printf("bpp %d\n", tex->bpp);
	for (x = 0; x < tex->width; x++)
		for (z = 0; z < tex->height; z++)
		{
// Vertex array. You need to scale this properly
			vertexArray[(x + z * tex->width)*3 + 0] = x / 1.0;
			vertexArray[(x + z * tex->width)*3 + 1] = 4*tex->imageData[(x + z * tex->width) * (tex->bpp/8)] / 100.0;
			vertexArray[(x + z * tex->width)*3 + 2] = z / 1.0;
// Normal vectors. You need to calculate these.
			if(x != 0 && z != 0){
				vec3 temp = calculateNormal(x,z, tex->width, vertexArray);
				
				normalArray[(x + z * tex->width)*3 + 0] = temp.x;	//N_x
				normalArray[(x + z * tex->width)*3 + 1] = temp.y;	//N_y
				normalArray[(x + z * tex->width)*3 + 2] = temp.z;	//N_z
			}
			if (x == tex->width-1 && z == tex->height-1){
				vec3 temp = calculateNormal(0,0, tex->width, vertexArray);
			
				normalArray[(0 + 0 * tex->width)*3 + 0] = temp.x;	//N_x
				normalArray[(0 + 0 * tex->width)*3 + 1] = temp.y;	//N_y
				normalArray[(0 + 0 * tex->width)*3 + 2] = temp.z;	//N_z
			}			
// Texture coordinates. You may want to scale them.
			texCoordArray[(x + z * tex->width)*2 + 0] = x; // (float)x / tex->width;
			texCoordArray[(x + z * tex->width)*2 + 1] = z; // (float)z / tex->height;
		}
	for (x = 0; x < tex->width-1; x++)
		for (z = 0; z < tex->height-1; z++)
		{
		// Triangle 1
			indexArray[(x + z * (tex->width-1))*6 + 0] = x + z * tex->width;
			indexArray[(x + z * (tex->width-1))*6 + 1] = x + (z+1) * tex->width;
			indexArray[(x + z * (tex->width-1))*6 + 2] = x+1 + z * tex->width;
		// Triangle 2
			indexArray[(x + z * (tex->width-1))*6 + 3] = x+1 + z * tex->width;
			indexArray[(x + z * (tex->width-1))*6 + 4] = x + (z+1) * tex->width;
			indexArray[(x + z * (tex->width-1))*6 + 5] = x+1 + (z+1) * tex->width;
		}
	
	// End of terrain generation
	
	// Create Model and upload to GPU:

	Model* model = LoadDataToModel(
			vertexArray,
			normalArray,
			texCoordArray,
			NULL,
			indexArray,
			vertexCount,
			triangleCount*3);

	return model;
}

// vertex array object
Model *m, *m2, *tm;
mat4 camMatrix;
// Reference to shader program
GLuint program;
GLuint tex1, tex2;
mat4 sphereTransform;
TextureData ttex; // terrain
int t = 0;

GLfloat calcHeight(GLfloat in_x, GLfloat in_z, int zLen, GLfloat *vertex){
	int x, z;
	vec3 n;
	x = (int) floor(in_x);
	z = (int) floor(in_z);
	float quad_x = in_x - x;
	float quad_z = in_z - z;
	GLfloat y_o, y_x, y_z, y_xz, res, d;
	
	if(quad_x + quad_z <= 1){	//Near triangle in quad
		y_o = vertex[(x + z * zLen)*3 + 1];
		y_x = vertex[((x+1) + z * zLen)*3 + 1];
		y_z = vertex[(x + (z+1) * zLen)*3 + 1];
		vec3 ox, oz;
		ox = SetVector(1,y_x-y_o,0);
		oz = SetVector(0,y_z-y_o,1);
		n = CrossProduct(ox,oz);
		d = -(n.x*x + n.y*y_o + n.z*z);
		res = (-d -n.x*in_x-n.z*in_z)/n.y;
		if(t == 0){
			printf("X_in: %f, Z_in: %f\n", in_x, in_z);
			printf("X: %f, Z: %f, res: %f\n", quad_x, quad_z, res);
		}
		return res;
		/*
		GLfloat calc = quad_z * y_z + (1-quad_x-quad_z)*y_o + quad_x*y_x;
		if(t == 0){
			printf("X_in: %f, Z_in: %f\n", in_x, in_z);
			printf("X: %f, Z: %f, Y_o: %f, Y_x: %f, Y_z: %f, calc: %f\n", quad_x, quad_z, y_o, y_x, y_z, calc);
		}
		return calc;
		*/
	} else {			//Far triangle in quad
		y_xz = vertex[((x+1) + (z+1) * zLen)*3 + 1]; 
		y_x = vertex[((x+1) + z * zLen)*3 + 1];
		y_z = vertex[(x + (z+1) * zLen)*3 + 1];
		vec3 xz_x, xz_z;
		xz_x = SetVector(1-1,y_x-y_xz,0-1);
		xz_z = SetVector(0-1,y_z-y_xz,1-1);
		n = CrossProduct(xz_x,xz_z);
		d = -(n.x*(x+1) + n.y*y_xz + n.z*(z+1));
		res = (-d -n.x*in_x-n.z*in_z)/n.y;
		return res;
		/*GLfloat calc = (1-quad_x) * y_z + (quad_x-quad_z)* y_xz + quad_z * y_x;
		if(t == 0){
			printf("X_in: %f, Z_in: %f\n", in_x, in_z);
			printf("X: %f, Z: %f, Y_xz: %f, Y_x: %f, Y_z: %f, calc: %f\n", quad_x, quad_z, y_xz, y_x, y_z, calc);
		}
		return calc;*/
	}
}

void checkInput(){
	if(glutKeyIsDown('w')){
		camMatrix = Mult(camMatrix, T(0,0,0.4f));
	}	
	if(glutKeyIsDown('s')){
		camMatrix = Mult(camMatrix, T(0,0,-0.4f));
	}	
	if(glutKeyIsDown('a')){
		camMatrix = Mult(camMatrix, T(0.4f,0,0));
	}	
	if(glutKeyIsDown('d')){
		camMatrix = Mult(camMatrix, T(-0.4f,0,0));
	}	
	if(glutKeyIsDown('i')){
		camMatrix = Mult(camMatrix, T(0,-0.4f,0));
	}	
	if(glutKeyIsDown('k')){
		camMatrix = Mult(camMatrix, T(0,0.4f,0));
	}
	if(glutKeyIsDown('j')){
		camMatrix = Mult(Ry(-1*M_PI/180),camMatrix );
	}
	if(glutKeyIsDown('l')){
		camMatrix = Mult(Ry(1*M_PI/180),camMatrix );
	}	
	if(glutKeyIsDown(GLUT_KEY_DOWN)){
		sphereTransform.m[3] -= sphereSpeed;
	}	
	if(glutKeyIsDown(GLUT_KEY_UP)){
		sphereTransform.m[3] += sphereSpeed;
	}	
	if(glutKeyIsDown(GLUT_KEY_RIGHT)){
		sphereTransform.m[11] += sphereSpeed;
	}	
	if(glutKeyIsDown(GLUT_KEY_LEFT)){
		sphereTransform.m[11] -= sphereSpeed;
	}	
	if(glutKeyIsDown('+')){
		if(t == 0){
		sphereSpeed += 0.01f;
		printf("Speed: %f\n", sphereSpeed);
		}
	}	
	if(glutKeyIsDown('-')){
		if(t== 0){
		sphereSpeed -= 0.01f;
		printf("Speed: %f\n", sphereSpeed);
		}
	}
	if(glutKeyIsDown('r')){
		vec3 cam = {0, 5, 8};
		vec3 lookAtPoint = {2, 5, 2};
		camMatrix = lookAt(cam.x, cam.y, cam.z,
					lookAtPoint.x, lookAtPoint.y, lookAtPoint.z,
					0.0, 1.0, 0.0);
	}	
	if(t++ <= 10){
		if(t == 10){
			//printf("X: %f, Y: %f, Z: %f\n", camMatrix.m[3], camMatrix.m[7], camMatrix.m[11]);
			t = 0;
		}
	}
}


void init(void)
{
	// GL inits
	glClearColor(0.8,0.8,0.8,0);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	printError("GL inits");

	m = LoadModelPlus("../object/groundsphere.obj");

	projectionMatrix = frustum(-0.1, 0.1, -0.1, 0.1, 0.2, 1000.0);

	// Load and compile shader
	program = loadShaders("terrain.vert", "terrain.frag");
	glUseProgram(program);
	printError("init shader");
	
	sphereTransform = IdentityMatrix();
	sphereSpeed = 0.1f;
	
	glUniformMatrix4fv(glGetUniformLocation(program, "projMatrix"), 1, GL_TRUE, projectionMatrix.m);
	glUniform1i(glGetUniformLocation(program, "tex"), 0); // Texture unit 0
	LoadTGATextureSimple("../texture/Grass_tile_B_diffuse.tga", &tex1);
	
	vec3 cam = {0, 0, 0};
	vec3 lookAtPoint = {1, 0, 0};
	camMatrix = lookAt(cam.x, cam.y, cam.z,
				lookAtPoint.x, lookAtPoint.y, lookAtPoint.z,
				0.0, 1.0, 0.0);
// Load terrain data
	
	LoadTGATextureData("../texture/fft-terrain.tga", &ttex);
	tm = GenerateTerrain(&ttex);
	printError("init terrain");
}

void display(void)
{
	// clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	mat4 total, modelView;
	
	printError("pre display");
	
	glUseProgram(program);

	// Build matrix
	
	modelView = IdentityMatrix();
	total = Mult(camMatrix, modelView);
	glUniformMatrix4fv(glGetUniformLocation(program, "mdlMatrix"), 1, GL_TRUE, total.m);
	
	glBindTexture(GL_TEXTURE_2D, tex1);		// Bind Our Texture tex1
	glUniform1i(glGetUniformLocation(program, "color"), false);
	DrawModel(tm, program, "inPosition", "inNormal", "inTexCoord");

	printError("display 2");

	//Draw sphere
	mat4 trans = T(0.0f, 0.0f, 0.0f);
	mat4 rot = Ry(0);
	mat4 scale = S(1.0f,1.0f,1.0f);
	total = Mult(trans,scale);
	total = Mult(rot, total);
	total.m[7] = calcHeight(sphereTransform.m[3], sphereTransform.m[11], ttex.width, tm->vertexArray);
	mat4 complete = Mult(camMatrix,Mult(total,sphereTransform));
	glUniformMatrix4fv(glGetUniformLocation(program, "mdlMatrix"), 1, GL_TRUE, complete.m);
	glUniform1i(glGetUniformLocation(program, "color"), true);
	DrawModel(m, program, "inPosition", "inNormal", "inTexCoord");

	glutSwapBuffers();
}

void timer(int i)
{
	glutTimerFunc(20, &timer, i);
	checkInput();
	glutPostRedisplay();
}

void mouse(int x, int y)
{
	//printf("%d %d\n", x, y);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
	glutInitContextVersion(3, 2);
	glutInitWindowSize (600, 600);
	glutCreateWindow ("TSBK07 Lab 4");
	glutDisplayFunc(display);
	init ();
	glutTimerFunc(20, &timer, 0);

	glutPassiveMotionFunc(mouse);

	glutMainLoop();
	exit(0);
}
