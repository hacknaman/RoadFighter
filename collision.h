// collision.h - 2010
// By Naman Gupta

#ifndef COLLISION_H
#define COLLISION_H
#include<stdio.h>
#include <GL/glu.h>
#include<stdlib.h>
#include<math.h>

int i=0,
ret=0;
float a,b;
//float height=0.10f;
//float hh=0.24f;
struct Car
{
int photo;
float x, y;	
int prop1, prop2;
};
typedef struct Car Car;


int collisio(Car arr[],int filled,float x,float y,float h,float w)
{
	for(i=0;i<filled;i++)
	{
		/*if(arr[i].y<=-2.0)
		break;
		lapni=x-width/2;
		rapni=x+width/2;
		lbot=arr[i].x-width/2;
		rbot=arr[i].x+width/2;
		bbot=arr[i].y-height/2;
		ubot=arr[i].y+hh/2;
		bapni=y-height/2;
		uapni=y+hh/2;
		if(lbot<=rapni&&rbot>=lapni&&bbot<=uapni&&ubot>=bapni)
			{ret=1;break;}*/
		a=arr[i].x+0.06;
		b=arr[i].y+0.12;
		if(fabs(a-x)<=w&&fabs(b-y)<=h)
			{ret=1;break;}
	}
	return ret;


}
#endif
