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

extern void DrawPlane();

extern void DrawSky();

AG3Danimenode	node[512];

char	zsortbuf[1024*10*50];

char	vtxbuf[10240*2];

u32 DrawBuffer[65536*32];

const int MotionList[] = { AG_AG3D_AG3DEXPORTMOTION};

static volatile u32 _SystemVSyncCount=0;
int frameCount;

Object Objects[OBJECT_MAX];

int playerNum;
int playerJoined[PLAYER_MAX];

typedef enum Page_t
  {
  TITLE,INSTRUCTION,INGAME,SCORE
}Page;

Page displayingPage;

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
	_dprintf("initObjects\n");
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
	_dprintf("prerender\n");

	if( DBuf.CmdCount > 0 ) {
		agTransferDrawDMAAsync( &(DBuf) );
	}

	agDrawBufferInit( &DBuf, DrawBuffer );

	agglBeginFrame( &DBuf, aglGetDispFrame(), AGGL_RGB_888, AG_Z_INDEX, 32, vtxbuf, sizeof(vtxbuf) );

	AG3DGLUglinit();

	agglClearColor( 0.015625f, 0.48046875f, 0.9921875f, 0.0f );
	agglClearDepthf( 1.0f );
	agglClear( (AGGLbitfield)(AGGL_COLOR_BUFFER_BIT | AGGL_DEPTH_BUFFER_BIT) );
}

void postrender(){

	_dprintf("postrender\n");
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

void startGame(){
	displayingPage = INGAME;
	frameCount = 0;
}

void initGame(){
	int i;
	_dprintf("initGame\n");

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

void  main( void ) {
	int i;
	int MotionNumber = MotionList[0];
	u32 v;
	int n;
	u32 pad;

	displayingPage = TITLE;
	frameCount = 0;


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

	
	initGame();


	while( 1 ) {
		agGamePadSync();
		frameCount++;
        // while( v >= _SystemVSyncCount ) {
        //     AG_IDLE_PROC();
        //     agGamePadSyncIdle();
        //     _dprintf("%d",_SystemVSyncCount);
        // }
		if(displayingPage == TITLE){
			prerender();
			drawTex2(AG_CG_TOP,0,0,1024<<2,768<<2);
			if(frameCount > 60){
		        for( n=0 ; n < PLAYER_MAX ; n++ ) {
		            pad = agGamePadGetData(n);
		            if (pad & GAMEPAD_START) {
		            	if(!playerJoined[n])
		            		joinPlayer(n);
		            }else if(playerJoined[n]){
		            	startGame();
		            }

		            if(playerJoined[n]){
		            	drawStr((100*n)<<2,100<<2,"hello");
		            }

		            if (pad & GAMEPAD_SELECT){
		            	displayingPage = INSTRUCTION;
		            	frameCount = 0;
		            }
	     	 	}
	     	}
			postrender();
		}else if(displayingPage == INSTRUCTION){
			prerender();
			drawRect(0,0,1024,768,1,1,1);
			drawStr(100<<2,100<<2,"hello");

			postrender();
			if(frameCount > 60)
		        for( n=0 ; n < PLAYER_MAX ; n++ ) {
		            pad = agGamePadGetData(n);
		            if (pad & GAMEPAD_SELECT){
		            	displayingPage = TITLE;
		            	initGame();
		            	frameCount = 0;
		            }
	     	 	}
		}else if(displayingPage == INGAME){

			int c=0;
			prerender();
			/* gl”wŒi‰Šú‰» */

			moveObjects();
			// drawHud(&Objects[agGamePadGetMyID()], _SystemVSyncCount);cm
			draw( frameCount , MotionNumber );
			drawObjects();
			drawHud(getPlayer((int)agGamePadGetMyID()), frameCount);

			for(n=0;n<playerNum;n++){
				if(Objects[n].stat != DEAD){
					c++;
				}
			}
			
			if(c==1){
				displayingPage = SCORE;
				frameCount = 0;
			}
			



			postrender();
		}else if(displayingPage == SCORE){
			prerender();
			drawRect(0,0,1024,768,129,137,177);

			sortPlayerByRank();

			for(n=0;n<playerNum;n++){
				drawTex3(AG_CG_1ST+n,100<<2,(100+100*n)<<2);
				drawTex3(AG_CG_NO1+n,200<<2,(100+100*n)<<2);
			}

			postrender();

			if(frameCount > 60)
		        for( n=0 ; n < PLAYER_MAX ; n++ ) {
		            pad = agGamePadGetData(n);
		            if (pad & GAMEPAD_START){
		            	displayingPage = TITLE;
		            	initGame();
		            	frameCount = 0;
		            }
	     	 	}
		}
	}
}

void sortPlayerByRank(){
	int i,j;
	for(i=0;i<playerNum;i++){
		int max = Objects[i].moveCount;
		for(j=i;j<playerNum;j++){
			if(max < Objects[i].moveCount){
				Object tmp = Objects[j];
				Objects[j] = Objects[i];
				Objects[i] = tmp;
				max = Objects[j].moveCount;
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

	DrawPlane();
	agglDisable( AGGL_LIGHTING );
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
