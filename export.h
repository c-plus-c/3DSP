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
#define AG_CG_OCEAN	(5)
#define AG_CG_32	(6)
#define AG_CG_33	(7)
#define AG_CG_34	(8)
#define AG_CG_35	(9)
#define AG_CG_36	(10)
#define AG_CG_37	(11)
#define AG_CG_38	(12)
#define AG_CG_39	(13)
#define AG_CG_40	(14)
#define AG_CG_41	(15)
#define AG_CG_42	(16)
#define AG_CG_43	(17)
#define AG_CG_44	(18)
#define AG_CG_45	(19)
#define AG_CG_46	(20)
#define AG_CG_47	(21)
#define AG_CG_48	(22)
#define AG_CG_49	(23)
#define AG_CG_50	(24)
#define AG_CG_51	(25)
#define AG_CG_52	(26)
#define AG_CG_53	(27)
#define AG_CG_54	(28)
#define AG_CG_55	(29)
#define AG_CG_56	(30)
#define AG_CG_57	(31)
#define AG_CG_58	(32)
#define AG_CG_59	(33)
#define AG_CG_60	(34)
#define AG_CG_61	(35)
#define AG_CG_62	(36)
#define AG_CG_63	(37)
#define AG_CG_64	(38)
#define AG_CG_65	(39)
#define AG_CG_66	(40)
#define AG_CG_67	(41)
#define AG_CG_68	(42)
#define AG_CG_69	(43)
#define AG_CG_70	(44)
#define AG_CG_71	(45)
#define AG_CG_72	(46)
#define AG_CG_73	(47)
#define AG_CG_74	(48)
#define AG_CG_75	(49)
#define AG_CG_76	(50)
#define AG_CG_77	(51)
#define AG_CG_78	(52)
#define AG_CG_79	(53)
#define AG_CG_80	(54)
#define AG_CG_81	(55)
#define AG_CG_82	(56)
#define AG_CG_83	(57)
#define AG_CG_84	(58)
#define AG_CG_85	(59)
#define AG_CG_86	(60)
#define AG_CG_87	(61)
#define AG_CG_88	(62)
#define AG_CG_89	(63)
#define AG_CG_90	(64)
#define AG_CG_91	(65)
#define AG_CG_92	(66)
#define AG_CG_93	(67)
#define AG_CG_94	(68)
#define AG_CG_95	(69)
#define AG_CG_96	(70)
#define AG_CG_97	(71)
#define AG_CG_98	(72)
#define AG_CG_99	(73)
#define AG_CG_100	(74)
#define AG_CG_101	(75)
#define AG_CG_102	(76)
#define AG_CG_103	(77)
#define AG_CG_104	(78)
#define AG_CG_105	(79)
#define AG_CG_106	(80)
#define AG_CG_107	(81)
#define AG_CG_108	(82)
#define AG_CG_109	(83)
#define AG_CG_110	(84)
#define AG_CG_111	(85)
#define AG_CG_112	(86)
#define AG_CG_113	(87)
#define AG_CG_114	(88)
#define AG_CG_115	(89)
#define AG_CG_116	(90)
#define AG_CG_117	(91)
#define AG_CG_118	(92)
#define AG_CG_119	(93)
#define AG_CG_120	(94)
#define AG_CG_121	(95)
#define AG_CG_122	(96)
#define AG_CG_123	(97)
#define AG_CG_124	(98)
#define AG_CG_125	(99)
#define AG_CG_126	(100)
#define AG_CG_BLACK	(101)

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
#define AG_AG3D_BULLETMODEL	(2)

/***************************************************************/
/*                        AG3D Tree Symbol                     */
/***************************************************************/
#define AG_AG3D_AG3DEXPORTTREE	(0)
#define AG_AG3D_PLANETREE	(1)
#define AG_AG3D_BULLETTREE	(2)

/***************************************************************/
/*                       AG3D Motion Symbol                    */
/***************************************************************/
#define AG_AG3D_AG3DEXPORTMOTION	(0)
#define AG_AG3D_PLANEMOTION	(1)
#define AG_AG3D_BULLETMOTION	(2)

/***************************************************************/
/*                        AG3D Camera Symbol                   */
/***************************************************************/
#define AG_AG3D_AG3DEXPORTPERSP	(0)
#define AG_AG3D_PLANEPERSP	(1)

/***************************************************************/
/*                          Data Member                        */
/***************************************************************/
extern const AGERomMember ageRM[102];
extern const AGERM3Member ageRM3[1];
extern const u32 ageReserve[1];
extern const u32 ageUser[1];
extern const AG3DModelHeadChunk age3dModel[3];
extern const AG3DDCmdHeadChunk age3dDCmd[3];
extern const AG3DTreeHeadChunk age3dTree[3];
extern const AG3DMotionHeadChunk age3dMotion[3];
extern const AG3DCameraHeadChunk age3dCamera[2];
extern const s16 ageVGCnt;

#ifdef __cplusplus
}
#endif

#endif /* __AG_EXPORT__ */
