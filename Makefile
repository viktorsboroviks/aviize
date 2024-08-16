.PHONY: \
	all \
	examples \
	format \
	clang-format \
	lint \
	cppcheck-lint \
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

lint: cppcheck-lint

cppcheck-lint: \
		include/aviize.hpp \
		examples/progress.cpp
	cppcheck \
		--enable=warning,portability,performance \
		--enable=style,information \
		--enable=missingInclude \
		--inconclusive \
		--library=std,posix,gnu \
		--platform=unix64 \
		--language=c++ \
		--std=c++20 \
		--inline-suppr \
		--check-level=exhaustive \
		--suppress=missingIncludeSystem \
		--suppress=checkersReport \
		--checkers-report=cppcheck_report.txt \
		-I./include \
		$^

clean:
	rm -rf `find . -name "*.o"`
