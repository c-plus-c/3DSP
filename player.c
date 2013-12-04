#include <amlib.h>
#include "export.h"
#include "player.h"
#include "pad.h"

static Object playerObject;

void player_init()
{
	playerObject.translation.X=0;
	playerObject.translation.Y=0;
	playerObject.translation.Z=0;
	
	playerObject.rotation.X=0;
	playerObject.rotation.Y=0;
	playerObject.rotation.Z=0;
}

void player_initWithParam(Vec3f pos,Vec3f angle)
{
	playerObject.translation.X=pos.X;
	playerObject.translation.Y=pos.Y;
	playerObject.translation.Z=pos.Z;
	
	playerObject.rotation.X=angle.X;
	playerObject.rotation.Y=angle.Y;
	playerObject.rotation.Z=angle.Z;
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
	if( PadLvl() & PAD_LEFT )
	{
		playerObject.translation.X-=0.01;
	}
	
	if( PadLvl() & PAD_RIGHT )
	{
		playerObject.translation.X+=0.01;
	}
}

/* TODO:今西
描画
*/
void player_drw(Object *dp)
{
	int err;
	static float counter=0;
	/* 描画 */
		/* 不透明 */
	agglDisable( AGGL_BLEND );
	agglDepthMask( AGGL_TRUE );
	
	agglPushMatrix() ;
	
	agglTranslatef(playerObject.translation.X,playerObject.translation.Y,playerObject.translation.Z);
	counter+=0.05;
	
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
		_dprintf( "!!!!!!!!!!!!!! err = %d, frame = %d !!!!!!!!!!!\n" , err, 0 );
	}
}