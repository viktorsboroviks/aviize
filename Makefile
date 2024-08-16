.PHONY: \
	all \
	examples \
	format \
	clang-format \
	clean

all: examples

examples: progress.o

progress.o: examples/progress.cpp
	g++ -Wall -Wextra -Werror -Wpedantic \
		-std=c++20 -O3 \
		-I./include \
		examples/progress.cpp -o $@

format: clang-format

clang-format: \
		include/aviize.hpp \
		examples/progress.cpp
	clang-format -i $^

clean:
	rm -rf `find . -name "*.o"`
