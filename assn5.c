#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct 
{
  float x;
  float y;
  float z;
	int *adj_faces;
	int no_of_adj_faces;
}Vertex;

typedef struct 
{
	int f_vertices[3];
	int adj_faces[3];
  int colour;
}Face;

typedef struct 
{
  int face1;
  int face2;
}Adj_Face;

int  seek_next_line(FILE *f)
{
  char c;
  while((c=fgetc(f))!='\n')
  {
    if(feof(f))  return  1;  
  }  
  return 0;
}

Face  *faces;
Vertex *vertices;

int b_search(int key,int min,int max,int *arr)
{
  //printf("b_search %d %d %d \n",min,max,key);
  int mid,ret;
  if(min>max) return 0; 
  mid=(min+max)/2;    
  if(arr[mid]==key){return 1;}
  else if(arr[mid]<key){ret=b_search(key,mid+1,max,arr); }
  else{ ret=b_search(key,min,mid-1,arr);}
  return ret;
}
int search(int key,int vertex)
{
   int size=vertices[vertex].no_of_adj_faces-1;
 //  printf(" search %d %d  %d \n",key,vertex,size );
   int ret=  b_search(key,0,size,vertices[vertex].adj_faces); 
 //  printf("return %d \n",ret );
   return ret;
}

Adj_Face find_adj_faces(int vertex1,int vertex2)
{
   Adj_Face a;
   int i,less_adj_faces,more_adj_faces,flag=0;
   if(vertices[vertex1].no_of_adj_faces==vertices[vertex2].no_of_adj_faces)
   {less_adj_faces=vertex1; more_adj_faces=vertex2;} 
   else
    {
      less_adj_faces=(vertices[vertex1].no_of_adj_faces>vertices[vertex2].no_of_adj_faces)?vertex2:vertex1;
      more_adj_faces=(vertices[vertex1].no_of_adj_faces<vertices[vertex2].no_of_adj_faces)?vertex2:vertex1;
    }  
  // printf("less %d  more %d  %d %d \n",less_adj_faces,more_adj_faces,vertices[less_adj_faces].no_of_adj_faces,vertices[more_adj_faces].no_of_adj_faces );
   for(i=0;i<vertices[less_adj_faces].no_of_adj_faces;i++)
   {
   //  printf("dEBG\n");
     if(search(vertices[less_adj_faces].adj_faces[i],more_adj_faces))
                                                { 
     //                                               printf("found %d\n",vertices[less_adj_faces].adj_faces[i] );
                                                    if(flag==0) {a.face1=vertices[less_adj_faces].adj_faces[i];flag=1;} 
                                                    else        {a.face2=vertices[less_adj_faces].adj_faces[i];       } 
                                                }
   }


   // for(i=0;i<vertices[vertex1].no_of_adj_faces;i++){printf("%d ",vertices[vertex1].adj_faces[i]);}
   // printf("\n");
   
   //for(i=0;i<vertices[vertex2].no_of_adj_faces;i++){printf("%d ",vertices[vertex2].adj_faces[i]);}
   //printf("\n"); 
   //a.face1=a.face2=0;
   return a;
}

void print_adj_faces(int vertex)
{  
  int i;
  for(i=0;i<vertices[vertex].no_of_adj_faces;i++){printf("%d ",vertices[vertex].adj_faces[i]);}
  printf("\n");
  return ;   
}

int find_appropriate_colour(int adj1,int adj2,int adj3)
{
  if(adj1==3714 && adj2==3712  && adj3==3756) {printf("wassup\n");}
   int col[3]={1,1,1};
   if(faces[adj1].colour!=-1) {  if(faces[adj1].colour<3) {col[faces[adj1].colour]=0;} else { faces[adj1].colour=1; col[faces[adj1].colour]=0;}  }
   if(adj1==3714 && adj2==3712  && adj3==3756) {printf("wassup1\n");}
   if(faces[adj2].colour!=-1){   if(faces[adj2].colour<3) {col[faces[adj2].colour]=0;} else { faces[adj2].colour=1; col[faces[adj2].colour]=0;} }
   if(adj1==3714 && adj2==3712  && adj3==3756) {printf("wassup2\n");}
   // printf("%d\n", faces[adj3].colour);
   if(faces[adj3].colour!=-1){   if(faces[adj3].colour<3) {col[faces[adj3].colour]=0;} else  {faces[adj3].colour=1; col[faces[adj3].colour]=0;} }
   if(adj1==3714 && adj2==3712  && adj3==3756) {printf("wassup3\n");}
   int i=0;
   while(col[i]!=1)
    { i++; }
    

   return i;
}

