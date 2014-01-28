#include <amlib.h>
#include <agdraw.h>

#include <vdpreg.h>
#include <aggl.h>
#include <ag3d.h>
#include <ag3danime.h>

#include <agGamePad.h>

#include "export.h"
#include "pad.h"
#include "extern.h"

#define READY_COUNT 90
#define TRANSITION_COUNT 10

extern void DrawPlane();

extern void DrawSky();

AG3Danimenode	node[512];

char	zsortbuf[1024*10*50];

char	vtxbuf[10240*2];

u32 DrawBuffer[65536*64];

AGESoundManagerData SndMgr;

const int MotionList[] = { AG_AG3D_AG3DEXPORTMOTION};

static volatile u32 _SystemVSyncCount=0;
int frameCount;

Object Objects[OBJECT_MAX];

int playerNum;
int playerJoined[PLAYER_MAX];

Page displayingPage;
Page destPage;

AGDrawBuffer DBuf;

void AG3DGLUglinit( void );
void sortPlayerByRank();
void draw( int frame , int motion_number );

static s32 ifnc_vsync(int type)
{
    _SystemVSyncCount++;
    // i_exec_swap=0;
    return(1);
}

void initObjects(){
	int i;
	for(i=0;i<OBJECT_MAX;i++){
		Objects[i].stat = INVISIBLE;
	}
}


void moveObjects(){
	int i;
	for(i=0;i<OBJECT_MAX;i++){
		if(Objects[i].stat != INVISIBLE && Objects[i].stat != DEAD)
			Objects[i].mov(&Objects[i]);
	}
}

void drawObjects(){
	int i;
	for(i=0;i<OBJECT_MAX;i++){
		if(Objects[i].stat != INVISIBLE && Objects[i].stat != DEAD)
			Objects[i].drw(&Objects[i]);
	}
}

void prerender(){

	if( DBuf.CmdCount > 0 ) {
		agTransferDrawDMAAsync( &(DBuf) );
	}

	agDrawBufferInit( &DBuf, DrawBuffer );

	agglBeginFrame( &DBuf, aglGetDispFrame(), AGGL_RGB_888, AG_Z_INDEX, 32, vtxbuf, sizeof(vtxbuf) );

	AG3DGLUglinit();
	agglClearColor( 144.0/255.0, 215.0/255.0, 236.0/255.0, 0.0f );
	agglClearDepthf( 1.0f );
	agglClear( (AGGLbitfield)(AGGL_COLOR_BUFFER_BIT | AGGL_DEPTH_BUFFER_BIT) );
}

void prerenderWithoutColoring(){
		if( DBuf.CmdCount > 0 ) {
		agTransferDrawDMAAsync( &(DBuf) );
	}

	agDrawBufferInit( &DBuf, DrawBuffer );

	agglBeginFrame( &DBuf, aglGetDispFrame(), AGGL_RGB_888, AG_Z_INDEX, 32, vtxbuf, sizeof(vtxbuf) );

	AG3DGLUglinit();

}

void postrender(){
	if(frameCount <= TRANSITION_COUNT){
		if(displayingPage != destPage){
			drawRect2(0,0,1024,768,(int)(((float)255/TRANSITION_COUNT)*(frameCount)),1,1,1);
		}else{
			drawRect2(0,0,1024,768,(int)(((float)255/TRANSITION_COUNT)*(TRANSITION_COUNT - frameCount)),1,1,1);
		}
	}



	agglDepthMask( AGGL_TRUE );
	agglFinishFrame();
	agDrawEODL( &DBuf );
	agTransferDrawWait();

	aglWaitVSyncN( 2 );
	aglSwap();
}

void allocFireballs(int pid){
	int offset = FIREBALL_OFFSET+FIREBALL_PER_PLAYER*pid, i;
	for(i = 0;i<FIREBALL_PER_PLAYER;i++){
		fireballInit(&Objects[offset + i],pid);
	}
}

