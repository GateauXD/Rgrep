#include <stdio.h>
#include <string.h>
#define MAXSIZE 4096

/**
 * You can use this recommended helper function 
 * Returns true if partial_line matches pattern, starting from
 * the first char of partial_line.
 */
int matches_leading(char *partial_line, char *pattern) {
  // Implement if desire 
	int i = 0;
	int dot = 1;
	int plus = 1;
	int question = 1;
	int backslash = 1;
	int charCheckers = 1;
	char preceding;
	char stringCheck[strlen(pattern)];

	while(i < strlen(pattern)){

		if(pattern[i] == '.'){
			dot = 0;

			char start = pattern[i-1];

			int j = i;

			while(pattern[j] == '.'){
				j++;
			}


			char end = pattern[i + j - 1];
			char end1 = pattern[i+j];

			i = i + j;
			
			if((partial_line[0] == start && partial_line[j] == end)){

				dot = 1;
			}

			else if(start == '\000' && end1 != '\000'){

				if(partial_line[j] == end1)
					dot = 1;
			}
			else if(start != '\000' && end == '\000'){
				
				if(partial_line[0] == start)
					dot =  1;
			}
			else if(start == '\000' && end1 == '\000'){
				if(strlen(partial_line) >= j){
					dot = 1;
				}
			}
		}
		else if(pattern[i] == '+'){
			plus = 0;
			preceding = pattern[i-1];

			int j;
			for(j = 0; j <= strlen(partial_line); j++){
				
				if(preceding == '.'){
					dot = 1;
					preceding = '\000';
				}
				if (partial_line[j] == preceding) {
					plus = 1;

				}
			}
		}

		else if(pattern[i] == '?'){
			char arr[strlen(pattern)];
			char arr2[strlen(pattern)];
			int j = 0;
			int arrcount = 0;
			int arrcount2 = 0; 
			while(j < strlen(pattern)){
				if(j == i-1){
					arr2[arrcount2] = pattern[j];
					arrcount2++;
				}
				else if(j == i){

				}
				else{
					arr[arrcount] = pattern[j];
					arr2[arrcount2] = pattern[j];
					arrcount2++;
					arrcount++;
				}
				j++;
			}
			arr[arrcount] = '\0';
			arr2[arrcount2] = '\0';

			int k = 0;
			for(k = 0; k < strlen(arr2); k++){
				if(arr[k] != partial_line[k] && arr2[k] != partial_line[k]){
					return 0;
				}
				question = 1;
			}
		}
		else{
			stringCheck[i] = pattern[i];
		}

		i++;
	}
	stringCheck[i] = '\0';

	int count = 0;
	while(stringCheck[count] != '\0'){
		if(stringCheck[count] == partial_line[count]){
			charCheckers = 1;
		}
		else{
			charCheckers = 0;
			break;
		}
		count++;
	}

	if(dot == 1 && plus == 1 && question == 1 && backslash == 1 && charCheckers == 1){
		return 1;
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
	for(i = strlen(line); i > strlen(pattern); i--){
		if(matches_leading(line, pattern) == 1){
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


