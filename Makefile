##
##   Makefile for sample
##

LIB3D = 1

# ソースファイル
C_SRC = main.c export.c pad.c fireball.c player.c pad.c

# CGROM ディレクトリ
CGROMDIR = ./

# 現在のディレクトリからランタイムルートディレクトリへの相対パス
ROOTDIR = ../

include $(ROOTDIR)/include/makefile.def

## Makefile ends here.
