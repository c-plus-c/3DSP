#include <amlib.h>
#include <aggl.h>
#include "export.h"
#include "extern.h"
void DrawSky()
{
	
	agglPushMatrix();
	agglScalef(2500,2500,2500);
		/* ツリー→ワールド座標変換 */
	ag3dSetRoot( 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, node );

		/* ツリー形状を求める */
	ag3dCalcTree( &(age3dTree[ AG_AG3D_SKYBACKTREE ]), &(age3dMotion[ AG_AG3D_SKYBACKMOTION ]), (float)1, node );
	ag3dDrawAnimenode( &(age3dModel[ AG_AG3D_SKYBACKMODEL ]), node, AG3D_OFFBLEND_ONDEPTH );

	agglPopMatrix();
	
		/* 半透明、Ｚバッファ更新 */
	agglEnable( AGGL_BLEND );

	agglBeginZsort( AGGL_FAR_FIRST, sizeof(zsortbuf), zsortbuf );
	ag3dDrawAnimenode( &(age3dModel[ AG_AG3D_SKYBACKMODEL ]), node, AG3D_ONBLEND_ONDEPTH );
	agglEndZsort();

		/* 半透明、Ｚバッファ非更新 */
	agglEnable( AGGL_BLEND );
	agglDepthMask( AGGL_FALSE );

	agglBeginZsort( AGGL_FAR_FIRST, sizeof(zsortbuf), zsortbuf );
	ag3dDrawAnimenode( &(age3dModel[ AG_AG3D_SKYBACKMODEL ]), node, AG3D_ONBLEND_OFFDEPTH );
	agglEndZsort();

	agglDepthMask( AGGL_TRUE );
}
