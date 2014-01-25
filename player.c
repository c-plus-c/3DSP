#include <amlib.h>
#include <agGamePad.h>

#include "export.h"
#include "player.h"
#include "pad.h"
#include "extern.h"

#define VELOCITY 0.6
#define PITCHACCELBAND 0.001
#define PITCHACCELBANDLIMIT 0.03

#define ROLLACCELBAND 0.005
#define ROLLACCELBANDLIMIT 0.05
#define ROLLBACK 8

#define YAWTIME 0.04

#define ROLLLIMIT (PI/6)
#define PITCHLIMIT (PI/5)

#define BRAKEINCREMENTATION 0.1
#define BRAKEMIN 1
#define BRAKEMAX 2.4

#define BLINK_COUNT 60
#define FIREBALL_INTERVAL 1
#define AMMO_LIMIT 20
#define FIREBALL_RELOAD_INTERVAL 5

#define HORMING_AMMO_COST 7


void playerInit(Object *dp,int pid)
{
	dp->translation.X=100*(pid/2);
	dp->translation.Y=100;
	dp->translation.Z=100*(pid%2);
	
	dp->direction.X=0;
	dp->direction.Y=0;
	dp->direction.Z=-1;

	dp->yaw=0;
	dp->roll=0;
	dp->pitch=0;

	dp->mov = player_move;
	dp->drw = player_drw;

	dp->pid = pid;

	dp->stat=VISIBLE;
	dp->fireballCount = AMMO_LIMIT;
	
	dp->pitchAccelerator=0;
	dp->rollAccelerator=0;
	
	dp->brakeVariable=1;
	dp->life = PLAYER_LIFE;
	
	dp->sideOut=0;
	
	dp->targeted=0;
}


/* TODO:今西
半径で判定以上に当たり判定をしたければ書く 
*/
int player_hc2(Object *dp,Object *sp,float cx, float cy, float cz)
{
	return 0;
}

Object* getPlayer(int pid){
	int i;
	for(i=0;i<playerNum;i++){
		if(Objects[i].pid == pid)
			return &Objects[i];
	}

	return NULL;
}

