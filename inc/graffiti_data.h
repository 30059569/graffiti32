#ifndef __GRAFFITI32_GRAFFITI_DATA_H__
#define __GRAFFITI32_GRAFFITI_DATA_H__

#include "graffiti.h"

const int PREDEFINED_LETTERS_SIZE = 61;
static TLeterInfo refAlfa[PREDEFINED_LETTERS_SIZE]={
{'A', 3, {{0, 10}, {5, 0}, {10, 10}}},
{'B', 6, {{0, 0}, {10, 3}, {0, 5}, {10, 8}, {0, 10}}},
{'B', 6, {{0, 0}, {0, 10}, {0, 7}, {10, 7}, {10, 10}, {0, 10}}},
{'B', 8, {{0, 10}, {0, 0}, {10, 0}, {10, 5}, {0, 5}, {10, 5}, {10, 10}, {0, 10}}},
{'B', 7, {{0, 0}, {10, 0}, {10, 5}, {0, 5}, {10, 5}, {10, 10}, {0, 10}}},
{'C', 4, {{10, 0}, {0, 0}, {0, 10}, {10, 10}}},
{'C', 4, {{5, 0}, {0, 0}, {0, 10}, {10, 10}}},
{'D', 5, {{0, 10}, {0, 0}, {10, 0}, {10, 10}, {0, 10}}},
{'D', 4, {{0, 10}, {10, 0}, {0, 0}, {10, 10}}},
{'D', 6, {{0, 0}, {0, 10}, {0, 0}, {10, 0}, {10, 10}, {0, 10}}},
{'D', 4, {{10, 10}, {0, 0}, {10, 0}, {0, 10}}},
{'E', 5, {{10, 0}, {0, 3}, {10, 5}, {0, 8}, {10, 10}}},
{'E', 6, {{0, 10}, {7, 5}, {6, 2}, {3, 3}, {3, 6}, {10, 0}}},
{'E', 6, {{0, 5}, {10, 5}, {10, 0}, {0, 0}, {0, 10}, {10, 10}}},
{'F', 3, {{10, 0}, {0, 0}, {0, 10}}},
{'F', 3, {{10, 0}, {0, 3}, {0, 10}}},
{'G', 6, {{10, 0}, {0, 0}, {0, 10}, {10, 10}, {10, 5}, {0, 5}}},
{'G', 6, {{10, 0}, {3, 0}, {3, 10}, {10, 10}, {10, 5}, {0, 5}}},
{'H', 4, {{0, 0}, {0, 10}, {7, 0}, {10, 10}}},
{'H', 4, {{0, 0}, {0, 10}, {5, 5}, {10, 10}}},
{'J', 3, {{10, 0}, {10, 10}, {0, 10}}},
{'J', 5, {{10, 0}, {10, 7}, {5, 10}, {0, 8}, {0, 6}}},
{'K', 4, {{10, 0}, {0, 10}, {0, 0}, {10, 10}}},
{'K', 5, {{10, 0}, {6, 3}, {0, 5}, {5, 7}, {10, 10}}},
{'L', 3, {{0, 0}, {0, 10}, {10, 10}}},
{'M', 5, {{0, 10}, {0, 0}, {5, 10}, {10, 0}, {10, 10}}},
{'M', 5, {{0, 10}, {3, 0}, {5, 10}, {8, 0}, {10, 10}}},
{'N', 4, {{0, 10}, {0, 0}, {10, 10}, {10, 0}}},
{'N', 4, {{0, 10}, {3, 0}, {7, 10}, {10, 0}}},
{'O', 7, {{5, 0}, {0, 2}, {0, 8}, {5, 10}, {10, 8}, {10, 2}, {5, 0}}},
{'O', 5, {{0, 0}, {0, 10}, {10, 10}, {10, 0}, {0, 0}}},
{'P', 5, {{0, 10}, {0, 0}, {10, 0}, {10, 5}, {0, 5}}},
{'Q', 9, {{5, 0}, {0, 2}, {0, 7}, {5, 10}, {10, 7}, {10, 3}, {5, 0}, {5, 1}, {10, 0}}},
{'Q', 6, {{0, 0}, {0, 10}, {10, 10}, {10, 0}, {0, 0}, {10, 0}}},
{'R', 6, {{0, 10}, {0, 0}, {10, 0}, {10, 4}, {1, 5}, {10, 10}}},
{'R', 5, {{0, 10}, {0, 0}, {10, 3}, {1, 5}, {10, 10}}},
{'S', 6, {{10, 0}, {0, 0}, {0, 5}, {10, 5}, {10, 10}, {0, 10}}},
{'S', 4, {{10, 0}, {0, 3}, {10, 7}, {0, 10}}},
{'T', 3, {{0, 0}, {10, 0}, {10, 10}}},
{'U', 3, {{0, 0}, {5, 10}, {10, 0}}},
{'V', 3, {{10, 0}, {5, 10}, {0, 0}}},
{'W', 5, {{0, 0}, {3, 10}, {5, 0}, {8, 10}, {10, 0}}},
{'W', 5, {{0, 0}, {3, 10}, {5, 5}, {8, 10}, {10, 0}}},
{'X', 4, {{0, 0}, {10, 10}, {10, 0}, {0, 10}}},
{'X', 7, {{0, 0}, {5, 10}, {8, 10}, {10, 5}, {8, 0}, {5, 0}, {0, 10}}},
{'Y', 4, {{0, 0}, {10, 10}, {0, 10}, {10, 0}}},
{'Y', 6, {{0, 0}, {10, 6}, {8, 10}, {2, 10}, {0, 6}, {10, 0}}},
{'Y', 8, {{0, 0}, {5, 3}, {10, 0}, {9, 6}, {4, 10}, {0, 8}, {1, 6}, {10, 4}}},
{'Z', 4, {{0, 0}, {10, 0}, {0, 10}, {10, 10}}},
{'Z', 4, {{0, 0}, {10, 3}, {0, 7}, {10, 10}}},

{'~', 4, {{10, 0}, {6, 10}, {3, 0}, {0, 10}}},
{'~', 4, {{10, 10}, {6, 0}, {3, 10}, {0, 0}}},
{'o', 7, {{5, 0}, {10, 3}, {10, 8}, {5, 10}, {0, 8}, {0, 3}, {5, 0}}},
{'o', 5, {{10, 0}, {10, 10}, {0, 10}, {0, 0}, {10, 0}}},
{'\\', 2, {{10, 10}, {0, 0}}},
{'/', 2, {{10, 0}, {0, 10}}},

{CHAR_OPTION, 2, {{0, 10}, {10, 0}}},
{CHAR_ENTER, 2, {{0, 0}, {10, 10}}},
{CHAR_RIGHT, 3, {{0, 5}, {10, 5}, {0, 5}}},
{CHAR_LEFT, 3, {{10, 5}, {0, 5}, {10, 5}}},
{CHAR_TAB, 3, {{0, 10}, {0, 0}, {10, 0}}}
};

