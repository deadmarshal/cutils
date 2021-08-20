#ifndef __STRUTILS_H
#define __STRUTILS_H

#include<string.h>
#include<stdlib.h>
#include<assert.h>
#include<stddef.h>
#include<ctype.h>
#include<stdio.h>

// By value:
const char* trim_left_copy(const char* str);
const char* trim_right_copy(const char* str);

#endif // __STRUTILS_H

///////////////IMPLEMENTATION PART///////////////
#ifdef STRUTILS_IMPLEMENTATION

const char* trim_left_copy(const char* str)
{
  // Number of spaces.
  size_t spaces = {0};
  do{spaces++;}while(isspace(str[spaces]));

  // Allocate a string.
  char* s = malloc((strlen(str) - spaces + 1) * sizeof(char));
  assert(s && "Memory allocation failed.\n");
  // Ptr to the first non-space character to copy to s.
  const char* ptr = &str[spaces];

  // Filling s with characters from str.
  size_t i = {0};
  while(*(ptr+i) != '\0')
    {
      s[i] = *(ptr + i);
      i++;
    }
  s[i] = '\0';
  
  return (const char*)s;
}

const char* trim_right_copy(const char* str)
{
  // Ptr to last character.
  const char *last = str + strlen(str)-1;
  // Decrement ptr as long as the pointed to character is space.
  while(last > str && isspace(*last)){last--;};
  // Size of actual string.
  size_t sz = (last - str) + 1;

  char* s = malloc((sz+1) * sizeof(char));
  assert(s && "Memory allocation failed.\n");
  
  size_t i = {0};
  while(i != sz)
    {
      s[i] = str[i];
      i++;
    }
  s[i] = '\0';
  
  return (const char*)s;
}

#endif
