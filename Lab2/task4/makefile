# set this variable to the director in which you saved the common files
commondir = ../common/

all : lab2-4.out

lab2-4.out : lab2-4.c $(commondir)GL_utilities.c $(commondir)VectorUtils3.c $(commondir)LittleOBJLoader.c $(commondir)LoadTGA.c $(commondir)Linux/MicroGlut.c
	gcc -Wall -o lab2-4.out -I$(commondir) -I../common/Linux -DGL_GLEXT_PROTOTYPES lab2-4.c $(commondir)GL_utilities.c $(commondir)LittleOBJLoader.c $(commondir)VectorUtils3.c $(commondir)LoadTGA.c $(commondir)Linux/MicroGlut.c -lXt -lX11 -lGL -lm

clean :
	rm lab2-4.out