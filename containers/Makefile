BUILD_DIR   = ./build
DISTRIB_DIR = ./dist
INC_DIR     = $(DISTRIB_DIR)/inc/containers
RANLIB = ranlib
INCLUDES += -I./
DEFINES  +=
LIBS     +=
override CFLAGS += $(INCLUDES) $(DEFINES) $(LIBS)

.PHONY: clean

all: containers

containers: $(DISTRIB_DIR)/libcontainers.a \
	          $(INC_DIR)/lists.h \
		        $(INC_DIR)/strings.h

$(DISTRIB_DIR)/libcontainers.a: $(BUILD_DIR)/lists.o \
	                              $(BUILD_DIR)/strings.o
	@echo $@
	@mkdir -p $(DISTRIB_DIR)
	@$(AR) $(ARFLAGS) $@ $?
	@$(RANLIB) $@

$(BUILD_DIR)/lists.o: lists.c
	@echo $@
	@mkdir -p $(dir $@)
	@$(CC) -c $<  $(CFLAGS) -o $@
lists.c: lists.h
lists.h:

$(INC_DIR)/lists.h: lists.h
	@echo $@
	@mkdir -p $(dir $@)
	@cp $< $@

$(BUILD_DIR)/strings.o: strings.c
	@echo $@
	@mkdir -p $(dir $@)
	@$(CC) -c $<  $(CFLAGS) -o $@
strings.c: strings.h
strings.h:

$(INC_DIR)/strings.h: strings.h
	@echo $@
	@mkdir -p $(dir $@)
	@cp $< $@

clean:
	@rm -rf $(BUILD_DIR) $(DISTRIB_DIR)
