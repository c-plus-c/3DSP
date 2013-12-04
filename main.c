#include <amlib.h>
#include <agdraw.h>
#include <vdpreg.h>
#include <agetool.h>

#include <agGamePad.h>

#include "game.h"

//TODO:今西 描画初期化	
void init_3d()
{

}

void main( void )
{
	init_3d();
	init_obj();
	init_map();
}


static volatile u32 _SystemVSyncCount=0;

static volatile int i_exec_draw=0;
static volatile int i_exec_swap=0;

static s32 ifnc_vsync(int type)
{
    _SystemVSyncCount++;
    i_exec_swap=0;
    return(1);
}


static s32 ifnc_draw(int type)
{
    aglSwap();
    draw_time_end();
    i_exec_draw=0;
    i_exec_swap=1;
    return(0);
}

static void wait_draw()
{
    while( i_exec_draw ) {
        AG_IDLE_PROC();
        agGamePadSyncIdle();
    }
}

static void wait_swap()
{
    while( i_exec_swap ) {
        AG_IDLE_PROC();
        agGamePadSyncIdle();
    }
}