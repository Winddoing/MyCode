OBJS = circle.o \
	   area.o \
	   volume.o

CC = gcc
AR = ar
CFLAGS = -Wall -O3 -I.
#LDFLAGS = -lm     #自定义变量

all : round libround.so libround.a

libround.so : $(OBJS)
	$(CC) -fpic -shared -o $@ $^
libround.a : $(OBJS)
	$(AR) -r $@ $^
round : $(OBJS) main.o
	$(CC) -o $@ $^ $(LDFLAGS)

circle.o : circle.c
area.o : area.c
volume.o : volume.c
main.o : main.c round.h

.PHONY : clean
clean :
	rm -f $(OBJS)



