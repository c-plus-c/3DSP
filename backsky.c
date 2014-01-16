#include <amlib.h>
#include <aggl.h>
#include "export.h"
#include "extern.h"
void DrawSky()
{
	agglEnable( AGGL_BLEND );
	agglDepthMask( AGGL_TRUE );

	agglPushMatrix();
	agglScalef(ACTIVE_RADIUS+20,(ACTIVE_RADIUS+20.0)/2.0,ACTIVE_RADIUS+20);
		/* ツリー→ワールド座標変換 */
	ag3dSetRoot( 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, node );

		/* ツリー形状を求める */
	ag3dCalcTree( &(age3dTree[ AG_AG3D_SKYBACKTREE ]), &(age3dMotion[ AG_AG3D_SKYBACKMOTION ]), (float)0, node );
	ag3dDrawAnimenodeDCmd( &(age3dModel[ AG_AG3D_SKYBACKMODEL ]), node, &(age3dDCmd[ AG_AG3D_SKYBACKMODEL ]), AG3D_ONBLEND_ONDEPTH );
	
	agglPopMatrix();
}
