CFLAGS := -g -Wall -Wpedantic #-fsanitize=address #-O2
SRC_DIR := src
UTILS_DIR := $(SRC_DIR)/utils
BUILD_DIR := build
TEST_DIR := tests

LIBNNUTILS_FILES := \
	$(UTILS_DIR)/dynamicarray.c \
	$(UTILS_DIR)/dynamicmatrix.c \
	$(UTILS_DIR)/fileIO.c \

LIBRAWCNEURALNETWORK_FILES := \
	$(SRC_DIR)/activationfunctions.c \
	$(SRC_DIR)/layer.c \
	$(SRC_DIR)/neuron.c \
	$(UTILS_DIR)/dynamicarray.c \
	$(UTILS_DIR)/dynamicmatrix.c \
	$(UTILS_DIR)/fileIO.c \

LIBRAWCNEURALNETWORK_LEGACY_FILES := \
	$(SRC_DIR)/activationfunctions.c \
	$(SRC_DIR)/legacy_layer.c \
	$(SRC_DIR)/legacy_neuron.c \
	$(UTILS_DIR)/dynamicarray.c \
	$(UTILS_DIR)/dynamicmatrix.c \
	$(UTILS_DIR)/fileIO.c \
	$(UTILS_DIR)/matrix.c \

all: raw-c-neural-network utilsTest legacyTest neuralNetworkTest

build_dir:
	$(shell if [ ! -d $(BUILD_DIR) ]; then mkdir $(BUILD_DIR); fi)

raw-c-neural-network: libRawCNeuralNetwork.a build_dir
	gcc $(CFLAGS) -o $(BUILD_DIR)/raw-c-neural-network $(SRC_DIR)/main.c -L. $(BUILD_DIR)/libRawCNeuralNetwork.a

libNeuralNetworkUtils.a: $(LIBNNUTILS_FILES:.c=.o) | build_dir
	ar rcs $(BUILD_DIR)/$@ $^
	ranlib $(BUILD_DIR)/$@

libRawCNeuralNetwork.a: $(LIBRAWCNEURALNETWORK_FILES:.c=.o) | build_dir
	ar rcs $(BUILD_DIR)/$@ $^
	ranlib $(BUILD_DIR)/$@

libRawCNeuralNetworkLegacy.a: $(LIBRAWCNEURALNETWORK_LEGACY_FILES:.c=.o) | build_dir
	ar rcs $(BUILD_DIR)/$@ $^
	ranlib $(BUILD_DIR)/$@

utilsTest: libNeuralNetworkUtils.a build_dir
	gcc $(CFLAGS) -o $(BUILD_DIR)/utilsTest $(TEST_DIR)/runUtilsTests.c -L. $(BUILD_DIR)/libNeuralNetworkUtils.a -lcheck

legacyTest: libNeuralNetworkUtils.a libRawCNeuralNetworkLegacy.a build_dir
	gcc $(CFLAGS) -o $(BUILD_DIR)/legacyTest $(TEST_DIR)/runLegacyTest.c -L. $(BUILD_DIR)/libNeuralNetworkUtils.a $(BUILD_DIR)/libRawCNeuralNetworkLegacy.a -lcheck

neuralNetworkTest: libNeuralNetworkUtils.a libRawCNeuralNetwork.a build_dir
	gcc $(CFLAGS) -o $(BUILD_DIR)/neuralNetworkTest $(TEST_DIR)/runNeuralNetworkTest.c -L. $(BUILD_DIR)/libNeuralNetworkUtils.a $(BUILD_DIR)/libRawCNeuralNetwork.a -lcheck

tests: utilsTest legacyTest neuralNetworkTest

clean:
	rm -f $(BUILD_DIR)/* $(shell find * -name "*.o")

.PHONY: clean
