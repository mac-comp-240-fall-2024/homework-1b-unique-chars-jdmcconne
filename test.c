/*
 * Exhaustive tests for the function hasUniqueChars, found in hasUniqueChars.c
 * Contributor: James McConnell
 */

#include <stdio.h>    // printf
#include <stdbool.h>  // to define a boolean type and true, false
#include <string.h>   // strcpy  to copy a string
#include <assert.h>


// declaration of function from hasUniqueChars.c
bool hasUniqueChars(char * inputStr);


int main() {

  // -------------------------------------------------------------
  // Tests for hasUniqueChars()
  // -------------------------------------------------------------

  char string3[128];   // can copy in up to 127 characters
  
  bool ok;    // holds the result of hasUniqueChars(); used in asserts
  
  // Test 1: a test case that should return false because characters are duplicated
  strcpy(string3, "This should fail (l and s and i and h)");
  ok = hasUniqueChars(string3);
  assert(!(ok));
  
  // Test 2: Simple string with no duplicates
  strcpy(string3, "abcdefghij");
  ok = hasUniqueChars(string3);
  assert(ok);
  
  // Test 3: Test string with all printable characters
  strcpy(string3, "!\"#$%&\\'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[]^_`abcdefghijklmnopqrstuvwxyz{|}~");
  ok = hasUniqueChars(string3);
  assert(ok);

  // Test 4: Test string with edge case values and multiple spaces
  strcpy(string3, "! \" ~ @ A");
  ok = hasUniqueChars(string3);
  assert(ok);

  // Test 5: Test string with edge case values, multiple spaces and repeat values
  strcpy(string3, "! \" ~ @ A B ] # !");
  ok = hasUniqueChars(string3);
  assert(!ok);

  // Test 6: Test string with nonprintable character
  strcpy(string3, "a b cc\t");
  ok = hasUniqueChars(string3);
  return 0;
}