void allocHormingBullets(int pid){
	int offset = HORMING_OFFSET + HORMING_PER_PLAYER*pid, i;

	for(i = 0;i<HORMING_PER_PLAYER;i++){
		hormingBulletInit(&Objects[offset + i],pid);
	}
}


void initGame(){
	int i;

	initObjects();
	playerNum = 0;

	for(i=0;i<PLAYER_MAX;i++){
		playerJoined[i] = 0;
		Objects[i].stat = INVISIBLE;
	}
}

void joinPlayer(int pid){
	playerInit(&Objects[playerNum],pid);
	allocFireballs(pid);
	allocHormingBullets(pid);

	playerJoined[pid] = 1;
	playerNum++;
}

void setPage(Page page){
	if(displayingPage != destPage)
		return;
	destPage = page;
	frameCount = 0;

	if(page == INGAME)
		playBgm(AS_SND_INGAME);
	else if(page == TITLE && displayingPage!=INSTRUCTION)
		playBgm(AS_SND_TITLE);
	else if(page == SCORE)
		playBgm(AS_SND_RESULT);
	else if(page == READY){
		StopCurrentBGM();
	}
}

void setCameraLongShot(){
	float fovy,f,cr,aspect,p1,p2;
	AGGLfloat c[3];
	AGGLfloat t[3];
	AGGLfloat u[3];
    
	c[0]=ACTIVE_RADIUS*2;
	c[1]=400;
	c[2]=0;
  
	t[0]=-ACTIVE_RADIUS;
	t[1]=20;
	t[2]=0;
  
	u[0]=-1;
	u[1]=1;
	u[2]=0;
	
	
	f=myabs(cr)*25.0/PI;
	fovy=25.0+f;
	aspect = ((AGGLfloat)FB_WIDTH) / ((AGGLfloat)FB_HEIGHT);
	agglMatrixMode( AGGL_PROJECTION );
	agglLoadIdentity();
	agglPerspectivef(fovy , aspect, 1, 20000 ); 
	agglMatrixMode( AGGL_MODELVIEW );

	agglLoadIdentity() ;
	agglLookAtf(c[0],c[1],c[2],t[0],t[1],t[2],u[0],u[1],u[2]);
}


