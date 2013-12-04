//オブジェクトクラス

#ifndef __OBJECT_H__
#define __OBJECT_H__

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
    Vec3f	rotation;
	Vec3f	translation;
    Stat	stat;
} Object;

#endif;