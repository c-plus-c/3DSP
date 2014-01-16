#include "export.h"
#include "Object.h"
#include "extern.h"

#define BULLET_VELOCITY 3

#define RANGE_COUNT 60



/* TODO:今西
描画
*/
void hormingBullet_drw(Object *dp){
		/* 不透明 */
	agglEnable( AGGL_BLEND );
	agglDepthMask( AGGL_TRUE );
	
	agglPushMatrix();
	
	agglTranslatef(dp->translation.X,dp->translation.Y,dp->translation.Z);
	agglScalef(0.1,0.1,0.1);
		/* ツリー→ワールド座標変換 */
	ag3dSetRoot( 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, node );

	
		/* ツリー形状を求める */
	ag3dCalcTree( &(age3dTree[ AG_AG3D_HORMINGBULLETTREE ]), &(age3dMotion[ AG_AG3D_HORMINGBULLETMOTION ]), (float)1, node );
	ag3dDrawAnimenodeDCmd( &(age3dModel[ AG_AG3D_HORMINGBULLETMODEL ]), node, &(age3dDCmd[ AG_AG3D_HORMINGBULLETMODEL ]), AG3D_ONBLEND_ONDEPTH );
	
	agglPopMatrix();
}

/* TODO:今西
*/
void hormingBullet_move(Object *dp){
	int i;

	
	//dp->translation.X+=dp->direction.X*BULLET_VELOCITY;
	//dp->translation.Y+=dp->direction.Y*BULLET_VELOCITY; 
	//dp->translation.Z+=dp->direction.Z*BULLET_VELOCITY;

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

void hormingBulletInit(Object *dp,int pid){
	dp->mov = hormingBullet_move;
	dp->drw = hormingBullet_drw;


	dp->pid = pid;
	dp->stat = INVISIBLE;
}


Object* getFreeHormingBullet(int pid){
	int offset = HORMING_OFFSET+HORMING_PER_PLAYER*pid, i;
	for(i = 0;i<HORMING_PER_PLAYER;i++){
		if(Objects[offset + i].stat == INVISIBLE)
			return &Objects[offset+i];
	}
	return NULL;
}

/*
void allocFireballs(int pid){
	int offset = FIREBALL_OFFSET+FIREBALL_PER_PLAYER*pid, i;
	for(i = 0;i<FIREBALL_PER_PLAYER;i++){
		fireballInit(&Objects[offset + i],pid);
	}
}

Object* getFreeFireball(int pid){
	int offset = FIREBALL_OFFSET+FIREBALL_PER_PLAYER*pid, i;
	for(i = 0;i<FIREBALL_PER_PLAYER;i++){
		if(Objects[offset + i].stat == INVISIBLE)
			return &Objects[offset+i];
	}
	return NULL;
}
*/