CXX = /usr/bin/g++
CFLAGS = -std=c++17
TESTS=vec quat mat


all: $(TESTS:%=bin/test_%) bin/compile
	$(foreach x,$^,$(x);)

clean:
	rm -f bin/* obj/*.o

bin/compile: obj/compile1.o obj/compile2.o
	mkdir -p bin
	$(CXX) $^ -o $@

obj/%.o: tests/%.cpp include/*
	mkdir -p obj
	$(CXX) $(CFLAGS) -I include -c $< -o $@

bin/%: tests/%.cpp include/*
	mkdir -p bin
	$(CXX) $(CFLAGS) -I include $< -lboost_unit_test_framework -o $@
