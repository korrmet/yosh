INCLUDES += -I$(abspath ./)
INCLUDES += -I$(abspath ./containers/)
DEFINES  +=
override CFLAGS += $(INCLUDES) $(DEFINES)
BUILD_DIR   = ./build

.PHONY: clean

all: sandbox

sandbox: libs/yosh/libyosh.a \
	       libs/dumbtools/libdumbtools.a
	@echo $@

libs/yosh/libyosh.a:
	@make -C ../../ BUILD_DIR=$(abspath $(BUILD_DIR)) \
		              DISTRIB_DIR=$(abspath $(dir $@)) \
									INC_DIR=$(abspath ./libs/containers) \
									CFLAGS=$(CFLAGS)

libs/dumbtools/libdumbtools.a:
	@make -C dumbtools/ BUILD_DIR=$(abspath $(BUILD_DIR)) \
		                  DISTRIB_DIR=$(abspath $(dir $@)) \
											CFLAGS=$(CFLAGS)

clean:
	@rm -rf build libs
