#include <amlib.h>
#include <agdraw.h>

#include <vdpreg.h>
#include <aggl.h>
#include <ag3d.h>
#include <ag3danime.h>

#include "export.h"

/* �m�[�h���o�b�t�@ */
/* �K�v�T�C�Y�� ag3dGetNodeSize() * ag3dGetTreeNodes(man_tree) */
static	AG3Danimenode	node[256];

/* �y�\�[�g���̎O�p�`�o�b�t�@ */
/* �K�v�T�C�Y�� agglGet**(AGGL_ZSORT_TRIANGLE_SIZE)�œ�����l * ag3dGetModelTris(man_model) */
static	char	zsortbuf[1024*10*10];

/* ���_�o�b�t�@�iagglDrawElements�p�j */
/* �����T�C�Y�� agglGet**(AGGL_TEMPORARY_VERTEX_SIZE)�œ�����l * ag3dGetModelVtxs(man_model) */
static	char	vtxbuf[10240*2];

u32 DrawBuffer[2][65536*16];

const int MotionList[] = { AG_AG3D_AG3DEXPORTMOTION , AG_AG3D_AG3DGIRL2MOTION , AG_AG3D_AG3DGIRL3MOTION };

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

		/* gl�w�i������ */
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

	/* �����ϊ��ݒ� */
	ag3dPerspective( &(age3dCamera[ AG_AG3D_AG3DEXPORTPERSP ]),
		(float)frame, ((float)DISP_WIDTH)/DISP_HEIGHT, 1.0f, 1000.0f );

	/* ���_���W�ϊ��ݒ� */
	ag3dLookAt( &(age3dCamera[ AG_AG3D_AG3DEXPORTPERSP ]), (float)frame );

	/* ���C�g�ݒ� */
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

	/* �c���[�����[���h���W�ϊ� */
	ag3dSetRoot( 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, node );

	/* �c���[�`������߂� */
	ag3dCalcTree( &(age3dTree[ AG_AG3D_AG3DEXPORTTREE ]), &(age3dMotion[ motion_number ]), (float)frame, node );

	/* �`�� */
		/* �s���� */
	agglDisable( AGGL_BLEND );
	agglDepthMask( AGGL_TRUE );

	ag3dDrawAnimenodeDCmd( &(age3dModel[ AG_AG3D_AG3DEXPORTMODEL ]), node, &(age3dDCmd[ AG_AG3D_AG3DEXPORTMODEL ]), AG3D_OFFBLEND_ONDEPTH );

		/* �������A�y�o�b�t�@�X�V */
	agglEnable( AGGL_BLEND );

	agglBeginZsort( AGGL_FAR_FIRST, sizeof(zsortbuf), zsortbuf );
	ag3dDrawAnimenode( &(age3dModel[ AG_AG3D_AG3DEXPORTMODEL ]), node, AG3D_ONBLEND_ONDEPTH );
	agglEndZsort();

		/* �������A�y�o�b�t�@��X�V */
	agglEnable( AGGL_BLEND );
	agglDepthMask( AGGL_FALSE );

	agglBeginZsort( AGGL_FAR_FIRST, sizeof(zsortbuf), zsortbuf );
	ag3dDrawAnimenode( &(age3dModel[ AG_AG3D_AG3DEXPORTMODEL ]), node, AG3D_ONBLEND_OFFDEPTH );
	agglEndZsort();

	agglDepthMask( AGGL_TRUE );

	/* �t���[���`��I�� */
	err = agglGetError();
	if ( err != 0 ) {
		_dprintf( "!!!!!!!!!!!!!! err = %d, frame = %d !!!!!!!!!!!\n" , err, frame );
	}
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
