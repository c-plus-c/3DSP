#include <amlib.h>

#include "export.h"
#include "extern.h"

long long int pow(long a,int b){
	long long int m = 1;
	for(;b>0;b--)
		m *= a;
	return m;
}

int drawNum(int x,int y, long long int num){
	int w,h;
	int d = 30,l = x,f = 0;
	for(;d>=0;d--){
		if(num/pow(10,d) > 0 || f==1){
			int number=num/pow(10,d) + '0' - ' ' + AG_CG_32;
			agDrawSETFCOLOR( &DBuf, ARGB( 255, 255, 0, 0 ) );
			ageTransferAAC( &DBuf,number, 0, &w, &h );
			agDrawSETDBMODE( &DBuf, 0xff, 0, 2, 1 );
			agDrawSPRITE( &DBuf, 1, l, y, l+w, y+h );

			num -= pow(10,d) *( num/pow(10,d));
			l += w;
			f = 1;
		}
	}
	return l;
}

int strlen(char* str){
	int i=0;
	while(1){
		if(str[i] == '\0')
			break;
		i++;
	}
	return i;
}


int drawStr(int x,int y, char* str){
	int l = strlen(str);
	int i,left = x;
	int w, h;

	for(i=0;i<l;i++){
		if(str[i] == '\n'){
			y += h;
			left = x;
			continue;
		}

		agDrawSETFCOLOR( &DBuf, ARGB( 255, 255, 0, 0 ) );
		ageTransferAAC( &DBuf, str[i] - ' ' + AG_CG_32, 0, &w, &h );
		agDrawSETDBMODE( &DBuf, 0xff, 0, 2, 1 );
		agDrawSPRITE( &DBuf, 1, left, y, left+(w), y+(h) );

		left += (w);
	}
	return left;
}

void drawRect(int x,int y,int w,int h){
    AGGLfloat a,r,g,b;

    a = 1;
    r = 1;
    g = 0;
    b = 0;
    agglColor4f( r, g, b, a );
    agglDrawSpritei( x,y,x+w,y+h, 0.0f );
}

void drawHud(Object *dp, u32 frameCount){
	int x,y,i;
	int offsetX = 400,offsetY = 400;
	int s = 10;

	drawRect(offsetX,offsetY,s,s);
	drawNum(offsetX<<2,offsetY<<2,dp->translation.Y);

	x = 0;
	x = drawStr(x,0, "Time Limit : ");
	x = drawNum(x,0, 100 - (frameCount/60));
	x = drawStr(x,0, " sec");

	x = 0;
	x = drawStr(x,100<<2, "Life : ");
	x = drawNum(x,100<<2, dp-> life);
	
	for(i=0;i<PLAYER_NUMS;i++){
		Object *dp2 = &Objects[i];
		if(dp->pid != dp2->pid){
			int dx = ((int)(dp2->translation.X - dp->translation.X))/4;
			int dz = ((int)(dp2->translation.Z - dp->translation.Z))/4;

			drawRect(offsetX+dx,offsetY+dz,s,s);
			drawNum((offsetX+dx)<<2,(offsetY+dz)<<2,dp2->translation.Y);
		}
	}
}