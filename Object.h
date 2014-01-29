//オブジェクトクラス

#ifndef __OBJECT_H__
#define __OBJECT_H__

#define PI (3.1415)

#define OBJECT_MAX 110
#define PLAYER_MAX 3

#define PLAYER_LIFE 1

#define FIREBALL_OFFSET 20
#define FIREBALL_PER_PLAYER 30
#define HORMING_OFFSET 4
#define HORMING_PER_PLAYER 5
#define GAMEPAD_LL 64
#define GAMEPAD_RR 128
//50~99-- fireball(pid=1) ...

typedef struct Vec3f_t
{
  float X;
  float Y;
  float Z;
}Vec3f;

typedef struct Vector2f_t
{
  float X;
  float Y;
}Vector2f;


typedef enum Stat_t
{
  VISIBLE, INVISIBLE, BLINK, DEAD, DYING
}Stat;

typedef enum Page_t
  {
  TITLE,INSTRUCTION,INGAME,SCORE,READY
}Page;

typedef struct ObjectLocal {
  int     pid;		//controller id

  int     life;
  int     moveCount;
  float     ammo;
  int     shotFrame;
  int     deadFrame;

  Vec3f	direction;
  Vec3f	translation;
  Stat	stat;
  float pitch;
  float roll;
  float yaw;
  
  float pitchAccelerator;
  float rollAccelerator;
  float brakeVariable;
  
  int target_pid;
  int sideOut;
  
  //odd = Shot at the frame (3 = targeted by 1 rocket and shot at the frame),(4=targeted by 2 rockets)
  int targeted;

  void  (*mov)( struct ObjectLocal *dp );
  void  (*drw)( struct ObjectLocal *dp );
} Object;




#endif
