#!/bin/bash

echo "Enter the program file"
read prog_file
lex $prog_file
gcc lex.yy.c -ll
printf "Enter 1 to give input file\nEnter 2 to give input from console\n"
read option
if [ "$option" -eq 1 ]
then
    echo "Enter the input filename"
    read inp_file
    ./a.out<$inp_file
else
    echo "Enter console input"
    ./a.out
fi
