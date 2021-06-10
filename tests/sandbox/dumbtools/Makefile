BUILD_DIR   = ./build
DISTRIB_DIR = ./dist
INC_DIR     = $(DISTRIB_DIR)/inc/dumbtools
RANLIB = ranlib
INCLUDES += -I$(abspath ./)
DEFINES  +=
LIBS     +=
override CFLAGS += $(INCLUDES) $(DEFINES) $(LIBS)

.PHONY: all clean

all: dumbtools

dumbtools: $(DISTRIB_DIR)/libdumbtools.a \
	         $(INC_DIR)/dumbtools.h
	@echo $@

$(DISTRIB_DIR)/libdumbtools.a: $(BUILD_DIR)/dumbtools.o
	@echo $@
	@mkdir -p $(dir $@)
	@$(AR) $(ARFLAGS) $@ $?
	@$(RANLIB) $@

$(BUILD_DIR)/dumbtools.o: dumbtools.c
	@echo $@
	@mkdir -p $(dir $@)
	$(CC) -c $< $(CFLAGS) -o $@

$(INC_DIR)/dumbtools.h: dumbtools.h
	@echo $@
	@mkdir -p $(dir $@)
	@cp $< $@

dumbtools.h:
dumbtools.c: dumbtools.h

test:
	@$(CC) tests.c -o tests
	@./tests

clean:
	@rm -rf $(BUILD_DIR) $(DISTRIB_DIR) $(INC_DIR) tests
