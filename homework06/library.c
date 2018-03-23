/* library.c: string utilities library */

#include "str.h"

#include <ctype.h>
#include <string.h>

/**
 * Convert all characters in string to lowercase.
 * @param   s       String to convert
 * @return          Pointer to beginning of modified string
 **/
char *	str_lower(char *s) {
  for (char *c = s; *c; c++)
    *c = tolower(*c);
  return s;
}

/**
 * Convert all characters in string to uppercase.
 * @param   s       String to convert
 * @return          Pointer to beginning of modified string
 **/
char *	str_upper(char *s) {
  for (char *c = s; *c; c++)
    *c = toupper(*c);
  return s;
}

/**
 * Returns whether or not the 's' string starts with given 't' string.
 * @param   s       String to search within
 * @param   t       String to check for
 * @return          Whether or not 's' starts with 't'
 **/
bool	str_startswith(const char *s, const char *t) {
for(const char *c = t; *c; c++){
    if(*c != *s)
      return false;
    s++;
  }
  return true;
}

/**
 * Returns whether or not the 's' string ends with given 't' string.
 * @param   s       String to search within
 * @param   t       String to check for
 * @return          Whether or not 's' ends with 't'
 **/
bool	str_endswith(const char *s, const char *t) {
  if(*(s + strlen(s) - strlen(t)) == *t) { return true; }
  else { return false; }
}

/**
 * Removes trailing newline (if present).
 * @param   s       String to modify
 * @return          Pointer to beginning of modified string
 **/
char *	str_chomp(char *s) {
  if (*(s + strlen(s) - 1) == '\n')
    *(s + strlen(s) - 1) = 0;
  return s;
}

/**
 * Removes whitespace from front and back of string (if present).
 * @param   s       String to modify
 * @return          Pointer to beginning of modified string
 **/
char *	str_strip(char *s) {
  while(isspace(*s)) {s++;}
  char *c = s;
  int sze = strlen(s) - 1;
  for(int i = 0; i < sze; i++){
    c++;
  }
  while(isspace(*c)){
    *c = 0;
    c--;
  }
  return s;
}

/**
 * Reverses a string.
 * @param   s       String to reverse
 * @return          Pointer to beginning of modified string
 **/
char *	str_reverse(char *s) {
  char *a = s;
  char *b = (s + strlen(s) - 1);
  while(a < b){
    char temp = *a;
    *a = *b;
    *b = temp;
    a++;
    b--;
  }
  return s;
}

/**
 * Replaces all instances of 'from' in 's' with corresponding values in 'to'.
 * @param   s       String to translate
 * @param   from    String with letter to replace
 * @param   to      String with corresponding replacment values
 * @return          Pointer to beginning of modified string
 **/
char *	str_translate(char *s, char *from, char *to) {
    int table[128];
    for(int i = 0; i < 128; i++){
      table[i] = i;
    }
    while(*from && *to){
      table[(int)*from] = *to;
      from++;
      to++;
    }
    for(char *c = s; *c; c++){
      *c = table[(int)*c];
      from++;
    }
    return s;
}

/**
 * Converts given string into an integer.
 * @param   s       String to convert
 * @param   base    Integer base
 * @return          Converted integer value
 **/
int	str_to_int(const char *s, int base) {
  int sum = 0;
  int val;
  int oldBase = 1;
  for(const char *c = s + strlen(s) - 1; c >= s; c--){
    val = *c;
    if(isupper(val)){ val = val - 55; }
    else if(islower(val)){ val = val - 87; }
    else if(isdigit(val)){ val = val - 48; }
    sum += val * oldBase;
    oldBase *= base;
   }
  return sum;
}


/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
