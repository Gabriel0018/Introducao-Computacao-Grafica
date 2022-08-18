#include <GL/glut.h>
#include <stdlib.h>

void init(void);
void display(void);

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (256, 256); 
    glutInitWindowPosition (100, 100); 
    glutCreateWindow ("Desenhando um poligono");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

void init(void){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glOrtho (0, 256, 0, 256, -1 ,1);
}

void poligonoRegular()
{   
    glVertex2i(100,150);
    glVertex2i(100,100);
    glVertex2i(150,100);
    glVertex2i(150,150);
}

void alteraTamanhoJanela(GLsizei w, GLsizei h)
{
    if(h == 0)
        h = 1;
    
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if(w<=h)
        gluOrtho2D(0.0f, 250.0f, 0.0f, 250.0f*h/w);
}

void display(void){
    int i;
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f (0.0, 0.0, 0.0);
    glBegin(GL_POLYGON); 
    poligonoRegular();
    glutReshapeFunc(alteraTamanhoJanela);  
    glEnd();
    glFlush();
}

