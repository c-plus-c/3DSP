#include <amlib.h>
#include <agdraw.h>
#include <agetool.h>
#include <agtransfer.h>
#include <vdpreg.h>

#include <stdlib.h>

u32 DrawBuffer[ 4096*10 ];

long long int pow(long a,int b){
	long long int m = 1;
	for(;b>0;b--)
		m *= a;
	return m;
}

void drawNum(AGDrawBuffer*DBuf,int x,int y, long long int num){
	int w,h;
	int d = 30,l = x,f = 0;
	for(;d>=0;d--){
		if(num/pow(10,d) > 0 || f==1){
			agDrawSETFCOLOR( DBuf, ARGB( 255, 255, 0, 0 ) );
			ageTransferAAC( DBuf, num/pow(10,d) - ' ' + '0', 0, &w, &h );
			agDrawSETDBMODE( DBuf, 0xff, 0, 2, 1 );
			agDrawSPRITE( DBuf, 1, l, y, l+w, y+h );

			num -= pow(10,d) *( num/pow(10,d));
			l += w;
			f = 1;
		}
	}
}

int strlen(char* str){
	int i=0;
	while(1){
		if(str[i] == '\0')
			break;
		i++;
	}
	return i;
}


void drawStr(AGDrawBuffer*DBuf,int x,int y, char* str){
	int l = strlen(str);
	int i,left = x;
	int w, h;

	for(i=0;i<l;i++){
		if(str[i] == '\n'){
			y += h;
			left = x;
			continue;
		}

		agDrawSETFCOLOR( DBuf, ARGB( 255, 255, 0, 0 ) );
		ageTransferAAC( DBuf, str[i] - 32, 0, &w, &h );
		agDrawSETDBMODE( DBuf, 0xff, 0, 2, 1 );
		agDrawSPRITE( DBuf, 1, left, y, left+(w), y+(h) );

		left += (w);
	}
}


void  main( void )  {
	AGDrawBuffer DBuf;
	int x0,y0,w0,h0,count = 0;
	int x1,y1,w1,h1;
	int x2,y2,w2,h2;

	agpDisableCpuInterrupts();
	aglInitialize();
	agpEnableCpuInterrupts();

	x0 = 200<<2;
	y0 = 200<<2;
	w0 = 100<<2;
	h0 = 100<<2;

	x1 = 500<<2;
	y1 = 300<<2;
	w1 = 100<<2;
	h1 = 200<<2;

	x2 = 550<<2;
	y2 = 350<<2;
	w2 = 100<<2;
	h2 = 200<<2;


	while( 1 ) {
		AGPolyT* pPolyT;
		AGPolyTC* pPolyTC;
		int w,h;

		// ディスプレイリストの作成
		agDrawBufferInit( &DBuf , DrawBuffer );

		// VRAM_FB設定
		agDrawSETDAVR( &DBuf , 0 , 0 , aglGetDrawFrame() , 0 , 0 );
		agDrawSETDAVF( &DBuf, 0, 0, FB_WIDTH<<2, FB_HEIGHT<<2 );

		agDrawSETFCOLOR( &DBuf, ARGB( 255, 0, 0, 0 ) );
		agDrawSETDBMODE( &DBuf, 0xff, 0, 0, 1 );
		agDrawSPRITE( &DBuf, 0, 0, 0, FB_WIDTH<<2, FB_HEIGHT<<2 );

		drawNum(&DBuf,10<<2,100<<2, count += 1);
		drawStr(&DBuf,30<<2,400<<2,"Carla Ventresca is co-creat`*}{`*}or with husband Henry Beckett of the internationallysyndicated comic strip On A Claire Day.\nStarting in October 2007, she became one of the new cartoonists for Parade Magazine.\nCarla won the 2007 National Cartoonists Society's Reuben award\nfor Best Greeting Cards. She also creates greeting cards for American Greetings with husband Henry.");

		// ディスプレイリスト生成終了
		agDrawEODL( &DBuf );

		// ディスプレイリストを転送して描画終了を待つ
		agTransferDrawDMA( &DBuf );

		aglWaitVSync();
		aglSwap();
	};
}
