INCLUDES += -I./
DEFINES  +=
LIBS     += -lcontainers
override CFLAGS += $(INCLUDES) $(DEFINES) $(LIBS)
BUILD_DIR   = ./build
DISTRIB_DIR = ./dist

.PHONY: clean all yosh

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
	@echo $@
	@mkdir -p $(DISTRIB_DIR)
	@$(AR) $(ARFLAGS) $(DISTRIB_DIR)/libyosh.a $?

$(BUILD_DIR)/builtin/about.o: builtin/about.c \
	                            $(BUILD_DIR)/containers/libcontainers.a
	@echo $@
	@mkdir -p $(dir $@)
	@$(CC) -c $< $(CFLAGS) -lcontainers -L$(BUILD_DIR)/containers -o $@
builtin/about.c: builtin/about.h
builtin/about.h:

$(DISTRIB_DIR)/inc/builtin/about.h: builtin/about.h
	@echo $@
	@mkdir -p $(dir $@)
	@cp $< $@

$(BUILD_DIR)/builtin/exit.o: builtin/exit.c \
	                           $(BUILD_DIR)/containers/libcontainers.a
	@echo $@
	@mkdir -p $(dir $@)
	@$(CC) -c $< $(CFLAGS) -lcontainers -L$(BUILD_DIR)/containers -o $@
builtin/exit.c: builtin/exit.h
builtin/exit.h:

$(DISTRIB_DIR)/inc/builtin/exit.h: builtin/exit.h
	@echo $@
	@mkdir -p $(dir $@)
	@cp $< $@

$(BUILD_DIR)/builtin/help.o: builtin/help.c \
	                           $(BUILD_DIR)/containers/libcontainers.a
	@echo $@
	@mkdir -p $(dir $@)
	@$(CC) -c $< $(CFLAGS) -lcontainers -L$(BUILD_DIR)/containers -o $@
builtin/help.c: builtin/help.h
builtin/help.h:

$(DISTRIB_DIR)/inc/builtin/help.h: builtin/help.h
	@echo $@
	@mkdir -p $(dir $@)
	@cp $< $@

$(BUILD_DIR)/yosh.o: yosh.c \
	                   $(BUILD_DIR)/containers/libcontainers.a
	@echo $@
	@mkdir -p $(dir $@)
	@$(CC) -c $< $(CFLAGS) -lcontainers -L$(BUILD_DIR)/containers -o $@
yosh.c: yosh.h builtin/about.h builtin/exit.h builtin/help.h
yosh.h:

$(DISTRIB_DIR)/inc/yosh.h: yosh.h
	@echo $@
	@mkdir -p $(dir $@)
	@cp $< $@

$(BUILD_DIR)/containers/libcontainers.a:
	@echo $@
	@make -C containers BUILD_DIR=$(abspath $(BUILD_DIR)) \
		                  DISTRIB_DIR=$(abspath $(BUILD_DIR))

containers/Makefile:
containers/lists.c:
containers/lists.h:
containers/strings.c:
containers/strings.h:

sandbox: yosh

clean:
	@rm -rf $(BUILD_DIR) $(DISTRIB_DIR)
