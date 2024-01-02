FILES = $(wildcard src/tests/*.cpp)
OBJ = $(foreach d,$(FILES),$(subst .cpp,.o,$(subst src/tests/,objects/,$(d))))
INCLUDE = src/tests src/include src/vendor

libtest.so: $(OBJ)
	g++ -shared -o lib/$@ $^

objects/%.o: src/tests/%.cpp
	if [ ! -d "objects" ]; then mkdir objects; fi
	g++ -g -fdiagnostics-color=always $(foreach d,$(INCLUDE),-I$(d)) -c -fPIC $<
	mv $(subst objects/,,$@) $@

clean:
	rm $(OBJ) lib/libtest.so