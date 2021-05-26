override INCLUDES += -I./
override DEFINES  +=
override CFLAGS += $(INCLUDES) $(DEFINES)
BUILD_DIR   = ./build
DISTRIB_DIR = ./dist

all: $(BUILD_DIR)/libyosh.a

$(BUILD_DIR)/libyosh.a: $(BUILD_DIR)/yosh.o \
                        $(BUILD_DIR)/builtin/about.o \
                        $(BUILD_DIR)/builtin/exit.o \
                        $(BUILD_DIR)/builtin/help.o
	mkdir -p $(DISTRIB_DIR)
	$(AR) $(ARFLAGS) $(DISTRIB_DIR)/libyosh.a $?
	mkdir -p $(DISTRIB_DIR)/inc
	cp ./yosh.h
	mkdir -p $(DISTRIB_DIR)/builtin
	cp ./builtin/about.h $(DISTRIB_DIR)/builtin
	cp ./builtin/exit.h  $(DISTRIB_DIR)/builtin
	cp ./builtin/help.h  $(DISTRIB_DIR)/builtin

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
