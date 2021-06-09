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

LIBRAWCNEURALNETWORK_OBJECTS := \
	$(patsubst %.c, %.o, $(LIBRAWCNEURALNETWORK_SOURCES))
LIBRAWCNEURALNETWORK_OBJECTS := \
	$(notdir $(LIBRAWCNEURALNETWORK_OBJECTS))
LIBRAWCNEURALNETWORK_OBJECTS := \
	$(addprefix obj/, $(LIBRAWCNEURALNETWORK_OBJECTS))

LIBRAWCNEURALNETWORK_UTILS_SOURCES := \
	$(UTILS_DIR)/dynamicarray.c \
	$(UTILS_DIR)/dynamicmatrix.c \
	$(UTILS_DIR)/fileIO.c \

LIBRAWCNEURALNETWORK_UTILS_OBJECTS := \
	$(patsubst %.c, %.o, $(LIBRAWCNEURALNETWORK_UTILS_SOURCES))
LIBRAWCNEURALNETWORK_UTILS_OBJECTS := \
	$(notdir $(LIBRAWCNEURALNETWORK_UTILS_OBJECTS))
LIBRAWCNEURALNETWORK_UTILS_OBJECTS := \
	$(addprefix obj/, $(LIBRAWCNEURALNETWORK_UTILS_OBJECTS))


vpath %.c $(SRC_DIR):$(UTILS_DIR)

all: raw-c-neural-network

$(OBJ_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $^

libNeuralNetworkUtils.a: $(LIBRAWCNEURALNETWORK_UTILS_OBJECTS)
	ar rcs $@ $^
	ranlib $@

libRawCNeuralNetwork.a: $(LIBRAWCNEURALNETWORK_OBJECTS) $(LIBRAWCNEURALNETWORK_UTILS_OBJECTS)
	ar rcs $@ $^
	ranlib $@

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.c
	$(CC) -g -c -o $@ $^

raw-c-neural-network: $(OBJ_DIR)/main.o libRawCNeuralNetwork.a libNeuralNetworkUtils.a
	$(CC) $(CFLAGS) -o $@ $^
	#$(CC) $(CFLAGS) -o $@ $^

clean:
	@find * ! -name "Makefile" ! -name "obj" ! -name "Makefile_old" -delete
	@rm -f obj/*

.PHONY: all tests clean #raw-c-neural-network libNeuralNetworkUtils.a libRawCNeuralNetwork.a libRawCNeuralNetworkLegacy.a utilsTest legacyTest neuralNetworkTest
