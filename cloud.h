#ifndef __CLOUD_H__
#define __CLOUD_H__

#define CLOUD_NUM 50

#include "Object.h"

typedef struct Cloud_t
{
	Vec3f Position;
	float Alpha;
	int Type;
}Cloud;

void GenerateClouds();

void DrawClouds();

#endif