CC := gcc
CFLAGS := -g -Wall -Wpedantic #-fsanitize=address #-O2 -Werror
SRC_DIR := src
BUILD_DIR := build
OBJ_DIR := $(BUILD_DIR)/obj
UTILS_DIR := $(SRC_DIR)/utils
TEST_DIR := tests

LIBRAWCNEURALNETWORK_SOURCES := \
	$(SRC_DIR)/activationfunctions.c \
	$(SRC_DIR)/layer.c \
	$(SRC_DIR)/neuron.c \
	$(SRC_DIR)/loss.c \

LIBRAWCNEURALNETWORK_UTILS_SOURCES := \
	$(UTILS_DIR)/fileIO.c \
	$(UTILS_DIR)/dynamicarray.c \
	$(UTILS_DIR)/dynamicmatrix.c \

LIBRAWCNEURALNETWORK_OBJECTS := \
	$(patsubst %.c, %.o, $(LIBRAWCNEURALNETWORK_SOURCES))
LIBRAWCNEURALNETWORK_OBJECTS := \
	$(notdir $(LIBRAWCNEURALNETWORK_OBJECTS))
LIBRAWCNEURALNETWORK_OBJECTS := \
	$(addprefix build/obj/, $(LIBRAWCNEURALNETWORK_OBJECTS))

LIBRAWCNEURALNETWORK_UTILS_OBJECTS := \
	$(patsubst %.c, %.o, $(LIBRAWCNEURALNETWORK_UTILS_SOURCES))
LIBRAWCNEURALNETWORK_UTILS_OBJECTS := \
	$(notdir $(LIBRAWCNEURALNETWORK_UTILS_OBJECTS))
LIBRAWCNEURALNETWORK_UTILS_OBJECTS := \
	$(addprefix build/obj/, $(LIBRAWCNEURALNETWORK_UTILS_OBJECTS))


vpath %.c $(SRC_DIR):$(UTILS_DIR):$(TEST_DIR)

all: $(BUILD_DIR)/raw-c-neural-network tests

$(OBJ_DIR)/%.o: %.c
	@mkdir -p build
	@mkdir -p build/obj
	$(CC) $(CFLAGS) -c -o $@ $^

$(BUILD_DIR)/libNeuralNetworkUtils.so: $(LIBRAWCNEURALNETWORK_UTILS_OBJECTS)
	$(CC) -shared -o $@ $^

$(BUILD_DIR)/libRawCNeuralNetwork.so: $(LIBRAWCNEURALNETWORK_UTILS_OBJECTS) $(LIBRAWCNEURALNETWORK_OBJECTS)
	$(CC) -shared -o $@ $^

$(BUILD_DIR)/raw-c-neural-network: $(OBJ_DIR)/main.o $(BUILD_DIR)/libRawCNeuralNetwork.so
	$(CC) $(CFLAGS) -o $@ $^ -lm

$(BUILD_DIR)/utilsTest: $(OBJ_DIR)/runUtilsTests.o $(BUILD_DIR)/libNeuralNetworkUtils.so
	$(CC) $(CFLAGS) -o $@ $^ -lcheck -lm

$(BUILD_DIR)/neuralNetworkTest: $(OBJ_DIR)/runNeuralNetworkTest.o $(BUILD_DIR)/libRawCNeuralNetwork.so
	$(CC) $(CFLAGS) -o $@ $^ -lcheck -lm
 
tests: $(BUILD_DIR)/utilsTest $(BUILD_DIR)/neuralNetworkTest

clean:
	@rm -rf build

.PHONY: all tests clean
