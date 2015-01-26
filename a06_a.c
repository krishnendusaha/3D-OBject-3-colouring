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

Face  *faces;
Vertex *vertices;


int  seek_next_line(FILE *f)
{
  char c;
  while((c=fgetc(f))!='\n')
  {
    if(feof(f))  return  1;  
  }  
  return 0;
}


int b_search(int key,int min,int max,int *arr)
{
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
   int ret=  b_search(key,0,size,vertices[vertex].adj_faces);
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
 
   for(i=0;i<vertices[less_adj_faces].no_of_adj_faces;i++)
   {
     if(search(vertices[less_adj_faces].adj_faces[i],more_adj_faces))
                                                { 
                                                    if(flag==0) {a.face1=vertices[less_adj_faces].adj_faces[i];flag=1;} 
                                                    else        {a.face2=vertices[less_adj_faces].adj_faces[i];       } 
                                                }
   }
 return a;
}


int find_appropriate_colour(int adj1,int adj2,int adj3)
{
   int col[3]={1,1,1};
   if(faces[adj1].colour!=-1){col[faces[adj1].colour]=0;}
   if(faces[adj2].colour!=-1){col[faces[adj2].colour]=0;}
   if(faces[adj3].colour!=-1){col[faces[adj3].colour]=0;}
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
    int a;

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

    rewind(f1);
 
    faces=(Face *)malloc(sizeof(Face)*f_count);
    vertices=(Vertex*)malloc(sizeof(Vertex)*(v_count+1));
  
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
        vertices[v_count].adj_faces=(int*)malloc(sizeof(int)*40);
        vertices[v_count].no_of_adj_faces=0;
        v_count++;
      }  
      else if(c=='f')
      {
        fscanf(f1,"%d %d %d ",&p,&q,&r);
        faces[f_count].f_vertices[0]=p;
        faces[f_count].f_vertices[1]=q;
        faces[f_count].f_vertices[2]=r;
        vertices[p].adj_faces[vertices[p].no_of_adj_faces++]=f_count;
        vertices[q].adj_faces[vertices[q].no_of_adj_faces++]=f_count;
        vertices[r].adj_faces[vertices[r].no_of_adj_faces++]=f_count;        
        f_count++;
      }
      else
      {
        if(seek_next_line(f1)) {  printf("break\n"); break;}
      }
    
   }
      fclose(f1);
      // Adj_Face  adj;
      // int j; 
      // for(i=0;i<f_count;i++)
      // { 
      //   adj=find_adj_faces(faces[i].f_vertices[0],faces[i].f_vertices[1]);
      //   if(adj.face1>=f_count||adj.face2>=f_count){printf("errora %d \n",i );  return 0;}
      //   if(adj.face1==i)
      //   { 
      //     j=0;
      //     while(faces[adj.face1].adj_faces[j]!=-1){j++;} 
      //     faces[adj.face1].adj_faces[j]=adj.face2; 
      //   }  
      //   else
      //   {
      //     j=0;
      //     while(faces[adj.face2].adj_faces[j]!=-1){j++;}
      //     faces[adj.face2].adj_faces[j]=adj.face1;
      //   }
  
      //  adj=find_adj_faces(faces[i].f_vertices[1],faces[i].f_vertices[2]);
      //  if(adj.face1>=f_count||adj.face2>=f_count){printf("errorb %d \n",i );return 0;}

      //  if(adj.face1==i)
      //  { 
      //     j=0;
      //     while(faces[adj.face1].adj_faces[j]!=-1){j++;}
      //     faces[adj.face1].adj_faces[j]=adj.face2;
      //  }
      //  else
      //  { 
      //    j=0;
      //    while(faces[adj.face2].adj_faces[j]!=-1){j++;} 
      //    faces[adj.face2].adj_faces[j]=adj.face1;
      //  }

      //   adj=find_adj_faces(faces[i].f_vertices[2],faces[i].f_vertices[0]);
      //   if(adj.face1>=f_count||adj.face2>=f_count){printf("errorc %d \n",i );return 0;}

      //   if(adj.face1==i)
      //   { 
      //     j=0;
      //     while(faces[adj.face1].adj_faces[j]!=-1){j++;}
      //     faces[adj.face1].adj_faces[j]=adj.face2; 
      //   }
      //   else
      //   { 
      //     j=0;
      //     while(faces[adj.face2].adj_faces[j]!=-1){j++;}
      //     faces[adj.face2].adj_faces[j]=adj.face1;
      //   }
 
      // } 


      int adj1,adj2,adj3;  
      // for(i=0;i<f_count;i++)
      // {
      //   adj1=faces[i].adj_faces[0];
      //   adj2=faces[i].adj_faces[1];
      //   adj3=faces[i].adj_faces[2];
      //  faces[i].colour=find_appropriate_colour(adj1,adj2,adj3);
      // }  
      printf("        vertices         adj_faces          colour\n");
      for(i=0;i<f_count;i++)
      { 
        adj1=faces[i].adj_faces[0];
        adj2=faces[i].adj_faces[1];
        adj3=faces[i].adj_faces[2];
        if((faces[adj1].colour==faces[i].colour)||(faces[adj2].colour==faces[i].colour)||(faces[adj3].colour==faces[i].colour)) {printf("error %d \n",i); return 0; }
        printf("%3d-   %3d %3d %3d    %3d %3d %3d      %d %d %d -> %d\n",i,faces[i].f_vertices[0],faces[i].f_vertices[1],faces[i].f_vertices[2],faces[i].adj_faces[0],faces[i].adj_faces[1],faces[i].adj_faces[2] ,faces[adj1].colour,faces[adj2].colour,faces[adj3].colour, faces[i].colour);
      } 
  

     for(i=0;i<v_count;i++)
     {
        printf("i %f %f %f  \n",i,vertices[i].x,vertices[i].y,vertices[i].z);
     }

    printf("%d %d \n",f_count,v_count );
    return 0;
  }
