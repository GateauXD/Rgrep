# Your program must compile with 'make'
# You must not change this file.

CC = gcc
FLAGS = -std=c99 -O0 -Wall -Werror -g -pedantic

rgrep:
	$(CC) $(FLAGS) rgrep.c -o rgrep

clean:
	rm -rf rgrep *.dSYM

check: clean rgrep
	test "`echo "a\nb\nc" | ./rgrep 'a'`" = "a"
	test "`echo "a\n" | ./rgrep 'a'`" = "a"
	test "`echo "a" | ./rgrep '...'`" = ""
	test "`echo "abc" | ./rgrep '.b.'`" = "abc"
	test "`echo "h\naaaaah" | ./rgrep 'a+h'`" = "aaaaah"
	test "`echo "h\naaaaahhhhh" | ./rgrep 'aa+hh+'`" = "aaaaahhhhh"
	test "`echo "h\naaaaahhhhh\n" | ./rgrep 'aa+hh+'`" = "aaaaahhhhh"
	test "`echo "a" | ./rgrep 'a?a'`" = "a"
	test "`echo "woot\nwot\nwat\n" | ./rgrep 'wo?t'`" = "wot"
	test "`echo "CCCCCCC\nC+\nC++" | ./rgrep '.\+\+'`" = "C++"
	test "`echo "GG" | ./rgrep '.+'`" = "GG"
	test "`echo "woooooo_CSE31.jpg" | ./rgrep 'w.+_...31\.jpg'`" = "woooooo_CSE31.jpg"
	test "`echo "aab" | ./rgrep 'bb?'`" = "aab"
	test "`echo "aaab" | ./rgrep 'a+b'`" = "aaab"
	test "`echo "aaab" | ./rgrep 'a+ab'`" = "aaab"
	test "`echo "+.\?" | ./rgrep '++'`" = "+.\?"
	test "`echo "aaabaabbba?+" | ./rgrep 'a.'`" = "aaabaabbba?+"
	test "`echo ".....a..b." | ./rgrep '\.'`" = ".....a..b."
	test "`echo ".+.+.+.+.+" | ./rgrep '.+'`" = ".+.+.+.+.+"
	test "`echo "8a7sd123ss" | ./rgrep '8?7'`" = "8a7sd123ss"
	test "`echo "19280598." | ./rgrep '8?'`" = "19280598."
	test "`echo "01/15/1998" | ./rgrep '1?\'`" = "01/15/1998"
	test "`echo "00+aa+bb\d" | ./rgrep '0+'`" = "00+aa+bb\d"
	test "`echo "abcdefg?h1jk+." | ./rgrep '?+'`" = "abcdefg?h1jk+."
	test "`echo "a b c d e f g" | ./rgrep '.+'`" = "a b c d e f g"
	test "`echo "a_b_c_d_e_f_g" | ./rgrep '.+'`" = "a_b_c_d_e_f_g"
	test "`echo "aAbBcCdDeEfFgG" | ./rgrep 'B+'`" = "aAbBcCdDeEfFgG"
	test "`echo "z  aa b c c d e" | ./rgrep 'a+'`" = "z  aa b c c d e"
	@echo "Passed sanity check."
