#include <stdio.h>
#include <string.h>
#define MAXSIZE 4096

//WIll try to implment a recurssive search pattern
int matches_leading(char *partial_line, char *pattern, int patternIndex) {
	//If you reached the end of the pattern and did not return 0 then the
	//pattern passed
	int i = patternIndex;

	if(pattern[i] == '\000'){
		return 1;
	}

	char next = pattern[i + 1];
	if(i != 0)
		char prev = pattern[i-1];

	if(pattern[i] == '\\'){

	}

	else if(pattern[i] == '.'){
			//This is for the case where it will return any length of char
		if(next == '+'){
			return matches_leading(partial_line, pattern, ++i);
		}
			//Since the dot will almost always pass then I will move on to the next thing in pattern.
		return matches_leading(partial_line++, pattern, ++i);
	}
	else if(pattern[i] == '+'){


	}
	else if(pattern[i] == '?'){


	}

	return 0;

}

/**
 * You may assume that all strings are properly null terminated 
 * and will not overrun the buffer set by M     AXSIZE 
 *
 * Implementation of the rgrep matcher function
 */
int rgrep_matches(char *line, char *pattern) {
	int i = 0;
	//While the line is longer than the pattern pass the partial line through
	//If any part of the partial lines passes then the line will be printed
	for(i = strlen(line); i > strlen(pattern); i--){
		if(matches_leading(line, pattern, 0) == 1){
			return 1;
		}
		else{
			line++;
		}
	}

	return 0;
}

int main(int argc, char **argv) {
	if (argc != 2) {
		fprintf(stderr, "Usage: %s <PATTERN>\n", argv[0]);
		return 2;
	}

    /* we're not going to worry about long lines */
	char buf[MAXSIZE];

	while (!feof(stdin) && !ferror(stdin)) {
		if (!fgets(buf, sizeof(buf), stdin)) {
			break;
		}
		if (rgrep_matches(buf, argv[1])) {
			fputs(buf, stdout);
			fflush(stdout);
		}
	}

	if (ferror(stdin)) {
		perror(argv[0]);
		return 1;
	}

	return 0;
}


