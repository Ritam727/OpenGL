FILES = $(wildcard src/include/*.cpp)
OBJ = $(foreach d,$(FILES),$(subst .cpp,.o,$(subst src/include/,objects/,$(d))))
HEADERS = $(wildcard src/include/*.hpp)
DEPS = src/vendor/stb_image/stb_image.cpp
TESTS = $(wildcard src/tests/*.cpp)
TEST_HEADERS = $(wildcard src/tests/*.hpp)
IM_FL = src/vendor/imgui
INCLUDE = src/vendor src/include
LIBRARIES = lib/libimgui.so lib/libtest.so
APPLICATION = objects/Application.o

Application: $(OBJ) $(HEADERS) $(DEPS) $(APPLICATION)
	if [ ! -d "bin" ]; then mkdir bin; fi
	g++ -g -fdiagnostics-color=always $(foreach d,$(INCLUDE),-I$d) -o $@ $(OBJ) $(APPLICATION) $(DEPS) -Llib/ -lGLU -lGL -lGLEW -lglfw -limgui -ltest

objects/%.o : src/include/%.cpp
	if [ ! -d "objects" ]; then mkdir objects; fi
	g++ -g -fdiagnostics-color=always $(foreach d,$(INCLUDE),-I$d) -c $<
	mv $(subst objects/,,$@) $@

objects/Application.o: $(LIBRARIES) src/Application.cpp
	g++ -g -fdiagnostics-color=always $(foreach d,$(INCLUDE),-I$(d)) -c src/Application.cpp
	mv Application.o objects/Application.o

lib/libtest.so: $(TESTS) $(TEST_HEADERS)
	if [ ! -d "lib" ]; then mkdir lib; fi
	make -f TestMakefile.mak -j2

lib/libimgui.so:
	if [ ! -d "lib" ]; then mkdir lib; fi
	make -f ImguiMakefile.mak -j2

clean:
	make -f TestMakefile.mak clean
	make -f ImguiMakefile.mak clean
	rm $(OBJ) Application
	rm -r objects -r lib -r bin