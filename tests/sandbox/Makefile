INCLUDES += -I$(abspath ./)
INCLUDES += -I$(abspath ./libs/yosh/inc)
INCLUDES += -I$(abspath ./libs/yosh/libs/containers/inc)
DEFINES  +=
LIBS     += -Llibs/yosh -lyosh
LIBS     += -Llibs/yosh/libs/containers/ -lcontainers
override CFLAGS += $(INCLUDES) $(DEFINES) $(LIBS)
BUILD_DIR   = ./build

.PHONY: clean

all: sandbox

sandbox: $(BUILD_DIR)/sandbox.o
	@echo $@
	@$(CC) $? $(CFLAGS) $(LIBS) -o $@

$(BUILD_DIR)/sandbox.o: sandbox.c
	@echo $@
	@$(CC) -c $< $(CFLAGS) -o $@

sandbox.c: libs/yosh/libyosh.a

libs/yosh/libyosh.a:
	@make -C ../../ BUILD_DIR=$(abspath $(BUILD_DIR)) \
		              DISTRIB_DIR=$(abspath $(dir $@)) \
									CFLAGS=$(CFLAGS)

clean:
	@rm -rf build libs sandbox
