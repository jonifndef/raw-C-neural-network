CFLAGS := -g -Wall -Wpedantic -O2
SRC_DIR := src
UTILS_DIR := $(SRC_DIR)/utils
BUILD_DIR := build
TEST_DIR := test

LIBNNUTILS_FILES := \
	$(UTILS_DIR)/dynamicarray.c \
	$(UTILS_DIR)/dynamicmatrix.c \
	$(UTILS_DIR)/fileIO.c \
	$(UTILS_DIR)/matrix.c \

LIBRAWCNEURALNETWORK_FILES := \
	$(SRC_DIR)/activationfunctions.c \
	$(SRC_DIR)/layer.c \
	$(SRC_DIR)/neuron.c \
	$(UTILS_DIR)/dynamicarray.c \
	$(UTILS_DIR)/dynamicmatrix.c \
	$(UTILS_DIR)/fileIO.c \
	$(UTILS_DIR)/matrix.c \

all: raw-c-neural-network

raw-c-neural-network: libRawCNeuralNetwork.a
	gcc $(CFLAGS) -o $(BUILD_DIR)/raw-c-neural-network $(SRC_DIR)/main.c -L. $(BUILD_DIR)/libRawCNeuralNetwork.a

libNeuralNetworkUtils.a: $(LIBNNUTILS_FILES)
	ar rcs $(BUILD_DIR)/$@ $^
	ranlib $(BUILD_DIR)/$@

libRawCNeuralNetwork.a: $(LIBRAWCNEURALNETWORK_FILES:.c=.o)
	ar rcs $(BUILD_DIR)/$@ $(LIBRAWCNEURALNETWORK_FILES:.c=.o)
	ranlib $(BUILD_DIR)/$@

test-1: libRawCNeuralNetwork.a
	gcc $(CFLAGS) -o $(BUILD_DIR)/test-a $(TEST_DIR)/main_test_non_dynamic_arrays.c -L. $(BUILD_DIR)/libRawCNeuralNetwork.a

clean:
	rm -f $(BUILD_DIR)/* $(shell find * -name "*.o")
