INCLUDES += -I./
DEFINES  +=
override CFLAGS += $(INCLUDES) $(DEFINES)
BUILD_DIR = ./build

all: tests yosh

yosh: $(BUILD_DIR)/yosh.o \
	    $(BUILD_DIR)/builtin/about.o \
	    $(BUILD_DIR)/builtin/exit.o \
		  $(BUILD_DIR)/builtin/help.o

$(BUILD_DIR)/builtin/about.o:
	mkdir -p build/builtin
	$(CC) -c builtin/about.c $(CFLAGS) -o $(BUILD_DIR)/builtin/about.o

$(BUILD_DIR)/builtin/exit.o:
	mkdir -p build/builtin
	$(CC) -c builtin/exit.c $(CFLAGS) -o $(BUILD_DIR)/builtin/exit.o

$(BUILD_DIR)/builtin/help.o:
	mkdir -p build/builtin
	$(CC) -c builtin/help.c $(CFLAGS) -o $(BUILD_DIR)/builtin/help.o

$(BUILD_DIR)/yosh.o:
	mkdir -p build
	$(CC) -c yosh.c $(CFLAGS) -o $(BUILD_DIR)/yosh.o

sandbox: yosh

.PHONY: clean

clean:
	rm -rf build
