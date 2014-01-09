#include <amlib.h>

#include "export.h"
#include "extern.h"

long long int pow(long a,int b){
	long long int m = 1;
	for(;b>0;b--)
		m *= a;
	return m;
}

void drawNum(int x,int y, long long int num){
	int w,h;
	int d = 30,l = x,f = 0;
	for(;d>=0;d--){
		if(num/pow(10,d) > 0 || f==1){
			int number=num/pow(10,d) + '0' - ' ' + AG_CG_32;
			agDrawSETFCOLOR( &DBuf, ARGB( 255, 255, 0, 0 ) );
			ageTransferAAC( &DBuf,number, 0, &w, &h );
			agDrawSETDBMODE( &DBuf, 0xff, 0, 2, 1 );
			agDrawSPRITE( &DBuf, 1, l, y, l+w, y+h );

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


void drawStr(int x,int y, char* str){
	int l = strlen(str);
	int i,left = x;
	int w, h;

	for(i=0;i<l;i++){
		if(str[i] == '\n'){
			y += h;
			left = x;
			continue;
		}

		agDrawSETFCOLOR( &DBuf, ARGB( 255, 255, 0, 0 ) );
		ageTransferAAC( &DBuf, str[i] - ' ' + AG_CG_32, 0, &w, &h );
		agDrawSETDBMODE( &DBuf, 0xff, 0, 2, 1 );
		agDrawSPRITE( &DBuf, 1, left, y, left+(w), y+(h) );

		left += (w);
	}
}