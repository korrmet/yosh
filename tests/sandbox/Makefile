INCLUDES += -I./
DEFINES  +=
override CFLAGS += $(INCLUDES) $(DEFINES)
BUILD_DIR   = ./build

.PHONY: clean

all: sandbox

sandbox: $(BUILD_DIR)/yosh/libyosh.a

$(BUILD_DIR)/yosh/libyosh.a:
	@make -C ../../ BUILD_DIR=$(abspath $(BUILD_DIR)) \
		              DISTRIB_DIR=$(abspath $(BUILD_DIR))

clean:
	@rm -rf build
