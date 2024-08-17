.PHONY: \
	all \
	examples \
	format \
	format-cpp \
	lint \
	lint-cpp \
	clean

all: examples

examples: progress.o

progress.o: examples/progress.cpp
	g++ -Wall -Wextra -Werror -Wpedantic \
		-std=c++20 -O3 \
		-I./include \
		examples/progress.cpp -o $@

format: format-cpp

format-cpp: \
		include/aviize.hpp \
		examples/progress.cpp
	clang-format -i $^

lint: lint-cpp

lint-cpp: \
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
	rm -rf `find . -name "*.txt"`
