#ifndef __PAD_H__
#define __PAD_H__

#define PAD_UP		(0x01)
#define PAD_DOWN	(0x02)
#define PAD_LEFT	(0x04)
#define PAD_RIGHT	(0x08)
#define PAD_A		(0x10)
#define PAD_B		(0x20)
#define PAD_X		(0x40)
#define PAD_Y		(0x80)

#define PAD_REPEAT_TIME		(5)

void PadInit( void );
void PadRun( void );
u8 PadTrg( void );
u8 PadLvl( void );
u8 PadRpt( void );

#endif // __PAD_H__
