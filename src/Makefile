dependencies = $(shell find ../build/ -type f -name "*.d")
-include ${dependencies}

CXX ?= g++
CXXFLAGS := ${CXXFLAGS} -std=c++17 -Wall -Wextra -g
CXXFLAGS +=\
	-I.\
	-I./engine/exceptions\
	-I./engine/renderer\
	-I./engine/scene\
	-I./shaders\

CXXFLAGS += $(shell pkg-config --cflags gtkmm-3.0 epoxy assimp)

libs := $(shell pkg-config --libs gtkmm-3.0 epoxy assimp)
header_only_files :=\
	engine/exceptions/not_implemented.h\
	engine/renderer/texture.h\
	engine/renderer/vertex.h\
	engine/scene/camera.h\
	engine/scene/light_source.h\
	engine/scene/scene.h


all: viewer

objects += ../build/mesh.o ${header_only_files}
../build/mesh.o: ./engine/renderer/mesh.cc
	${CXX} ${CXXFLAGS} -c $< -o $@ -MD

objects += ../build/renderer.o ${header_only_files}
../build/renderer.o: ./engine/renderer/renderer.cc
	${CXX} ${CXXFLAGS} -c $< -o $@ -MD

objects += ../build/shader.o ${header_only_files}
../build/shader.o: ./engine/renderer/shader.cc
	${CXX} ${CXXFLAGS} -c $< -o $@ -MD

objects += ../build/main.o ${header_only_files}
../build/main.o: ./main.cc
	${CXX} ${CXXFLAGS} -c $< -o $@ -MD

objects += ../build/object.o ${header_only_files}
../build/object.o: ./engine/object/object.cc
	${CXX} ${CXXFLAGS} -c $< -o $@ -MD

objects += ../build/material.o ${header_only_files}
../build/material.o: ./engine/object/components/material.cc
	${CXX} ${CXXFLAGS} -c $< -o $@ -MD

objects += ../build/transform.o ${header_only_files}
../build/transform.o: ./engine/object/components/transform.cc
	${CXX} ${CXXFLAGS} -c $< -o $@ -MD

viewer: ${objects}
	${CXX} ${CXXFLAGS} -o $@ $^ $(libs)

clean:
	rm -f ../build/*
	rm -f viewer
