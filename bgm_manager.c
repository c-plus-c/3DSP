#include <agesndmgr.h>


static SNDHANDLE handle;

void SetCurrentBGMHandle(int rom_index,int loop)
{
	handle=ageSndMgrAlloc(rom_index, 0, loop, AGE_SNDMGR_PANMODE_LR12, 0);
	
	// ボリューム設定(フェードターゲットボリューム)
	ageSndMgrSetVolume( handle , 100 );

	// パン設定.
	ageSndMgrSetPan( handle , 128 );
}

void PlayCurrentBGM()
{
	ageSndMgrPlay(handle);
}

void ReleaseCurrentBGMHandle()
{
	ageSndMgrRelease(handle);
}

void StopCurrentBGM()
{
	ageSndMgrStop(handle);
}

void playBgm(int rom_index){
	StopCurrentBGM();
	ReleaseCurrentBGMHandle();
	SetCurrentBGMHandle(rom_index,1);
	PlayCurrentBGM();
}