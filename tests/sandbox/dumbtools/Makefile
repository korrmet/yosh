INCLUDES += -I$(abspath ./)
DEFINES  +=
override CFLAGS += $(INCLUDES) $(DEFINES)
BUILD_DIR   = ./build
DISTRIB_DIR = ./dist
INC_DIR     = $(DISTRIB_DIR)/inc

.PHONY: all clean

all: dumbtools

dumbtools: $(DISTRIB_DIR)/libdumbtools.o \
	         $(INC_DIR)/dumbtools.h
	@echo $@

$(DISTRIB_DIR)/libdumbtools.o: $(BUILD_DIR)/dumbtools.o
	@echo $@
	@mkdir -p $(dir $@)
	@$(LD) -r $(LDFLAGS) $? -o $@

$(BUILD_DIR)/dumbtools.o: dumbtools.c
	@echo $@
	@mkdir -p $(dir $@)
	@$(CC) -c $< $(CFLAGS) -o $@

$(INC_DIR)/dumbtools.h: dumbtools.h
	@echo $@
	@mkdir -p $(dir $@)
	@cp $< $@

dumbtools.h:
dumbtools.c: dumbtools.h

clean:
	@rm -rf $(BUILD_DIR) $(DISTRIB_DIR) $(INC_DIR)
