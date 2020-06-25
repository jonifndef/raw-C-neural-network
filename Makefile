CFLAGS = -g -Wall -Werror -Wpedantic

all: raw-c-neural-network

raw-c-neural-network:
	gcc $(CFLAGS) -o raw-c-neural-network main.c neuron.c layer.c

clean:
	rm -f raw-c-neural-network
