CXX = /usr/bin/g++
CFLAGS = -std=c++17


all: bin/test_mat
	bin/test_mat

clean:
	rm -f bin/*

bin/%: tests/%.cpp
	mkdir -p bin
	$(CXX) $(CFLAGS) -I include $^ -lboost_unit_test_framework -o $@
