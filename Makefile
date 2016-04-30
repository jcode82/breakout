#
# Makefile
#
# Computer Science 50
# Problem Set 3
#

breakout: breakout.c Makefile
	clang -ggdb3 -O0 -std=c99 -Wall -Werror -Wno-unused-variable -o breakout breakout.c -lcs -lm

working_example_breakout: working_example_breakout.c Makefile
	clang -ggdb3 -O0 -std=c99 -Wall -Werror -Wno-unused-variable -o working_example_breakout working_example_breakout.c -lcs -lm

clean:
	rm -f *.o core breakout working_example_breakout