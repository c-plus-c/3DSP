//オブジェクトクラス

#ifndef __OBJECT_H__
#define __OBJECT_H__

#define PI (3.1415)

#define OBJECT_MAX 200
#define PLAYER_MAX 3

#define PLAYER_LIFE 10

#define FIREBALL_OFFSET 20
#define FIREBALL_PER_PLAYER 60
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
  int     fireballCount;
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
  
  int targeted;

  void  (*mov)( struct ObjectLocal *dp );
  void  (*drw)( struct ObjectLocal *dp );
} Object;




#endif
