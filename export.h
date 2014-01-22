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
#define AG_CG_BLACK	(6)
#define AG_CG_NEWBODY_2	(7)
#define AG_CG_NEWBODY_3	(8)
#define AG_CG_NEWBODY_4	(9)
#define AG_CG_RED	(10)
#define AG_CG_WALL	(11)
#define AG_CG_RADAR	(12)
#define AG_CG_RED_ICON	(13)
#define AG_CG_BLUE_ICON	(14)
#define AG_CG_YELLOW_ICON	(15)
#define AG_CG_WHITE_ICON	(16)
#define AG_CG_HORMINGBULLETICON	(17)
#define AG_CG_1ST	(18)
#define AG_CG_2ND	(19)
#define AG_CG_3RD	(20)
#define AG_CG_4TH	(21)
#define AG_CG_B1	(22)
#define AG_CG_B2	(23)
#define AG_CG_B3	(24)
#define AG_CG_B4	(25)
#define AG_CG_B5	(26)
#define AG_CG_B6	(27)
#define AG_CG_B7	(28)
#define AG_CG_B8	(29)
#define AG_CG_B9	(30)
#define AG_CG_B10	(31)
#define AG_CG_BULLETENEGYDISPLAY	(32)
#define AG_CG_BULLETENEGYBAR	(33)
#define AG_CG_NO1	(34)
#define AG_CG_NO2	(35)
#define AG_CG_NO3	(36)
#define AG_CG_NO4	(37)
#define AG_CG_READY	(38)
#define AG_CG_START	(39)
#define AG_CG_RESULT	(40)
#define AG_CG_STARTAL	(41)
#define AG_CG_TOP	(42)
#define AG_CG_32	(43)
#define AG_CG_33	(44)
#define AG_CG_34	(45)
#define AG_CG_35	(46)
#define AG_CG_36	(47)
#define AG_CG_37	(48)
#define AG_CG_38	(49)
#define AG_CG_39	(50)
#define AG_CG_40	(51)
#define AG_CG_41	(52)
#define AG_CG_42	(53)
#define AG_CG_43	(54)
#define AG_CG_44	(55)
#define AG_CG_45	(56)
#define AG_CG_46	(57)
#define AG_CG_47	(58)
#define AG_CG_48	(59)
#define AG_CG_49	(60)
#define AG_CG_50	(61)
#define AG_CG_51	(62)
#define AG_CG_52	(63)
#define AG_CG_53	(64)
#define AG_CG_54	(65)
#define AG_CG_55	(66)
#define AG_CG_56	(67)
#define AG_CG_57	(68)
#define AG_CG_58	(69)
#define AG_CG_59	(70)
#define AG_CG_60	(71)
#define AG_CG_61	(72)
#define AG_CG_62	(73)
#define AG_CG_63	(74)
#define AG_CG_64	(75)
#define AG_CG_65	(76)
#define AG_CG_66	(77)
#define AG_CG_67	(78)
#define AG_CG_68	(79)
#define AG_CG_69	(80)
#define AG_CG_70	(81)
#define AG_CG_71	(82)
#define AG_CG_72	(83)
#define AG_CG_73	(84)
#define AG_CG_74	(85)
#define AG_CG_75	(86)
#define AG_CG_76	(87)
#define AG_CG_77	(88)
#define AG_CG_78	(89)
#define AG_CG_79	(90)
#define AG_CG_80	(91)
#define AG_CG_81	(92)
#define AG_CG_82	(93)
#define AG_CG_83	(94)
#define AG_CG_84	(95)
#define AG_CG_85	(96)
#define AG_CG_86	(97)
#define AG_CG_87	(98)
#define AG_CG_88	(99)
#define AG_CG_89	(100)
#define AG_CG_90	(101)
#define AG_CG_91	(102)
#define AG_CG_92	(103)
#define AG_CG_93	(104)
#define AG_CG_94	(105)
#define AG_CG_95	(106)
#define AG_CG_96	(107)
#define AG_CG_97	(108)
#define AG_CG_98	(109)
#define AG_CG_99	(110)
#define AG_CG_100	(111)
#define AG_CG_101	(112)
#define AG_CG_102	(113)
#define AG_CG_103	(114)
#define AG_CG_104	(115)
#define AG_CG_105	(116)
#define AG_CG_106	(117)
#define AG_CG_107	(118)
#define AG_CG_108	(119)
#define AG_CG_109	(120)
#define AG_CG_110	(121)
#define AG_CG_111	(122)
#define AG_CG_112	(123)
#define AG_CG_113	(124)
#define AG_CG_114	(125)
#define AG_CG_115	(126)
#define AG_CG_116	(127)
#define AG_CG_117	(128)
#define AG_CG_118	(129)
#define AG_CG_119	(130)
#define AG_CG_120	(131)
#define AG_CG_121	(132)
#define AG_CG_122	(133)
#define AG_CG_123	(134)
#define AG_CG_124	(135)
#define AG_CG_125	(136)
#define AG_CG_126	(137)

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
#define AG_AG3D_NEWPLANE1MODEL	(3)
#define AG_AG3D_NEWPLANE2MODEL	(4)
#define AG_AG3D_NEWPLANE3MODEL	(5)
#define AG_AG3D_NEWPLANE4MODEL	(6)
#define AG_AG3D_HORMINGBULLETMODEL	(7)
#define AG_AG3D_SKYBACKMODEL	(8)

/***************************************************************/
/*                        AG3D Tree Symbol                     */
/***************************************************************/
#define AG_AG3D_AG3DEXPORTTREE	(0)
#define AG_AG3D_PLANETREE	(1)
#define AG_AG3D_BULLETTREE	(2)
#define AG_AG3D_NEWPLANE1TREE	(3)
#define AG_AG3D_NEWPLANE2TREE	(4)
#define AG_AG3D_NEWPLANE3TREE	(5)
#define AG_AG3D_NEWPLANE4TREE	(6)
#define AG_AG3D_HORMINGBULLETTREE	(7)
#define AG_AG3D_SKYBACKTREE	(8)

/***************************************************************/
/*                       AG3D Motion Symbol                    */
/***************************************************************/
#define AG_AG3D_AG3DEXPORTMOTION	(0)
#define AG_AG3D_PLANEMOTION	(1)
#define AG_AG3D_BULLETMOTION	(2)
#define AG_AG3D_NEWPLANE1MOTION	(3)
#define AG_AG3D_NEWPLANE2MOTION	(4)
#define AG_AG3D_NEWPLANE3MOTION	(5)
#define AG_AG3D_NEWPLANE4MOTION	(6)
#define AG_AG3D_HORMINGBULLETMOTION	(7)
#define AG_AG3D_SKYBACKMOTION	(8)

/***************************************************************/
/*                        AG3D Camera Symbol                   */
/***************************************************************/
#define AG_AG3D_AG3DEXPORTPERSP	(0)

/***************************************************************/
/*                          Data Member                        */
/***************************************************************/
extern const AGERomMember ageRM[138];
extern const AGERM3Member ageRM3[1];
extern const u32 ageReserve[1];
extern const u32 ageUser[1];
extern const AG3DModelHeadChunk age3dModel[9];
extern const AG3DDCmdHeadChunk age3dDCmd[9];
extern const AG3DTreeHeadChunk age3dTree[9];
extern const AG3DMotionHeadChunk age3dMotion[9];
extern const AG3DCameraHeadChunk age3dCamera[1];
extern const s16 ageVGCnt;

#ifdef __cplusplus
}
#endif

#endif /* __AG_EXPORT__ */
