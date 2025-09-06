#!/bin/bash

sum=0
for num in "$@"; do
    sum=$((sum + num))
done

average=$((sum / $#))
echo "Количество чисел: $#"
echo "Среднее: $average"