BUILD_DIR := build
SRC_DIR := src
LIB := wheelib
INC_DIR := -Isrc
LIB_DIR := -L$(BUILD_DIR)/lib
OTHER_LIBS := -lpthread
CC := gcc
CFLAGS := -g -Wall -O0

# $@：表示目标文件
# $^：表示所有依赖文件
# $<：表示第一个依赖文件

EXE_SRC = $(wildcard *.c)
EXE_OBJ = $(EXE_SRC:%.c=$(BUILD_DIR)/obj/%.o)
EXE_DEP = $(EXE_OBJ:.o=.d)
EXES = $(EXE_SRC:%.c=%)

all: $(EXES) 

$(EXES): %:$(BUILD_DIR)/obj/%.o $(BUILD_DIR)/lib/lib$(LIB).so
	$(CC) $(LIB_DIR) -l$(LIB) $(OTHER_LIBS) $< -o $@

$(EXE_OBJ): $(BUILD_DIR)/obj/%.o:%.c
	@mkdir -p $(dir $@)
	$(CC) -MMD -MP $(INC_DIR) $(CFLAGS) -c $< -o $@


###############################################
#            Build dynamic library           ##
###############################################
LIB_SRC = $(shell find $(SRC_DIR) -name '*.c')	# all source files
LIB_OBJ = $(LIB_SRC:%.c=$(BUILD_DIR)/obj/%.o)				# all object files
LIB_DEP = $(LIB_OBJ:.o=.d)								# all dependencies

# all .o => .so
$(BUILD_DIR)/lib/lib$(LIB).so: $(LIB_OBJ)
	@mkdir -p $(dir $@)
	$(CC) -shared $^ -o $@

# all .c => .o + .d
$(LIB_OBJ): $(BUILD_DIR)/obj/%.o:%.c
	@mkdir -p $(dir $@)
	$(CC) -MMD -MP $(INC_DIR) $(CFLAGS) -fPIC -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)
	rm -f $(EXES)

# dependencies
-include $(LIB_DEP)
-include $(EXE_DEP)