void  main( void ) {
	int i;
	int MotionNumber = MotionList[0];
	u32 v;
	int n;
	u32 pad;
	int err;
	displayingPage == TITLE;



	agpDisableCpuInterrupts();
	aglInitialize();
	agpEnableCpuInterrupts();

	aglAddInterruptCallback(AG_INT_TYPE_VBLA,ifnc_vsync);
#ifdef DEBUG
	_dprintf( ">> Dogfighters start.\n" );
#endif

	agglInitialize();
	agglDisplaySize( FB_WIDTH , FB_HEIGHT );
	DBuf.CmdCount = 0;
	
	PadInit();

	agGamePadSyncInit( &_SystemVSyncCount, 30);
	v = _SystemVSyncCount;

	
	ageSndMgrInit(&SndMgr, AGE_SOUND_ROM_OFFSET);

	for (i = 0; i < AG_SND_MAX_MASTERVOLUME; i++) {
		ageSndMgrSetMasterVolume(i, 255);
	};

	ageSndMgrSetChannelVolume(0, 128);
	ageSndMgrSetChannelVolume(1, 128);
	
	initGame();

	setPage(TITLE);

	while( 1 ) {
		agGamePadSync();
		ageSndMgrRun();
		frameCount++;
		if(displayingPage == TITLE){
			prerender();
			drawTex2(AG_CG_TOP,0,0,1024,768);
			if(frameCount > 20){
		        for( n=0 ; n < PLAYER_MAX ; n++ ) {
		            pad = agGamePadGetData(n);
		            if (pad & GAMEPAD_START) {
		            	if(!playerJoined[n]){
		            		// joinPlayer(n);
		            		for(i=0;i<3;i++)
		            			joinPlayer(i);
		            	}
		            }else if(playerJoined[n]){
		            	setPage(READY);
						ageSndMgrPlayOneshot( AS_SND_SELECT , 0 , SOUND_VOLUME , AGE_SNDMGR_PANMODE_LR12 , 128 , 0 );
		            }

		            if(playerJoined[n]){
		            	drawStr((100*n)<<2,100<<2,"hello");
		            }

		            if (pad & GAMEPAD_SELECT){
		            	setPage(INSTRUCTION);
						ageSndMgrPlayOneshot( AS_SND_IN , 0 , SOUND_VOLUME , AGE_SNDMGR_PANMODE_LR12 , 128 , 0 );
		            }
	     	 	}
	     	}
			postrender();
		}else if(displayingPage == INSTRUCTION){
			prerender();
			drawRect(0,0,1024,768,1,1,1);
			drawStr(100<<2,100<<2,"20123hellohello");
			drawNum(100<<2,200<<2,20123);

			postrender();
			if(frameCount > 20)
		        for( n=0 ; n < PLAYER_MAX ; n++ ) {
		            pad = agGamePadGetData(n);
		            if (pad & GAMEPAD_SELECT){
						ageSndMgrPlayOneshot( AS_SND_IN , 0 , SOUND_VOLUME , AGE_SNDMGR_PANMODE_LR12 , 128 , 0 );
		            	setPage(TITLE);
		            	initGame();
		            }
	     	 	}
		}else if(displayingPage == READY){
			prerender();

			
			moveObjects();
			draw( frameCount , MotionNumber );
			drawObjects();
			drawHud(getPlayer((int)agGamePadGetMyID()), frameCount);
			if(frameCount > READY_COUNT/2)
				drawTex2(AG_CG_START,262,168,500,400);
			else
				drawTex2(AG_CG_READY,162,168,700,400);

			postrender();

			if(frameCount > READY_COUNT){
				setPage(INGAME);
			}

		}else if(displayingPage == INGAME){

			int c=0;
			prerender();
			/* gl”wŒi‰Šú‰» */

			moveObjects();
			draw( frameCount , MotionNumber );
			drawObjects();
			drawHud(getPlayer((int)agGamePadGetMyID()), frameCount);

			if(getPlayer((int)agGamePadGetMyID())->stat == DEAD){
				setCameraLongShot();
			}


			for(n=0;n<playerNum;n++){
				if(Objects[n].stat != DEAD){
					c++;
				}
			}

			if(c==1){
				setPage(SCORE);
			}
			

			postrender();
		}else if(displayingPage == SCORE){
			prerender();

			drawTex2(AG_CG_RESULTBACK,0,0,1024,768);

			sortPlayerByRank();

			for(n=0;n<playerNum;n++){
				int l;
				if(frameCount > (n+1)*10){
					l = 200;
				}else{
					int c = frameCount - n*10;
					l = 200 + (10-c)*(10-c)*(10-c);
				}
				_dprintf("%d\n",Objects[n].deadFrame);
				drawTex2(AG_CG_1ST+n,100,(100+100*n),70,30);
				drawTex2(AG_CG_NO1+Objects[n].pid,l,(100+100*n),100,30);
			}

			if(frameCount > (playerNum+1)*10){
				drawTex2(AG_CG_STARTAL,700,700,250,32);
			}

			postrender();

			if(frameCount > (playerNum+1)*10)
		        for( n=0 ; n < PLAYER_MAX ; n++ ) {
		            pad = agGamePadGetData(n);
		            if (pad & GAMEPAD_START){
		            	setPage(TITLE);
		            	initGame();
		            }
	     	 	}
		}
		if(displayingPage != destPage){
			if(frameCount>=TRANSITION_COUNT||destPage == INGAME){
				displayingPage = destPage;
				frameCount = 0;
			}
		}
	}
}

