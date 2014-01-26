#include <amlib.h>
#include <aggl.h>
#include "export.h"
#include "extern.h"
void DrawSky()
{
	agglEnable( AGGL_BLEND );
	agglDepthMask( AGGL_TRUE );

	agglPushMatrix();	
	
	agglTranslatef(0,-100.0,0);
	agglScalef(SKY_SPHERE_RADIUS, SKY_SPHERE_RADIUS, SKY_SPHERE_RADIUS);
	ag3dSetRoot( 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, node );

	ag3dCalcTree( &(age3dTree[ AG_AG3D_SKYSPHERETREE ]), &(age3dMotion[ AG_AG3D_SKYSPHEREMOTION ]), (float)0, node );
	ag3dDrawAnimenodeDCmd( &(age3dModel[ AG_AG3D_SKYSPHEREMODEL ]), node, &(age3dDCmd[ AG_AG3D_SKYSPHEREMODEL ]), AG3D_ONBLEND_ONDEPTH);
	
	agglPopMatrix();
}
