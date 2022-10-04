dependencies = $(shell find ../build/ -type f -name "*.d")
-include ${dependencies}

CXX = g++
CXXFLAGS := ${CXXFLAGS} -std=c++17 -Wall -Wextra -g
CXXFLAGS +=\
	-I.\
	-I./core/exceptions\
	-I./core/opengl/renderer\
	-I./core/opengl/scene\
	-I./core/opengl/shader

CXXFLAGS += $(shell pkg-config --cflags gtkmm-3.0 epoxy assimp)
libs := $(shell pkg-config --libs gtkmm-3.0 epoxy assimp)

header_only_files :=\
	core/exceptions/not_implemented.h\
	core/exceptions/file_not_found.h\
	core/exceptions/shader_compile_error.h\
	core/opengl/renderer/texture.h\
	core/opengl/renderer/vertex.h\
	core/opengl/scene/camera.h\
	core/opengl/scene/light_source.h\
	core/opengl/scene/scene.h


all: viewer

objects += ../build/mesh.o
../build/mesh.o: core/opengl/renderer/mesh.cc ${header_only_files}
	${CXX} ${CXXFLAGS} -c $< -o $@ -MD

objects += ../build/renderer.o
../build/renderer.o: core/opengl/renderer/renderer.cc ${header_only_files}
	${CXX} ${CXXFLAGS} -c $< -o $@ -MD

objects += ../build/main.o
../build/main.o: ./main.cc ${header_only_files}
	${CXX} ${CXXFLAGS} -c $< -o $@ -MD

objects += ../build/object.o
../build/object.o: object/object.cc ${header_only_files}
	${CXX} ${CXXFLAGS} -c $< -o $@ -MD

objects += ../build/material.o
../build/material.o: object/components/material.cc ${header_only_files}
	${CXX} ${CXXFLAGS} -c $< -o $@ -MD

objects += ../build/transform.o
../build/transform.o: object/components/transform.cc ${header_only_files}
	${CXX} ${CXXFLAGS} -c $< -o $@ -MD

objects += ../build/shader.o
../build/shader.o: core/opengl/shader/shader.cc
	${CXX} ${CXXFLAGS} -c $< -o $@ -MD

objects += ../build/shader_program.o
../build/shader_program.o: core/opengl/shader/shader_program.cc ${header_only_files}
	${CXX} ${CXXFLAGS} -c $< -o $@ -MD

objects += ../build/shader_program_builder.o
../build/shader_program_builder.o: core/opengl/shader/shader_program_builder.cc ${header_only_files}
	${CXX} ${CXXFLAGS} -c $< -o $@ -MD

viewer: ${objects}
	${CXX} ${CXXFLAGS} $^ $(libs) -o $@

clean:
	rm -f ../build/*
	rm -f viewer
