typedef struct {
    int     pid;		//controller id
    float	anglex;
    float	angley;
    float 	anglez;
    int     stat;
} ObjectLocal;

#define STAT_IDEL  0
#define STAT_DEAD  1

/* TODO:今西
半径で判定以上に当たり判定をしたければ書く 
*/
static int player_hc2(Object *dp,Object *sp,float cx, float cy, float cz)
{

}
/* TODO:今西
パッド処理
*/
static void player_move(Object *dp)
{

}

/* TODO:今西
描画
*/
static void player_drw(Object *dp)
{

}