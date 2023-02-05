CC := gcc
CFLAGS := -g -Wall -Wpedantic #-fsanitize=address #-O2 -Werror
SRC_DIR := ../src
OBJ_DIR := obj
OUT_DIR := output
UTILS_DIR := $(SRC_DIR)/utils
TEST_DIR := ../tests

LIBRAWCNEURALNETWORK_SOURCES := \
	$(SRC_DIR)/activationfunctions.c \
	$(SRC_DIR)/layer.c \
	$(SRC_DIR)/neuron.c \

LIBRAWCNEURALNETWORK_UTILS_SOURCES := \
	$(UTILS_DIR)/fileIO.c \
	$(UTILS_DIR)/dynamicarray.c \
	$(UTILS_DIR)/dynamicmatrix.c \

LIBRAWCNEURALNETWORK_OBJECTS := \
	$(patsubst %.c, %.o, $(LIBRAWCNEURALNETWORK_SOURCES))
LIBRAWCNEURALNETWORK_OBJECTS := \
	$(notdir $(LIBRAWCNEURALNETWORK_OBJECTS))
LIBRAWCNEURALNETWORK_OBJECTS := \
	$(addprefix obj/, $(LIBRAWCNEURALNETWORK_OBJECTS))

LIBRAWCNEURALNETWORK_UTILS_OBJECTS := \
	$(patsubst %.c, %.o, $(LIBRAWCNEURALNETWORK_UTILS_SOURCES))
LIBRAWCNEURALNETWORK_UTILS_OBJECTS := \
	$(notdir $(LIBRAWCNEURALNETWORK_UTILS_OBJECTS))
LIBRAWCNEURALNETWORK_UTILS_OBJECTS := \
	$(addprefix obj/, $(LIBRAWCNEURALNETWORK_UTILS_OBJECTS))


vpath %.c $(SRC_DIR):$(UTILS_DIR):$(TEST_DIR)

all: $(OUT_DIR)/raw-c-neural-network tests

$(OBJ_DIR)/%.o: %.c
	@mkdir -p obj
	@mkdir -p output
	$(CC) $(CFLAGS) -c -o $@ $^

$(OUT_DIR)/libNeuralNetworkUtils.a: $(LIBRAWCNEURALNETWORK_UTILS_OBJECTS)
	ar rcs $@ $^
	ranlib $@

$(OUT_DIR)/libRawCNeuralNetwork.a: $(LIBRAWCNEURALNETWORK_UTILS_OBJECTS) $(LIBRAWCNEURALNETWORK_OBJECTS)
	ar rcs $@ $^
	ranlib $@

$(OUT_DIR)/raw-c-neural-network: $(OBJ_DIR)/main.o $(OUT_DIR)/libRawCNeuralNetwork.a
	$(CC) $(CFLAGS) -o $@ $^ -lm

$(OUT_DIR)/utilsTest: $(OBJ_DIR)/runUtilsTests.o $(OUT_DIR)/libNeuralNetworkUtils.a
	$(CC) $(CFLAGS) -o $@ $^ -lcheck -lm

$(OUT_DIR)/neuralNetworkTest: $(OBJ_DIR)/runNeuralNetworkTest.o $(OUT_DIR)/libRawCNeuralNetwork.a
	$(CC) $(CFLAGS) -o $@ $^ -lcheck -lm
 
tests: $(OUT_DIR)/utilsTest $(OUT_DIR)/neuralNetworkTest

clean:
	@find * ! -name "Makefile" ! -name "obj" -delete
	@rm -rf obj

.PHONY: all tests clean