void ManualMove(Object *dp)
{
  u32 pad;

  pad = agGamePadGetData(dp->pid);
  
  if( (pad & GAMEPAD_L) != 0){ //左に旋回
	if(dp->rollAccelerator>0) dp->rollAccelerator=0;
	dp->rollAccelerator-=ROLLACCELBAND;
	if(dp->rollAccelerator<-ROLLACCELBANDLIMIT) dp->rollAccelerator=-ROLLACCELBANDLIMIT;
	dp->roll+=dp->rollAccelerator;
	if(dp->roll<-ROLLLIMIT){
		dp->roll=-ROLLLIMIT;
		dp->rollAccelerator=0;
	}
    dp->yaw-=dp->roll*YAWTIME;
  }else if( (pad & GAMEPAD_R) != 0){ //右に旋回
  
	if(dp->rollAccelerator<0) dp->rollAccelerator=0;
	dp->rollAccelerator+=ROLLACCELBAND;
	if(dp->rollAccelerator>ROLLACCELBANDLIMIT) dp->rollAccelerator=ROLLACCELBANDLIMIT;
	dp->roll+=dp->rollAccelerator;
	if(dp->roll>ROLLLIMIT){
		dp->roll=ROLLLIMIT;
		dp->rollAccelerator=0;
	}
    dp->yaw-=dp->roll*YAWTIME;

   }else{ //旋回解除処理
  
	if(dp->roll<0)
	{
		dp->rollAccelerator+=ROLLACCELBAND*ROLLBACK;
		if(dp->rollAccelerator>ROLLACCELBANDLIMIT*ROLLBACK) dp->rollAccelerator=ROLLACCELBANDLIMIT*ROLLBACK;
		dp->roll+=dp->rollAccelerator;
		if(dp->roll<-ROLLLIMIT) dp->roll=-ROLLLIMIT;
		else if(dp->roll>=0){
			dp->roll=0;
			dp->rollAccelerator=0;
		}
	}else if(dp->roll>0){
		dp->rollAccelerator-=ROLLACCELBAND*ROLLBACK;
		if(dp->rollAccelerator<-ROLLACCELBANDLIMIT*ROLLBACK) dp->rollAccelerator=-ROLLACCELBANDLIMIT*ROLLBACK;
		dp->roll+=dp->rollAccelerator;
		if(dp->roll>ROLLLIMIT) dp->roll=ROLLLIMIT;
		else if(dp->roll<=0){
			dp->roll=0;
			dp->rollAccelerator=0;
		}
	}else{
		dp->rollAccelerator=0;
	}
	dp->yaw-=dp->roll*YAWTIME;
  }

  if ((pad & GAMEPAD_U) != 0){ //上昇
	if(dp->pitchAccelerator>0) dp->pitchAccelerator=0;
	dp->pitchAccelerator-=PITCHACCELBAND;
	if(dp->pitchAccelerator<-PITCHACCELBANDLIMIT) dp->pitchAccelerator=-PITCHACCELBANDLIMIT;
	dp->pitch+=dp->pitchAccelerator;
	/*
	if(dp->pitch<-PITCHLIMIT){
		dp->pitch=-PITCHLIMIT;
		dp->pitchAccelerator=0;
	}
	*/
	if(dp->pitch<0)
	{
		dp->pitch+=2*PI;
	}
  }else if((pad & GAMEPAD_D) != 0){ //下降
	if(dp->pitchAccelerator<0) dp->pitchAccelerator=0;
	dp->pitchAccelerator+=PITCHACCELBAND;
	if(dp->pitchAccelerator>PITCHACCELBANDLIMIT) dp->pitchAccelerator=PITCHACCELBANDLIMIT;
	dp->pitch+=dp->pitchAccelerator;
	/*
	if(dp->pitch>PITCHLIMIT){
		dp->pitch=PITCHLIMIT;
		dp->pitchAccelerator=0;
	}
	*/
	if(dp->pitch>2*PI){
		dp->pitch-=2*PI;
	}
  }else{
	dp->pitchAccelerator=0;
  }
  
  //ブレーキ
  if((pad & GAMEPAD_LL) != 0)
  {
	dp->brakeVariable+=BRAKEINCREMENTATION;
	dp->brakeVariable=min(BRAKEMAX,dp->brakeVariable);
  }else{
	dp->brakeVariable-=BRAKEINCREMENTATION;
	dp->brakeVariable=max(BRAKEMIN,dp->brakeVariable);
  }

  if(frameCount%FIREBALL_RELOAD_INTERVAL == 0){
  	if(dp->fireballCount < AMMO_LIMIT)
  		dp->fireballCount++;
  }

  if((pad & GAMEPAD_A) != 0)
  {
  	Object* fireball;
  	if(dp->shotFrame < FIREBALL_INTERVAL){
  		dp->shotFrame++;
  	}else if(dp->fireballCount > 0){
		fireball = getFreeFireball(dp->pid);
		if(fireball != NULL){
			fireball->stat = VISIBLE;
			fireball->direction = dp->direction;
			fireball->translation = dp->translation;
			fireball->moveCount = 0;

			dp->fireballCount--;
			dp->shotFrame = 0;
		}
		ageSndMgrPlayOneshot( AS_SND_SHOT , 0 , SOUND_VOLUME , AGE_SNDMGR_PANMODE_LR12 , 128 , 0 );
	}
  }

  if((pad & GAMEPAD_B) != 0)
  {
  	Object* horming;
	
  	if(dp->shotFrame < FIREBALL_INTERVAL){
  		dp->shotFrame++;
  	}else if(dp->fireballCount > HORMING_AMMO_COST){
		horming = getFreeHormingBullet(dp->pid);
		if(horming != NULL){
			int i;
			float l2min;
			horming->stat = VISIBLE;
			horming->direction=dp->direction;
			horming->translation=dp->translation;
			horming->moveCount = 0;

			dp->fireballCount-=HORMING_AMMO_COST;
			dp->shotFrame = 0;
			
			l2min=100000000.0;
			for(i=0;i<playerNum;i++)
			{
				float l,dx,dy,dz;
				if(Objects[i].pid==dp->pid || Objects[i].stat == DEAD) continue;
				
				dx=Objects[i].translation.X-dp->translation.X;
				dy=Objects[i].translation.Y-dp->translation.Y;
				dz=Objects[i].translation.Z-dp->translation.Z;
				
				l=dx*dx+dy*dy+dz*dz;
				if(l<l2min){
					horming->target_pid=i;
					l2min=l;
				}
			}
			
			Objects[horming->target_pid].targeted=2;
		}
		ageSndMgrPlayOneshot( AS_SND_HSHOT , 0 , SOUND_VOLUME , AGE_SNDMGR_PANMODE_LR12 , 128 , 0 );
	}
  }
}

