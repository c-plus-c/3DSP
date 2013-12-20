#include <amlib.h>
#include "export.h"
#include "player.h"
#include "pad.h"

static Player playerObject;

void player_init()
{
	playerObject.Obj.translation.X=0;
	playerObject.Obj.translation.Y=0;
	playerObject.Obj.translation.Z=30;
	
	playerObject.Obj.direction.X=0;
	playerObject.Obj.direction.Y=0;
	playerObject.Obj.direction.Z=-1;

	playerObject.Obj.yaw=0;
	playerObject.Obj.roll=0;
	playerObject.Obj.pitch=0;
}

void player_initWithParam(Vec3f pos,Vec3f angle)
{
	playerObject.Obj.translation.X=pos.X;
	playerObject.Obj.translation.Y=pos.Y;
	playerObject.Obj.translation.Z=pos.Z;
	
	playerObject.Obj.direction.X=angle.X;
	playerObject.Obj.direction.Y=angle.Y;
	playerObject.Obj.direction.Z=angle.Z;

	playerObject.Obj.yaw=0;
	playerObject.Obj.roll=0;
	playerObject.Obj.pitch=0;
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
  float cp,sp,cb,sb,ch,sh;
  float tx,ty,tz;
  

  if( PadLvl() & PAD_RIGHT )
    {
      //roll=-0.3;
      playerObject.Obj.yaw-=0.04;
    }
  
  if( PadLvl() & PAD_LEFT )
    {
      //roll=0.3;
      playerObject.Obj.yaw+=0.04;
    }

  if (PadLvl() & PAD_DOWN)
    {
      playerObject.Obj.pitch+=0.04;
    }

  if(PadLvl() & PAD_UP)
    {
      playerObject.Obj.pitch-=0.04;
    }

  ch=cosf(playerObject.Obj.yaw);
  sh=sinf(playerObject.Obj.yaw);
  cp=cosf(playerObject.Obj.pitch);
  sp=sinf(playerObject.Obj.pitch);
  cb=cosf(playerObject.Obj.roll);
  sb=sinf(playerObject.Obj.roll);

  tx=0;
  ty=0;
  tz=-0.3;

  //playerObject.Obj.direction.X=(ch*cb+sh*sp*sb)*tx+(-ch*sb+sh*sp*cb)*ty+(sh*cp)*tz;
  //playerObject.Obj.direction.Y=(sb*cp)*tx+(cb*cp)*ty+(-sp)*tz;
  //playerObject.Obj.direction.Z=(-sh*cb+ch*sp*sb)*tx+(sb*sh+ch*sp*cb)*ty+(ch*cp)*tz;
  
  playerObject.Obj.direction.X=(sh*cp)*tz;
  playerObject.Obj.direction.Y=-sp*tz;
  playerObject.Obj.direction.Z=(ch*cp)*tz;
  
  
  playerObject.Obj.translation.X+=playerObject.Obj.direction.X;
  playerObject.Obj.translation.Y+=playerObject.Obj.direction.Y; 
  playerObject.Obj.translation.Z+=playerObject.Obj.direction.Z;
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
	
	agglTranslatef(playerObject.Obj.translation.X,playerObject.Obj.translation.Y,playerObject.Obj.translation.Z);
	agglRotatef(playerObject.Obj.roll/PI*180,0,0,1);
	agglRotatef(playerObject.Obj.yaw/PI*180,0,1,0);
	agglRotatef(playerObject.Obj.pitch/PI*180,1,0,0);
	
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
	agglEndZsort();
       
		/* 半透明、Ｚバッファ非更新 */
	//agglEnable( AGGL_BLEND );
	//agglDepthMask( AGGL_FALSE );

	//agglBeginZsort( AGGL_FAR_FIRST, sizeof(zsortbuf), zsortbuf );
	//ag3dDrawAnimenode( &(age3dModel[ AG_AG3D_AG3DEXPORTMODEL ]), node, AG3D_ONBLEND_OFFDEPTH );
	//agglEndZsort();

	agglDepthMask( AGGL_TRUE );

	/* フレーム描画終了 */
	err = agglGetError();
	if ( err != 0 ) {
	  //_dprintf( "!!!!!!!!!!!!!! err = %x, frame = %d !!!!!!!!!!!\n" , err, 0 );
	}
}
