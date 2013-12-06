#include <amlib.h>
#include "export.h"
#include "player.h"
#include "pad.h"

static Object playerObject;
static double AxisX,AxisY,AxisZ;

void player_init()
{
	playerObject.translation.X=0;
	playerObject.translation.Y=0;
	playerObject.translation.Z=50;
	
	playerObject.direction.X=0;
	playerObject.direction.Y=0;
	playerObject.direction.Z=-1;
}

void player_initWithParam(Vec3f pos,Vec3f angle)
{
	playerObject.translation.X=pos.X;
	playerObject.translation.Y=pos.Y;
	playerObject.translation.Z=pos.Z;
	
	playerObject.direction.X=angle.X;
	playerObject.direction.Y=angle.Y;
	playerObject.direction.Z=angle.Z;
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
  double radius=0.05,normal;
  if( PadLvl() & PAD_LEFT )
    {
      //playerObject.direction.X-=0.01;
      playerObject.direction.X=playerObject.direction.X*cosf(radius)-playerObject.direction.Z*sinf(radius);
      playerObject.direction.Z=playerObject.direction.X*sinf(radius)+playerObject.direction.Z*cosf(radius);
    }
  
  if( PadLvl() & PAD_RIGHT )
    {
      //playerObject.direction.X+=0.01;
      playerObject.direction.X=playerObject.direction.X*cosf(-radius)-playerObject.direction.Z*sinf(-radius);
      playerObject.direction.Z=playerObject.direction.X*sinf(-radius)+playerObject.direction.Z*cosf(-radius);
    }

  if (PadLvl() & PAD_UP)
    {
      playerObject.direction.Y=playerObject.direction.Y*cosf(radius)-playerObject.direction.Z*sinf(radius);
      playerObject.direction.Z=playerObject.direction.Y*sinf(radius)+playerObject.direction.Z*cosf(radius);
    }

  if(PadLvl() & PAD_DOWN)
    {
      playerObject.direction.Y=playerObject.direction.Y*cosf(-radius)-playerObject.direction.Z*sinf(-radius);
      playerObject.direction.Z=playerObject.direction.Y*sinf(-radius)+playerObject.direction.Z*cosf(-radius);
    }

  
  normal=sqrtf(playerObject.direction.X*playerObject.direction.X+playerObject.direction.Y*playerObject.direction.Y+playerObject.direction.Z*playerObject.direction.Z);

  playerObject.direction.X/=normal;
  playerObject.direction.Y/=normal;
  playerObject.direction.Z/=normal;
  
  playerObject.translation.X+=playerObject.direction.X*0.5;
  playerObject.translation.Y+=playerObject.direction.Y*0.5; 
  playerObject.translation.Z+=playerObject.direction.Z*0.5;

  AxisX=atan2f(playerObject.direction.Y,playerObject.direction.Z)*180/PI;
  AxisY=(atan2f(playerObject.direction.X,playerObject.direction.Z)+PI)*180/PI;
  AxisZ=atan2f(playerObject.direction.X,playerObject.direction.Y)*180/PI;
}

/* TODO:今西
描画
*/
void player_drw(Object *dp)
{

	int err;
	static float counter=0;

	_dprintf("%f %f %f\n",AxisX,AxisY,AxisZ);
	/* 描画 */
		/* 不透明 */
	agglDisable( AGGL_BLEND );
	agglDepthMask( AGGL_TRUE );
	
	agglTranslatef(playerObject.translation.X,playerObject.translation.Y,playerObject.translation.Z);
	counter+=0.05;

	agglRotatef(AxisX,1,0,0);
	agglRotatef(AxisY,0,1,0);
	agglRotatef(AxisZ,0,0,1);
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
	agglEnable( AGGL_BLEND );
	agglDepthMask( AGGL_FALSE );

	agglBeginZsort( AGGL_FAR_FIRST, sizeof(zsortbuf), zsortbuf );
	ag3dDrawAnimenode( &(age3dModel[ AG_AG3D_AG3DEXPORTMODEL ]), node, AG3D_ONBLEND_OFFDEPTH );
	agglEndZsort();

	agglDepthMask( AGGL_TRUE );

	/* フレーム描画終了 */
	err = agglGetError();
	if ( err != 0 ) {
		_dprintf( "!!!!!!!!!!!!!! err = %x, frame = %d !!!!!!!!!!!\n" , err, 0 );
	}
}
