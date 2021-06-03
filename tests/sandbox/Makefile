INCLUDES += -I$(abspath ./)
INCLUDES += -I$(abspath ./libs/yosh/inc)
INCLUDES += -I$(abspath ./libs/yosh/inc/containers)
INCLUDES += -I$(abspath ./libs/dumbtools/inc)
DEFINES  +=
LIBS     += -Llibs/yosh -lyosh
LIBS     += -Llibs/dumbtools/ -ldumbtools 
override CFLAGS += $(INCLUDES) $(DEFINES) #$(LIBS)
BUILD_DIR   = ./build

.PHONY: clean

all: sandbox

sandbox: libs/yosh/libyosh.a \
	       libs/dumbtools/libdumbtools.a \
				 $(BUILD_DIR)/sandbox.o
	@echo $@
	@$(CC) $? $(CFLAGS) -o $@

$(BUILD_DIR)/sandbox.o: sandbox.c
	@echo $@
	@$(CC) -c $< $(CFLAGS) -o $@

sandbox.c: libs/

libs/yosh/libyosh.a:
	@make -C ../../ BUILD_DIR=$(abspath $(BUILD_DIR)) \
		              DISTRIB_DIR=$(abspath $(dir $@)) \
									CFLAGS=$(CFLAGS)

libs/dumbtools/libdumbtools.a:
	@make -C dumbtools/ BUILD_DIR=$(abspath $(BUILD_DIR)) \
		                  DISTRIB_DIR=$(abspath $(dir $@)) \
											CFLAGS=$(CFLAGS)

clean:
	@rm -rf build libs
