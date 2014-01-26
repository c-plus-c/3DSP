#include "export.h"
#include "Object.h"
#include "extern.h"

#define BULLET_VELOCITY 2.5

#define RANGE_COUNT 120



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
	float x1,y1,z1,xo,yo,zo,l1,o1;
	
	x1=Objects[dp->target_pid].translation.X-dp->translation.X;
	y1=Objects[dp->target_pid].translation.Y-dp->translation.Y;
	z1=Objects[dp->target_pid].translation.Z-dp->translation.Z;
	
	l1=sqrtf(x1*x1+y1*y1+z1*z1);
	if(l1!=0.0){
		x1/=l1;
		y1/=l1;
		z1/=l1;
	}
	
	x1*=BULLET_VELOCITY*3;
	y1*=BULLET_VELOCITY*3;
	z1*=BULLET_VELOCITY*3;
	
	xo=dp->direction.X+x1;
	yo=dp->direction.Y+y1;
	zo=dp->direction.Z+z1;
	
	o1=sqrtf(xo*xo+yo*yo+zo*zo);
	
	if(o1!=0.0)
	{
		xo/=o1;
		yo/=o1;
		zo/=o1;
	}
	xo*=BULLET_VELOCITY;
	yo*=BULLET_VELOCITY;
	zo*=BULLET_VELOCITY;
	
	dp->direction.X=xo;
	dp->direction.Y=yo;
	dp->direction.Z=zo;
	
	dp->translation.X+=dp->direction.X*BULLET_VELOCITY;
	dp->translation.Y+=dp->direction.Y*BULLET_VELOCITY; 
	dp->translation.Z+=dp->direction.Z*BULLET_VELOCITY;

	for(i =0;i<playerNum;i++){
		if(collision(dp, &Objects[i])){
			if(Objects[i].stat != BLINK&&Objects[i].stat != DYING){
				Objects[i].life--;
				Objects[i].stat = BLINK;
				Objects[i].moveCount = 0;
				ageSndMgrPlayOneshot( AS_SND_HIT , 0 , SOUND_VOLUME , AGE_SNDMGR_PANMODE_LR12 , 128 , 0 );
			}

			if(Objects[i].life <= 0){
				Objects[i].stat = DYING;
				Objects[i].deadFrame = frameCount;
				Objects[i].moveCount = 0;
				ageSndMgrPlayOneshot( AS_SND_DIE , 0 , SOUND_VOLUME , AGE_SNDMGR_PANMODE_LR12 , 128 , 0 );
			}
			Objects[dp->target_pid].targeted=0;
			dp->stat = INVISIBLE;
		}
	}
	
	dp->moveCount++;
	if(dp->moveCount > RANGE_COUNT){
		dp->stat = INVISIBLE;
		Objects[dp->target_pid].targeted=0;
	}
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