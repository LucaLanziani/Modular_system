#ifndef __DEBUG_H__
#define __DEBUG_H__

//#define DEBUG
#ifdef DEBUG
  #define DEBUG_MODULE
#endif
 
#ifdef DEBUG_MODULE
  #define YELLOW "\033[1;33m"
  #define RED "\033[31m"
  #define GREEN "\033[32m"
  #define NORMAL "\033[0m"
#endif
 
#ifdef DEBUG_MODULE
  #define PRINTE(format, args...)  printf(RED format NORMAL "\n", ##args);
  #define PRINTW(format, args...)  printf(YELLOW format NORMAL "\n", ##args);
  #define PRINTA(format, args...)  printf(GREEN format NORMAL "\n", ##args);
#else
  #define PRINTE(format, args...)
  #define PRINTW(format, args...)
  #define PRINTA(format, args...)
#endif

#endif
