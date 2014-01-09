//オブジェクトクラス

#ifndef __OBJECT_H__
#define __OBJECT_H__

#define PI (3.1415)

#define OBJECT_MAX 100

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

typedef enum VerticalState_t
{
	VNORMAL,VLEFT,VRIGHT
}VerticalState;

typedef struct ObjectLocal {
  int     pid;		//controller id
  int     visibility;
  Vec3f	direction;
  Vec3f	translation;
  Stat	stat;
  float pitch;
  float roll;
  float yaw;
  
  float pitchAccelerator;
  float rollAccelerator;

  void  (*mov)( struct ObjectLocal *dp );
  void  (*drw)( struct ObjectLocal *dp );
  VerticalState verticalState;
} Object;




#endif
