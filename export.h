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
#define AG_CG_NO1_HALF	(24)
#define AG_CG_NO2_HALF	(25)
#define AG_CG_NO3_HALF	(26)
#define AG_CG_NO4_HALF	(27)
#define AG_CG_NO1_MINI	(28)
#define AG_CG_NO2_MINI	(29)
#define AG_CG_NO3_MINI	(30)
#define AG_CG_NO4_MINI	(31)
#define AG_CG_TOP	(32)
#define AG_CG_MANUAL	(33)
#define AG_CG_RESULTBACK	(34)
#define AG_CG_RESULT	(35)
#define AG_CG_READY	(36)
#define AG_CG_START	(37)
#define AG_CG_STARTAL	(38)
#define AG_CG_HBW	(39)
#define AG_CG_AUTOPILOTNOTICE	(40)
#define AG_CG_PLANE_SIDE_50	(41)
#define AG_CG_PLANE_SIDE_70	(42)
#define AG_CG_PHM14_0185	(43)
#define AG_CG_SKY	(44)
#define AG_CG_BOTTOMCLOUD	(45)
#define AG_CG_S10_32	(46)
#define AG_CG_S10_33	(47)
#define AG_CG_S10_34	(48)
#define AG_CG_S10_35	(49)
#define AG_CG_S10_36	(50)
#define AG_CG_S10_37	(51)
#define AG_CG_S10_38	(52)
#define AG_CG_S10_39	(53)
#define AG_CG_S10_40	(54)
#define AG_CG_S10_41	(55)
#define AG_CG_S10_42	(56)
#define AG_CG_S10_43	(57)
#define AG_CG_S10_44	(58)
#define AG_CG_S10_45	(59)
#define AG_CG_S10_46	(60)
#define AG_CG_S10_47	(61)
#define AG_CG_S10_48	(62)
#define AG_CG_S10_49	(63)
#define AG_CG_S10_50	(64)
#define AG_CG_S10_51	(65)
#define AG_CG_S10_52	(66)
#define AG_CG_S10_53	(67)
#define AG_CG_S10_54	(68)
#define AG_CG_S10_55	(69)
#define AG_CG_S10_56	(70)
#define AG_CG_S10_57	(71)
#define AG_CG_S10_58	(72)
#define AG_CG_S10_59	(73)
#define AG_CG_S10_60	(74)
#define AG_CG_S10_61	(75)
#define AG_CG_S10_62	(76)
#define AG_CG_S10_63	(77)
#define AG_CG_S10_64	(78)
#define AG_CG_S10_65	(79)
#define AG_CG_S10_66	(80)
#define AG_CG_S10_67	(81)
#define AG_CG_S10_68	(82)
#define AG_CG_S10_69	(83)
#define AG_CG_S10_70	(84)
#define AG_CG_S10_71	(85)
#define AG_CG_S10_72	(86)
#define AG_CG_S10_73	(87)
#define AG_CG_S10_74	(88)
#define AG_CG_S10_75	(89)
#define AG_CG_S10_76	(90)
#define AG_CG_S10_77	(91)
#define AG_CG_S10_78	(92)
#define AG_CG_S10_79	(93)
#define AG_CG_S10_80	(94)
#define AG_CG_S10_81	(95)
#define AG_CG_S10_82	(96)
#define AG_CG_S10_83	(97)
#define AG_CG_S10_84	(98)
#define AG_CG_S10_85	(99)
#define AG_CG_S10_86	(100)
#define AG_CG_S10_87	(101)
#define AG_CG_S10_88	(102)
#define AG_CG_S10_89	(103)
#define AG_CG_S10_90	(104)
#define AG_CG_S10_91	(105)
#define AG_CG_S10_92	(106)
#define AG_CG_S10_93	(107)
#define AG_CG_S10_94	(108)
#define AG_CG_S10_95	(109)
#define AG_CG_S10_96	(110)
#define AG_CG_S10_97	(111)
#define AG_CG_S10_98	(112)
#define AG_CG_S10_99	(113)
#define AG_CG_S10_100	(114)
#define AG_CG_S10_101	(115)
#define AG_CG_S10_102	(116)
#define AG_CG_S10_103	(117)
#define AG_CG_S10_104	(118)
#define AG_CG_S10_105	(119)
#define AG_CG_S10_106	(120)
#define AG_CG_S10_107	(121)
#define AG_CG_S10_108	(122)
#define AG_CG_S10_109	(123)
#define AG_CG_S10_110	(124)
#define AG_CG_S10_111	(125)
#define AG_CG_S10_112	(126)
#define AG_CG_S10_113	(127)
#define AG_CG_S10_114	(128)
#define AG_CG_S10_115	(129)
#define AG_CG_S10_116	(130)
#define AG_CG_S10_117	(131)
#define AG_CG_S10_118	(132)
#define AG_CG_S10_119	(133)
#define AG_CG_S10_120	(134)
#define AG_CG_S10_121	(135)
#define AG_CG_S10_122	(136)
#define AG_CG_S10_123	(137)
#define AG_CG_S10_124	(138)
#define AG_CG_S10_125	(139)
#define AG_CG_S10_126	(140)
#define AG_CG_S32_32	(141)
#define AG_CG_S32_33	(142)
#define AG_CG_S32_34	(143)
#define AG_CG_S32_35	(144)
#define AG_CG_S32_36	(145)
#define AG_CG_S32_37	(146)
#define AG_CG_S32_38	(147)
#define AG_CG_S32_39	(148)
#define AG_CG_S32_40	(149)
#define AG_CG_S32_41	(150)
#define AG_CG_S32_42	(151)
#define AG_CG_S32_43	(152)
#define AG_CG_S32_44	(153)
#define AG_CG_S32_45	(154)
#define AG_CG_S32_46	(155)
#define AG_CG_S32_47	(156)
#define AG_CG_S32_48	(157)
#define AG_CG_S32_49	(158)
#define AG_CG_S32_50	(159)
#define AG_CG_S32_51	(160)
#define AG_CG_S32_52	(161)
#define AG_CG_S32_53	(162)
#define AG_CG_S32_54	(163)
#define AG_CG_S32_55	(164)
#define AG_CG_S32_56	(165)
#define AG_CG_S32_57	(166)
#define AG_CG_S32_58	(167)
#define AG_CG_S32_59	(168)
#define AG_CG_S32_60	(169)
#define AG_CG_S32_61	(170)
#define AG_CG_S32_62	(171)
#define AG_CG_S32_63	(172)
#define AG_CG_S32_64	(173)
#define AG_CG_S32_65	(174)
#define AG_CG_S32_66	(175)
#define AG_CG_S32_67	(176)
#define AG_CG_S32_68	(177)
#define AG_CG_S32_69	(178)
#define AG_CG_S32_70	(179)
#define AG_CG_S32_71	(180)
#define AG_CG_S32_72	(181)
#define AG_CG_S32_73	(182)
#define AG_CG_S32_74	(183)
#define AG_CG_S32_75	(184)
#define AG_CG_S32_76	(185)
#define AG_CG_S32_77	(186)
#define AG_CG_S32_78	(187)
#define AG_CG_S32_79	(188)
#define AG_CG_S32_80	(189)
#define AG_CG_S32_81	(190)
#define AG_CG_S32_82	(191)
#define AG_CG_S32_83	(192)
#define AG_CG_S32_84	(193)
#define AG_CG_S32_85	(194)
#define AG_CG_S32_86	(195)
#define AG_CG_S32_87	(196)
#define AG_CG_S32_88	(197)
#define AG_CG_S32_89	(198)
#define AG_CG_S32_90	(199)
#define AG_CG_S32_91	(200)
#define AG_CG_S32_92	(201)
#define AG_CG_S32_93	(202)
#define AG_CG_S32_94	(203)
#define AG_CG_S32_95	(204)
#define AG_CG_S32_96	(205)
#define AG_CG_S32_97	(206)
#define AG_CG_S32_98	(207)
#define AG_CG_S32_99	(208)
#define AG_CG_S32_100	(209)
#define AG_CG_S32_101	(210)
#define AG_CG_S32_102	(211)
#define AG_CG_S32_103	(212)
#define AG_CG_S32_104	(213)
#define AG_CG_S32_105	(214)
#define AG_CG_S32_106	(215)
#define AG_CG_S32_107	(216)
#define AG_CG_S32_108	(217)
#define AG_CG_S32_109	(218)
#define AG_CG_S32_110	(219)
#define AG_CG_S32_111	(220)
#define AG_CG_S32_112	(221)
#define AG_CG_S32_113	(222)
#define AG_CG_S32_114	(223)
#define AG_CG_S32_115	(224)
#define AG_CG_S32_116	(225)
#define AG_CG_S32_117	(226)
#define AG_CG_S32_118	(227)
#define AG_CG_S32_119	(228)
#define AG_CG_S32_120	(229)
#define AG_CG_S32_121	(230)
#define AG_CG_S32_122	(231)
#define AG_CG_S32_123	(232)
#define AG_CG_S32_124	(233)
#define AG_CG_S32_125	(234)
#define AG_CG_S32_126	(235)

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
extern const AGERomMember ageRM[236];
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
