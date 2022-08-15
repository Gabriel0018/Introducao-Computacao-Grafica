#include <GL/glut.h>
#include <stdlib.h>

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

void bresenham(int x1, int x2, int y1, int y2){
  int dx = x2 - x1;
  int dy = y2 - y1;
  int d = (2 * dy) - dx; //valor inicial de d
  int incrementoE = 2 * dy; //incremento para mover E
  int incrementoNE = 2 * (dy-dx); //incremento para mover NE
  int x, y;
  x = x1;
  y = y1;

  glVertex2i(x,y);
 
  while(x < x2){
        if (d <= 0){ //Seleciona E
            d += incrementoE; 
            x++; 
        } 
            
        else{ //Seleciona NE
            d += incrementoNE; 
            x++; 
            y++;
        }
        glVertex2i(x,y);               
    }      
}

void display(void){
  int i;
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f (0.0, 0.0, 0.0);
  glBegin(GL_POINTS);
  bresenham(120,160,200,240);  
  glEnd();
  glFlush();
}

