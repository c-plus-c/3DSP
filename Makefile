##
##   Makefile for sample
##

LIB3D = 1

# ソースファイル
C_SRC = main.c export.c pad.c fireball.c player.c pad.c plane.c draw_utils.c backsky.c

# CGROM ディレクトリ
CGROMDIR = ./

# 現在のディレクトリからランタイムルートディレクトリへの相対パス
ROOTDIR = ../../..

# 追加のライブラリ
EXTRA_LIBS = $(ROOTDIR)/library/agGamePad$(LIBPOSTFIX).lib

include $(ROOTDIR)/include/makefile.def

## Makefile ends here.
