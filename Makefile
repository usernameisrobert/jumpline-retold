CC := gcc
#
CFLAGS   := -Wall -Wextra -std=c23 -g
DEPFLAGS := -MMD -MP

LDLIBS   := -lraylib -lGL -lm -lpthread -ldl

# Define Modes (Defaulting to debug if not specified)
# to change mode do make MODE=(mode)
MODE ?= debug

ifeq ($(MODE),release)
    CFLAGS += -O2
else ifeq ($(MODE),debug)
    CFLAGS += -O0
else
    $(error Unknown MODE: $(MODE). Choose 'debug' or 'release')
endif

SRC_DIR  := src
BUILD_DIR:= build

TARGET   := $(BUILD_DIR)/jumplinert

SRCS     := $(wildcard $(SRC_DIR)/*.c)
OBJS     := $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))
DEPS     := $(OBJS:.o=.d)

.PHONY: all clean

all: $(TARGET)

# build all c into objs
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(DEPFLAGS) -c $< -o $@

# build the objs and compile it into an executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

-include $(DEPS)

clean:
	rm -rf $(BUILD_DIR)
