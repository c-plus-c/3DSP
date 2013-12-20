//オブジェクトクラス

#ifndef __OBJECT_H__
#define __OBJECT_H__

#define PI (3.1415)

typedef struct Vec3f_t
{
  float X;
  float Y;
  float Z;
}Vec3f;

typedef enum Stat_t
  {
  IDLE,DEAD
}Stat;

typedef struct ObjectLocal {
  int     pid;		//controller id
  Vec3f	direction;
  Vec3f	translation;
  Stat	stat;
  float pitch;
  float roll;
  float yaw;
} Object;

#endif
