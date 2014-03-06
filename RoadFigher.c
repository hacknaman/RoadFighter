//  RoadFighter.c - 2010
//  by Naman Gupta


#include<math.h>
#include "texture.h"
#include "collision.h"
#include "scoring.h"
/* ascii code for the escape key */
#define ESCAPE 27
int score;
extern GLuint base;
Car burning;
extern ret;
float dir;
register float left;
register float right,part;
Car cars[5];
int super;
int ghus =0;
Car visible[100000];
int window; 
float last_distance = 0;
float susu=-2.0;
Car finish[1];
float distance = 0;
int keys[256];
//int indexArray[5];
int counter = 0; 
float part=0.0;
int filled = 0;
float velocity = 0.00;
float little_velocity = 0.01;
float acceleration = 0.0005;
int background;
float left=-0.06,right=0.06;
const float shift=0.3f,length=0.6f;
float turn=0.0,len=0.0;


void InitGL(int Width, int Height)	        // We call this right after our OpenGL window is created.
{
	
	dir= rand()%12-5;
    LoadGLTextures("Asset/background.bmp",&background);				// Load The Texture(s) 
    LoadGLTextures("Asset/car3.bmp",&cars[0].photo);
	LoadGLTextures("Asset/car3.bmp",&cars[1].photo);
    LoadGLTextures("Asset/pagal.bmp",&cars[2].photo);			
    LoadGLTextures("Asset/ullu.bmp",&cars[3].photo);
	LoadGLTextures("Asset/abc.bmp",&super);
    LoadGLTextures("Asset/end.bmp",&finish[0].photo);
    LoadGLTextures("Asset/car_burning.bmp",&cars[4].photo);
	cars[0].prop1 = 0;
	cars[0].prop2 = 0;
	cars[1].prop1 = 0;
	cars[1].prop2 = 0;
	cars[2].prop1 = 1;
	cars[2].prop2 = 0;
	cars[3].prop1 = 0;
	cars[3].prop2 = 1;
	finish[0].y=2.0f;	
    
    glEnable(GL_TEXTURE_2D);			// Enable Texture Mapping
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);	// Clear The Background Color To Blue 
    glClearDepth(1.0);				// Enables Clearing Of The Depth Buffer
    glDepthFunc(GL_LESS);			// The Type Of Depth Test To Do
    glEnable(GL_DEPTH_TEST);			// Enables Depth Testing
    glShadeModel(GL_SMOOTH);			// Enables Smooth Color Shading
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();				// Reset The Projection Matrix
    
    gluPerspective(45.0f,(GLfloat)Width/(GLfloat)Height,0.1f,100.0f);	// Calculate The Aspect Ratio Of The Window
    
    glMatrixMode(GL_MODELVIEW);
//	BuildFont();
}

/* The function called when our window is resized (which shouldn't happen, because we're fullscreen) */
void ReSizeGLScene(int Width, int Height)
{
    if (Height==0)				// Prevent A Divide By Zero If The Window Is Too Small
	Height=1;

    glViewport(0, 0, Width, Height);		// Reset The Current Viewport And Perspective Transformation

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(45.0f,(GLfloat)Width/(GLfloat)Height,0.1f,100.0f);
    glMatrixMode(GL_MODELVIEW);
}

void behave(int index)
{
	if(visible[index].prop1!=0||visible[index].prop2!=0)
	{
	//float direction;
	if(visible[index].prop1==1)
	{
			 dir = visible[index].x-left;
		//printf("batao %f\n%f", visible[index].x, left);
			
			//printf("suno yar %f\n", visible[index].x);
		}
	
	
	if(visible[index].prop2==1)
	{
	
	}
	if(visible[index].y<0.8)
		{	
		
	if(dir>0)
			
			{visible[index].x-=0.003;
			if(visible[index].x<-0.6) visible[index].x= -0.6;}
			
			else 
			{visible[index].x+=0.003;
			if(visible[index].x>0.6) visible[index].x= 0.6;}
	
	}
	}
}

