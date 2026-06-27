KDIR = /home/sheriff/Desktop/projects/oss/linux/include/uapi
CC = gcc
CFLAGS = -Wall -Wextra -I. -Isrc -Ideps -pthread -g -include deps/compat.h

SRCS = src/main.c src/vhost_backend.c  src/vblk_proto.c src/engine/lz4_engine.c deps/libvhost-user.c

OBJS = main.o deps/libvhost-user.o 

all: vblk_test

vblk_test: $(OBJS) 
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

deps/%.o: deps/%.c 
	      $(CC) $(CFLAGS) -c $< -o $@ 

clean:
	rm -f *.o deps/*.o vblk_test
