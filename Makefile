PLATFORM ?= PLATFORM_DESKTOP

# Define Modes (Defaulting to debug if not specified)
MODE ?= debug

SRC_DIR   := src
BUILD_DIR := build

# Platform Configuration
ifeq ($(PLATFORM),PLATFORM_WEB)
    # Web / Emscripten Configuration
    CC     := emcc
    # Fallback to -std=c2x because the runner's GCC/Emscripten lacks full C23 support
    CFLAGS := -Wall -Wextra -std=c2x -g -D_DEFAULT_SOURCE
    
    # Emscripten specific flags (Includes Raylib source paths from GitHub Action)
    RAYLIB_SRC_PATH ?= ./raylib-src
    CFLAGS += -I$(RAYLIB_SRC_PATH)/src -L$(RAYLIB_SRC_PATH)/src
    
    # Link to the web version of raylib and pass Emscripten shell/preload settings
    LDLIBS := -lraylib.web -s USE_GLFW=3 -s ASYNCIFY -s TOTAL_MEMORY=67108864 --shell-file minshell.html --preload-file assets
    
    # GitHub Pages requires the main file to be index.html
    TARGET := $(BUILD_DIR)/index.html
else
    # Native Desktop Configuration (Your original setup)
    CC     := gcc
    CFLAGS := -Wall -Wextra -std=c23 -g
    LDLIBS := -lraylib -lGL -lm -lpthread -ldl
    TARGET := $(BUILD_DIR)/jumplinert
endif

DEPFLAGS := -MMD -MP

# Mode Configuration
ifeq ($(MODE),release)
    CFLAGS += -O2
else ifeq ($(MODE),debug)
    CFLAGS += -O0
else
    $(error Unknown MODE: $(MODE). Choose 'debug' or 'release')
endif

# Files/Targets
SRCS     := $(wildcard $(SRC_DIR)/*.c)
OBJS     := $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))
DEPS     := $(OBJS:.o=.d)

.PHONY: all clean run

all: $(TARGET)

# Build all C files into object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(DEPFLAGS) -c $< -o $@

# Link object files into final executable/HTML
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

-include $(DEPS)

clean:
	rm -rf $(BUILD_DIR)

run: $(TARGET)
ifeq ($(PLATFORM),PLATFORM_WEB)
	@echo "Cannot run web build directly. Host the $(BUILD_DIR) directory on a local server."
else
	./$(TARGET)
endif
