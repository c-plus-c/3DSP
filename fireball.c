#include "fireball.h"

#define RANGE_COUNT 60

void fireballInit(Object *dp,int pid){
	dp->mov = fireball_move;
	dp->drw = fireball_drw;

	dp->pid = pid;
	dp->stat = INVISIBLE;
}

/* TODO:今西
描画
*/
void fireball_drw(Object *dp){
		/* 不透明 */
	agglEnable( AGGL_BLEND );
	agglDepthMask( AGGL_TRUE );
	
	agglPushMatrix();
	
	agglTranslatef(dp->translation.X,dp->translation.Y,dp->translation.Z);
	agglScalef(0.1,0.1,0.1);
		/* ツリー→ワールド座標変換 */
	ag3dSetRoot( 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, node );

	
		/* ツリー形状を求める */
	ag3dCalcTree( &(age3dTree[ AG_AG3D_BULLETTREE ]), &(age3dMotion[ AG_AG3D_BULLETMOTION ]), (float)1, node );
	ag3dDrawAnimenodeDCmd( &(age3dModel[ AG_AG3D_BULLETMODEL ]), node, &(age3dDCmd[ AG_AG3D_BULLETMODEL ]), AG3D_ONBLEND_ONDEPTH );
	//ag3dDrawAnimenode( &(age3dModel[ AG_AG3D_BULLETMODEL ]), node, AG3D_ONBLEND_ONDEPTH );
	
		/* 半透明、Ｚバッファ更新 */
	//agglEnable( AGGL_BLEND );

	//agglBeginZsort( AGGL_FAR_FIRST, sizeof(zsortbuf), zsortbuf );
	//ag3dDrawAnimenode( &(age3dModel[ AG_AG3D_BULLETMODEL ]), node, AG3D_ONBLEND_ONDEPTH );
	//agglEndZsort();
	
				/* 半透明、Ｚバッファ非更新 */
	//agglEnable( AGGL_BLEND );
	//agglDepthMask( AGGL_FALSE );

	//agglBeginZsort( AGGL_FAR_FIRST, sizeof(zsortbuf), zsortbuf );
	//ag3dDrawAnimenode( &(age3dModel[ AG_AG3D_BULLETMODEL ]), node, AG3D_ONBLEND_OFFDEPTH );
	//agglEndZsort();
	
	agglPopMatrix();
}

// fireball, player
int collision(Object *dp, Object *dp2){
  Vec3f	translation = dp->translation, translation2 = dp2->translation;
  int s = 1;

  if(dp2->pid == dp->pid)
  	return 0;

  if(dp2->stat == BLINK)
  	return 0;


  if(!( translation2.X + s > translation.X && translation2.X - s < translation.X ))
  	return 0;

  if(!( translation2.Y + s > translation.Y && translation2.Y - s < translation.Y ))
  	return 0;

  if(!( translation2.Z + s > translation.Z && translation2.Z - s < translation.Z ))
  	return 0;

  return 1;
}

/* TODO:今西
*/
void fireball_move(Object *dp){
	int i;

	dp->translation.X+=dp->direction.X*BULLET_VELOCITY;
	dp->translation.Y+=dp->direction.Y*BULLET_VELOCITY; 
	dp->translation.Z+=dp->direction.Z*BULLET_VELOCITY;

	for(i =0;i<PLAYER_NUMS;i++){
		if(collision(dp, &Objects[i])){
			Objects[i].life--;
			Objects[i].stat = BLINK;
			Objects[i].moveCount = 0;

			dp->stat = INVISIBLE;
		}
	}
	dp->moveCount++;
	if(dp->moveCount > RANGE_COUNT)
		dp->stat = INVISIBLE;
}



Object* getFreeFireball(int pid){
	int offset = FIREBALL_OFFSET+FIREBALL_PER_PLAYER*pid, i;
	for(i = 0;i<FIREBALL_PER_PLAYER;i++){
		if(Objects[offset + i].stat == INVISIBLE)
			return &Objects[offset+i];
	}
	return NULL;
}