void AutoMove(Object *dp)
{
	if(dp->sideOut==1) dp->yaw+=0.02;
}
/* TODO:今西
パッド処理
*/
void player_move(Object *dp)
{
  float cp,sp,cb,sb,ch,sh;
  float tx,ty,tz;
  float nx,ny,nz;


  if(dp->sideOut==1)
  {
	AutoMove(dp);
  }
  else if(displayingPage != READY)
  {
	ManualMove(dp);
  }
  
  if(dp->stat == BLINK){
  	dp->moveCount++;
  	if(dp->moveCount > BLINK_COUNT)
  		dp->stat = VISIBLE;
  }

  //ピッチロールヨー角から自機の方向ベクトルを算出
  ch=cosf(dp->yaw);
  sh=sinf(dp->yaw);
  cp=cosf(dp->pitch);
  sp=sinf(dp->pitch);
  //cb=cosf(dp->roll);
  //sb=sinf(dp->roll);
  cb=1;
  sb=0;
  
  tz=-1;

  //dp->direction.X=(ch*cb+sh*sp*sb)*tx+(-ch*sb+sh*sp*cb)*ty+(sh*cp)*tz;
  //dp->direction.Y=(sb*cp)*tx+(cb*cp)*ty+(-sp)*tz;
  //dp->direction.Z=(-sh*cb+ch*sp*sb)*tx+(sb*sh+ch*sp*cb)*ty+(ch*cp)*tz;
  
  dp->direction.X=(sh*cp)*tz;
  dp->direction.Y=-sp*tz;
  dp->direction.Z=(ch*cp)*tz;
  
  //移動
  dp->translation.X+=dp->direction.X*VELOCITY/dp->brakeVariable;
  dp->translation.Y+=dp->direction.Y*VELOCITY/dp->brakeVariable; 
  dp->translation.Z+=dp->direction.Z*VELOCITY/dp->brakeVariable;
  
  dp->sideOut=(dp->translation.X*dp->translation.X+dp->translation.Z*dp->translation.Z>=ACTIVE_RADIUS*ACTIVE_RADIUS)?1:0;
  
  if(dp->translation.Y<=ACTIVE_LOWEST) dp->translation.Y=ACTIVE_LOWEST;
  else if(dp->translation.Y>=ACTIVE_HIGHEST) dp->translation.Y=ACTIVE_HIGHEST;
  
  
  if(agGamePadGetMyID()==dp->pid){
  //カメラ位置の計算
	float fovy,f,cr,aspect,p1,p2;
	AGGLfloat c[3];
	AGGLfloat t[3];
	AGGLfloat u[3];
    ty=1;
	nx=(-ch*sb+sh*sp*cb)*ty;
	ny=(cb*cp)*ty;
	nz=(sb*sh+ch*sp*cb)*ty;
	c[0]=dp->translation.X-15*dp->direction.X+2.5*nx;
	c[1]=dp->translation.Y-15*dp->direction.Y+2.5*ny;
	c[2]=dp->translation.Z-15*dp->direction.Z+2.5*nz;
  
	t[0]=dp->translation.X+1*nx;
	t[1]=dp->translation.Y+1*ny;
	t[2]=dp->translation.Z+1*nz;
  
	u[0]=nx;
	u[1]=ny;
	u[2]=nz;
  
	cr=dp->roll*(PITCHLIMIT/ROLLLIMIT);
	
	p1=2*PI-dp->pitch;
	p2=dp->pitch;
	
	p1/=1.5;
	p2/=1.5;
	
	f=myabs(cr)*25.0/PI;
	fovy=25.0+f;
	aspect = ((AGGLfloat)FB_WIDTH) / ((AGGLfloat)FB_HEIGHT);
	agglMatrixMode( AGGL_PROJECTION );
	agglLoadIdentity();
	agglPerspectivef(fovy , aspect, 1, 20000 ); 
	agglMatrixMode( AGGL_MODELVIEW );

	agglLoadIdentity() ;
	agglLookAtf(c[0],c[1],c[2],t[0],t[1],t[2],u[0],u[1],u[2]);
	//agglLookAtf(100,100,100,dp->translation.X,dp->translation.Y,dp->translation.Z,0,1,0);
	
	if(dp->targeted==2){
		ageSndMgrPlayOneshot( AS_SND_WARNING , 0 , SOUND_VOLUME , AGE_SNDMGR_PANMODE_LR12 , 128 , 0 );
		dp->targeted=1;
	}
  }
}

