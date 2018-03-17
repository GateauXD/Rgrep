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
				//Check if the next characters is one of the wild cards that rely on the
				// previous character
				if(next == '+'){
					//For the plus if you check the prev character which is i
					//if the character does not match then the plus will not work
					if(pattern[i] != partial_line[0]){
						return 0;
					}
					//Since the conditon ^ passed then + condition was passed so move on
					//Move the pattern cursor two to the right to skip the letter and
					//the +
					return matches_leading(partial_line, pattern, i = i + 2);
			  }
				//Like the + where it checks the next character for the wildcard
			  else if(next == '?'){
					//This is the condition where the char before ? does not exist so it moves
					//on
					if(pattern[i] != partial_line[0]){
						//Skips over the ? and moves over the next character
						return matches_leading(partial_line, pattern, i = i + 2);
					}
					//When it includes things before and after the question mark
					//This means the pattern and partial_line are the same so we need
					//To check after the ?
					return matches_leading(partial_line++, pattern, i = i+2);

			  }

			  return 0;

			}

			/**
			 * You may assume that all strings are properly null terminated
			 * and will not overrun the buffer set by M     AXSIZE
			 *
