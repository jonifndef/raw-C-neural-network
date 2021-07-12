CC := gcc
CFLAGS := -g -Wall -Wpedantic #-fsanitize=address #-O2 -Werror
SRC_DIR := ../src
OBJ_DIR := obj
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

LIBRAWCNEURALNETWORK_LEGACY_SOURCES := \
	$(SRC_DIR)/legacy_activationfunctions.c \
	$(SRC_DIR)/legacy_layer.c \
	$(SRC_DIR)/legacy_neuron.c \
	$(UTILS_DIR)/matrix.c \

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

LIBRAWCNEURALNETWORK_LEGACY_OBJECTS := \
	$(patsubst %.c, %.o, $(LIBRAWCNEURALNETWORK_LEGACY_SOURCES))
LIBRAWCNEURALNETWORK_LEGACY_OBJECTS := \
	$(notdir $(LIBRAWCNEURALNETWORK_LEGACY_OBJECTS))
LIBRAWCNEURALNETWORK_LEGACY_OBJECTS := \
	$(addprefix obj/, $(LIBRAWCNEURALNETWORK_LEGACY_OBJECTS))


vpath %.c $(SRC_DIR):$(UTILS_DIR):$(TEST_DIR)

all: raw-c-neural-network tests

$(OBJ_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $^

libNeuralNetworkUtils.a: $(LIBRAWCNEURALNETWORK_UTILS_OBJECTS)
	ar rcs $@ $^
	ranlib $@

libRawCNeuralNetwork.a: $(LIBRAWCNEURALNETWORK_UTILS_OBJECTS) $(LIBRAWCNEURALNETWORK_OBJECTS)
	ar rcs $@ $^
	ranlib $@

raw-c-neural-network: $(OBJ_DIR)/main.o libRawCNeuralNetwork.a
	$(CC) $(CFLAGS) -o $@ $^ -lm

utilsTest: $(OBJ_DIR)/runUtilsTests.o libNeuralNetworkUtils.a
	$(CC) $(CFLAGS) -o $@ $^ -lcheck -lm

neuralNetworkTest: $(OBJ_DIR)/runNeuralNetworkTest.o libRawCNeuralNetwork.a
	$(CC) $(CFLAGS) -o $@ $^ -lcheck -lm
 
legacyTest: $(OBJ_DIR)/runLegacyTest.o $(LIBRAWCNEURALNETWORK_LEGACY_OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ -lcheck -lm

tests: utilsTest neuralNetworkTest legacyTest

clean:
	@find * ! -name "Makefile" ! -name "obj" -delete
	@rm -f obj/*

.PHONY: all tests clean
