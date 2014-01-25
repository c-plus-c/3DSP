#include <amlib.h>
#include <aggl.h>
#include "export.h"
#include "extern.h"
void DrawPlane()
{
	//ボトムクラウド描画
	agglPushMatrix();
	
	agglDisable( AGGL_BLEND );
	agglDepthMask( AGGL_TRUE );
	
	agglScalef(ACTIVE_RADIUS*1.2,ACTIVE_RADIUS*0.2,ACTIVE_RADIUS*1.2);
	ag3dSetRoot( 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, node );

	ag3dCalcTree( &(age3dTree[ AG_AG3D_BOTTOMCLOUDTREE ]), &(age3dMotion[ AG_AG3D_BOTTOMCLOUDMODEL ]), (float)0, node );
	//ag3dDrawAnimenode( &(age3dModel[ AG_AG3D_BOTTOMCLOUDMODEL ]), node, AG3D_OFFBLEND_ONDEPTH );
	
	agglEnable( AGGL_BLEND );

	agglBeginZsort( AGGL_FAR_FIRST, sizeof(zsortbuf), zsortbuf );
	ag3dDrawAnimenode( &(age3dModel[ AG_AG3D_BOTTOMCLOUDMODEL ]), node, AG3D_ONBLEND_ONDEPTH );
	agglEndZsort();
	
	//agglEnable( AGGL_BLEND );
	//agglDepthMask( AGGL_FALSE );

	//agglBeginZsort( AGGL_FAR_FIRST, sizeof(zsortbuf), zsortbuf );
	//ag3dDrawAnimenode( &(age3dModel[ AG_AG3D_BOTTOMCLOUDMODEL ]), node, AG3D_ONBLEND_OFFDEPTH );
	//agglEndZsort();
	
	agglPopMatrix();
}
