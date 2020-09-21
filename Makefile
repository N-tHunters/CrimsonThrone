CC := g++
CFLAGS := -std=c++11 -Wall -g -Isrc -Iinclude -lGL -ldl -lglfw -lGLEW -lX11 -lpthread -lSOIL -lassimp
TARGET := main

BASE_SRCS = $(wildcard base/*.cpp)
BASE_OBJS = $(patsubst %.cpp,%.o,$(BASE_SRCS))

RENDER_SRCS=$(wildcard render/*.cpp)
RENDER_OBJS=$(patsubst %.cpp,%.o,$(RENDER_SRCS))

SRCS := $(wildcard *.cpp)
OBJS := $(patsubst %.cpp,%.o,$(SRCS))

# OS specific
ifeq ($(OS),Windows_NT)
	RM := del
else
	RM := rm
endif

all: $(TARGET)

$(TARGET): main.o $(BASE_OBJS) $(RENDER_OBJS)
	$(CC) -o $@ $^ -g $(CFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(TARGET) $(patsubst base/%,base\\%,$(BASE_OBJS)) $(OBJS) $(patsubst render/%,render\\%,$(RENDER_OBJS))

.PHONY: all clean


