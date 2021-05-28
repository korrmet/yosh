override INCLUDES += -I./
override DEFINES  +=
override CFLAGS += $(INCLUDES) $(DEFINES)
BUILD_DIR   = ./build
DISTRIB_DIR = ./dist

all: containers

containers: $(DISTRIB_DIR)/libcontainers.a \
	          $(DISTRIB_DIR)/inc/lists.h \
		        $(DISTRIB_DIR)/inc/strings.h

$(DISTRIB_DIR)/libcontainers.a: $(BUILD_DIR)/lists.o \
	                              $(BUILD_DIR)/strings.o
	mkdir -p $(DISTRIB_DIR)
	$(AR) $(ARFLAGS) $(DISTRIB_DIR)/libcontainers.a $?

$(BUILD_DIR)/lists.o: lists.c
	mkdir -p $(dir $@)
	$(CC) -c $<  $(CFLAGS) -o $@
lists.c: lists.h
lists.h:

$(DISTRIB_DIR)/inc/lists.h: lists.h
	mkdir -p $(dir $@)
	cp $< $@

$(BUILD_DIR)/strings.o: strings.c
	mkdir -p $(dir $@)
	$(CC) -c $<  $(CFLAGS) -o $@
strings.c: strings.h
strings.h:

$(DISTRIB_DIR)/inc/strings.h: strings.h
	mkdir -p $(dir $@)
	cp $< $@

.PHONY: clean

clean:
	rm -rf $(BUILD_DIR) $(DISTRIB_DIR)
