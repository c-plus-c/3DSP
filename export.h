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
#define AG_CG_NO1	(20)
#define AG_CG_NO2	(21)
#define AG_CG_NO3	(22)
#define AG_CG_NO4	(23)
#define AG_CG_TOP	(24)
#define AG_CG_RESULTBACK	(25)
#define AG_CG_READY	(26)
#define AG_CG_START	(27)
#define AG_CG_STARTAL	(28)
#define AG_CG_RESULT	(29)
#define AG_CG_HBW	(30)
#define AG_CG_AUTOPILOTNOTICE	(31)
#define AG_CG_PHM14_0185	(32)
#define AG_CG_SKY	(33)
#define AG_CG_BOTTOMCLOUD	(34)
#define AG_CG_S10_32	(35)
#define AG_CG_S10_33	(36)
#define AG_CG_S10_34	(37)
#define AG_CG_S10_35	(38)
#define AG_CG_S10_36	(39)
#define AG_CG_S10_37	(40)
#define AG_CG_S10_38	(41)
#define AG_CG_S10_39	(42)
#define AG_CG_S10_40	(43)
#define AG_CG_S10_41	(44)
#define AG_CG_S10_42	(45)
#define AG_CG_S10_43	(46)
#define AG_CG_S10_44	(47)
#define AG_CG_S10_45	(48)
#define AG_CG_S10_46	(49)
#define AG_CG_S10_47	(50)
#define AG_CG_S10_48	(51)
#define AG_CG_S10_49	(52)
#define AG_CG_S10_50	(53)
#define AG_CG_S10_51	(54)
#define AG_CG_S10_52	(55)
#define AG_CG_S10_53	(56)
#define AG_CG_S10_54	(57)
#define AG_CG_S10_55	(58)
#define AG_CG_S10_56	(59)
#define AG_CG_S10_57	(60)
#define AG_CG_S10_58	(61)
#define AG_CG_S10_59	(62)
#define AG_CG_S10_60	(63)
#define AG_CG_S10_61	(64)
#define AG_CG_S10_62	(65)
#define AG_CG_S10_63	(66)
#define AG_CG_S10_64	(67)
#define AG_CG_S10_65	(68)
#define AG_CG_S10_66	(69)
#define AG_CG_S10_67	(70)
#define AG_CG_S10_68	(71)
#define AG_CG_S10_69	(72)
#define AG_CG_S10_70	(73)
#define AG_CG_S10_71	(74)
#define AG_CG_S10_72	(75)
#define AG_CG_S10_73	(76)
#define AG_CG_S10_74	(77)
#define AG_CG_S10_75	(78)
#define AG_CG_S10_76	(79)
#define AG_CG_S10_77	(80)
#define AG_CG_S10_78	(81)
#define AG_CG_S10_79	(82)
#define AG_CG_S10_80	(83)
#define AG_CG_S10_81	(84)
#define AG_CG_S10_82	(85)
#define AG_CG_S10_83	(86)
#define AG_CG_S10_84	(87)
#define AG_CG_S10_85	(88)
#define AG_CG_S10_86	(89)
#define AG_CG_S10_87	(90)
#define AG_CG_S10_88	(91)
#define AG_CG_S10_89	(92)
#define AG_CG_S10_90	(93)
#define AG_CG_S10_91	(94)
#define AG_CG_S10_92	(95)
#define AG_CG_S10_93	(96)
#define AG_CG_S10_94	(97)
#define AG_CG_S10_95	(98)
#define AG_CG_S10_96	(99)
#define AG_CG_S10_97	(100)
#define AG_CG_S10_98	(101)
#define AG_CG_S10_99	(102)
#define AG_CG_S10_100	(103)
#define AG_CG_S10_101	(104)
#define AG_CG_S10_102	(105)
#define AG_CG_S10_103	(106)
#define AG_CG_S10_104	(107)
#define AG_CG_S10_105	(108)
#define AG_CG_S10_106	(109)
#define AG_CG_S10_107	(110)
#define AG_CG_S10_108	(111)
#define AG_CG_S10_109	(112)
#define AG_CG_S10_110	(113)
#define AG_CG_S10_111	(114)
#define AG_CG_S10_112	(115)
#define AG_CG_S10_113	(116)
#define AG_CG_S10_114	(117)
#define AG_CG_S10_115	(118)
#define AG_CG_S10_116	(119)
#define AG_CG_S10_117	(120)
#define AG_CG_S10_118	(121)
#define AG_CG_S10_119	(122)
#define AG_CG_S10_120	(123)
#define AG_CG_S10_121	(124)
#define AG_CG_S10_122	(125)
#define AG_CG_S10_123	(126)
#define AG_CG_S10_124	(127)
#define AG_CG_S10_125	(128)
#define AG_CG_S10_126	(129)
#define AG_CG_S32_32	(130)
#define AG_CG_S32_33	(131)
#define AG_CG_S32_34	(132)
#define AG_CG_S32_35	(133)
#define AG_CG_S32_36	(134)
#define AG_CG_S32_37	(135)
#define AG_CG_S32_38	(136)
#define AG_CG_S32_39	(137)
#define AG_CG_S32_40	(138)
#define AG_CG_S32_41	(139)
#define AG_CG_S32_42	(140)
#define AG_CG_S32_43	(141)
#define AG_CG_S32_44	(142)
#define AG_CG_S32_45	(143)
#define AG_CG_S32_46	(144)
#define AG_CG_S32_47	(145)
#define AG_CG_S32_48	(146)
#define AG_CG_S32_49	(147)
#define AG_CG_S32_50	(148)
#define AG_CG_S32_51	(149)
#define AG_CG_S32_52	(150)
#define AG_CG_S32_53	(151)
#define AG_CG_S32_54	(152)
#define AG_CG_S32_55	(153)
#define AG_CG_S32_56	(154)
#define AG_CG_S32_57	(155)
#define AG_CG_S32_58	(156)
#define AG_CG_S32_59	(157)
#define AG_CG_S32_60	(158)
#define AG_CG_S32_61	(159)
#define AG_CG_S32_62	(160)
#define AG_CG_S32_63	(161)
#define AG_CG_S32_64	(162)
#define AG_CG_S32_65	(163)
#define AG_CG_S32_66	(164)
#define AG_CG_S32_67	(165)
#define AG_CG_S32_68	(166)
#define AG_CG_S32_69	(167)
#define AG_CG_S32_70	(168)
#define AG_CG_S32_71	(169)
#define AG_CG_S32_72	(170)
#define AG_CG_S32_73	(171)
#define AG_CG_S32_74	(172)
#define AG_CG_S32_75	(173)
#define AG_CG_S32_76	(174)
#define AG_CG_S32_77	(175)
#define AG_CG_S32_78	(176)
#define AG_CG_S32_79	(177)
#define AG_CG_S32_80	(178)
#define AG_CG_S32_81	(179)
#define AG_CG_S32_82	(180)
#define AG_CG_S32_83	(181)
#define AG_CG_S32_84	(182)
#define AG_CG_S32_85	(183)
#define AG_CG_S32_86	(184)
#define AG_CG_S32_87	(185)
#define AG_CG_S32_88	(186)
#define AG_CG_S32_89	(187)
#define AG_CG_S32_90	(188)
#define AG_CG_S32_91	(189)
#define AG_CG_S32_92	(190)
#define AG_CG_S32_93	(191)
#define AG_CG_S32_94	(192)
#define AG_CG_S32_95	(193)
#define AG_CG_S32_96	(194)
#define AG_CG_S32_97	(195)
#define AG_CG_S32_98	(196)
#define AG_CG_S32_99	(197)
#define AG_CG_S32_100	(198)
#define AG_CG_S32_101	(199)
#define AG_CG_S32_102	(200)
#define AG_CG_S32_103	(201)
#define AG_CG_S32_104	(202)
#define AG_CG_S32_105	(203)
#define AG_CG_S32_106	(204)
#define AG_CG_S32_107	(205)
#define AG_CG_S32_108	(206)
#define AG_CG_S32_109	(207)
#define AG_CG_S32_110	(208)
#define AG_CG_S32_111	(209)
#define AG_CG_S32_112	(210)
#define AG_CG_S32_113	(211)
#define AG_CG_S32_114	(212)
#define AG_CG_S32_115	(213)
#define AG_CG_S32_116	(214)
#define AG_CG_S32_117	(215)
#define AG_CG_S32_118	(216)
#define AG_CG_S32_119	(217)
#define AG_CG_S32_120	(218)
#define AG_CG_S32_121	(219)
#define AG_CG_S32_122	(220)
#define AG_CG_S32_123	(221)
#define AG_CG_S32_124	(222)
#define AG_CG_S32_125	(223)
#define AG_CG_S32_126	(224)

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
#define AG_AG3D_CUBEMODEL	(7)
#define AG_AG3D_SKYSPHEREMODEL	(8)
#define AG_AG3D_BOTTOMCLOUDMODEL	(9)

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
#define AG_AG3D_CUBETREE	(7)
#define AG_AG3D_SKYSPHERETREE	(8)
#define AG_AG3D_BOTTOMCLOUDTREE	(9)

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
#define AG_AG3D_CUBEMOTION	(7)
#define AG_AG3D_SKYSPHEREMOTION	(8)
#define AG_AG3D_BOTTOMCLOUDMOTION	(9)

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
extern const AGERomMember ageRM[225];
extern const AGERM3Member ageRM3[1];
extern const u32 ageReserve[1];
extern const u32 ageUser[1];
extern const AG3DModelHeadChunk age3dModel[10];
extern const AG3DDCmdHeadChunk age3dDCmd[10];
extern const AG3DTreeHeadChunk age3dTree[10];
extern const AG3DMotionHeadChunk age3dMotion[10];
extern const AG3DCameraHeadChunk age3dCamera[1];
extern const s16 ageVGCnt;
extern const AGESoundRomMember ageSRM[10];

#ifdef __cplusplus
}
#endif

#endif /* __AG_EXPORT__ */
