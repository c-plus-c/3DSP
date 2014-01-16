#include <amlib.h>
#include "pad.h"

static u8 pad_data;
static u8 pad_trg;
static u8 pad_rep;
static u8 pad_rep_count[8];

void PadInit( void ) {
	int i;

	pad_data = 0;
	pad_trg = 0;
	pad_rep = 0;
	for( i=0 ; i<8 ; i++ ) {
		pad_rep_count[i] = 0;
	};
}

void PadRun( void ) {
	int i;
	u16 pad = ~(*((volatile u16*)0xa9000002));

	pad_trg = (pad_data ^ pad)&pad;
	pad_data = pad;

	pad_rep = 0;
	for( i=0 ; i<8 ; i++ ) {
		u8 pos = 1<<i;

		if( (pad_trg&pos) != 0 ) {
			pad_rep_count[i] = 0;
			pad_rep |= pos;
		}
		else if( (pad_data&pos) != 0 ) {
			pad_rep_count[i]++;
			if( pad_rep_count[i] >= PAD_REPEAT_TIME ) {
				pad_rep |= pos;
				pad_rep_count[i] = 0;
			};
		};
	};
}

u8 PadTrg( void ) {
	return( pad_trg );
}

u8 PadLvl( void ) {
	return( pad_data );
}

u8 PadRpt( void ) {
	return( pad_rep );
}
