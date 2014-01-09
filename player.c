#include <amlib.h>
#include <agGamePad.h>

#include "export.h"
#include "player.h"
#include "pad.h"
#include "extern.h"

#define VELOCITY 1
#define PITCHACCELBAND 0.01
#define PITCHACCELBANDLIMIT 0.1

#define ROLLACCELBAND 0.01
#define ROLLACCELBANDLIMIT 0.1


void playerInit(Object *dp,int pid)
{
	dp->translation.X=0;
	dp->translation.Y=0;
	dp->translation.Z=10;
	
	dp->direction.X=0;
	dp->direction.Y=0;
	dp->direction.Z=-1;

	dp->yaw=0;
	dp->roll=0;
	dp->pitch=0;

	dp->mov = player_move;
	dp->drw = player_drw;

	dp->pid = pid;

	dp->visibility=1;
	
	dp->pitchAccelerator=0;
	dp->rollAccelerator=0;
}


/* TODO:今西
半径で判定以上に当たり判定をしたければ書く 
*/
int player_hc2(Object *dp,Object *sp,float cx, float cy, float cz)
{

}
/* TODO:今西
パッド処理
*/
void player_move(Object *dp)
{
  AGGLfloat c[3];
  AGGLfloat t[3];
  AGGLfloat u[3];
  float cp,sp,cb,sb,ch,sh;
  float tx,ty,tz;
  float nx,ny,nz;
  AGGLfloat aspect;
  u32 pad;

  pad = agGamePadGetData(dp->pid);
  
  if( (pad & GAMEPAD_L) != 0 ){
	if(dp->rollAccelerator>0) dp->rollAccelerator=0;
	dp->rollAccelerator-=ROLLACCELBAND;
	if(dp->rollAccelerator<-ROLLACCELBANDLIMIT) dp->rollAccelerator=-ROLLACCELBANDLIMIT;
	dp->roll+=dp->rollAccelerator;
	if(dp->roll<-PI/6){
		dp->roll=-PI/6;
		dp->rollAccelerator=0;
	}
    dp->yaw+=0.04;
  }else if( (pad & GAMEPAD_R) != 0 ){
  
	if(dp->rollAccelerator<0) dp->rollAccelerator=0;
	dp->rollAccelerator+=ROLLACCELBAND;
	if(dp->rollAccelerator>ROLLACCELBANDLIMIT) dp->rollAccelerator=ROLLACCELBANDLIMIT;
	dp->roll+=dp->rollAccelerator;
	if(dp->roll>PI/6){
		dp->roll=PI/6;
		dp->rollAccelerator=0;
	}
    dp->yaw-=0.04;
  }else{
  
	if(dp->roll<0)
	{
		dp->rollAccelerator+=ROLLACCELBAND;
		if(dp->rollAccelerator>ROLLACCELBANDLIMIT) dp->rollAccelerator=ROLLACCELBANDLIMIT;
		dp->roll+=dp->rollAccelerator;
		if(dp->roll<-PI/3) dp->roll=-PI/3;
		else if(dp->roll>=0){
			dp->roll=0;
			dp->rollAccelerator=0;
		}
	}else if(dp->roll>0){
		dp->rollAccelerator-=ROLLACCELBAND;
		if(dp->rollAccelerator<-ROLLACCELBANDLIMIT) dp->rollAccelerator=-ROLLACCELBANDLIMIT;
		dp->roll+=dp->rollAccelerator;
		if(dp->roll>PI/3) dp->roll=PI/3;
		else if(dp->roll<=0){
			dp->roll=0;
			dp->rollAccelerator=0;
		}
	}else{
		dp->rollAccelerator=0;
	}
  }

  if ((pad & GAMEPAD_U) != 0){
	if(dp->pitchAccelerator>0) dp->pitchAccelerator=0;
	dp->pitchAccelerator-=PITCHACCELBAND;
	if(dp->pitchAccelerator<-PITCHACCELBANDLIMIT) dp->pitchAccelerator=-PITCHACCELBANDLIMIT;
	dp->pitch+=dp->pitchAccelerator;
	if(dp->pitch<-PI/3){
		dp->pitch=-PI/3;
		dp->pitchAccelerator=0;
	}
  }else if((pad & GAMEPAD_D) != 0){
	if(dp->pitchAccelerator<0) dp->pitchAccelerator=0;
	dp->pitchAccelerator+=PITCHACCELBAND;
	if(dp->pitchAccelerator>PITCHACCELBANDLIMIT) dp->pitchAccelerator=PITCHACCELBANDLIMIT;
	dp->pitch+=dp->pitchAccelerator;
	if(dp->pitch>PI/3){
		dp->pitch=PI/3;
		dp->pitchAccelerator=0;
	}
  }else{
	if(dp->pitch<0)
	{
		dp->pitchAccelerator+=PITCHACCELBAND;
		if(dp->pitchAccelerator>PITCHACCELBANDLIMIT) dp->pitchAccelerator=PITCHACCELBANDLIMIT;
		dp->pitch+=dp->pitchAccelerator;
		if(dp->pitch<-PI/3) dp->pitch=-PI/3;
		else if(dp->pitch>=0){
			dp->pitch=0;
			dp->pitchAccelerator=0;
		}
	}else if(dp->pitch>0){
		dp->pitchAccelerator-=PITCHACCELBAND;
		if(dp->pitchAccelerator<-PITCHACCELBANDLIMIT) dp->pitchAccelerator=-PITCHACCELBANDLIMIT;
		dp->pitch+=dp->pitchAccelerator;
		if(dp->pitch>PI/3) dp->pitch=PI/3;
		else if(dp->pitch<=0){
			dp->pitch=0;
			dp->pitchAccelerator=0;
		}
	}else{
		dp->pitchAccelerator=0;
	}
  }

  ch=cosf(dp->yaw);
  sh=sinf(dp->yaw);
  cp=cosf(dp->pitch);
  sp=sinf(dp->pitch);
  //cb=cosf(dp->roll);
  //sb=sinf(dp->roll);
  cb=1;
  sb=0;

  tx=0;
  ty=0;
  tz=-1;

  //dp->direction.X=(ch*cb+sh*sp*sb)*tx+(-ch*sb+sh*sp*cb)*ty+(sh*cp)*tz;
  //dp->direction.Y=(sb*cp)*tx+(cb*cp)*ty+(-sp)*tz;
  //dp->direction.Z=(-sh*cb+ch*sp*sb)*tx+(sb*sh+ch*sp*cb)*ty+(ch*cp)*tz;
  
  dp->direction.X=(sh*cp)*tz;
  dp->direction.Y=-sp*tz;
  dp->direction.Z=(ch*cp)*tz;
  
  
  dp->translation.X+=dp->direction.X*VELOCITY;
  dp->translation.Y+=dp->direction.Y*VELOCITY; 
  dp->translation.Z+=dp->direction.Z*VELOCITY;

  if(agGamePadGetMyID()==dp->pid){
  
    ty=1;
	nx=(-ch*sb+sh*sp*cb)*ty;
	ny=(cb*cp)*ty;
	nz=(sb*sh+ch*sp*cb)*ty;
	c[0]=dp->translation.X-10*dp->direction.X+2.5*nx;
	c[1]=dp->translation.Y-10*dp->direction.Y+2.5*ny;
	c[2]=dp->translation.Z-10*dp->direction.Z+2.5*nz;
  
	t[0]=dp->translation.X+1*nx;
	t[1]=dp->translation.Y+1*ny;
	t[2]=dp->translation.Z+1*nz;
  
	u[0]=nx;
	u[1]=ny;
	u[2]=nz;
  
	aspect = ((AGGLfloat)FB_WIDTH) / ((AGGLfloat)FB_HEIGHT);
	agglMatrixMode( AGGL_PROJECTION );
	agglLoadIdentity();
	agglPerspectivef( 25.0, aspect, 1, 1000 ); 
	agglMatrixMode( AGGL_MODELVIEW );

	agglLoadIdentity() ;
	//agglLookAtf(c[0],c[1],c[2],t[0],t[1],t[2],u[0],u[1],u[2]);
	agglLookAtf(100,100,100,dp->translation.X,dp->translation.Y,dp->translation.Z,0,1,0);
	
	_dprintf("%f %f %f\n",u[0],u[1],u[2]);
  }
}

