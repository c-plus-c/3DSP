//オブジェクトクラス
typedef struct ObjectLocal {
    int     pid;		//controller id
    float	anglex;
    float	angley;
    float 	anglez;
    int     stat;
} Object;

#define STAT_IDEL  0
#define STAT_DEAD  1