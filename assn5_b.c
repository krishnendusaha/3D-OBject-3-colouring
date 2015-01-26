#include <GL/glut.h>
#include <stdio.h>
GLfloat light_diffuse[] = {1.0, 0.0, 0.0, 1.0};  /* Red diffuse light. */
GLfloat light_position[] = {1.0, 1.0, 1.0, 0.0};
int f_count=0;
GLint **faces;
GLfloat **vertices;

int  seek_next_line(FILE *f)
{
  char c;
  while((c=fgetc(f))!='\n')
  {
    if(feof(f))  return  1;  
  }  
  return 0;
}


void draw(void)
{
  int i,a,b;  
  for (i = 0; i < f_count; i++) {
    glBegin(GL_TRIANGLES);
    a=faces[i][0];
    glVertex3f(vertices[a][0],vertices[a][1],vertices[a][2]);
    a=faces[i][0];
    glVertex3f(vertices[a][0],vertices[a][1],vertices[a][2]);
    a=faces[i][0];
    glVertex3f(vertices[a][0],vertices[a][1],vertices[a][2]);
    glEnd();
  }
}

void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  draw();
  glutSwapBuffers();
}

void init(void)
{

  /* Enable a single OpenGL light. */
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHTING);

  /* Use depth buffering for hidden surface elimination. */
  glEnable(GL_DEPTH_TEST);

  /* Setup the view of the cube. */
  glMatrixMode(GL_PROJECTION);
  gluPerspective( /* field of view in degree */ 40.0,
    /* aspect ratio */ 1.0,
    /* Z near */ 1.0, /* Z far */ 10.0);
  glMatrixMode(GL_MODELVIEW);
  gluLookAt(0.0, 0.0, 5.0,  /* eye is at (0,0,5) */
    0.0, 0.0, 0.0,      /* center is at (0,0,0) */
    0.0, 1.0, 0.);      /* up is in positive Y direction */

  /* Adjust cube position to be asthetic angle. */
  glTranslatef(0.0, 0.0, -1.0);
  // glRotatef(60, 1.0, 0.0, 0.0);
  // glRotatef(-20, 0.0, 0.0, 1.0);
}

int main(int argc, char **argv)
{
    FILE * f1;
    int v_count=0,i;
    char c;
    if(argc==1)
    {
      f1=fopen("apple.obj","r");
    }  
    else
    {
      f1=fopen(argv[1],"r");
    }
    

    while(1)
    {
  	   if(feof(f1)) { break; } 
  	   c=fgetc(f1);
       if(seek_next_line(f1)) {  printf("break\n"); break;}
    
       if(c=='v')
   	   {
   		v_count++;
   	   }	
       if(c=='f')
       {
     	f_count++;
       }
     
    }
    // printf("%d %d \n",f_count,v_count );
    rewind(f1);
    faces=(GLint**)malloc(sizeof(GLint*)*f_count);
    for(i=0;i<f_count;i++){  faces[i]=(GLint*)malloc(sizeof(GLint)*3); }
    vertices=(GLfloat**)malloc(sizeof(GLfloat*)*v_count);
    for(i=0;i<v_count;i++){  vertices[i]=(GLfloat*)malloc(sizeof(GLfloat)*3); }	
    // printf("ok\n");
    int p,q,r;
    float d,e,f;
    f_count=0;
    v_count=0;
    i=0;
  
    while(1)
    {
       // printf("%d %d\n",f_count,v_count);
       if(feof(f1)) { break; } 
       c=fgetc(f1);
    
      if(c=='v')
      {
        fscanf(f1,"%f %f %f ",&d,&e,&f);
        vertices[v_count][0]=d;
        vertices[v_count][1]=e;
        vertices[v_count][2]=f; 
        v_count++;
      }  
      else if(c=='f')
      {
        fscanf(f1,"%d %d %d ",&p,&q,&r);
        faces[f_count][0]=p;
        faces[f_count][1]=q;
        faces[f_count][2]=r;
        f_count++;
      }
      else
      {
        if(seek_next_line(f1)) {  printf("break\n"); break;}
      }
    }    
     // printf("vertices\n");
     // for(i=0;i<v_count;i++){printf("%d %f %f %f \n",i,vertices[i][0],vertices[i][1],vertices[i][2] );}
     // printf("faces\n");
     // for(i=0;i<f_count;i++){printf("%d %d %d %d \n",i,faces[i][0],faces[i][1],faces[i][2] );}


     //  printf("%d %d\n",f_count,v_count);
     //  return 0;
	glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("apple");
    printf("debg1\n");
    glutDisplayFunc(display);
    printf("debg2\n");
    init();
    printf("debg3\n");
    sleep(5);
    glutMainLoop();
       
    return 0;             /* ANSI C requires main to return int. */
}