FILES = $(wildcard src/vendor/imgui/*.cpp)
OBJ = $(foreach d,$(FILES),$(subst .cpp,.o,$(subst src/vendor/imgui/,objects/,$(d))))
INCLUDE = .

libimgui.so: $(OBJ)
	g++ -shared -o lib/$@ $^

objects/%.o: src/vendor/imgui/%.cpp
	if [ ! -d "objects" ]; then mkdir objects; fi
	g++ -g -fdiagnostics-color=always $(foreach d,$(INCLUDE),-I$(d)) -c -fPIC $<
	mv $(subst objects/,,$@) $@

clean:
	rm $(OBJ) lib/libimgui.so