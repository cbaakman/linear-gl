CXX = /usr/bin/g++
CFLAGS = -std=c++17
LIB_NAME = linear-gl
VERSION = 1.0.0

TESTS = vec quat mat


all: $(TESTS:%=bin/test_%)
	export LD_LIBRARY_PATH=lib; $(foreach x,$^,$(x);)

clean:
	rm -f bin/* obj/*.o lib/*

lib/lib$(LIB_NAME).so.$(VERSION): obj/vec.o obj/quat.o obj/matrix.o obj/triangle.o obj/plane.o
	mkdir -p lib
	$(CXX) $^ -o $@ -shared -fPIC

obj/%.o: src/%.cpp include/*
	mkdir -p obj
	$(CXX) $(CFLAGS) -I include -c $< -o $@ -fPIC

obj/%.o: tests/%.cpp include/*
	mkdir -p obj
	$(CXX) $(CFLAGS) -I include -c $< -o $@

bin/%: tests/%.cpp include/* lib/lib$(LIB_NAME).so.$(VERSION)
	mkdir -p bin
	$(CXX) $(CFLAGS) -I include -L lib $< -lboost_unit_test_framework -l$(LIB_NAME) -o $@

install:
	install -d -m755 /usr/local/lib
	install -d -m755 /usr/local/include/linear-gl
	install -m644 lib/lib$(LIB_NAME).so.$(VERSION) /usr/local/lib/lib$(LIB_NAME).so.$(VERSION)
	install -D include/*.h /usr/local/include/linear-gl/
