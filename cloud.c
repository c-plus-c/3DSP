#include "cloud.h"
#include <amlib.h>
#include <aggl.h>
#include "export.h"
#include "extern.h"

Cloud clouds[CLOUD_NUM];

void GenerateClouds()
{
	int i;
	for (i = 0; i < CLOUD_NUM; ++i)
	{
		clouds[i].Position.X = ACTIVE_RADIUS - frand() * 2 * ACTIVE_RADIUS;
		clouds[i].Position.Y = 50 + frand() * 120;
		clouds[i].Position.Z = ACTIVE_RADIUS - frand() * 2 * ACTIVE_RADIUS;
		clouds[i].Alpha = 1;
		clouds[i].Type = i % 4;
	}
}

void DrawClouds()
{
	int i;
	for (i = 0; i < CLOUD_NUM; ++i)
	{
		agglPushMatrix();
		agglBillboard(AGGL_BILLBOARD_PLUSZ, AGGL_BILLBOARD_ROTFREE, AGGL_BILLBOARD_TOEYE);

		agglDisable(AGGL_BLEND);
		agglDepthMask(AGGL_TRUE);

		agglTranslatef(clouds[i].Position.X, clouds[i].Position.Y, clouds[i].Position.Z);

		agglScalef(10, 10, 10);
		ag3dSetRoot(1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, node);

		ag3dCalcTree(&(age3dTree[AG_AG3D_CLOUD1TREE + clouds[i].Type]), &(age3dMotion[AG_AG3D_CLOUD1MOTION + clouds[i].Type]), (float)0, node);
		ag3dDrawAnimenode(&(age3dModel[AG_AG3D_CLOUD1MODEL + clouds[i].Type]), node, AG3D_OFFBLEND_ONDEPTH);

		/* 半透明、Ｚバッファ更新 */
		agglEnable(AGGL_BLEND);

		agglBeginZsort(AGGL_FAR_FIRST, sizeof(zsortbuf), zsortbuf);
		ag3dDrawAnimenode(&(age3dModel[AG_AG3D_CLOUD1MODEL + clouds[i].Type]), node, AG3D_ONBLEND_ONDEPTH);
		agglEndZsort();

		agglEnable(AGGL_BLEND);
		agglDepthMask(AGGL_FALSE);

		agglBeginZsort(AGGL_FAR_FIRST, sizeof(zsortbuf), zsortbuf);
		ag3dDrawAnimenode(&(age3dModel[AG_AG3D_CLOUD1MODEL + clouds[i].Type]), node, AG3D_ONBLEND_OFFDEPTH);
		agglEndZsort();

		agglPopMatrix();
	}
}