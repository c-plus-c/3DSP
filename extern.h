#ifndef __EXTERN_H__
#define __EXTERN_H__

#include <agexport.h>
#include <amlib.h>
#include <agdraw.h>

#include <vdpreg.h>
#include <aggl.h>
#include <ag3d.h>
#include <ag3danime.h>

#include "Object.h"

#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))
#define myabs(a) ((a) > 0 ? (a) : (-a))
#define SKY_SPHERE_RADIUS 1500.0

/* ノード情報バッファ */
/* 必要サイズは ag3dGetNodeSize() * ag3dGetTreeNodes(man_tree) */
extern AG3Danimenode node[512];

/* Ｚソート時の三角形バッファ */
/* 必要サイズは agglGet**(AGGL_ZSORT_TRIANGLE_SIZE)で得られる値 * ag3dGetModelTris(man_model) */
extern char	zsortbuf[1024*10*50];

/* 頂点バッファ（agglDrawElements用） */
/* 推奨サイズは agglGet**(AGGL_TEMPORARY_VERTEX_SIZE)で得られる値 * ag3dGetModelVtxs(man_model) */
extern char	vtxbuf[10240*2];

extern u32 DrawBuffer[2][65536*32];

extern const int MotionList[1];

extern Object Objects[OBJECT_MAX];

extern AGDrawBuffer DBuf;

extern int drawNum(int x,int y, long long int num);

extern int drawStr(int x,int y, char* str);

extern void drawHud(Object *dp, u32 frameCount);

extern volatile u32 frameCount;

extern void allocFireballs(int pid);
extern Object* getFreeFireball(int pid);

#endif