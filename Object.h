//オブジェクトクラス

#ifndef __OBJECT_H__
#define __OBJECT_H__

#define PI (3.1415926535f)

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
  double pitch;
  double roll;
  double yaw;
} Object;

#endif
