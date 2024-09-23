/*
 * hasUniqueChars.c
 * 
 * Contains method hasUniqueChars and its helper methods.  Checks whether strings contain 
 * both all printable characters and all unique values (Excluding spaces)
 * Author: James McConnell
 */

#include <stdio.h>  // fprintf, printf
#include <stdlib.h> // exit() defined here
#include <string.h> // useful string operations
#include <ctype.h>  //useful character operations
#include <stdbool.h>  // to define a boolean type and true, false
                      // see https://en.wikibooks.org/wiki/C_Programming/stdbool.h

#include "binary_convert.h"


/*
 * This function is for debugging by printing out the value
 * of an input insigned long as a binary string.
 */
void seeBits(unsigned long value, char *debug_text) {
  
  // string to represent binary value of variable value
  char *bin_str;

  bin_str = ulong_to_bin_str(value);
  printf("%s%s\n", debug_text, bin_str);
  free(bin_str);
  
}

/*
 * Given an input string of chars, check for any non-printing
 * characters and print an error and exit if the string has any.
 */
void checkInvalid(char * inputStr) {
  char nextChar;
  int i;
  
  for(i = 0; i < strlen(inputStr); i++) {
    nextChar = inputStr[i];

    // if nextChar is invalid (31 or less or 127 as an ascii char code), then bail out
    if ((nextChar <= 31 ) || (nextChar == 127)) {
      fprintf(stderr, "invalid character in string\n");
      exit(EXIT_FAILURE);
    }
  }
}


/*
 * Accepts a string, checks if input string contains only printable characters without duplicates
 * (Excluding spaces) and outputs a boolean value.  If the string 
 * contains non-printable characters, an invalid character error will be thrown.  If all characters
 * are printable but there are duplicates, false will be returned, while if there are no duplicates, 
 * true will be returned.
 */
bool hasUniqueChars(char * inputStr) {
  // bail out quickly if any invalid characters
  checkInvalid(inputStr);
  
  int i;   // loop counter
  
  // unsigned long can handle 64 different chars in a string
  // if a bit at a position is 1, then we have seen that character
  unsigned long checkBitsA_z = 0;   // for checking A through z and {|}~
  unsigned long checkBitsexcl_amp =0;  // for checking ! though @ 

  char nextChar;         // next character in string to check

  // -------------------------------------------------------------
  // This section contains code to display the initial values of checkBitsA_z
  // and checkBitsexcl_amp, for debugging purposes. 
  // It also illustrates how to use the seeBits function for debugging.
  // Printed values should initially be all zeros
  
  // char debug_str_A_z[128];
  // strcpy(debug_str_A_z, "checkBitsA_z before: \n");
  // seeBits(checkBitsA_z, debug_str_A_z);
  
  // char debug_str_excl_amp[128];
  // strcpy(debug_str_excl_amp, "checkBitsexcl_amp before: \n");
  // seeBits(checkBitsexcl_amp, debug_str_excl_amp);
  // -------------------------------------------------------------
  
  for(i = 0; i < strlen(inputStr); i++) { //loop through input string
    nextChar = inputStr[i];
  
    //Check if char is a space, and whether to store it in checkBitsA_z or checkBitsexcl_amp.
    if((int)nextChar < 65 && (int)nextChar != 32){
      if(checkBitsexcl_amp & (long)1 << ((long)nextChar - 33)){  //Check if duplicate
        return false;
      }
      //Update long to reflect that we've seen this character
      checkBitsexcl_amp |= (long)1 << ((long)nextChar - 33);
    }
    else if((int)nextChar != 32){//Handle space edge case
      if( checkBitsA_z & (long)1 << ((long)nextChar - 65)){  //Check if duplicate
        return false;
      }
      //Update long to reflect that we've seen this character
      checkBitsA_z |= (long)1 << ((long)nextChar - 65);
    }
  }

  // if through all the characters, then no duplicates found
  return true;
  
}
