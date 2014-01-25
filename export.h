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
#define AGE_SOUND_ROM_OFFSET	(0x40000)

/***************************************************************/
/*                    Rom Member Symbol                        */
/***************************************************************/
#define AG_CG_MAINWING_EDGED	(0)
#define AG_CG_NEWBODY	(1)
#define AG_CG_CANNON	(2)
#define AG_CG_VERTICAL_EDGE	(3)
#define AG_CG_HORIZON_EDGE	(4)
#define AG_CG_BLACK	(5)
#define AG_CG_NEWBODY_2	(6)
#define AG_CG_NEWBODY_3	(7)
#define AG_CG_NEWBODY_4	(8)
#define AG_CG_RED	(9)
#define AG_CG_RADAR	(10)
#define AG_CG_RED_ICON	(11)
#define AG_CG_BLUE_ICON	(12)
#define AG_CG_YELLOW_ICON	(13)
#define AG_CG_WHITE_ICON	(14)
#define AG_CG_HORMINGBULLETICON	(15)
#define AG_CG_1ST	(16)
#define AG_CG_2ND	(17)
#define AG_CG_3RD	(18)
#define AG_CG_4TH	(19)
#define AG_CG_B1	(20)
#define AG_CG_B2	(21)
#define AG_CG_B3	(22)
#define AG_CG_B4	(23)
#define AG_CG_B5	(24)
#define AG_CG_B6	(25)
#define AG_CG_B7	(26)
#define AG_CG_B8	(27)
#define AG_CG_B9	(28)
#define AG_CG_B10	(29)
#define AG_CG_BULLETENEGYDISPLAY	(30)
#define AG_CG_BULLETENEGYBAR	(31)
#define AG_CG_NO1	(32)
#define AG_CG_NO2	(33)
#define AG_CG_NO3	(34)
#define AG_CG_NO4	(35)
#define AG_CG_READY	(36)
#define AG_CG_START	(37)
#define AG_CG_RESULT	(38)
#define AG_CG_STARTAL	(39)
#define AG_CG_TOP	(40)
#define AG_CG_32	(41)
#define AG_CG_33	(42)
#define AG_CG_34	(43)
#define AG_CG_35	(44)
#define AG_CG_36	(45)
#define AG_CG_37	(46)
#define AG_CG_38	(47)
#define AG_CG_39	(48)
#define AG_CG_40	(49)
#define AG_CG_41	(50)
#define AG_CG_42	(51)
#define AG_CG_43	(52)
#define AG_CG_44	(53)
#define AG_CG_45	(54)
#define AG_CG_46	(55)
#define AG_CG_47	(56)
#define AG_CG_48	(57)
#define AG_CG_49	(58)
#define AG_CG_50	(59)
#define AG_CG_51	(60)
#define AG_CG_52	(61)
#define AG_CG_53	(62)
#define AG_CG_54	(63)
#define AG_CG_55	(64)
#define AG_CG_56	(65)
#define AG_CG_57	(66)
#define AG_CG_58	(67)
#define AG_CG_59	(68)
#define AG_CG_60	(69)
#define AG_CG_61	(70)
#define AG_CG_62	(71)
#define AG_CG_63	(72)
#define AG_CG_64	(73)
#define AG_CG_65	(74)
#define AG_CG_66	(75)
#define AG_CG_67	(76)
#define AG_CG_68	(77)
#define AG_CG_69	(78)
#define AG_CG_70	(79)
#define AG_CG_71	(80)
#define AG_CG_72	(81)
#define AG_CG_73	(82)
#define AG_CG_74	(83)
#define AG_CG_75	(84)
#define AG_CG_76	(85)
#define AG_CG_77	(86)
#define AG_CG_78	(87)
#define AG_CG_79	(88)
#define AG_CG_80	(89)
#define AG_CG_81	(90)
#define AG_CG_82	(91)
#define AG_CG_83	(92)
#define AG_CG_84	(93)
#define AG_CG_85	(94)
#define AG_CG_86	(95)
#define AG_CG_87	(96)
#define AG_CG_88	(97)
#define AG_CG_89	(98)
#define AG_CG_90	(99)
#define AG_CG_91	(100)
#define AG_CG_92	(101)
#define AG_CG_93	(102)
#define AG_CG_94	(103)
#define AG_CG_95	(104)
#define AG_CG_96	(105)
#define AG_CG_97	(106)
#define AG_CG_98	(107)
#define AG_CG_99	(108)
#define AG_CG_100	(109)
#define AG_CG_101	(110)
#define AG_CG_102	(111)
#define AG_CG_103	(112)
#define AG_CG_104	(113)
#define AG_CG_105	(114)
#define AG_CG_106	(115)
#define AG_CG_107	(116)
#define AG_CG_108	(117)
#define AG_CG_109	(118)
#define AG_CG_110	(119)
#define AG_CG_111	(120)
#define AG_CG_112	(121)
#define AG_CG_113	(122)
#define AG_CG_114	(123)
#define AG_CG_115	(124)
#define AG_CG_116	(125)
#define AG_CG_117	(126)
#define AG_CG_118	(127)
#define AG_CG_119	(128)
#define AG_CG_120	(129)
#define AG_CG_121	(130)
#define AG_CG_122	(131)
#define AG_CG_123	(132)
#define AG_CG_124	(133)
#define AG_CG_125	(134)
#define AG_CG_126	(135)
#define AG_CG_CLOUD01	(136)
#define AG_CG_CLOUD02	(137)
#define AG_CG_CLOUD03	(138)
#define AG_CG_CLOUD04	(139)
#define AG_CG_CELL	(140)
#define AG_CG_BOTTOMCLOUD	(141)
#define AG_CG_HBW	(142)

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
#define AG_AG3D_BULLETMODEL	(1)
#define AG_AG3D_NEWPLANE1MODEL	(2)
#define AG_AG3D_NEWPLANE2MODEL	(3)
#define AG_AG3D_NEWPLANE3MODEL	(4)
#define AG_AG3D_NEWPLANE4MODEL	(5)
#define AG_AG3D_HORMINGBULLETMODEL	(6)
#define AG_AG3D_CLOUD1MODEL	(7)
#define AG_AG3D_CLOUD2MODEL	(8)
#define AG_AG3D_CLOUD3MODEL	(9)
#define AG_AG3D_CLOUD4MODEL	(10)
#define AG_AG3D_SKYBACKMODEL	(11)
#define AG_AG3D_BOTTOMCLOUDMODEL	(12)

