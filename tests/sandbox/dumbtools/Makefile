INCLUDES += -I$(abspath ./)
DEFINES  +=
override CFLAGS += $(INCLUDES) $(DEFINES)
BUILD_DIR   = ./build
DISTRIB_DIR = ./dist
INC_DIR     = $(DISTRIB_DIR)/inc

.PHONY: all clean

all: dumbtools

dumbtools:
	@echo $@

clean:
	@rm -rf build
