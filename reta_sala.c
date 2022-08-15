#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>

void init(void);
void display(void);

int main(int argc, char** argv){
  glutInit(&argc, argv);
  glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize (256, 256); 
  glutInitWindowPosition (100, 100); 
  glutCreateWindow ("Desenhando uma linha");
  init();
  glutDisplayFunc(display); 
  glutMainLoop();
  return 0;
}

void init(void){
  glClearColor(1.0, 1.0, 1.0, 1.0);
  glOrtho (0, 256, 0, 256, -1 ,1);
}

void sala(int x1, int x2, int y1, int y2){
int np, i;
float dx, dy, dxp, dyp, x, y;

dx = x2 - x1;
dy = y2 - y1;

np = fabs((y2,y1)) + 1;

dxp = dx / np;
dyp = dy / np;
x = x1 + 0.5;
y = y1 + 0.5;

for (i = 0; i < np; i++){
        glVertex2i(x,y);
        x += dx;
        y += dy;
    }
}

void display(void){
  int i;
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f (0.0, 0.0, 0.0);
  glBegin(GL_LINES);
  sala(120,160,200,240);  
  glEnd();
  glFlush();
}

