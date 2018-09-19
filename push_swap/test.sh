#!/bin/bash

IN100=$(ruby -e "puts (0..99).to_a.shuffle.join(' ')")
IN500=$(ruby -e "puts (0..499).to_a.shuffle.join(' ')")
IN5=$(ruby -e "puts (1..5).to_a.shuffle.join(' ')")
BIN="./push_swap"
echo Sort 5
echo $IN5
$BIN $IN5 | wc -l

echo Sort 100
echo $IN100
$BIN $IN100 | wc -l

echo Sort 500
echo $IN500
$BIN $IN500 | wc -l
