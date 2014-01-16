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

Vector2f Rotate(Vector2f from,int degree)
{
	Vector2f ret;
	float rad=degree*PI/180;
	ret.X=from.X*cosf(rad)-from.Y*sinf(rad);
	ret.Y=from.X*sinf(rad)+from.Y*cosf(rad);
	
	return ret;
}

void drawTex2(int texNum, int x, int y, int w,int h){
	ageTransferAAC( &DBuf, texNum, NULL, NULL );
	agDrawSETDBMODE( &DBuf, 0xff, 0, 2, 1 );
	agDrawSPRITE( &DBuf, 1, x, y, x+w, y+h );
}

void drawRect(int x,int y,int w,int h,int _r,int _g,int _b){
    AGGLfloat a,r,g,b;

    a = 1;
    r = (float)_r/255.0;
    g = (float)_g/255.0;
    b = (float)_b/255.0;
    agglColor4f( r, g, b, a );
    agglDisable(AGGL_TEXTURE_2D);
    agglDrawSpritei( x,y,x+w,y+h, 0.0f );
}


void drawTex(int texNum, int x,int y,int w, int h,float r){
	int s = 10<<2;

	agDrawSETDBMODE( &DBuf , 0xff , AG_BLEND_NORMAL , 2 , 1 );		

	ageTransferAAC( &DBuf, texNum, 0, NULL, NULL );
	{
		Vector2f rotation;
		float s, c;
		AGPolyT* p;

		s = sinf( r );
		c = cosf( r );

		p = agDrawTRIANGLE_T( &DBuf , (4-1) , 0 , 0 , 0 , 0 );

		rotation.X=-w*c-h*s;
		rotation.Y=-w*s+h*c;
		
		p->x = (s16)((int)rotation.X+x)<<2;
		p->y = (s16)((int)rotation.Y+y)<<2;
		p->u = 0<<12;
		p->v = 0<<12;
		p++;

		rotation=Rotate(rotation,-90);
		p->x = (s16)((int)rotation.X+x)<<2;
		p->y = (s16)((int)rotation.Y+y)<<2;
		p->u = 1<<12;
		p->v = 0<<12;
		p++;

		rotation=Rotate(rotation,180);

		p->x = (s16)((int)rotation.X+x)<<2;
		p->y = (s16)((int)rotation.Y+y)<<2;
		p->u = 0<<12;
		p->v = 1<<12;
		p++;

		rotation=Rotate(rotation,90);

		p->x = (s16)((int)rotation.X+x)<<2;
		p->y = (s16)((int)rotation.Y+y)<<2;
		p->u = 1<<12;
		p->v = 1<<12;
	};
}

void drawRadar(Object *dp){
	int offsetX = 874,offsetY = 618,i;
	int texs[] = {AG_CG_RED_ICON,AG_CG_BLUE_ICON,AG_CG_YELLOW_ICON,AG_CG_WHITE_ICON};

	drawTex(AG_CG_RADAR,offsetX,offsetY,100,100,0);

	for(i=0;i<PLAYER_NUMS;i++){
		Object *dp2 = &Objects[i];
		int dx, dz;

		drawTex(texs[dp2->pid],(int)(dp2->translation.X*100/SKY_SPHERE_RADIUS+offsetX),(int)(dp2->translation.Z*100/SKY_SPHERE_RADIUS+offsetY),
			6,9,atan2f(dp2->direction.Z,dp2->direction.X)-PI/2);
		drawNum((((int)(dp2->translation.X*100/SKY_SPHERE_RADIUS)<<2) +(offsetX<<2)),
			(((int)(dp2->translation.Z*100/SKY_SPHERE_RADIUS)<<2) +(offsetY<<2)),dp2->translation.Y);
	}
}

void drawAmmoBar(Object *dp){
	int w = 300,h = 20;
	drawRect(50,700-50,w,h,249,192,81);
	drawRect(50,700-50, (int)((float)w * dp->fireballCount/AMMO_LIMIT),h,235,115,12 );
}


void drawHud(Object *dp, u32 frameCount){
	int x,y,i;
	int offsetX = 400,offsetY = 400;
	int s = 10;

	drawRadar(dp);
	drawAmmoBar(dp);

	// drawRect(offsetX,offsetY,s,s);
	// drawNum(offsetX<<2,offsetY<<2,dp->translation.Y);

	// x = 0;
	// x = drawStr(x,0, "Time Limit : ");
	// x = drawNum(x,0, 100 - (frameCount/60));
	// x = drawStr(x,0, " sec");

	// x = 0;
	// x = drawStr(x,100<<2, "Life : ");
	// x = drawNum(x,100<<2, dp-> life);
	
	// for(i=0;i<PLAYER_NUMS;i++){
	// 	Object *dp2 = &Objects[i];
	// 	if(dp->pid != dp2->pid){
	// 		int dx = ((int)(dp2->translation.X - dp->translation.X))/4;
	// 		int dz = ((int)(dp2->translation.Z - dp->translation.Z))/4;

	// 		drawRect(offsetX+dx,offsetY+dz,s,s);
	// 		drawNum((offsetX+dx)<<2,(offsetY+dz)<<2,dp2->translation.Y);
	// 	}
	// }
}