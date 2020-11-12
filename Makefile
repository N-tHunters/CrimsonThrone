CFLAGS := -std=c++17 -Werror -Isrc -Iinclude -g -m64 -s -O3
CXFLAGS := -Iinclude
TARGET := main

BASE_SRCS = $(wildcard base/*.cpp)
BASE_OBJS = $(patsubst %.cpp,%.o,$(BASE_SRCS))

MAGIC_SRCS = $(wildcard base/magic/*.cpp)
MAGIC_OBJS = $(patsubst %.cpp,%.o,$(MAGIC_SRCS))

RENDER_SRCS=$(wildcard render/*.cpp)
RENDER_OBJS=$(patsubst %.cpp,%.o,$(RENDER_SRCS))

PHYSICS_SRCS=$(wildcard physics/*.cpp)
PHYSICS_OBJS=$(patsubst %.cpp,%.o,$(PHYSICS_SRCS))

SOUND_SRCS=$(wildcard sound/*.cpp)
SOUND_OBJS=$(patsubst %.cpp,%.o,$(SOUND_SRCS))

UI_SRCS=$(wildcard UI/*.cpp)
UI_OBJS=$(patsubst %.cpp,%.o,$(UI_SRCS))

OTH_SRCS=$(wildcard src/*.c)
OTH_OBJS=$(patsubst %.c,%.o,$(OTH_SRCS))

SRCS := $(wildcard *.cpp)
OBJS := $(patsubst %.cpp,%.o,$(SRCS))

# OS specific
ifeq ($(OS),Windows_NT)
	RM := rm
	LFLAGS := -static-libgcc -static-libstdc++ -L ./lib -lgdi32 -lglu32 -lglew32 -lzlib1 -lopengl32 -lglfw3 -lassimp -lOpenAL32 -lfreetype
	SFLAGS := #-Wl,--subsystem,windows

	CC := x86_64-w64-mingw32-g++
	CCX := x86_64-w64-mingw32-gcc

	REMOVABLE := $(TARGET).exe

else
	RM := rm
	LFLAGS := -lGL -ldl -lglfw -lGLEW -lX11 -lpthread -lassimp -lopenal -lfreetype
	SFLAGS :=

	REMOVABLE := $(TARGET)

	CC := g++
	CCX := gcc
endif

all: $(TARGET)

$(TARGET): $(TARGET).o $(BASE_OBJS) $(RENDER_OBJS) $(PHYSICS_OBJS) $(OTH_OBJS) $(SOUND_OBJS) $(UI_OBJS) $(MAGIC_OBJS)
	$(CC) -o $@ $^ $(CFLAGS) $(LFLAGS) $(SFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.c
	$(CCX) $(CXFLAGS) -c $< -o $@

clean:
	$(RM) $(BASE_OBJS) $(MAGIC_OBJS) $(RENDER_OBJS) $(PHYSICS_OBJS) $(OTH_OBJS) $(SOUND_OBJS) $(TARGET).o $(REMOVABLE)

cleanRender:
	$(RM) $(RENDER_OBJS) $(TARGET).o $(REMOVABLE)

cleanPhysics:
	$(RM) $(PHYSICS_OBJS) $(TARGET).o $(REMOVABLE)

cleanSound:
	$(RM) $(SOUND_OBJS) $(TARGET).o $(REMOVABLE)

cleanUI:
	$(RM) $(UI_OBJS) $(TARGET).o $(REMOVABLE)

.PHONY: all cleanAll


