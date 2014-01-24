#include <amlib.h>
#include <aggl.h>
#include "export.h"
#include "extern.h"
void DrawPlane()
{
	agglEnable( AGGL_BLEND );
	agglDepthMask( AGGL_TRUE );
	
	agglPushMatrix();
	
	//agglBillboard( AGGL_BILLBOARD_PLUSY,  AGGL_BILLBOARD_ROTFREE,  AGGL_BILLBOARD_TOEYE);
	
	agglScalef(1500,1,1500);
		/* ツリー→ワールド座標変換 */
	ag3dSetRoot( 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, node );

		/* ツリー形状を求める */
	ag3dCalcTree( &(age3dTree[ AG_AG3D_PLANETREE ]), &(age3dMotion[ AG_AG3D_PLANEMOTION ]), (float)0, node );
	ag3dDrawAnimenodeDCmd( &(age3dModel[ AG_AG3D_PLANEMODEL ]), node,&(age3dDCmd[ AG_AG3D_PLANEMODEL ]), AG3D_ONBLEND_ONDEPTH);
	
	agglPopMatrix();
}
