#ifndef __STRUTILS_H
#define __STRUTILS_H

#include<string.h>
#include<stdlib.h>
#include<assert.h>
#include<stddef.h>
#include<ctype.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
  char *data;
  size_t sz;
}char_array;
  
void trim(char *str);
void trim_left(char *str);
void trim_right(char *str);
const char *trim_copy(const char *str);
const char *trim_left_copy(const char *str);
const char *trim_right_copy(const char *str);
char_array *to_char_array(char *str);

#ifdef __cplusplus
}
#endif

#endif // __STRUTILS_H

///////////////IMPLEMENTATION PART///////////////
#ifdef STRUTILS_IMPLEMENTATION

void trim(char *str)
{
  trim_left(str);
  trim_right(str);
}

void trim_left(char *str)
{
  size_t idx = {0};
  do{idx++;}while(isspace(str[idx]));
  char *last = &str[strlen(str)];
  
  ptrdiff_t sz = last - str;
  char *s = realloc(str, sz+1);
  assert(s && "Memory allocation failed.\n");

  size_t i = {0};
  while(str[idx] != '\0')
    {
      s[i] = str[idx];
      idx++; i++;
    }
  s[i] = '\0';
  str = s;
}

void trim_right(char *str)
{
  char *last = str + strlen(str) - 1;
  do{last--;}while(isspace(*last));
  ptrdiff_t sz = last - str + 1;

  char *s = realloc(str, sz+1);
  assert(s && "Memory allocation failed.\n");
  
  size_t i = {0};
  while(i != sz)
    {
      s[i] = str[i];
      i++;
    }
  s[i] = '\0';
  str = s;
}

const char *trim_copy(const char *str)
{
  char *s = strdup(str);
  assert(s && "Memory allocation failed.\n");
  trim_left(s);
  trim_right(s);
  
  return (const char*)s;
}

const char *trim_left_copy(const char *str)
{
  // Number of spaces.
  size_t spaces = {0};
  do{spaces++;}while(isspace(str[spaces]));

  // Allocate a string.
  char *s = malloc((strlen(str) - spaces + 1) * sizeof(char));
  assert(s && "Memory allocation failed.\n");
  // Ptr to the first non-space character to copy to s.
  const char *ptr = &str[spaces];

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

const char *trim_right_copy(const char *str)
{
  // Ptr to last character.
  const char *last = str + strlen(str)-1;
  // Decrement ptr as long as the pointed to character is space.
  while(last > str && isspace(*last)){last--;};
  // Size of actual string.
  size_t sz = (last - str) + 1;
  
  char *s = malloc((sz+1) * sizeof(char));
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

char_array *to_char_array(char *str)
{
  // Get size of str
  size_t sz = strlen(str);
  // Allocate memory for char_array struct
  char_array *arr = malloc(sizeof(char_array));
  assert(arr && "Memory allocation failed.\n");
  // Allocate memory for data in char_array struct
  arr->data = malloc(sz * sizeof(char));
  assert(arr->data && "Memory allocation failed.\n");
  // Set sz in char_array struct
  arr->sz = sz;
  
  // Copy the characters
  size_t i = {0};
  while(str[i] != '\0')
    {
      *(arr->data + i) = *(str + i);
      i++;
    }
  
  return arr;
}

#endif
