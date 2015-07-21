#include <amlib.h>
#include <aggl.h>
#include "export.h"
#include "extern.h"
#include "Object.h"

void DrawCubes()
{
	int i;
	float x[] = { 0, 150, -150, 150, -150, 0 };
	float y[] = { 50, 150, 150, 150, 150, 250 };
	float z[] = { 0, -150, 150, -150, 150, 0 };
	agglEnable(AGGL_BLEND);
	agglDepthMask(AGGL_TRUE);

	for (i = 0; i < 6; ++i){
		agglPushMatrix();

		agglTranslatef(x[i], y[i], z[i]);

		agglScalef(10, 10, 10);
		ag3dSetRoot(1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, node);

		ag3dCalcTree(&(age3dTree[AG_AG3D_CUBETREE]), &(age3dMotion[AG_AG3D_CUBEMOTION]), (float)0, node);
		ag3dDrawAnimenodeDCmd(&(age3dModel[AG_AG3D_CUBEMODEL]), node, &(age3dDCmd[AG_AG3D_CUBEMODEL]), AG3D_ONBLEND_ONDEPTH);

		agglPopMatrix();
	}

}