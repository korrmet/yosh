BUILD_DIR   = ./build
DISTRIB_DIR = ./dist
INC_DIR     = $(DISTRIB_DIR)/inc/yosh
RANLIB = ranlib
INCLUDES += -I$(abspath ./)
INCLUDES += -I$(abspath $(DISTRIB_DIR)/libs/containers/inc)
DEFINES  +=
LIBS     +=
override CFLAGS += $(INCLUDES) $(DEFINES) $(LIBS)

.PHONY: clean all yosh

all: yosh

yosh: $(DISTRIB_DIR)/libyosh.a \
	    $(INC_DIR)/yosh.h \
	    $(INC_DIR)/builtin/about.h \
		  $(INC_DIR)/builtin/exit.h \
		  $(INC_DIR)/builtin/help.h
	@echo $@

$(DISTRIB_DIR)/libyosh.a: $(BUILD_DIR)/yosh.o \
                          $(BUILD_DIR)/builtin/about.o \
                          $(BUILD_DIR)/builtin/exit.o \
                          $(BUILD_DIR)/builtin/help.o
	@echo $@
	@mkdir -p $(dir $@)
	@$(AR) $(ARFLAGS) $@ $?
	@$(RANLIB) $@

$(BUILD_DIR)/builtin/about.o: builtin/about.c
	@echo $@
	@mkdir -p $(dir $@)
	@$(CC) -c $< $(CFLAGS) -o $@
builtin/about.c: builtin/about.h
builtin/about.h:

$(INC_DIR)/builtin/about.h: builtin/about.h
	@echo $@
	@mkdir -p $(dir $@)
	@cp $< $@

$(BUILD_DIR)/builtin/exit.o: builtin/exit.c
	@echo $@
	@mkdir -p $(dir $@)
	@$(CC) -c $< $(CFLAGS) -o $@
builtin/exit.c: builtin/exit.h
builtin/exit.h:

$(INC_DIR)/builtin/exit.h: builtin/exit.h
	@echo $@
	@mkdir -p $(dir $@)
	@cp $< $@

$(BUILD_DIR)/builtin/help.o: builtin/help.c
	@echo $@
	@mkdir -p $(dir $@)
	@$(CC) -c $< $(CFLAGS) -o $@
builtin/help.c: builtin/help.h
builtin/help.h:

$(INC_DIR)/builtin/help.h: builtin/help.h
	@echo $@
	@mkdir -p $(dir $@)
	@cp $< $@

$(BUILD_DIR)/yosh.o: yosh.c \
	                   $(DISTRIB_DIR)/libs/containers/libcontainers.a
	@echo $@
	@mkdir -p $(dir $@)
	@$(CC) -c $< $(CFLAGS) -L$(BUILD_DIR)/containers -lcontainers -o $@
yosh.c: yosh.h builtin/about.h builtin/exit.h builtin/help.h
yosh.h:

$(INC_DIR)/yosh.h: yosh.h
	@echo $@
	@mkdir -p $(dir $@)
	@cp $< $@

$(DISTRIB_DIR)/libs/containers/libcontainers.a:
	@echo $@
	@make -C containers BUILD_DIR=$(abspath $(BUILD_DIR)/containers) \
		                  DISTRIB_DIR=$(abspath $(dir $@))

clean:
	@rm -rf $(BUILD_DIR) $(DISTRIB_DIR)
