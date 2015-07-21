#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "export.h"
#include "Object.h"
#include "extern.h"

/* TODO:今西 */

void player_init();

void player_initWithParam(Vec3f pos, Vec3f angle);

/*
半径で判定以上に当たり判定をしたければ書く
*/
int player_hc2(Object *dp, Object *sp, float cx, float cy, float cz);
/* TODO:今西
パッド処理
*/
void player_move(Object *dp);

/* TODO:今西
描画
*/
void player_drw(Object *dp);

#endif
