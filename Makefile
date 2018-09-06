CXX = /usr/bin/g++
CFLAGS = -std=c++17
TESTS=vec quat mat


all: $(TESTS:%=bin/test_%)
	$(foreach x,$^,$(x);)

clean:
	rm -f bin/*

bin/%: tests/%.cpp
	mkdir -p bin
	$(CXX) $(CFLAGS) -I include $^ -lboost_unit_test_framework -o $@
