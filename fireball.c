#include "fireball.h"


void fireballInit(Object *dp,int pid){
	dp->mov = fireball_move;
	dp->drw = fireball_drw;

	dp->pid = pid;
	dp->visibility = 0;
}

/* TODO:今西
描画
*/
void fireball_drw(Object *dp){
		/* 不透明 */
	/*
	agglDisable( AGGL_BLEND );
	agglDepthMask( AGGL_TRUE );
	*/
	
	agglPushMatrix();
	
	agglTranslatef(dp->translation.X,dp->translation.Y,dp->translation.Z);
	
		/* ツリー→ワールド座標変換 */
	ag3dSetRoot( 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, node );

	
		/* ツリー形状を求める */
	ag3dCalcTree( &(age3dTree[ AG_AG3D_BULLETTREE ]), &(age3dMotion[ AG_AG3D_BULLETMOTION ]), (float)1, node );
	ag3dDrawAnimenodeDCmd( &(age3dModel[ AG_AG3D_BULLETMODEL ]), node, &(age3dDCmd[ AG_AG3D_BULLETMODEL ]), AG3D_OFFBLEND_ONDEPTH );

	
		/* 半透明、Ｚバッファ更新 */
	agglEnable( AGGL_BLEND );

	agglBeginZsort( AGGL_FAR_FIRST, sizeof(zsortbuf), zsortbuf );
	ag3dDrawAnimenode( &(age3dModel[ AG_AG3D_BULLETMODEL ]), node, AG3D_ONBLEND_ONDEPTH );
	agglEndZsort();
	
				/* 半透明、Ｚバッファ非更新 */
	agglEnable( AGGL_BLEND );
	agglDepthMask( AGGL_FALSE );

	agglBeginZsort( AGGL_FAR_FIRST, sizeof(zsortbuf), zsortbuf );
	ag3dDrawAnimenode( &(age3dModel[ AG_AG3D_BULLETMODEL ]), node, AG3D_ONBLEND_OFFDEPTH );
	agglEndZsort();
	
	agglPopMatrix();
}

/* TODO:今西
*/
void fireball_move(Object *dp){
	dp->translation.X+=dp->direction.X*BULLET_VELOCITY;
	dp->translation.Y+=dp->direction.Y*BULLET_VELOCITY; 
	dp->translation.Z+=dp->direction.Z*BULLET_VELOCITY;	
}