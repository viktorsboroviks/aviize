.PHONY: \
	all \
	examples \
	format \
	format-cpp \
	format-python \
	lint \
	lint-cpp \
	lint-python \
	clean

all: examples

examples: progress.o

progress.o: examples/progress.cpp
	g++ -Wall -Wextra -Werror -Wpedantic \
		-std=c++20 -O3 \
		-I./include \
		examples/progress.cpp -o $@

format: format-cpp format-python

format-cpp: \
		include/aviize.hpp \
		examples/progress.cpp
	clang-format -i $^

format-python: python/aviize.py
	black $^

lint: lint-cpp lint-python

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

lint-python: python/aviize.py
	pylint $^
	flake8 $^

clean:
	rm -rf `find . -name "*.o"`
	rm -rf `find . -name "*.txt"`
