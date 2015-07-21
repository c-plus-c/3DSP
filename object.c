#include <amlib.h>
#include <agdraw.h>
#include <vdpreg.h>
#include <agetool.h>

#include <agGamePad.h>

#include "game.h"

Object  object_data[OBJECT_NUMS];
Object *object_list[MAP_BLK_Y*MAP_BLK_X];

void object_clear()
{
	int n;
	/* クリア */
	for (n = 0; n < OBJECT_NUMS; n++) {
		object_data[n].h.type = OBJECTTYPE_FREE;
	}
	for (n = 0; n < (MAP_BLK_Y*MAP_BLK_X); n++) {
		object_list[n] = NULL;
	}
}

Object *object_alloc(int type)
{
	int n;
	Object *dp;

	/* 空きを検索 */
	for (n = 0; n < OBJECT_NUMS; n++) {
		dp = &(object_data[n]);
		if (dp->h.type == OBJECTTYPE_FREE) {
			dp->h.type = type;
			dp->h.pri = OBJECTPRI_BLEND_OFF;
			dp->h.mov = NULL;
			dp->h.hit = NULL;
			dp->h.drw = NULL;
			dp->h.hc2 = NULL;
			/* ブロックリンク構築用 */
			dp->h.next = NULL;
			dp->h.back = NULL;
			dp->h.blkx = 0;  /* オブジェクトが存在するブロック位置X */
			dp->h.blky = 0;  /* オブジェクトが存在するブロック位置X */
			dp->h.blkz = 0;
			dp->h.list = -1; /* オブジェクトが存在するブロックのリンクリスト */
			return(dp);
		}
	}
#if 1
	_dprintf("ブロックリストに空きが無い?\n");
	_rtl_exit();
#endif
	return(NULL);
}

void object_free(Object *dp)
{
	object_unlink(dp);
	dp->h.type = OBJECTTYPE_FREE;
}

Object *object_hitcheck(Object *cp, float cx, float cy, u32 mask)
{
	float px, py, pz;
	Object *dp;
	int bx, by, bz, bn;
	float cd, dd, dx, dy, dz;

	px = cp->h.posx + cx;
	py = cp->h.posy + cy;
	pz = cp->h.posz + cz;
	for (by = -1; by <= 1; by++) {
		if ((cp->h.blky + by) >= 0 && (cp->h.blky + by) < MAP_BLK_Y) {
			for (bx = -1; bx < 1; bx++) {
				if ((cp->h.blkx + bx) >= 0 && (cp->h.blkx + bx) < MAP_BLK_X) {
					for (bz = -1; bz < 1; bz++){
						if (cp->h.blkz + bz >= 0 && (cp->h.blkz + bz) < MAP_blk_Z){
							bn = (cp->h.blky + by) * MAP_BLK_X*MAP_BLK_Y + (cp->h.blkx + bx)*MAP_BLK_X + (cp->h.blkz + bz);
							dp = object_list[bn];
							while (dp != NULL) {
								if (dp->h.type != OBJECTTYPE_FREE && dp->h.hit != NULL && cp != dp && (dp->h.type & mask) != 0) {
									/* 自分以外と判定 */
									cd = cp->h.rsiz + dp->h.rsiz;
									cd = cd*cd;
									dx = dp->h.posx - px; dx = dx*dx;
									dy = dp->h.posy - py; dy = dy*dy;
									dz = dp->h.posz - pz; dz = dz*dz;
									dd = dx + dy + dz;
									if (dd < cd) {
										if (dp->h.hc2 != NULL) {
											if (dp->h.hc2(dp, cp, cx, cy, cz)) {
												return(dp);
											}
										}
										else {
											return(dp);
										}
									}
								}
								dp = dp->h.next;
							}
						}
					}
				}
			}
		}
	}
	return(NULL);
}


void    object_unlink(Object *dp)
{
	if (dp->h.list == -1) {
		return;
	}
	if (dp->h.back == NULL) {
		if (dp->h.next == NULL) {
			object_list[dp->h.list] = NULL;
		}
		else {
			object_list[dp->h.list] = dp->h.next;
			dp->h.next->h.back = NULL;
		}
	}
	else {
		if (dp->h.next == NULL) {
			dp->h.back->h.next = NULL;
		}
		else {
			dp->h.back->h.next = dp->h.next;
			dp->h.next->h.back = dp->h.back;
		}
	}
	dp->h.list = -1;
	dp->h.back = NULL;
	dp->h.next = NULL;
}

void    object_link(Object *dp)
{
	Object    **lp;
	Object    *cp;
	int        bx;
	int        by;
	int		   bz;
	int        bn;

	bx = (int)(dp->h.posx / BLK_PIX_X);
	if (bx < 0) {
		bx = 0;
	}
	if (bx >= MAP_BLK_X) {
		bx = (MAP_BLK_X - 1);
	}
	dp->h.blkx = bx;

	by = (int)(dp->h.posy / BLK_PIX_Y);
	if (by < 0) {
		by = 0;
	}
	if (by >= MAP_BLK_Y) {
		by = (MAP_BLK_Y - 1);
	}
	dp->h.blky = by;

	bz = (int)(bp->h.posz / BLK_PIX_Z);
	if (bz < 0) {
		bz = 0;
	}
	if (bz >= MAP_BLK_Z) {
		bz = (MAP_BLK_Z - 1);
	}
	dp->h.blkz = bz;


	bn = ((by * MAP_BLK_X * MAP_BLK_Y) + bx * MAP_BLK_X + bz);
	lp = object_list + bn;

	object_unlink(dp);
	if (*lp != NULL) {
		cp = *lp;
		dp->h.next = cp;
		cp->h.back = dp;
		*lp = dp;
	}
	else {
		*lp = dp;
	}
	dp->h.list = bn;
}
