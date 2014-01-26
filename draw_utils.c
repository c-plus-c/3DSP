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
	ageTransferAAC( &DBuf, texNum,0, NULL, NULL );
	agDrawSETDBMODE( &DBuf, 0xff, 0, 2, 1 );
	agDrawSPRITE( &DBuf, 1, x, y, x+w, y+h );
}

void drawTex4(int texNum, int x, int y,float ratio){
	int w,h;
	ageTransferAAC( &DBuf, texNum,0, &w, &h );
	agDrawSETDBMODE( &DBuf, 0xff, 0, 2, 1 );
	agDrawSPRITE( &DBuf, 1, x, y, x+w*ratio, y+h*ratio );
}

int drawTex3(int texNum, int x,int y){
	int w,h;
	ageTransferAAC( &DBuf, texNum,0, &w, &h );
	agDrawSETDBMODE( &DBuf, 0xff, 0, 2, 1 );
	agDrawSPRITE( &DBuf, 1, x, y, x+w, y+h );
	return w;
}

void drawRect(int x,int y,int w,int h,int r,int g,int b){
	agDrawSETFCOLOR( &DBuf, ARGB( 255, r, g, b) );
	agDrawSETDBMODE( &DBuf, 0xff, 0, 0, 1 );
	agDrawSPRITE( &DBuf, 0, x<<2, y<<2, (x+w)<<2, (y+h)<<2 );
}

void drawRect2(int x, int y, int w, int h, int a, int r, int g, int b){
	agDrawSETFCOLOR( &DBuf, ARGB( a, r, g, b) );
	agDrawSETDBMODE( &DBuf, 0xff, 0, 0, 1 );
	agDrawSPRITE( &DBuf, 0, x<<2, y<<2, (x+w)<<2, (y+h)<<2 );
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

	for(i=0;i<playerNum;i++){
		Object *dp2 = &Objects[i];
		int dx, dz;
		if(dp2->stat == DEAD)
			continue;
		if(dp->pid == dp2->pid){
			drawTex(texs[dp2->pid],(int)(dp2->translation.X*100/ACTIVE_RADIUS+offsetX),(int)(dp2->translation.Z*100/ACTIVE_RADIUS+offsetY),
				8,12,atan2f(dp2->direction.Z,dp2->direction.X)-PI/2);
		}else{
			drawTex(texs[dp2->pid],(int)(dp2->translation.X*100/ACTIVE_RADIUS+offsetX),(int)(dp2->translation.Z*100/ACTIVE_RADIUS+offsetY),
				6,9,atan2f(dp2->direction.Z,dp2->direction.X)-PI/2);
		}
		drawNum((((int)(dp2->translation.X*100/ACTIVE_RADIUS)<<2) +(offsetX<<2)),
			(((int)(dp2->translation.Z*100/ACTIVE_RADIUS)<<2) +(offsetY<<2)),dp2->translation.Y);
	}
}

void drawBar(int x,int y,int w,int h,int amount, int max, int colorSet){
	int r,g,b,r2,g2,b2;

	if(colorSet == 0){
		r=	249;
		g=	192;
		b=	81;
		r2=	235;
		g2=	115;
		b2=	12;
	}else{
		r=	153;
		g=	217;
		b=	219;
		r2=	74;
		g2=	83;
		b2=	142;
	}

	drawRect(x,y,w,h,255,255,255);
	drawRect(x+1,y+1,w-2,h-2,r,g,b);
	drawRect(x,y, (int)((float)w * amount/max),h,255,255,255);
	drawRect(x+1,y+1, (int)((float)w * amount/max)-2,h-2,r2,g2,b2);
}

void drawSelfInfo(Object *dp){
	int bw = 300,bh= 10,l;

	drawTex3(AG_CG_NO1+dp->pid,20,60);
	drawBar(80,17,500,10,dp->life,PLAYER_LIFE,0);
	drawBar(80,26,300,10,dp->fireballCount,AMMO_LIMIT,1);
}

void drawEnemyInfo(Object *dp, int idx){
	drawTex4(AG_CG_NO1+dp->pid,30,50 + 290*idx,0.5);
	drawBar(80,15+70*idx,150,6,dp->life,PLAYER_LIFE,0);
	drawBar(80,20+70*idx,70,6,dp->fireballCount,AMMO_LIMIT,1);
}

void drawHud(Object *dp, u32 frameCount){
	int n,i=1;
	int offsetX = 400,offsetY = 400;
	int s = 10;

	drawSelfInfo(dp);
	for(n=0;n<playerNum;n++){
		if(Objects[n].pid != dp->pid){
			drawEnemyInfo(&Objects[n],i);
			i++;
		}else if(dp->targeted>0){
			drawTex2(AG_CG_HBW, 10<<2, 650<<2, 264<<2, 91<<2);
		}
	}
	drawRadar(dp);



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