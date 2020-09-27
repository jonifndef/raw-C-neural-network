CFLAGS = -g -Wall -Wpedantic -O2
SRC_DIR = src
BUILD_DIR = build
SRC_FILES = $(SRC_DIR)/*.c $(SRC_DIR)/utils/fileIO.c
LIB-NN-MATHS-FILES = \
	$(SRC_DIR)/utils/dynamicarray.o \
	$(SRC_DIR)/utils/dynamicmatrix.o \
	$(SRC_DIR)/utils/matrix.o \

all: raw-c-neural-network

raw-c-neural-network: lib-nn-maths.a
	gcc $(CFLAGS) -o $(BUILD_DIR)/raw-c-neural-network $(SRC_FILES) -L. $(BUILD_DIR)/lib-nn-maths.a

lib-nn-maths.a: $(LIB-NN-MATHS-FILES)
	ar rcs $(BUILD_DIR)/$@ $^
	ranlib $(BUILD_DIR)/$@

clean:
	rm -f $(BUILD_DIR)/raw-c-neural-network $(BUILD_DIR)/lib-nn-maths.a $(SRC_DIR)/utils/*.o