int main(int argc,char** argv)
{
  FILE * f1,* f2;
  if(argc==1)
  {
    f1=fopen("apple.obj","r");
    f2=fopen("apple_colour.obj","w");  
  }  
  else
  {
    char * out=(char*)malloc(sizeof(char)*20);
    strncpy(out,argv[1],strlen(argv[1])-4);
    strcat(out,"_colour.obj");
    f1=fopen(argv[1],"r");
    f2=fopen(out,"w");  
 
  }
  char c;
  int v_count=0,f_count=0,i=0;
  

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
  //  printf("%d %d \n",f_count,v_count );
  // return 0;
  rewind(f1);
 
  faces=(Face *)malloc(sizeof(Face)*f_count);
  vertices=(Vertex*)malloc(sizeof(Vertex)*(v_count+1));
  
  for(i=0;i<v_count+1;i++)
  {
    vertices[i].adj_faces=(int*)malloc(sizeof(int)*40);
    vertices[i].no_of_adj_faces=0;
  }
 
  for(i=0;i<f_count;i++)
  {
    faces[i].colour=-1;
    faces[i].adj_faces[0]=-1;
    faces[i].adj_faces[1]=-1;
    faces[i].adj_faces[2]=-1;
     
  }
 
  
   int p,q,r;
   float d,e,f;
   f_count=0;
   v_count=1;
   i=0;
  
   while(1)
   {
    
       if(feof(f1)) { break; } 
       c=fgetc(f1);
    
      if(c=='v')
      {
        fscanf(f1,"%f %f %f ",&d,&e,&f);
        vertices[v_count].x=d;
        vertices[v_count].y=e;
        vertices[v_count].z=f; 
        v_count++;
      }  
      else if(c=='f')
      {
        fscanf(f1,"%d %d %d ",&p,&q,&r);
        faces[f_count].f_vertices[0]=p;
        faces[f_count].f_vertices[1]=q;
        faces[f_count].f_vertices[2]=r;
        // printf("p\n");  
        //  if(f_count==1680){printf("ABCD%d %d  \n",p,vertices[p].no_of_adj_faces++ );}
         vertices[p].adj_faces[vertices[p].no_of_adj_faces++]=f_count;

        //  if(vertices[p].no_of_adj_faces==40){ printf("******error%d %d\n",p,f_count ); return 0;}
        //  if(p>v_count){printf("error %d %d \n",p,f_count );}
        // printf("q\n");
         vertices[q].adj_faces[vertices[q].no_of_adj_faces++]=f_count;
        //  if(vertices[q].no_of_adj_faces==40){ printf("******error%d %d\n",q,f_count ); return 0;}
        //  if(q>v_count){printf("error %d %d \n",q,f_count );}
        // printf("r\n"); 
         vertices[r].adj_faces[vertices[r].no_of_adj_faces++]=f_count;
         // if(vertices[r].no_of_adj_faces==40){ printf("******error%d %d\n",r,f_count ); return 0;}
         // if(r>v_count){printf("error %d %d \n",r,f_count );}

        f_count++;
       // printf("%d - %d %d %d \n",f_count,p,q,r );
      }
      else
      {
        if(seek_next_line(f1)) {  printf("break\n"); break;}
      }
    
   }
   
   fclose(f1);
   printf("debg1\n");
   Adj_Face  adj;
  

 
 int j; 
for(i=0;i<f_count;i++)
{
  
  adj=find_adj_faces(faces[i].f_vertices[0],faces[i].f_vertices[1]);
  if(adj.face1>=f_count||adj.face2>=f_count){printf("errora %d \n",i );  return 0;}
  if(adj.face1==i)
  { 
    j=0;
    while(faces[adj.face1].adj_faces[j]!=-1){j++;} 
    faces[adj.face1].adj_faces[j]=adj.face2; 
  }  
  else
  {
    j=0;
    while(faces[adj.face2].adj_faces[j]!=-1){j++;}
    faces[adj.face2].adj_faces[j]=adj.face1;
  }
    adj=find_adj_faces(faces[i].f_vertices[1],faces[i].f_vertices[2]);
  if(adj.face1>=f_count||adj.face2>=f_count){printf("errorb %d \n",i );return 0;}

  if(adj.face1==i)
  { 
    j=0;
    while(faces[adj.face1].adj_faces[j]!=-1){j++;}
    faces[adj.face1].adj_faces[j]=adj.face2;
  }
  else
  { 
    j=0;
    while(faces[adj.face2].adj_faces[j]!=-1){j++;} 
    faces[adj.face2].adj_faces[j]=adj.face1;
  }

  adj=find_adj_faces(faces[i].f_vertices[2],faces[i].f_vertices[0]);
  if(adj.face1>=f_count||adj.face2>=f_count){printf("errorc %d \n",i );return 0;}

  if(adj.face1==i)
  { 
    j=0;
    while(faces[adj.face1].adj_faces[j]!=-1){j++;}
    faces[adj.face1].adj_faces[j]=adj.face2; 
  }
  else
  { 
     j=0;
     while(faces[adj.face2].adj_faces[j]!=-1){j++;}
     faces[adj.face2].adj_faces[j]=adj.face1;
  }
} 
  printf("debg2\n");
  print_adj_faces(2088);
  print_adj_faces(2050);
  adj=find_adj_faces(2088,2050);
  printf("%d %d \n",adj.face1,adj.face2 );
  
   int adj1,adj2,adj3; 
   printf("        vertices         adj_faces          colour\n");
   for(i=0;i<f_count;i++)
   {
     adj1=faces[i].adj_faces[0];
     adj2=faces[i].adj_faces[1];
     adj3=faces[i].adj_faces[2];
    // if((faces[adj1].colour==faces[i].colour)||(faces[adj2].colour==faces[i].colour)||(faces[adj3].colour==faces[i].colour)) {printf("error %d \n",i); return 0; }
     printf("%3d-   %3d %3d %3d    %3d %3d %3d      %d %d %d -> %d\n",i,faces[i].f_vertices[0],faces[i].f_vertices[1],faces[i].f_vertices[2],faces[i].adj_faces[0],faces[i].adj_faces[1],faces[i].adj_faces[2] ,faces[adj1].colour,faces[adj2].colour,faces[adj3].colour, faces[i].colour);
   } 


  for(i=0;i<f_count;i++)
  {
     //printf("d %d\n",i);
     adj1=faces[i].adj_faces[0];
     adj2=faces[i].adj_faces[1];
     adj3=faces[i].adj_faces[2];
     //if(i==3713){printf("%d %d %d\n",adj1,adj2,adj3 );}
     faces[i].colour=find_appropriate_colour(adj1,adj2,adj3);
     if(i==3713) break;
  }  

  // printf("        vertices         adj_faces          colour\n");
  //  for(i=0;i<f_count;i++)
  //  {
  //    adj1=faces[i].adj_faces[0];
  //    adj2=faces[i].adj_faces[1];
  //    adj3=faces[i].adj_faces[2];
  //    if((faces[adj1].colour==faces[i].colour)||(faces[adj2].colour==faces[i].colour)||(faces[adj3].colour==faces[i].colour)) {printf("error %d \n",i); return 0; }
  //    printf("%3d-   %3d %3d %3d    %3d %3d %3d      %d %d %d -> %d\n",i,faces[i].f_vertices[0],faces[i].f_vertices[1],faces[i].f_vertices[2],faces[i].adj_faces[0],faces[i].adj_faces[1],faces[i].adj_faces[2] ,faces[adj1].colour,faces[adj2].colour,faces[adj3].colour, faces[i].colour);
  //  } 
  
   fprintf(f2,"mtllib ./e.mtl\n" );
   for(i=1;i<v_count;i++)
   {
     fprintf(f2,"v %f %f %f  \n",vertices[i].x,vertices[i].y,vertices[i].z);
   }

   fprintf(f2, "usemtl flatwhite\n");
   for(i=0;i<f_count;i++)
   {
    if(faces[i].colour==0) { fprintf(f2, "f %d %d %d \n",faces[i].f_vertices[0],faces[i].f_vertices[1],faces[i].f_vertices[2] );}
   }
    
  fprintf(f2, "usemtl  shinyred\n");
  for(i=0;i<f_count;i++)
   {
    if(faces[i].colour==1) { fprintf(f2, "f %d %d %d \n",faces[i].f_vertices[0],faces[i].f_vertices[1],faces[i].f_vertices[2] );}
   }
  
  fprintf(f2, "usemtl clearblue\n");
  for(i=0;i<f_count;i++)
   {
    if(faces[i].colour==2) { fprintf(f2, "f %d %d %d \n",faces[i].f_vertices[0],faces[i].f_vertices[1],faces[i].f_vertices[2] );}
   }


  fclose(f2);
  
printf("end\n");
return 0;
}