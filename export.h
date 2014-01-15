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
#define AG_CG_MAINWING_EDGED	(0)
#define AG_CG_NEWBODY	(1)
#define AG_CG_CANNON	(2)
#define AG_CG_VERTICAL_EDGE	(3)
#define AG_CG_HORIZON_EDGE	(4)
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
#define AG_CG_65	(38)
#define AG_CG_66	(39)
#define AG_CG_67	(40)
#define AG_CG_68	(41)
#define AG_CG_69	(42)
#define AG_CG_70	(43)
#define AG_CG_71	(44)
#define AG_CG_72	(45)
#define AG_CG_73	(46)
#define AG_CG_74	(47)
#define AG_CG_75	(48)
#define AG_CG_76	(49)
#define AG_CG_77	(50)
#define AG_CG_78	(51)
#define AG_CG_79	(52)
#define AG_CG_80	(53)
#define AG_CG_81	(54)
#define AG_CG_82	(55)
#define AG_CG_83	(56)
#define AG_CG_84	(57)
#define AG_CG_85	(58)
#define AG_CG_86	(59)
#define AG_CG_87	(60)
#define AG_CG_88	(61)
#define AG_CG_89	(62)
#define AG_CG_90	(63)
#define AG_CG_91	(64)
#define AG_CG_92	(65)
#define AG_CG_93	(66)
#define AG_CG_94	(67)
#define AG_CG_95	(68)
#define AG_CG_96	(69)
#define AG_CG_97	(70)
#define AG_CG_98	(71)
#define AG_CG_99	(72)
#define AG_CG_100	(73)
#define AG_CG_101	(74)
#define AG_CG_102	(75)
#define AG_CG_103	(76)
#define AG_CG_104	(77)
#define AG_CG_105	(78)
#define AG_CG_106	(79)
#define AG_CG_107	(80)
#define AG_CG_108	(81)
#define AG_CG_109	(82)
#define AG_CG_110	(83)
#define AG_CG_111	(84)
#define AG_CG_112	(85)
#define AG_CG_113	(86)
#define AG_CG_114	(87)
#define AG_CG_115	(88)
#define AG_CG_116	(89)
#define AG_CG_117	(90)
#define AG_CG_118	(91)
#define AG_CG_119	(92)
#define AG_CG_120	(93)
#define AG_CG_121	(94)
#define AG_CG_122	(95)
#define AG_CG_123	(96)
#define AG_CG_124	(97)
#define AG_CG_125	(98)
#define AG_CG_126	(99)
#define AG_CG_BLACK	(100)
#define AG_CG_SKYSPHERE	(101)
#define AG_CG_NEWBODY_2	(102)
#define AG_CG_NEWBODY_3	(103)
#define AG_CG_NEWBODY_4	(104)
#define AG_CG_RADAR	(105)
#define AG_CG_RED_ICON	(106)
#define AG_CG_BLUE_ICON	(107)
#define AG_CG_YELLOW_ICON	(108)
#define AG_CG_WHITE_ICON	(109)

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
#define AG_AG3D_SKYBACKMODEL	(3)
#define AG_AG3D_NEWPLANE1MODEL	(4)
#define AG_AG3D_NEWPLANE2MODEL	(5)
#define AG_AG3D_NEWPLANE3MODEL	(6)
#define AG_AG3D_NEWPLANE4MODEL	(7)

/***************************************************************/
/*                        AG3D Tree Symbol                     */
/***************************************************************/
#define AG_AG3D_AG3DEXPORTTREE	(0)
#define AG_AG3D_PLANETREE	(1)
#define AG_AG3D_BULLETTREE	(2)
#define AG_AG3D_SKYBACKTREE	(3)
#define AG_AG3D_NEWPLANE1TREE	(4)
#define AG_AG3D_NEWPLANE2TREE	(5)
#define AG_AG3D_NEWPLANE3TREE	(6)
#define AG_AG3D_NEWPLANE4TREE	(7)

/***************************************************************/
/*                       AG3D Motion Symbol                    */
/***************************************************************/
#define AG_AG3D_AG3DEXPORTMOTION	(0)
#define AG_AG3D_PLANEMOTION	(1)
#define AG_AG3D_BULLETMOTION	(2)
#define AG_AG3D_SKYBACKMOTION	(3)
#define AG_AG3D_NEWPLANE1MOTION	(4)
#define AG_AG3D_NEWPLANE2MOTION	(5)
#define AG_AG3D_NEWPLANE3MOTION	(6)
#define AG_AG3D_NEWPLANE4MOTION	(7)

/***************************************************************/
/*                        AG3D Camera Symbol                   */
/***************************************************************/
#define AG_AG3D_AG3DEXPORTPERSP	(0)

/***************************************************************/
/*                          Data Member                        */
/***************************************************************/
extern const AGERomMember ageRM[110];
extern const AGERM3Member ageRM3[1];
extern const u32 ageReserve[1];
extern const u32 ageUser[1];
extern const AG3DModelHeadChunk age3dModel[8];
extern const AG3DDCmdHeadChunk age3dDCmd[8];
extern const AG3DTreeHeadChunk age3dTree[8];
extern const AG3DMotionHeadChunk age3dMotion[8];
extern const AG3DCameraHeadChunk age3dCamera[1];
extern const s16 ageVGCnt;

#ifdef __cplusplus
}
#endif

#endif /* __AG_EXPORT__ */
