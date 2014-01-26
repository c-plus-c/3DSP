#include <amlib.h>
#include <aggl.h>
#include "export.h"
#include "extern.h"
void DrawSky()
{
	agglEnable( AGGL_BLEND );
	agglDepthMask( AGGL_TRUE );

	agglPushMatrix();	
	
	agglScalef(ACTIVE_RADIUS+20,(ACTIVE_RADIUS+20.0),ACTIVE_RADIUS+20);
	ag3dSetRoot( 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, node );

	ag3dCalcTree( &(age3dTree[ AG_AG3D_SKYBACKTREE ]), &(age3dMotion[ AG_AG3D_SKYBACKMOTION ]), (float)1, node );
	ag3dDrawAnimenodeDCmd( &(age3dModel[ AG_AG3D_SKYBACKMODEL ]), node, &(age3dDCmd[ AG_AG3D_SKYBACKMODEL ]), AG3D_ONBLEND_ONDEPTH);
	
	//agglEnable( AGGL_BLEND );

	//agglBeginZsort( AGGL_FAR_FIRST, sizeof(zsortbuf), zsortbuf );
	//ag3dDrawAnimenode( &(age3dModel[ AG_AG3D_SKYBACKMODEL ]), node, AG3D_ONBLEND_ONDEPTH );
	//agglEndZsort();
	
	//agglEnable( AGGL_BLEND );
	//agglDepthMask( AGGL_FALSE );

	//agglBeginZsort( AGGL_FAR_FIRST, sizeof(zsortbuf), zsortbuf );
	//ag3dDrawAnimenode( &(age3dModel[ AG_AG3D_SKYBACKMODEL ]), node, AG3D_ONBLEND_OFFDEPTH );
	//agglEndZsort();
	
	
	agglPopMatrix();
}
