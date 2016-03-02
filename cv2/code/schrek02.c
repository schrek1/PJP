/*
  FILE: main.c

  DESCRIPTION:
    Kielet kääntäjät ja tulkit 1. harjoitus 2004.
      Languages, Compilers and Interpreters, Exercise 1, 2008/2009.
a
  AUTHORS:
    Jan Voracek, Joni Kämäräinen, Jarno Mielikäinen
  Modified by Kari Jyrkinen, Jarmo Ilonen, Arto Kaarna

 */

#include <stdio.h> /* IO */
#include <stdlib.h>
#include <ctype.h>

typedef int ParserState;

#define STATE_INIT ((ParserState ) 1)
#define STATE_INIT_A ((ParserState ) 2)
#define STATE_INIT_B ((ParserState ) 3)
#define STATE_HEAD_OK ((ParserState ) 4)
#define STATE_END_A ((ParserState ) 5)
#define STATE_END_B ((ParserState ) 6)
#define STATE_OK ((ParserState ) 7)
#define STATE_ERR ((ParserState ) 8)
#define STATE_UNKNOWN ((ParserState ) 8)

/* internals */
ParserState nextState(ParserState state_, char input_);
ParserState a(ParserState);
ParserState b(ParserState);
ParserState other(ParserState);

int main(int argc, char **argv) {
  ParserState state = STATE_INIT;
  char c;
  int i = 0;

  if (argc < 2) {
    puts("Word not given");
    exit(1);
  }

  while ((c = *(argv[1] + i++)) != '\0') {
    /* A character can not be a capital letter and it should be alphanumeric. */
    if ((c < 65 || c > 90) && isalnum(c)) {
      state = nextState(state, c);
    } else {
      state = STATE_ERR;
    }
  }

  if (state == STATE_OK) {
    puts("The given word is derived from the language ^(ab|ba)[c-z0-9]*(ab|ba)$");
  } else {
    puts("Language definition doesn't match with the given word.");
  }
  return 0;
}

ParserState nextState(ParserState state_, char input_) {
  ParserState newState;

  switch (input_) {
    case 'a':
      newState = a(state_);
      break;

    case 'b':
      newState = b(state_);
      break;

    default:
      newState = other(state_);

  };
  return newState;
}

ParserState a(ParserState s_) {
  switch (s_) {
    case STATE_INIT:
      return STATE_INIT_A;
      break;
    case STATE_INIT_B:
      return STATE_HEAD_OK;
      break;
    case STATE_HEAD_OK:
      return STATE_END_A;
      break;
    case STATE_END_B:
      return STATE_OK;
      break;
  }
  return STATE_UNKNOWN;
}

ParserState b(ParserState s_) {
  switch (s_) {
    case STATE_INIT:
      return STATE_INIT_B;
      break;
    case STATE_INIT_A:
      return STATE_HEAD_OK;
      break;
    case STATE_HEAD_OK:
      return STATE_END_B;
      break;
    case STATE_END_A:
      return STATE_OK;
      break;
  }
  return STATE_UNKNOWN;
}

ParserState other(ParserState s_) {
  if (s_ == STATE_HEAD_OK)
    return STATE_HEAD_OK;
  else
    return STATE_UNKNOWN;
}