void sortPlayerByRank(){
	int i,j;
	for(i=0;i<playerNum;i++){
		if(Objects[i].stat != DEAD){
				Object tmp = Objects[0];
				Objects[0] = Objects[i];
				Objects[i] = tmp;
		}
	}
	for(i=1;i<playerNum;i++){
		for(j=i+1;j<playerNum;j++){
			if(Objects[i].deadFrame < Objects[j].deadFrame){
				Object tmp = Objects[j];
				Objects[j] = Objects[i];
				Objects[i] = tmp;
			}
		}
	}
}

void draw( int frame , int motion_number  ) {
	int err;


	/* ƒ‰ƒCƒgÝ’è */
{
		const static AGGLfloat lpos[4] = { 1.0f, 1.0f, 1.0f, 0.0f } ;
		const static AGGLfloat lamb[3] = { 1.0f, 1.0f, 1.0f } ;
		const static AGGLfloat ldif[3] = { 1.0f, 1.0f, 1.0f } ;
		const static AGGLfloat lspc[3] = { 1.0f, 1.0f, 1.0f } ;
		agglLightfv( AGGL_LIGHT0, AGGL_AMBIENT,  lamb);
		agglLightfv( AGGL_LIGHT0, AGGL_DIFFUSE,  ldif);
		agglLightfv( AGGL_LIGHT0, AGGL_SPECULAR, lspc);
		agglLightfv( AGGL_LIGHT0, AGGL_POSITION, lpos);
		agglEnable( AGGL_LIGHT0 );
};

	//agglEnable( AGGL_LIGHTING );
	
	agglDisable( AGGL_LIGHTING );
	DrawCubes();
	DrawPlane();
	DrawSky();
}

void AG3DGLUglinit( void ) {
	agglDisable( AGGL_ALPHA_TEST );
	agglDisable( AGGL_BLEND );
	agglDisable( AGGL_COLOR_MATERIAL );
	agglEnable( AGGL_CULL_FACE );
	agglDisable( AGGL_DEPTH_TEST );
	agglDisable( AGGL_LIGHTING );
	agglDisable( AGGL_MATRIX_PALETTE );
	agglDisable( AGGL_NORMALIZE );
	agglDisable( AGGL_PERSPECTIVE_CORRECTION );
	agglEnable( AGGL_RESCALE_NORMAL );
	agglDisable( AGGL_SCISSOR_TEST );
	agglDisable( AGGL_TEXTURE_2D );
	//agglDisable( AGGL_LIGHT0 );
	agglEnable( AGGL_LIGHT0 );
	agglDisable( AGGL_LIGHT1 );
	agglDisable( AGGL_LIGHT2 );
	agglDisable( AGGL_LIGHT3 );
	agglDisable( AGGL_LIGHT4 );
	agglDisable( AGGL_LIGHT5 );
	agglDisable( AGGL_LIGHT6 );
	agglDisable( AGGL_LIGHT7 );

	agglDisableClientState( AGGL_VERTEX_ARRAY );
	agglDisableClientState( AGGL_COLOR_ARRAY );
	agglDisableClientState( AGGL_NORMAL_ARRAY );
	agglDisableClientState( AGGL_TEXTURE_COORD_ARRAY );
	agglDisableClientState( AGGL_MATRIX_INDEX_ARRAY );
	agglDisableClientState( AGGL_WEIGHT_ARRAY );

	agglLightModelf( AGGL_LIGHT_MODEL_TWO_SIDE, 0.0f );

	agglFrontFace( AGGL_CCW );
	agglShadeModel( AGGL_SMOOTH );

	agglColorMask( AGGL_TRUE, AGGL_TRUE );
	agglDepthMask( AGGL_TRUE );
	agglEnable( AGGL_DEPTH_TEST );
	agglDepthFunc( AGGL_LEQUAL );

	agglEnable( AGGL_BLEND );
	agglBlendFunc( AGGL_BLEND_FRONT );
	agglAlphaFunc( AGGL_GREATER, 0.01f );
}
