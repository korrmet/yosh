override INCLUDES += -I./
override DEFINES  +=
override CFLAGS += $(INCLUDES) $(DEFINES)
BUILD_DIR   = ./build
DISTRIB_DIR = ./dist

all: yosh

yosh: $(DISTRIB_DIR)/libyosh.a \
	    $(DISTRIB_DIR)/inc/yosh.h \
	    $(DISTRIB_DIR)/inc/builtin/about.h \
		  $(DISTRIB_DIR)/inc/builtin/exit.h \
		  $(DISTRIB_DIR)/inc/builtin/help.h

$(DISTRIB_DIR)/libyosh.a: $(BUILD_DIR)/yosh.o \
                          $(BUILD_DIR)/builtin/about.o \
                          $(BUILD_DIR)/builtin/exit.o \
                          $(BUILD_DIR)/builtin/help.o
	mkdir -p $(DISTRIB_DIR)
	$(AR) $(ARFLAGS) $(DISTRIB_DIR)/libyosh.a $?

$(BUILD_DIR)/builtin/about.o: builtin/about.c
	mkdir -p $(dir $@)
	$(CC) -c $< $(CFLAGS) -o $@
builtin/about.c: builltin/about.h
builtin/about.h:

$(DISTRIB_DIR)/inc/builtin/about.h: builtin/about.h
	mkdir -p $(dir $@)
	cp $< $@

$(BUILD_DIR)/builtin/exit.o: builtin/exit.c
	mkdir -p $(dir $@)
	$(CC) -c $< $(CFLAGS) -o $@
builtin/exit.c: builtin/exit.h
builtin/exit.h:

$(DISTRIB_DIR)/inc/builtin/exit.h: builtin/exit.h
	mkdir -p $(dir $@)
	cp $< $@

$(BUILD_DIR)/builtin/help.o: builtin/help.c
	mkdir -p $(dir $@)
	$(CC) -c $< $(CFLAGS) -o $@
builtin/help.c: builtin/help.h
builtin/help.h:

$(DISTRIB_DIR)/inc/builtin/help.h: builtin/help.h
	mkdir -p $(dir $@)
	cp $< $@

$(BUILD_DIR)/yosh.o:
	mkdir -p $(dir $@)
	$(CC) -c $< $(CFLAGS) -o $@
yosh.c: yosh.h builtin/about.h builtin/exit.h builtin/help.h/
yosh.h:

$(DISTRIB_DIR)/inc/yosh.h: yosh.h
	mkdir -p $(dir $@)
	cp $< $@

sandbox: yosh

.PHONY: clean

clean:
	rm -rf $(BUILD_DIR) $(DISTRIB_DIR)
