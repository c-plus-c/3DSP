#include <amlib.h>
#include <aggl.h>
#include "export.h"
#include "extern.h"
#include "Object.h"

void DrawCubes()
{
	agglPushMatrix();
	
	agglEnable( AGGL_BLEND );
	agglDepthMask( AGGL_TRUE );
	
	agglTranslatef(0,100,0);
	
	agglScalef(10,10,10);
	ag3dSetRoot( 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, node );

	ag3dCalcTree( &(age3dTree[ AG_AG3D_CUBETREE]), &(age3dMotion[ AG_AG3D_CUBEMOTION ]), (float)0, node );
	ag3dDrawAnimenodeDCmd( &(age3dModel[ AG_AG3D_CUBEMODEL ]), node,&(age3dDCmd[ AG_AG3D_CUBEMODEL ]), AG3D_ONBLEND_ONDEPTH );
	
	agglPopMatrix();
}