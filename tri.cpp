#include <GL/glut.h>
#include <stdlib.h>

void renderScene(void) {
glClear(GL_COLOR_BUFFER_BIT);
glColor3f( 1,1,1);
glBegin(GL_TRIANGLES);
glColor3f( 0,1,0);
glVertex3f(0.0, 0.0, 0.0);
glVertex3f(0.5, 0.0, 0.0);
glVertex3f(0.0, 0.5, 0.0);
glEnd();
glFlush();
}

int main(int argc, char** argv) {
glutInit(&argc, argv);
glutInitWindowPosition(0,0);
glutInitWindowSize(700,700);
glutInitDisplayMode(GLUT_DEPTH | GLUT_SINGLE | GLUT_RGBA);
glutCreateWindow("GLUT");
glutDisplayFunc(renderScene);
glutMainLoop();
} 