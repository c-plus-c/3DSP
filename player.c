#include <amlib.h>
#include <agGamePad.h>

#include "export.h"
#include "player.h"
#include "pad.h"
#include "extern.h"


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
  if( (pad & GAMEPAD_R) != 0 )
    {
      //roll=-0.3;
      dp->yaw-=0.01;
    }
  
  if( (pad & GAMEPAD_L) != 0 )
    {
      //roll=0.3;
      dp->yaw+=0.01;
    }

  if ((pad & GAMEPAD_U) != 0)
    {
      dp->pitch+=0.02;
    }

  if((pad & GAMEPAD_D) != 0)
    {
      dp->pitch-=0.02;
    }

  ch=cosf(dp->yaw);
  sh=sinf(dp->yaw);
  cp=cosf(dp->pitch);
  sp=sinf(dp->pitch);
  cb=cosf(dp->roll);
  sb=sinf(dp->roll);

  tx=0;
  ty=0;
  tz=-0.3;

  //dp->direction.X=(ch*cb+sh*sp*sb)*tx+(-ch*sb+sh*sp*cb)*ty+(sh*cp)*tz;
  //dp->direction.Y=(sb*cp)*tx+(cb*cp)*ty+(-sp)*tz;
  //dp->direction.Z=(-sh*cb+ch*sp*sb)*tx+(sb*sh+ch*sp*cb)*ty+(ch*cp)*tz;
  
  dp->direction.X=(sh*cp)*tz;
  dp->direction.Y=-sp*tz;
  dp->direction.Z=(ch*cp)*tz;
  
  
  dp->translation.X+=dp->direction.X;
  dp->translation.Y+=dp->direction.Y; 
  dp->translation.Z+=dp->direction.Z;

  if(agGamePadGetMyID()==dp->pid){
  
    ty=1;
	nx=(-ch*sb+sh*sp*cb)*ty;
	ny=(cb*cp)*ty;
	nz=(sb*sh+ch*sp*cb)*ty;
	c[0]=dp->translation.X-30*dp->direction.X+3*nx;
	c[1]=dp->translation.Y-30*dp->direction.Y+3*ny;
	c[2]=dp->translation.Z-30*dp->direction.Z+3*nz;
  
  //t[0]=dp->translation.X;
 // t[1]=dp->translation.Y;
  //t[2]=dp->translation.Z;
  
	t[0]=dp->translation.X;
	t[1]=dp->translation.Y;
	t[2]=dp->translation.Z;
  
	u[0]=nx;
	u[1]=ny;
	u[2]=nz;
  
	aspect = ((AGGLfloat)FB_WIDTH) / ((AGGLfloat)FB_HEIGHT);
	agglMatrixMode( AGGL_PROJECTION );
	agglLoadIdentity();
	agglPerspectivef( 25.0, aspect, 1, 1000 ); 
	agglMatrixMode( AGGL_MODELVIEW );

	agglLoadIdentity() ;
	agglLookAtf(c[0],c[1],c[2],t[0],t[1],t[2],u[0],u[1],u[2]);
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
	agglRotatef(dp->roll/PI*180,0,0,1);
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