/* The main drawing function. */
void DrawGLScene()
{
    int i=0;
    static int burning=0;
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// Clear The Screen And The Depth Buffer
    glLoadIdentity();				// Reset The View

    glTranslatef(0.0f,0.0f,-5.0f);              // move 5 units into the screen.
    if(len<length)
        len=part;
//Now we load the road.
    glBindTexture(GL_TEXTURE_2D, background);   // choose the texture to use.

    glBegin(GL_POLYGON);		                // begin drawing a cube
    
    glTexCoord2f(0.0f, part); glVertex3f(-1.5f, -1.5f,  1.0f);	// Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0f, part); glVertex3f( 1.5f, -1.5f,  1.0f);	// Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.5f, 1.5f-3.0*part,  1.0f);	// Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.5f, 1.5f-3.0*part,  1.0f);	// Top Left Of The Texture and Quad
    glEnd();
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.5f, 1.5-3.0*part,  1.0f);	// Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.5f, 1.5-3.0*part,  1.0f);	// Bottom Right Of The Texture and Quad
   // glTexCoord2f(1.0f, len); glVertex3f( 1.5f+len*shift/length, 1.5f-3.0f*part+3.0*len,  1.0f);	// Top Right Of The Texture and Quad


    glTexCoord2f(1.0f,part); glVertex3f(1.5,1.5f,1.0f);
    glTexCoord2f(0.0f,part); glVertex3f(-1.5,1.5f,1.0f);

    glEnd();
    if(!burning)   
        glBindTexture(GL_TEXTURE_2D, cars[0].photo);
    else
        glBindTexture(GL_TEXTURE_2D, cars[4].photo);

    glBegin(GL_QUADS);

    glTexCoord2f(0.0f, 0.0f); glVertex3f(left, -1.2f,  1.1f);	// Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f(right, -1.2f,  1.1f);	// Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f(right, -1.2+0.24,  1.1f);	// Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f(left, -1.2+0.24,  1.1f);	// Top Left Of The Texture and Quad    
                      
    glEnd();              
    //printf("%f %f\n", distance, last_distance);
    int faltu;
	for(faltu = filled-1; faltu>=0; faltu--)
	{
		if(visible[faltu].y<-2.0) 
		{
		visible[faltu].y+=little_velocity;
		visible[faltu].y-=velocity;
		counter++;
		
		}
		else
		{
		glBindTexture(GL_TEXTURE_2D, visible[faltu].photo);
		glBegin(GL_QUADS);
		
		glTexCoord2f(0.0f, 0.0f); glVertex3f(visible[faltu].x, visible[faltu].y,  1.1f);	// Bottom Left Of The Texture and Quad
		glTexCoord2f(1.0f, 0.0f); glVertex3f(visible[faltu].x+0.12, visible[faltu].y,  1.1f);	// Bottom Right Of The Texture and Quad
		glTexCoord2f(1.0f, 1.0f); glVertex3f(visible[faltu].x+0.12, visible[faltu].y+0.24,  1.1f);	// Top Right Of The Texture and Quad
		glTexCoord2f(0.0f, 1.0f); glVertex3f(visible[faltu].x, visible[faltu].y+0.24,  1.1f);	// Top Left Of The Texture and Quad    
		glEnd();
		visible[faltu].y+=little_velocity;
		visible[faltu].y-=velocity;
	behave(faltu);
		counter++;
		}
	}
	last_distance = 1.5-visible[filled-1].y;
	//float y;
	//if(velocity!=0)
	//y = 2.5/(velocity);
	//else {  y= 10000.0f;}
	//int x = (int)(2000*velocity);
	//printf("%f", y);
	//printf("conter value is %d\n", counter);
	//if(counter%(((int)(y)))==0)
	if(last_distance>=0.8)
	{
	
	{
	visible[filled] =  cars[(rand()%4)];
	visible[filled].x = (rand()%(2*655))/1000.0-0.655;
	visible[filled].y = 1.6f;
	glBindTexture(GL_TEXTURE_2D, visible[filled].photo);
	glBegin(GL_QUADS);
		
	glTexCoord2f(0.0f, 0.0f); glVertex3f(visible[filled].x, visible[filled].y,  1.1f);	// Bottom Left Of The Texture and Quad
	glTexCoord2f(1.0f, 0.0f); glVertex3f(visible[filled].x+0.12, visible[filled].y,  1.1f);	// Bottom Right Of The Texture and Quad
	glTexCoord2f(1.0f, 1.0f); glVertex3f(visible[filled].x+0.12, visible[filled].y+0.24,  1.1f);	// Top Right Of The Texture and Quad
	glTexCoord2f(0.0f, 1.0f); glVertex3f(visible[filled].x, visible[filled].y+0.24,  1.1f);	// Top Left Of The Texture and Quad    
	glEnd();
	visible[filled].y+=little_velocity;
	visible[filled].y-=velocity;
	behave(filled);
	filled++;
	//last_distance = distance;
	//printf("%f\n", visible[filled].x);
	//if(filled=1000000) filled = 0;
	}
	}
		
	//printf("%d\n", filled);
	if(collisio(visible,filled,(left+right)/2,-1.08f,0.24f,0.12f)==1)
		{burning=1; ret = 0; }
    if(distance>=100)
{
	glBindTexture(GL_TEXTURE_2D, finish[0].photo);
	glBegin(GL_QUADS);
		finish[0].x=0.0f;
	glTexCoord2f(0.0f, 0.0f); glVertex3f(finish[0].x-0.655,finish[0].y-0.05, 1.1f);	// Bottom Left Of The Texture and Quad
	glTexCoord2f(1.0f, 0.0f); glVertex3f( finish[0].x+0.655,finish[0].y-0.05, 1.1f);	// Bottom Right Of The Texture and Quad
	glTexCoord2f(1.0f, 1.0f); glVertex3f( finish[0].x+0.655,finish[0].y+0.05, 1.1f);	// Top Right Of The Texture and Quad
	glTexCoord2f(0.0f, 1.0f); glVertex3f(finish[0].x-0.655,finish[0].y+0.05, 1.1f);	// Top Left Of The Texture and Quad    
	glEnd();
		finish[0].y-=velocity;

if(collisio(finish,1,(left+right)/2,-1.08,0.1,1.4)==1)
{	glutDestroyWindow(window); 
	exit(0);
}
}
if((distance>=70.0&&distance<=70.5)||ghus==1)
{ghus=1;
	glBindTexture(GL_TEXTURE_2D, super);
	glBegin(GL_QUADS);
		
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-2.9,susu,  1.12f);	// Bottom Left Of The Texture and Quad
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-2.0,susu,  1.12f);	// Bottom Right Of The Texture and Quad
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-2.0,susu+1,  1.12f);	// Top Right Of The Texture and Quad
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-2.9,susu+1,  1.12f);	// Top Left Of The Texture and Quad    
	glEnd();
	susu+=0.05;
	if(susu>=2.0)
	{ghus=0;susu=-2.0;}
}
	if(!burning)
    {
	    if(keys['w'])
		{velocity+=acceleration; if(velocity>0.025) velocity = 0.025;  distance+= velocity; part+=velocity;   }
		if(keys['s'])
		{ velocity-=4*acceleration;  if(velocity<0.0) velocity = 0.0; distance+= 1*velocity;  part+=velocity; }
		if((!keys['w']))
		{ velocity-=acceleration;    if(velocity<0.0) velocity = 0.0; distance+= 1*velocity; part+=velocity; }
	    if(keys['a'])
		if(left >=-0.655)
	    	{	left-=0.006;	right-=0.006;	}
		else
		    burning=1;
	    if(keys['d'] )
		if( right<=0.655)
		{	right+=0.006;	left+=0.006;	}
		else
		     burning=1;
			 
		
	    if(part>=1.0f)
		part=0.0;
	    else if(part<=0.0)
		part=1.0;
    }
	if(burning)
	{
		velocity=0;
		if(keys['r']) burning = 0;
	}
	
	  glColor3f(1.0f, 1.0f, 1.0f);

  // Position The Text On The Screen
  glRasterPos2f(1.89, 0.6f);
	score+=velocity*1000;
	char text[10];
	sprintf(text, "%d", score);
