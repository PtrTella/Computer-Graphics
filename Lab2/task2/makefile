# set this variable to the director in which you saved the common files
commondir = ../common/

all : lab2-2.out

lab2-2.out : lab2-2.c $(commondir)GL_utilities.c $(commondir)VectorUtils3.c $(commondir)LittleOBJLoader.c $(commondir)LoadTGA.c $(commondir)Linux/MicroGlut.c
	gcc -Wall -o lab2-2.out -I$(commondir) -I../common/Linux -DGL_GLEXT_PROTOTYPES lab2-2.c $(commondir)GL_utilities.c $(commondir)LittleOBJLoader.c $(commondir)VectorUtils3.c $(commondir)LoadTGA.c $(commondir)Linux/MicroGlut.c -lXt -lX11 -lGL -lm

clean :
	rm lab2-2.out
