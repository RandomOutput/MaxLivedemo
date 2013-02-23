APP = live
include $(SDK_DIR)/Makefile.defs
OBJS = assets.gen.o main.o
ASSETDEPS += assets.lua *.png *.xm *.raw
include $(SDK_DIR)/Makefile.rules