/* TODO:今西
描画
*/
void player_drw(Object *dp)
{

	int err;
	/* 描画 */
		/* 不透明 */
	agglDisable( AGGL_BLEND );
	agglDepthMask( AGGL_TRUE );
	
	agglPushMatrix();
	
	agglTranslatef(dp->translation.X,dp->translation.Y,dp->translation.Z);

	agglRotatef(dp->roll/PI*180,dp->direction.X,dp->direction.Y,dp->direction.Z);
	agglRotatef(dp->yaw/PI*180,0,1,0);
	agglRotatef(dp->pitch/PI*180,1,0,0);
		/* ツリー→ワールド座標変換 */
	ag3dSetRoot( 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, node );

	
		/* ツリー形状を求める */
	ag3dCalcTree( &(age3dTree[ AG_AG3D_AG3DEXPORTTREE ]), &(age3dMotion[ 0 ]), (float)0, node );
	ag3dDrawAnimenodeDCmd( &(age3dModel[ AG_AG3D_AG3DEXPORTMODEL ]), node, &(age3dDCmd[ AG_AG3D_AG3DEXPORTMODEL ]), AG3D_OFFBLEND_ONDEPTH );

	agglPopMatrix();
	
		/* 半透明、Ｚバッファ更新 */
	agglEnable( AGGL_BLEND );

	agglBeginZsort( AGGL_FAR_FIRST, sizeof(zsortbuf), zsortbuf );
	ag3dDrawAnimenode( &(age3dModel[ AG_AG3D_AG3DEXPORTMODEL ]), node, AG3D_ONBLEND_ONDEPTH );
	
}