/* TODO:今西
描画
*/
void player_drw(Object *dp)
{

	int err;

	if(dp->stat == BLINK)
		if(dp->moveCount%3 == 0)
			return;

	/* 描画 */
		/* 不透明 */
	agglEnable( AGGL_BLEND );
	agglDepthMask( AGGL_TRUE );
	
	agglPushMatrix();
	
	agglTranslatef(dp->translation.X,dp->translation.Y,dp->translation.Z);

	agglRotatef(dp->roll/PI*180,dp->direction.X,dp->direction.Y,dp->direction.Z);
	agglRotatef(dp->yaw/PI*180,0,1,0);
	agglRotatef(dp->pitch/PI*180,1,0,0);
		/* ツリー→ワールド座標変換 */
	ag3dSetRoot( 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, node );

	switch(dp->pid){
		case 0:
			ag3dCalcTree( &(age3dTree[ AG_AG3D_NEWPLANE1TREE ]), &(age3dMotion[ AG_AG3D_NEWPLANE1MOTION ]), (float)1, node );
			ag3dDrawAnimenodeDCmd( &(age3dModel[ AG_AG3D_NEWPLANE1MODEL ]), node, &(age3dDCmd[ AG_AG3D_NEWPLANE1MODEL ]), AG3D_ONBLEND_ONDEPTH);
		break;
		case 1:
			ag3dCalcTree( &(age3dTree[ AG_AG3D_NEWPLANE2TREE ]), &(age3dMotion[ AG_AG3D_NEWPLANE2MOTION ]), (float)1, node );
			ag3dDrawAnimenodeDCmd( &(age3dModel[ AG_AG3D_NEWPLANE2MODEL ]), node, &(age3dDCmd[ AG_AG3D_NEWPLANE2MODEL ]), AG3D_ONBLEND_ONDEPTH);		
		break;
		case 2:
			ag3dCalcTree( &(age3dTree[ AG_AG3D_NEWPLANE3TREE ]), &(age3dMotion[ AG_AG3D_NEWPLANE3MOTION ]), (float)1, node );
			ag3dDrawAnimenodeDCmd( &(age3dModel[ AG_AG3D_NEWPLANE3MODEL ]), node, &(age3dDCmd[ AG_AG3D_NEWPLANE3MODEL ]), AG3D_ONBLEND_ONDEPTH);		
		break;
		case 3:
			ag3dCalcTree( &(age3dTree[ AG_AG3D_NEWPLANE4TREE ]), &(age3dMotion[ AG_AG3D_NEWPLANE4MOTION ]), (float)1, node );
			ag3dDrawAnimenodeDCmd( &(age3dModel[ AG_AG3D_NEWPLANE4MODEL ]), node, &(age3dDCmd[ AG_AG3D_NEWPLANE4MODEL ]), AG3D_ONBLEND_ONDEPTH);		
		break;
	}
	
	agglPopMatrix();
	
    agglMatrixMode( AGGL_TEXTURE ) ;
    agglLoadIdentity() ;
    agglMatrixMode( AGGL_MODELVIEW );
}
