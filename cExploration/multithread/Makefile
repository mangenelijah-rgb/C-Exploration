# Target executable name
TARGET := prog

# Directories
SRC_DIR := src
OBJ_DIR := obj

# Find all .c files in SRC_DIR and its subdirectories
SRCS := $(shell find $(SRC_DIR) -name "*.c")

# Generate object file paths inside OBJ_DIR mirroring the SRC_DIR structure
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Generate dependency file paths for tracking header changes
DEPS := $(OBJS:.o=.d)

# Compiler and Flags
CC       := gcc
CFLAGS   := -Wall -Wextra -O2 -pthread
CPPFLAGS := $(addprefix -I,$(sort $(dir $(SRCS)))) -MMD -MP
LDFLAGS  := -pthread

# Default rule
all: $(TARGET)

# Link the executable
$(TARGET): $(OBJS)
	@echo "Linking executable with pthreads: $@"
	$(CC) $(OBJS) $(LDFLAGS) -o $@

# Compile source files to object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "Compiling: $<"
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

# Include automatically generated dependency files
-include $(DEPS)

# Clean build artifacts
clean:
	@echo "Cleaning up..."
	rm -rf $(OBJ_DIR) $(TARGET)

.PHONY: all clean