const int PREDEFINED_NUMBER_SIZE = 35;
static TLeterInfo refNumber[PREDEFINED_NUMBER_SIZE]={
{'0', 5, {{0, 0}, {0, 10}, {10, 10}, {10, 0}, {0, 0}}},
{'0', 7, {{5, 0}, {0, 2}, {0, 7}, {5, 10}, {10, 7}, {10, 2}, {5, 0}}},
{'2', 4, {{0, 0}, {10, 0}, {0, 10}, {10, 10}}},
{'2', 8, {{0, 2}, {3, 0}, {7, 0}, {10, 2}, {10, 5}, {1, 8}, {0, 10}, {10, 10}}},
{'2', 4, {{0, 0}, {10, 3}, {0, 7}, {10, 10}}},
{'3', 7, {{0, 0}, {10, 0}, {10, 5}, {0, 5}, {10, 5}, {10, 10}, {0, 10}}},
{'3', 5, {{0, 0}, {10, 3}, {0, 5}, {10, 7}, {0, 10}}},
{'4', 3, {{10, 0}, {0, 10}, {10, 10}}},
{'4', 3, {{0, 0}, {0, 10}, {10, 10}}},
{'4', 4, {{10, 0}, {0, 5}, {10, 5}, {10, 10}}},
{'5', 6, {{10, 0}, {0, 0}, {0, 5}, {10, 5}, {10, 10}, {0, 10}}},
{'5', 5, {{0, 0}, {0, 5}, {10, 5}, {10, 10}, {0, 10}}},
{'6', 6, {{10, 0}, {0, 0}, {0, 10}, {10, 10}, {10, 5}, {0, 5}}},
{'6', 7, {{10, 0}, {0, 4}, {0, 10}, {10, 10}, {10, 5}, {5, 5}, {2, 7}}},
{'7', 3, {{0, 0}, {10, 0}, {10, 10}}},
{'7', 3, {{0, 0}, {10, 0}, {0, 10}}},
{'7', 2, {{10, 0}, {0, 10}}},
{'8', 4, {{0, 0}, {10, 10}, {0, 10}, {10, 0}}},
{'8', 10, {{3, 0}, {0, 2}, {0, 5}, {10, 7}, {10, 10}, {0, 10}, {0, 7}, {10, 4}, {10, 0}, {7, 0}}},
{'9', 5, {{10, 0}, {0, 0}, {0, 5}, {10, 5}, {10, 10}}},
{'9', 5, {{0, 0}, {0, 5}, {10, 5}, {10, 0}, {10, 10}}},
{'9', 4, {{0, 0}, {4, 6}, {10, 0}, {10, 10}}},

{'*', 4, {{10, 0}, {0, 10}, {0, 0}, {10, 10}}},
{'+', 4, {{0, 0}, {10, 10}, {10, 0}, {0, 10}}},
{'>', 3, {{0, 0}, {10, 5}, {0, 10}}},
{'<', 3, {{10, 0}, {0, 5}, {10, 10}}},
{'(', 4, {{10, 0}, {0, 0}, {0, 10}, {10, 10}}},
{')', 4, {{0, 0}, {10, 0}, {10, 10}, {0, 10}}},
{'~', 4, {{10, 0}, {6, 10}, {3, 0}, {0, 10}}},
{'~', 4, {{10, 10}, {6, 0}, {3, 10}, {0, 0}}},

{'/', 2, {{0, 10}, {10, 0}}},
{CHAR_ENTER, 2, {{0, 0}, {10, 10}}},
{CHAR_RIGHT, 3, {{0, 5}, {10, 5}, {0, 5}}},
{CHAR_LEFT, 3, {{10, 5}, {0, 5}, {10, 5}}},
{CHAR_TAB, 3, {{0, 10}, {0, 0}, {10, 0}}}
};

static char DOT_CHARACTERS[26] = {
	'^'/*A*/, '}'/*B*/, (char)'\0xa9'/*C*/, '&'/*D*/, '{'/*E*/, '\''/*F*/,
	'^'/*G*/, '"'/*H*/, '!'/*I*/, ', '/*J*/, '*'/*K*/, '`'/*L*/,
	'^'/*M*/, '#'/*N*/, '@'/*O*/, (char)'\0xa3'/*P*/, (char)'\0xd6'/*Q*/, (char)'\0xae'/*R*/,
	'$'/*S*/, '?'/*T*/, (char)'\0xac'/*U*/, '~'/*V*/, '%'/*W*/, '+'/*X*/,
	'&'/*Y*/, '='/*Z*/
};

#endif
