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

u32 DrawBuffer[2][65536*32];

const int MotionList[] = { AG_AG3D_AG3DEXPORTMOTION};

static volatile u32 _SystemVSyncCount=0;
int frameCount = 0;

Object Objects[OBJECT_MAX];

typedef enum Page_t
  {
  TITLE,INGAME
}Page;

AGDrawBuffer DBuf;

void AG3DGLUglinit( void );
void draw( int frame , int motion_number );

static s32 ifnc_vsync(int type)
{
    _SystemVSyncCount++;
    // i_exec_swap=0;
    return(1);
}

void initObjects(){
	int i;
	_dprintf( "init\n");
	for(i=0;i<OBJECT_MAX;i++){
		Objects[i].stat = INVISIBLE;
	}
}


void moveObjects(){
	int i;
	_dprintf( "move\n");
	for(i=0;i<OBJECT_MAX;i++){
		if(Objects[i].stat != INVISIBLE)
			Objects[i].mov(&Objects[i]);
	}
}

void drawObjects(){
	int i;
	_dprintf( "draw\n");
	for(i=0;i<OBJECT_MAX;i++){
		if(Objects[i].stat != INVISIBLE)
			Objects[i].drw(&Objects[i]);
	}
}


void  main( void ) {
	int page, i;
	int MotionNumber = MotionList[0];
	Page displayingPage =TITLE;
	u32 v;
	int n;
	u32 pad;


	agpDisableCpuInterrupts();
	aglInitialize();
	agpEnableCpuInterrupts();

	aglAddInterruptCallback(AG_INT_TYPE_VBLA,ifnc_vsync);

#ifdef DEBUG
	_dprintf( ">> sample [ag3d_Model] start.\n" );
#endif

	agglInitialize();
	agglDisplaySize( FB_WIDTH , FB_HEIGHT );

	ag3dInitTree( &(age3dTree[ AG_AG3D_AG3DEXPORTTREE ]), node );
	ag3dInitTree( &(age3dTree[ AG_AG3D_PLANETREE ]),node);

	page = 0;
	DBuf.CmdCount = 0;
	
	PadInit();

	agGamePadSyncInit( &_SystemVSyncCount, 30);
	v = _SystemVSyncCount;

	initObjects();

	for (i = 0; i < PLAYER_NUMS; ++i)
	{
		playerInit(&Objects[i], i);
		allocFireballs(i);
	}


	while( 1 ) {
		agGamePadSync();

        // while( v >= _SystemVSyncCount ) {
        //     AG_IDLE_PROC();
        //     agGamePadSyncIdle();
        //     _dprintf("%d",_SystemVSyncCount);
        // }
		if(displayingPage == TITLE){

	        for( n=0 ; n < PLAYER_NUMS ; n++ ) {
	            pad = agGamePadGetData(n);
	            if ( (pad & GAMEPAD_START) ) {
	            	displayingPage = INGAME;
	            }
     	   }
		}else if(displayingPage == INGAME){
			frameCount++;

	        // for( n=0 ; n < 3 ; n++ ) {
	        //     pad = agGamePadGetData(n);
	        //     if ( (pad & GAMEPAD_START) ) {
	        //     	initObjects();
	        //     }
     	   // }

			if( DBuf.CmdCount > 0 ) {
				agTransferDrawDMAAsync( &(DBuf) );
			}

			page ^= 1;
			agDrawBufferInit( &DBuf, DrawBuffer[page] );

			agglBeginFrame( &DBuf, aglGetDispFrame(), AGGL_RGB_888, AG_Z_INDEX, 32, vtxbuf, sizeof(vtxbuf) );

			AG3DGLUglinit();

			
			/* gl”wŒi‰Šú‰» */
			agglClearColor( 0.125f, 0.200f, 0.300f, 0.0f );
			agglClearDepthf( 1.0f );
			agglClear( (AGGLbitfield)(AGGL_COLOR_BUFFER_BIT | AGGL_DEPTH_BUFFER_BIT) );

			moveObjects();
			// drawHud(&Objects[agGamePadGetMyID()], _SystemVSyncCount);
			draw( frameCount , MotionNumber );
			drawObjects();
			drawHud(&Objects[(int)agGamePadGetMyID()], _SystemVSyncCount);

			agglDepthMask( AGGL_TRUE );


			agglFinishFrame();

			// frame++;
			// if ( frame >= ag3dGetMotionFrames( &(age3dMotion[ MotionNumber ]) ) ) {
			// 	frame = 0;
			// 	MotionNumber = MotionList[ rand() % (sizeof( MotionList )/sizeof( MotionList[0] )) ];
			// };


			agDrawEODL( &DBuf );

			agTransferDrawWait();

			aglSwap();
			aglWaitVSync();
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
