#include <stdio.h>
#include <string.h>
#define MAXSIZE 4096

//WIll try to implment a recurssive search pattern
int matches_leading(char *partial_line, char *pattern, int patternIndex) {
	//If you reached the end of the pattern and did not return 0 then the
	//pattern passed
	int i = patternIndex;
	char plus = '+';
	char slash ='\\';
	char dot = '.';
	char question = '?';
	int wildcheck = 0;

	if(pattern[i] == '\000'){
		return 1;
	}

	char next = pattern[i + 1];

	if(pattern[i] == '\\'){
		if (pattern[i+1] == plus || slash || dot || question) {
			wildcheck = 1;
		}
			return matches_leading(partial_line, pattern, i=i+1);
		}

	else if(pattern[i] == '.' && wildcheck != 1){
		//This is for the case where it will return any length of char .+
		if(next == '+'){
			return matches_leading(partial_line, pattern, i=i+2);
		}
		//Since the dot will almost always pass then I will move on to the next thing in pattern.
		return matches_leading(++partial_line, pattern, ++i);
	}
	//Check if the next characters is one of the wild cards that rely on the
	// previous character
	if(next == '+' && wildcheck == 0){
		//For the plus if you check the prev character which is i
		//if the character does not match then the plus will not work
		int lineCount = 0;
		if(pattern[i] != partial_line[lineCount]){
			return 0;
		}
		while(pattern[i] == *partial_line){
			partial_line++;
		}

		//Since the conditon ^ passed then + condition was passed so move on
		//Move the pattern cursor two to the right to skip the letter and
		//the +
		return matches_leading(++partial_line, pattern, i = i + 2);
	}
	//Like the + where it checks the next character for the wildcard
	else if(next == '?' && wildcheck == 0){
		//This is the condition where the char before ? does not exist so it moves
		//on
		if(pattern[i] != partial_line[0]){
			//Skips over the ? and moves over the next character
			return matches_leading(partial_line, pattern, i = i + 2);
		}
		//When it includes things before and after the question mark
		//This means the pattern and partial_line are the same so we need
		//To check after the ?
		return matches_leading(++partial_line, pattern, i = i+2);
	}
	//This means that none of the wildcard got called and that we are checking
	//if the characters match
	else{
		if(pattern[i] == partial_line[0]){
			return matches_leading(++partial_line, pattern, ++i);
		}
		else{
			return 0;
		}
	}
	return 0;
}

int rgrep_matches(char *line, char *pattern) {
  int i = 0;
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
