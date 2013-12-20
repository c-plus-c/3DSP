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
#define AG_CG_32	(0)
#define AG_CG_33	(1)
#define AG_CG_34	(2)
#define AG_CG_35	(3)
#define AG_CG_36	(4)
#define AG_CG_37	(5)
#define AG_CG_38	(6)
#define AG_CG_39	(7)
#define AG_CG_40	(8)
#define AG_CG_41	(9)
#define AG_CG_42	(10)
#define AG_CG_43	(11)
#define AG_CG_44	(12)
#define AG_CG_45	(13)
#define AG_CG_46	(14)
#define AG_CG_47	(15)
#define AG_CG_48	(16)
#define AG_CG_49	(17)
#define AG_CG_50	(18)
#define AG_CG_51	(19)
#define AG_CG_52	(20)
#define AG_CG_53	(21)
#define AG_CG_54	(22)
#define AG_CG_55	(23)
#define AG_CG_56	(24)
#define AG_CG_57	(25)
#define AG_CG_58	(26)
#define AG_CG_59	(27)
#define AG_CG_60	(28)
#define AG_CG_61	(29)
#define AG_CG_62	(30)
#define AG_CG_63	(31)
#define AG_CG_64	(32)
#define AG_CG_65	(33)
#define AG_CG_66	(34)
#define AG_CG_67	(35)
#define AG_CG_68	(36)
#define AG_CG_69	(37)
#define AG_CG_70	(38)
#define AG_CG_71	(39)
#define AG_CG_72	(40)
#define AG_CG_73	(41)
#define AG_CG_74	(42)
#define AG_CG_75	(43)
#define AG_CG_76	(44)
#define AG_CG_77	(45)
#define AG_CG_78	(46)
#define AG_CG_79	(47)
#define AG_CG_80	(48)
#define AG_CG_81	(49)
#define AG_CG_82	(50)
#define AG_CG_83	(51)
#define AG_CG_84	(52)
#define AG_CG_85	(53)
#define AG_CG_86	(54)
#define AG_CG_87	(55)
#define AG_CG_88	(56)
#define AG_CG_89	(57)
#define AG_CG_90	(58)
#define AG_CG_91	(59)
#define AG_CG_92	(60)
#define AG_CG_93	(61)
#define AG_CG_94	(62)
#define AG_CG_95	(63)
#define AG_CG_96	(64)
#define AG_CG_97	(65)
#define AG_CG_98	(66)
#define AG_CG_99	(67)
#define AG_CG_100	(68)
#define AG_CG_101	(69)
#define AG_CG_102	(70)
#define AG_CG_103	(71)
#define AG_CG_104	(72)
#define AG_CG_105	(73)
#define AG_CG_106	(74)
#define AG_CG_107	(75)
#define AG_CG_108	(76)
#define AG_CG_109	(77)
#define AG_CG_110	(78)
#define AG_CG_111	(79)
#define AG_CG_112	(80)
#define AG_CG_113	(81)
#define AG_CG_114	(82)
#define AG_CG_115	(83)
#define AG_CG_116	(84)
#define AG_CG_117	(85)
#define AG_CG_118	(86)
#define AG_CG_119	(87)
#define AG_CG_120	(88)
#define AG_CG_121	(89)
#define AG_CG_122	(90)
#define AG_CG_123	(91)
#define AG_CG_124	(92)
#define AG_CG_125	(93)
#define AG_CG_126	(94)
#define AG_CG_CANNON	(95)
#define AG_CG_VERTICAL_EDGE	(96)
#define AG_CG_HORIZON_EDGE	(97)
#define AG_CG_MAINWING_EDGED	(98)
#define AG_CG_BODY	(99)
#define AG_CG_OCEAN	(100)

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
#define AG_AG3D_PLANEMODEL	(1)

/***************************************************************/
/*                        AG3D Tree Symbol                     */
/***************************************************************/
#define AG_AG3D_AG3DEXPORTTREE	(0)
#define AG_AG3D_PLANETREE	(1)

/***************************************************************/
/*                       AG3D Motion Symbol                    */
/***************************************************************/
#define AG_AG3D_AG3DEXPORTMOTION	(0)
#define AG_AG3D_PLANEMOTION	(1)

/***************************************************************/
/*                        AG3D Camera Symbol                   */
/***************************************************************/
#define AG_AG3D_AG3DEXPORTPERSP	(0)
#define AG_AG3D_PLANEPERSP	(1)

/***************************************************************/
/*                          Data Member                        */
/***************************************************************/
extern const AGERomMember ageRM[101];
extern const AGERM3Member ageRM3[1];
extern const u32 ageReserve[1];
extern const u32 ageUser[1];
extern const AG3DModelHeadChunk age3dModel[2];
extern const AG3DDCmdHeadChunk age3dDCmd[2];
extern const AG3DTreeHeadChunk age3dTree[2];
extern const AG3DMotionHeadChunk age3dMotion[2];
extern const AG3DCameraHeadChunk age3dCamera[2];
extern const s16 ageVGCnt;

#ifdef __cplusplus
}
#endif

#endif /* __AG_EXPORT__ */
