#!/bin/bash
input_file="test_cat.txt"
flags=("-n" "-b" "-s" "-e" "-t" "-v")
cat_output_file="cat_output.txt"
s21_cat_output_file="s21_cat_output.txt"

for flag in "${flags[@]}"; do
    echo "Tecт флага $flag:"

    cat $flag "$input_file" > "$cat_output_file"

    ./s21_cat $flag "$input_file" > "$s21_cat_output_file"

    if diff "$cat_output_file" "$s21_cat_output_file" 
    then
        echo "робит"
    else
        echo "не робит"
    fi

done
rm "$cat_output_file" "$s21_cat_output_file"