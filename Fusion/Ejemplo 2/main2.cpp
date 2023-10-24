#include <stdlib.h>
#include <stdio.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#define MAXZ 8.0
#define MINZ -8.0

static float solidoZ = MAXZ;
static float transparenteZ = MINZ;
static GLuint listaEsfera, listaCubo;

static void init(void)
{
   GLfloat mat_especular[] = { 1.0, 1.0, 1.0, 1.0 };
   GLfloat mat_shininess[] = { 100.0 };
   GLfloat posicion[] = { 0.5, 0.5, 1.0, 0.0 };

   glMaterialfv(GL_FRONT, GL_SPECULAR, mat_especular);
   glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
   glLightfv(GL_LIGHT0, GL_POSITION, posicion);

   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   glEnable(GL_DEPTH_TEST);

   listaEsfera = glGenLists(1);
   glNewList(listaEsfera, GL_COMPILE);
      glutSolidSphere(0.4, 16, 16);
   glEndList();

   listaCubo = glGenLists(1);
   glNewList(listaCubo, GL_COMPILE);
      glutSolidCube(0.6);
   glEndList();
}

void display(void)
{
   GLfloat mat_solido[] = { 0.75, 0.75, 0.0, 1.0 };
   GLfloat mat_cero[] = { 0.0, 0.0, 0.0, 1.0 };
   GLfloat mat_transparente[] = { 0.0, 0.8, 0.8, 0.6 };
   GLfloat mat_emision[] = { 0.0, 0.3, 0.3, 0.6 };

   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   glPushMatrix();
      glTranslatef(-0.15, -0.15, solidoZ);
      glMaterialfv(GL_FRONT, GL_EMISSION, mat_cero);
      glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_solido);
      glCallList(listaEsfera);
   glPopMatrix();

   glPushMatrix();
      glTranslatef(0.15, 0.15, transparenteZ);
      glRotatef(15.0, 1.0, 1.0, 0.0);
      glRotatef(30.0, 0.0, 1.0, 0.0);
      glMaterialfv(GL_FRONT, GL_EMISSION, mat_emision);
      glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_transparente);
      glEnable(GL_BLEND);
      glDepthMask(GL_FALSE);
      glBlendFunc(GL_SRC_ALPHA, GL_ONE);
      glCallList(listaCubo);
      glDepthMask(GL_TRUE);
      glDisable(GL_BLEND);
   glPopMatrix();

   glFlush();
}

void reshape(int w, int h)
{
   glViewport(0, 0, (GLint) w, (GLint) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   if (w <= h)
      glOrtho (-1.5, 1.5, -1.5*(GLfloat)h/(GLfloat)w,
             1.5*(GLfloat)h/(GLfloat)w, -10.0, 10.0);
   else
      glOrtho (-1.5*(GLfloat)w/(GLfloat)h,
             1.5*(GLfloat)w/(GLfloat)h, -1.5, 1.5, -10.0, 10.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y)
{
   switch (key) {
      case 'a':
      case 'A':
         solidoZ = MINZ;
         transparenteZ = MAXZ;
         glutPostRedisplay();
         break;
      case 'r':
      case 'R':
         solidoZ = MAXZ;
         transparenteZ = MINZ;
         glutPostRedisplay();
         break;
      case 27:
        exit(0);
    }
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize(400, 400);
   glutCreateWindow(argv[0]);
   init();
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutDisplayFunc(display);
   glutMainLoop();
   return 0;
}

