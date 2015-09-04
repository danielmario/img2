CFLAGS = -Os
LDLIBS = -lIL

all: img2 test

test: img2
	./img2 png test.jpg
