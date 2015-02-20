#include <stdio.h>
#include <GL/glut.h>
#include <string>
#include "SerialClass.h"

Serial* SP;
enum COMANDO { ADELANTE = 'a', ATRAS = 'b', DERECHA = 'c', IZQUIERDA = 'd', DETENERSE = 's'};

void init (void)
{
    glClearColor(0.0,0.0,0.0,0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0,200.0,0.0,200.0);
}


void keyboardFunc(unsigned char key, int x, int y)
{
}

void enviarComando(COMANDO com){
    char* c = new char[1];
    c[0] = com;
    SP->WriteData(c, 1);
}

void specialFunc(int key, int x, int y)
{
     switch (key)
    {
       case 27 :      break;
       case 100 : printf("GLUT_KEY_LEFT %d\n",key);   break;
       case 102: printf("GLUT_KEY_RIGHT %d\n",key);  ;  break;
       case 101:
       printf("GLUT_KEY_UP %d\n",key);
       enviarComando(ADELANTE);
       break;
       case 103 : printf("GLUT_KEY_DOWN %d\n",key);  ;  break;
    }

}

void specialUpFunc(int key, int x, int y)
{
     switch (key)
    {
       case 27 :      break;
       case 100 : printf("upGLUT_KEY_LEFT %d\n",key);   break;
       case 102: printf("upGLUT_KEY_RIGHT %d\n",key);  ;  break;
       case 101:
       printf("upGLUT_KEY_UP %d\n",key);
       enviarComando(DETENERSE);
       break;
       case 103 : printf("upGLUT_KEY_DOWN %d\n",key);  ;  break;
    }

}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glFlush();
}


int main(int argc, char **argv)
{

    SP = new Serial("\\\\.\\COM4");    // adjust as needed

	if (SP->IsConnected())
		printf("We're connected\n");


    printf("Press ALT or  SHIFT or  CTRL in combination with other keys. \n\n");

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowPosition(800,20);
    glutInitWindowSize(400, 300);
    glutCreateWindow("A simple example");
    init();

    glutDisplayFunc(display);

    glutSpecialFunc( specialFunc );
    glutSpecialUpFunc( specialUpFunc );
    glutKeyboardFunc( keyboardFunc );

    glutIgnoreKeyRepeat(1);
    glutMainLoop();

return 0;
}
