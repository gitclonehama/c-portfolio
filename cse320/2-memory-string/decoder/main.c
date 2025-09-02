/**
 * Main program for testing the decoder
 */
#include <stdio.h>
#include "decoder.h"

/*
 * Main
 */
int main()
{
  const char *encoded="\
i-lEQ38hl0lE-E333hQ8h0Q8h3hhE8-ih-3ELLli3-8iQlEL%-0833q-lEQ3\
Q8l8-8-i-3L-hq-883qL-qqLhl3E33E00-QE-088-L-ELL838Q88ihq8h8Ll\
QL-33EQ33h3-qQ0l3Q38L3h-3-Q3Q0Q-8iL8h3iL3L80%3l-8lhhlhhl0-L3\
q88EQ%3833q3iqEii3Ll-lE88-q-h-0Q38L003E3l0l-38l-lE8-ii3Ll388\
l80qE-q8i-8l0h08%-Lliihi8%E00Lq-Eqq838LE8i3hlhl-%qq-ELi-L3--\
iE80E0Q30Lqql-h-3l3lQ83il-h38LLEiq0Lhl3qLi%0Qhq30Lq80qiil-83\
lqL-LLhl--Q3Q00-8l8-808lEl-Q33%iL83-EL3iQ3-883q388i3Ll-8E83-\
-l38q3lQ0Q38L3h0E8%Ql-il0lq3Q38L3h8--QlL0338-8Q0Eqq3-8i3l3Q-\
8l0lE-38LLE-388qq8E-h88h3--h-E0QEq83833iLl-8ll-8h8lEii3Ll33Q\
Q83hllq-hqEiiL0";

  char decoded[1000];

  decoder(encoded, decoded, sizeof(decoded));
  printf("%s\n", decoded);

  return 0;
}

