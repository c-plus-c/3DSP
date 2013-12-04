#include <amlib.h>
#include <agdraw.h>

#include <vdpreg.h>
#include <aggl.h>
#include <ag3d.h>
#include <ag3danime.h>

#include "export.h"
#include "pad.h"
#include "player.h"


AG3Danimenode	node[256];

char	zsortbuf[1024*10*50];

char	vtxbuf[10240*2];

u32 DrawBuffer[2][65536*16];

const int MotionList[] = { AG_AG3D_AG3DEXPORTMOTION};

void AG3DGLUglinit( void );
void draw( int frame , int motion_number );

void  main( void ) {
	AGDrawBuffer DBuf;
	int page;
	int frame;
	int MotionNumber = MotionList[0];

	agpDisableCpuInterrupts();
	aglInitialize();
	agpEnableCpuInterrupts();

#ifdef DEBUG
	_dprintf( ">> sample [ag3d_Model] start.\n" );
#endif

	agglInitialize();
	agglDisplaySize( FB_WIDTH , FB_HEIGHT );

	ag3dInitTree( &(age3dTree[ AG_AG3D_AG3DEXPORTTREE ]), node );

	page = 0;
	DBuf.CmdCount = 0;
	frame = 0;

	while( 1 ) {
		if( DBuf.CmdCount > 0 ) {
			agTransferDrawDMAAsync( &(DBuf) );
		}

		page ^= 1;
		agDrawBufferInit( &DBuf, DrawBuffer[page] );

		agglBeginFrame( &DBuf, aglGetDispFrame(), AGGL_RGB_888, AG_Z_INDEX, 32, vtxbuf, sizeof(vtxbuf) );

		AG3DGLUglinit();

		/* gl背景初期化 */
		agglClearColor( 0.125f, 0.200f, 0.300f, 0.0f );
		agglClearDepthf( 1.0f );
		agglClear( (AGGLbitfield)(AGGL_COLOR_BUFFER_BIT | AGGL_DEPTH_BUFFER_BIT) );

		draw( frame , MotionNumber );

		agglFinishFrame();

		frame++;
		if ( frame >= ag3dGetMotionFrames( &(age3dMotion[ MotionNumber ]) ) ) {
			frame = 0;
			MotionNumber = MotionList[ rand() % (sizeof( MotionList )/sizeof( MotionList[0] )) ];
		};

		agDrawEODL( &DBuf );

		agTransferDrawWait();

		aglSwap();
		aglWaitVSync();
	}
}

void draw( int frame , int motion_number  ) {
	int err;
	
	static AGGLfloat c[3]={ 0,3.7,-7 };
        static AGGLfloat t[3]={ 0.0,0.7,0.0 };
        static AGGLfloat u[3]={ 0.0f, 0.7f, 0.0f };

        AGGLfloat aspect = ((AGGLfloat)FB_WIDTH) / ((AGGLfloat)FB_HEIGHT);
        agglMatrixMode( AGGL_PROJECTION );
        agglLoadIdentity();

        agglPerspectivef( 25.0, aspect, 1, 100 ); /* 100.0 +/-80.0 */
        agglMatrixMode( AGGL_MODELVIEW );

        agglLoadIdentity() ;
        agglLookAtf(c[0],c[1],c[2],t[0],t[1],t[2],u[0],u[1],u[2]);



	/* ライト設定 */
{
		const static AGGLfloat lpos[4] = { 1.0f, 1.0f, 1.0f, 0.0f } ;
		const static AGGLfloat lamb[3] = { 0.5f, 0.3f, 0.3f } ;
		const static AGGLfloat ldif[3] = { 0.5f, 0.5f, 0.5f } ;
		const static AGGLfloat lspc[3] = { 0.0f, 0.0f, 0.0f } ;
		agglLightfv( AGGL_LIGHT0, AGGL_AMBIENT,  lamb);
		agglLightfv( AGGL_LIGHT0, AGGL_DIFFUSE,  ldif);
		agglLightfv( AGGL_LIGHT0, AGGL_SPECULAR, lspc);
		agglLightfv( AGGL_LIGHT0, AGGL_POSITION, lpos);
		agglEnable( AGGL_LIGHT0 );
};

	player_drw(NULL);
	/* ツリー→ワールド座標変換 */
	//ag3dSetRoot( 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, node );

	/* ツリー形状を求める */
	//ag3dCalcTree( &(age3dTree[ AG_AG3D_AG3DEXPORTTREE ]), &(age3dMotion[ 0 ]), (float)frame, node );

	/* 描画 */
		/* 不透明 */
	//agglDisable( AGGL_BLEND );
	//agglDepthMask( AGGL_TRUE );

	//ag3dDrawAnimenodeDCmd( &(age3dModel[ AG_AG3D_AG3DEXPORTMODEL ]), node, &(age3dDCmd[ AG_AG3D_AG3DEXPORTMODEL ]), AG3D_OFFBLEND_ONDEPTH );

		/* 半透明、Ｚバッファ更新 */
	//agglEnable( AGGL_BLEND );

	//agglBeginZsort( AGGL_FAR_FIRST, sizeof(zsortbuf), zsortbuf );
	//ag3dDrawAnimenode( &(age3dModel[ AG_AG3D_AG3DEXPORTMODEL ]), node, AG3D_ONBLEND_ONDEPTH );
	//agglEndZsort();

		/* 半透明、Ｚバッファ非更新 */
	//agglEnable( AGGL_BLEND );
	//agglDepthMask( AGGL_FALSE );

	//agglBeginZsort( AGGL_FAR_FIRST, sizeof(zsortbuf), zsortbuf );
	//ag3dDrawAnimenode( &(age3dModel[ AG_AG3D_AG3DEXPORTMODEL ]), node, AG3D_ONBLEND_OFFDEPTH );
	//agglEndZsort();

	//agglDepthMask( AGGL_TRUE );

	/* フレーム描画終了 */
	//err = agglGetError();
	//if ( err != 0 ) {
	//	_dprintf( "!!!!!!!!!!!!!! err = %d, frame = %d !!!!!!!!!!!\n" , err, frame );
	//}

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
	agglDisable( AGGL_LIGHT0 );
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
