#ifndef __FIREBALL_H__
#define __FIREBALL_H__

#include "export.h"
#include "Object.h"
#include "extern.h"

typedef struct Fireball_t
{
  Object Obj;
}Fireball;

/* TODO:今西
描画
*/
void fireball_drw(Object *dp);

/* TODO:今西
*/
void fireball_move(Object *dp);

#endif
