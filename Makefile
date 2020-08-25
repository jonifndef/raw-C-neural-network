CFLAGS = -g -Wall -Werror -Wpedantic
SRC_DIR = src
BUILD_DIR = build
SRC_FILES = $(SRC_DIR)/*.c $(SRC_DIR)/utils/*.c

all: raw-c-neural-network

raw-c-neural-network:
	gcc $(CFLAGS) -o $(BUILD_DIR)/raw-c-neural-network $(SRC_FILES)

clean:
	rm -f $(BUILD_DIR)/raw-c-neural-network
