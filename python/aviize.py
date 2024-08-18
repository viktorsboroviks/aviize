# pylint: disable=missing-function-docstring
"""
Aviize.
"""

import sys

ASCII_ESC_CLEAR_LINE = "\033[K"
ASCII_ESC_MOVE_UP = "\033[F"

OUT = sys.stderr


def erase_line(out=OUT):
    erase_lines(1, out=out)


def erase_lines(n_lines, out=OUT):
    for _ in range(n_lines):
        out.write(ASCII_ESC_MOVE_UP)
        out.write(ASCII_ESC_CLEAR_LINE)


def print_line(text, out=OUT):
    out.write(text + "\n")
