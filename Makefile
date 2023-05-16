main: main.cpp
	g++ -g -o $@ $^ -std=c++20

.PHONY: clean
clean:
	rm -f main