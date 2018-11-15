#!/bin/bash

array=("item 1" "item 2" "item 3")
for i in "${array[@]}"; do   # The quotes are necessary here
    echo "$i"
done

list='"item 1" "item 2" "item 3"'
for i in $list; do
    echo $i
done
for i in "$list"; do
    echo $i
done
for i in ${array[@]}; do
    echo $i
done