//  glColor3f(.0, 0.0, 0.0);

  glPrint(text);      
           // print gl text to the screen.
 

	
	
	
    // since this is double buffered, swap the buffers to display what just got drawn.
    glutSwapBuffers();
}

/* The function called whenever a key is pressed. */
void keyPressed(unsigned char key, int x, int y) 
{
    /* avoid thrashing this procedure */
   // usleep(100);
keys[key]=1;
	//printf("%d  %d  %d  %d",'c','v','c'|'v',(int)('c')==(int)('c'|'v'));
    /* If escape is pressed, kill everything. */
    if (key == ESCAPE ) 
    { 
	/* shut down our window */
	glutDestroyWindow(window); 
      
      /* exit the program...normal termination. */
	exit(0);                   
    }
}
void keyup(unsigned char key,int x,int y)
{
keys[key]=0;
}

int main(int argc, char **argv) 
{  
    /* Initialize GLUT state - glut will take any command line arguments that pertain to it or 
       X Windows - look at its documentation at http://reality.sgi.com/mjk/spec3/spec3.html */  
    glutInit(&argc, argv);  

    /* Select type of Display mode:   
     Double buffer 
     RGBA color
     Alpha components supported 
     Depth buffer */  
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);  

    /* get a 640 x 480 window */
    glutInitWindowSize(640, 480);  

    /* the window starts at the upper left corner of the screen */
    glutInitWindowPosition(0, 0);  

    /* Open a window */  
    window = glutCreateWindow("RoadFighter - Naman");  

    /* Register the function to do all our OpenGL drawing. */
    glutDisplayFunc(&DrawGLScene);  

    /* Go fullscreen.  This is as soon as possible. */
    glutFullScreen();

    /* Even if there are no events, redraw our gl scene. */
    glutIdleFunc(&DrawGLScene);

    /* Register the function called when our window is resized. */
    glutReshapeFunc(&ReSizeGLScene);

    /* Register the function called when the keyboard is pressed. */
    glutKeyboardFunc(&keyPressed);
    glutKeyboardUpFunc(&keyup);

    /* Initialize our window. */
    InitGL(640, 480);
  
    /* Start Event Processing Engine */  
    glutMainLoop();  

    return 1;
}
