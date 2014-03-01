// scoring.h - 2010
// By Naman Gupta

#ifndef SCORING_H
#define SCORING_H

#include <GL/glx.h>     // Header file fot the glx libraries.
#include <GL/glut.h>    // Header File For The GLUT Library 
#include <GL/gl.h>	// Header File For The OpenGL32 Library
#include <GL/glu.h>	// Header File For The GLu32 Library

#include <stdio.h>      // Header file for standard file i/o.




GLuint base;
GLvoid BuildFont(GLvoid) 
{
    Display *dpy;
    XFontStruct *fontInfo;  // storage for our font.

    base = glGenLists(96);                      // storage for 96 characters.
    
   
    dpy = XOpenDisplay(NULL); // default to DISPLAY env.   

    fontInfo = XLoadQueryFont(dpy, "-adobe-helvetica-medium-r-normal--30-*-*-*-p-*-iso8859-1");
    if (fontInfo == NULL) {
	fontInfo = XLoadQueryFont(dpy, "fixed");
	if (fontInfo == NULL) {
	    printf("no X font available?\n");
	}
    }

    // after loading this font info, this would probably be the time
    // to rotate, scale, or otherwise twink your fonts.  

    // start at character 32 (space), get 96 characters (a few characters past z), and
    // store them starting at base.
    glXUseXFont(fontInfo->fid, 32, 96, base);

    // free that font's info now that we've got the 
    // display lists.
    XFreeFont(dpy, fontInfo);

    // close down the 2nd display connection.
    XCloseDisplay(dpy);
}

GLvoid KillFont(GLvoid)                         // delete the font.
{
    glDeleteLists(base, 96);                    // delete all 96 characters.
}

GLvoid glPrint(char *text)                      // custom gl print routine.
{
    if (text == NULL) {                         // if there's no text, do nothing.
	return;
    }
    
    glPushAttrib(GL_LIST_BIT);                  // alert that we're about to offset the display lists with glListBase
    glListBase(base - 32);                      // sets the base character to 32.

    glCallLists(strlen(text), GL_UNSIGNED_BYTE, text); // draws the display list text.
    glPopAttrib();                              // undoes the glPushAttrib(GL_LIST_BIT);
}

#endif
