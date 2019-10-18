#!/bin/bash


lex sql_par.l
yacc sql_par.y
gcc y.tab.c -ly -ll -lm
./a.out