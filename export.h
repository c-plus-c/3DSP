#ifndef __AG_EXPORT__
#define __AG_EXPORT__

#include <agexport.h>
#include <ag3d.h>

#ifdef __cplusplus
extern "C" {
#endif

/***************************************************************/
/*                       FrameBuffer                           */
/***************************************************************/
#define AGE_FB_WIDTH	(1024)
#define AGE_FB_HEIGHT	(768)
#define AGE_DISP_WIDTH	(1024)
#define AGE_DISP_HEIGHT	(768)
#define AGE_FB_ADDR0	(7602176)
#define AGE_FB_ADDR1	(6815744)
#define AGE_ZB_ADDR	(6815744)
#define AGE_ZB_DEPTH	(4)
#define AGE_ZMD	(1)
#define AGE_AAC_ADDR	(13631488)
#define AGE_AAC_SIZE	(13631488)
#define AGE_SOUND_ROM_OFFSET	(0x800000)

/***************************************************************/
/*                    Rom Member Symbol                        */
/***************************************************************/
#define AG_CG_CANNON	(0)
#define AG_CG_VERTICAL_EDGE	(1)
#define AG_CG_HORIZON_EDGE	(2)
#define AG_CG_MAINWING_EDGED	(3)
#define AG_CG_BODY	(4)

/***************************************************************/
/*                     RM3 Member Symbol                       */
/***************************************************************/

/***************************************************************/
/*                       Vram Group Symbol                     */
/***************************************************************/

/***************************************************************/
/*                        AG3D Model Symbol                    */
/***************************************************************/
#define AG_AG3D_AG3DEXPORTMODEL	(0)

/***************************************************************/
/*                        AG3D Tree Symbol                     */
/***************************************************************/
#define AG_AG3D_AG3DEXPORTTREE	(0)

/***************************************************************/
/*                       AG3D Motion Symbol                    */
/***************************************************************/
#define AG_AG3D_AG3DEXPORTMOTION	(0)

/***************************************************************/
/*                        AG3D Camera Symbol                   */
/***************************************************************/
#define AG_AG3D_AG3DEXPORTPERSP	(0)

/***************************************************************/
/*                          Data Member                        */
/***************************************************************/
extern const AGERomMember ageRM[5];
extern const AGERM3Member ageRM3[1];
extern const u32 ageReserve[1];
extern const u32 ageUser[1];
extern const AG3DModelHeadChunk age3dModel[1];
extern const AG3DDCmdHeadChunk age3dDCmd[1];
extern const AG3DTreeHeadChunk age3dTree[1];
extern const AG3DMotionHeadChunk age3dMotion[1];
extern const AG3DCameraHeadChunk age3dCamera[1];
extern const s16 ageVGCnt;

#ifdef __cplusplus
}
#endif

#endif /* __AG_EXPORT__ */
