#!/bin/bash


lex calc.l
yacc calc.y
gcc y.tab.c -ly -ll -lm
./a.out