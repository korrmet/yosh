INCLUDES += -I$(abspath ./)
DEFINES  +=
override CFLAGS += $(INCLUDES) $(DEFINES)
BUILD_DIR   = ./build
DISTRIB_DIR = ./dist
INC_DIR     = $(DISTRIB_DIR)/inc

.PHONY: clean all yosh

all: yosh

yosh: $(DISTRIB_DIR)/libyosh.o \
	    $(INC_DIR)/yosh.h \
	    $(INC_DIR)/builtin/about.h \
		  $(INC_DIR)/builtin/exit.h \
		  $(INC_DIR)/builtin/help.h
	@echo $@

$(DISTRIB_DIR)/libyosh.o: $(BUILD_DIR)/yosh.o \
                          $(BUILD_DIR)/builtin/about.o \
                          $(BUILD_DIR)/builtin/exit.o \
                          $(BUILD_DIR)/builtin/help.o
	@echo $@
	@mkdir -p $(dir $@)
	@$(LD) -r $(LDFLAGS) $? -o $@

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
	                   $(BUILD_DIR)/containers/libcontainers.o
	@echo $@
	@mkdir -p $(dir $@)
	@$(CC) -c $< $(CFLAGS) -L$(BUILD_DIR)/containers -lcontainers -o $@
yosh.c: yosh.h builtin/about.h builtin/exit.h builtin/help.h
yosh.h:

$(INC_DIR)/yosh.h: yosh.h
	@echo $@
	@mkdir -p $(dir $@)
	@cp $< $@

$(BUILD_DIR)/containers/libcontainers.o:
	@echo $@
	@make -C containers BUILD_DIR=$(abspath $(dir $@)) \
		                  DISTRIB_DIR=$(abspath $(dir $@)) \
											INC_DIR=$(abspath $(INC_DIR)/containers)

clean:
	@rm -rf $(BUILD_DIR) $(DISTRIB_DIR)
