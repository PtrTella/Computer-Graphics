# set this variable to the director in which you saved the common files
commondir = ../common/

all : lab3.out 

lab3.out : lab3.c $(commondir)GL_utilities.c $(commondir)VectorUtils3.c $(commondir)LittleOBJLoader.c $(commondir)LoadTGA.c $(commondir)Linux/MicroGlut.c
	gcc -Wall -o lab3.out -I$(commondir) -I../common/Linux -DGL_GLEXT_PROTOTYPES lab3.c $(commondir)GL_utilities.c $(commondir)LittleOBJLoader.c $(commondir)VectorUtils3.c $(commondir)LoadTGA.c $(commondir)Linux/MicroGlut.c -lXt -lX11 -lGL -lm


clean :
	rm lab3.out
