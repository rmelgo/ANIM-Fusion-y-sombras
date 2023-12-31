#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>

static int primeroIzquierda = GL_TRUE;

static void init(void)
{
   glEnable(GL_BLEND);
   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   glClearColor(0.0, 0.0, 0.0, 0.0);
}

static void dibujarTrianguloIzquierdo()
{
   glBegin(GL_TRIANGLES);
      glColor4f(1.0, 1.0, 0.0, 0.75);
      glVertex3f(0.1, 0.9, 0.0); 
      glVertex3f(0.1, 0.1, 0.0); 
      glVertex3f(0.7, 0.5, 0.0); 
   glEnd();
}


static void dibujarTrianguloDerecho()
{
   glBegin(GL_TRIANGLES);
      glColor4f(0.0, 1.0, 1.0, 0.75);
      glVertex3f(0.9, 0.9, 0.0); 
      glVertex3f(0.3, 0.5, 0.0); 
      glVertex3f(0.9, 0.1, 0.0); 
   glEnd();
}

void display(void)
{
   glClear(GL_COLOR_BUFFER_BIT);

   if (primeroIzquierda) {
      dibujarTrianguloIzquierdo();
      dibujarTrianguloDerecho();
   }
   else {
      dibujarTrianguloDerecho();
      dibujarTrianguloIzquierdo();
   }
   glFlush();
}

void reshape(int w, int h)
{
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   if (w <= h) 
      gluOrtho2D(0.0, 1.0, 0.0, 1.0*(GLfloat)h/(GLfloat)w);
   else 
      gluOrtho2D(0.0, 1.0*(GLfloat)w/(GLfloat)h, 0.0, 1.0);
}

void keyboard(unsigned char key, int x, int y)
{
   switch (key) {
      case 't':
      case 'T':
         primeroIzquierda = !primeroIzquierda;
         glutPostRedisplay();   
         break;
      case 27: //el 27 hace referencia al car�cter de escape
         exit(0);
         break;
      default:
         break;
   }
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
   glutInitWindowSize(400, 400);
   glutInitWindowPosition(0, 0);
   glutCreateWindow(argv[0]);
   init();
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutDisplayFunc(display);
   glutMainLoop();
   return 0;
}
