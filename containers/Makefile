override INCLUDES += -I./
override DEFINES  +=
override CFLAGS += $(INCLUDES) $(DEFINES)
BUILD_DIR   = ./build
DISTRIB_DIR = ./dist

.PHONY: clean

all: containers

containers: $(DISTRIB_DIR)/libcontainers.a \
	          $(DISTRIB_DIR)/inc/lists.h \
		        $(DISTRIB_DIR)/inc/strings.h

$(DISTRIB_DIR)/libcontainers.a: $(BUILD_DIR)/lists.o \
	                              $(BUILD_DIR)/strings.o
	@echo $@
	@mkdir -p $(DISTRIB_DIR)
	@$(AR) $(ARFLAGS) $(DISTRIB_DIR)/libcontainers.a $?

$(BUILD_DIR)/lists.o: lists.c
	@echo $@
	@mkdir -p $(dir $@)
	@$(CC) -c $<  $(CFLAGS) -o $@
lists.c: lists.h
lists.h:

$(DISTRIB_DIR)/inc/lists.h: lists.h
	@echo $@
	@mkdir -p $(dir $@)
	@cp $< $@

$(BUILD_DIR)/strings.o: strings.c
	@echo $@
	@mkdir -p $(dir $@)
	@$(CC) -c $<  $(CFLAGS) -o $@
strings.c: strings.h
strings.h:

$(DISTRIB_DIR)/inc/strings.h: strings.h
	@echo $@
	@mkdir -p $(dir $@)
	@cp $< $@

clean:
	@rm -rf $(BUILD_DIR) $(DISTRIB_DIR)
