CC := g++
CFLAGS := -std=c++11 -Wall -g
TARGET := test

BASE_SRCS = $(wildcard base/*.cpp)
BASE_OBJS = $(patsubst %.cpp,%.o,$(BASE_SRCS))

SRCS := $(wildcard *.cpp)
OBJS := $(patsubst %.cpp,%.o,$(SRCS))

all: $(TARGET)

$(TARGET): $(OBJS) $(BASE_OBJS)
	$(CC) -o $@ $^ -g

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	del $(TARGET) $(patsubst base/%,base\\%,$(BASE_OBJS)) $(OBJS)

.PHONY: all clean
