#include <agexport.h>
#include <amlib.h>
#include <agdraw.h>

#include <vdpreg.h>
#include <aggl.h>
#include <ag3d.h>
#include <ag3danime.h>

/* ノード情報バッファ */
/* 必要サイズは ag3dGetNodeSize() * ag3dGetTreeNodes(man_tree) */
extern AG3Danimenode node[256];

/* Ｚソート時の三角形バッファ */
/* 必要サイズは agglGet**(AGGL_ZSORT_TRIANGLE_SIZE)で得られる値 * ag3dGetModelTris(man_model) */
extern char	zsortbuf[1024*10*50];

/* 頂点バッファ（agglDrawElements用） */
/* 推奨サイズは agglGet**(AGGL_TEMPORARY_VERTEX_SIZE)で得られる値 * ag3dGetModelVtxs(man_model) */
extern char	vtxbuf[10240*2];

extern u32 DrawBuffer[2][65536*16];

extern const int MotionList[1];