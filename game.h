#include <aggl.h>
#include <ag3d.h>
#include <ag3danime.h>

#define PI    (3.141592654f)
#define SQRT2 (1.414213562f)

#define PLAYER_NUMS 3
#define MAP_BLK_X 256    /* MAPのx方向ブロック数 */
#define MAP_BLK_Y 256    /* MAPのy方向ブロック数 */
#define MAP_BLK_Z 256    /* MAPのz方向ブロック数 */
#define BLK_PIX_X 64    /* ブロックのx方向ピクセル数 */
#define BLK_PIX_Y 64    /* ブロックのy方向ピクセル数 */
#define BLK_PIX_Y 64    /* ブロックのz方向ピクセル数 */
#define DSP_PIX_X 1024  /* 表示領域水平サイズ */
#define DSP_PIX_Y 768   /* 表示領域垂直サイズ */
#define MAP_BLK_DRAW 64 /* プレイヤーからこの数だけ離れたブロックまで描画する */

#define OBJECT_NUMS      1024
#define OBJECT_LOCAL_U32 16

#define OBJECTTYPE_FREE   0x0000  /* 空き             */
#define OBJECTTYPE_PLAYER 0x0001  /* プレイヤー       */
#define OBJECTTYPE_HBLOCK 0x0002  /* 弾     */

#define OBJECTTYPE_MASK_HIT_N 0x000f  /* 当たり判定通常  (マップ上の障害物など)     */
#define OBJECTTYPE_MASK_HIT_S 0x00f0  /* 当たり判定短距離(上に乗ったら判定の物など) */

#define OBJECTPRI_BLEND_OFF 0  /* ???????????????? */
#define OBJECTPRI_BLEND_H   1
#define OBJECTPRI_BLEND_M   2
#define OBJECTPRI_BLEND_L   3
#define OBJECTPRI_NUMS      4

typedef struct _object_ {
	/* 共通部分 */
	struct _struct_objecthead_ {
		int   pri;
		float posx;
		float posy;
		float posz;
		float rsiz; /* 当たり判定範囲 posx,posy,posz からの 半径 */
		int   type; /* OBJECTTYPE_* */
		/* ブロックリンク構築用 */
		struct _object_ *next;
		struct _object_ *back;
		int   blkx; /* オブジェクトが存在するブロック位置X */
		int   blky; /* オブジェクトが存在するブロック位置Y */
		int   blkz;	/* オブジェクトが存在するブロック位置Z */
		int   list; /* オブジェクトが存在するブロックのリンクリスト */        //たぶん未使用
		/* 描画用データ */
		u32   rgb;  /* 色           */
		int   bmp;  /* ビットマップ */
		/* 処理関数 */
		void(*mov)(struct _object_ *dp);                      /* 移動関数   */
		void(*hit)(struct _object_ *dp, struct _object_ *sp); /* 当たり処理(sp:当って来たもの) */
		void(*drw)(struct _object_ *dp);                      /* 描画関数   */
		int(*hc2)(struct _object_ *dp, struct _object_ *sp, float dx, float dy, float dz); /* 2次当たり判定(sp:当って来たもの) */
	} h;
	/* 共通部分 */
	struct _struct_objctdata_ {
		u32    data[OBJECT_LOCAL_U32];
	} d;
} Object;

extern Object  object_data[OBJECT_NUMS];         /* オブジェクトの実体 */
extern Object *object_list[MAP_BLK_Y*MAP_BLK_X*MAP_BLK_Z]; /* オブジェクトのブロックからのリンクリスト */

/*-- game.c --*/
void	init_map();

/*-- object.c --*/
void	init_obj();