/***************************************************************/
/*                        AG3D Tree Symbol                     */
/***************************************************************/
#define AG_AG3D_AG3DEXPORTTREE	(0)
#define AG_AG3D_BULLETTREE	(1)
#define AG_AG3D_NEWPLANE1TREE	(2)
#define AG_AG3D_NEWPLANE2TREE	(3)
#define AG_AG3D_NEWPLANE3TREE	(4)
#define AG_AG3D_NEWPLANE4TREE	(5)
#define AG_AG3D_HORMINGBULLETTREE	(6)
#define AG_AG3D_CLOUD1TREE	(7)
#define AG_AG3D_CLOUD2TREE	(8)
#define AG_AG3D_CLOUD3TREE	(9)
#define AG_AG3D_CLOUD4TREE	(10)
#define AG_AG3D_SKYBACKTREE	(11)
#define AG_AG3D_BOTTOMCLOUDTREE	(12)

/***************************************************************/
/*                       AG3D Motion Symbol                    */
/***************************************************************/
#define AG_AG3D_AG3DEXPORTMOTION	(0)
#define AG_AG3D_BULLETMOTION	(1)
#define AG_AG3D_NEWPLANE1MOTION	(2)
#define AG_AG3D_NEWPLANE2MOTION	(3)
#define AG_AG3D_NEWPLANE3MOTION	(4)
#define AG_AG3D_NEWPLANE4MOTION	(5)
#define AG_AG3D_HORMINGBULLETMOTION	(6)
#define AG_AG3D_CLOUD1MOTION	(7)
#define AG_AG3D_CLOUD2MOTION	(8)
#define AG_AG3D_CLOUD3MOTION	(9)
#define AG_AG3D_CLOUD4MOTION	(10)
#define AG_AG3D_SKYBACKMOTION	(11)
#define AG_AG3D_BOTTOMCLOUDMOTION	(12)

/***************************************************************/
/*                        AG3D Camera Symbol                   */
/***************************************************************/
#define AG_AG3D_AG3DEXPORTPERSP	(0)

/***************************************************************/
/*                       Sound Member Symbol                   */
/***************************************************************/
#define AS_SND_INGAME	(0)
#define AS_SND_RESULT	(1)
#define AS_SND_TITLE	(2)
#define AS_SND_DIE	(3)
#define AS_SND_HSHOT	(4)
#define AS_SND_SELECT	(5)
#define AS_SND_SHOT	(6)
#define AS_SND_WARNING	(7)
#define AS_SND_HIT	(8)
#define AS_SND_IN	(9)

/***************************************************************/
/*                          Data Member                        */
/***************************************************************/
extern const AGERomMember ageRM[143];
extern const AGERM3Member ageRM3[1];
extern const u32 ageReserve[1];
extern const u32 ageUser[1];
extern const AG3DModelHeadChunk age3dModel[13];
extern const AG3DDCmdHeadChunk age3dDCmd[13];
extern const AG3DTreeHeadChunk age3dTree[13];
extern const AG3DMotionHeadChunk age3dMotion[13];
extern const AG3DCameraHeadChunk age3dCamera[1];
extern const s16 ageVGCnt;
extern const AGESoundRomMember ageSRM[10];

#ifdef __cplusplus
}
#endif

#endif /* __AG_EXPORT__ */
