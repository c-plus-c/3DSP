##
##   Makefile for sample
##

LIB3D = 1

# �\�[�X�t�@�C��
C_SRC = main.c export.c pad.c fireball.c player.c pad.c plane.c draw_utils.c backsky.c

# CGROM �f�B���N�g��
CGROMDIR = ./

# ���݂̃f�B���N�g�����烉���^�C�����[�g�f�B���N�g���ւ̑��΃p�X
ROOTDIR = ../../..

# �ǉ��̃��C�u����
EXTRA_LIBS = $(ROOTDIR)/library/agGamePad$(LIBPOSTFIX).lib

include $(ROOTDIR)/include/makefile.def

## Makefile ends here.
