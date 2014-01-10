#ifndef __FIREBALL_H__
#define __FIREBALL_H__

#include "export.h"
#include "Object.h"
#include "extern.h"

#define BULLET_VELOCITY 1.5

/* TODO:今西
描画
*/
void fireball_drw(Object *dp);

/* TODO:今西
*/
void fireball_move(Object *dp);

#endif
