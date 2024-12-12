#!/bin/bash

input_file="test_grep.txt"
input_file2="test_grep2.txt"

flags=("-i" "-v" "-c" "-l" "-n" "-s" "-h")

grep_output_file="grep_output.txt"
s21_grep_output_file="s21_grep_output.txt"
echo "Tests without -e flag"
for flag in "${flags[@]}"; do
    echo "Flag $flag:"

    grep He $flag "$input_file" > "$grep_output_file"

    ./s21_grep He $flag "$input_file" > "$s21_grep_output_file"

    if diff "$grep_output_file" "$s21_grep_output_file"
    then
        echo "success"
    else
        echo "fail"
    fi
    echo "--------------------------"

done

echo ""
echo ""

echo "Tests with -e flag"
for flag in "${flags[@]}"; do
    echo "Flag $flag:"

    grep -e he $flag "$input_file" > "$grep_output_file"

    ./s21_grep -e he $flag "$input_file" > "$s21_grep_output_file"

    if diff "$grep_output_file" "$s21_grep_output_file"
    then
        echo "success"
    else
        echo "fail"
    fi
    echo "--------------------------"
done

echo ""
echo ""

echo "Tests with 2 files"
for flag in "${flags[@]}"; do
    echo "Flag $flag:"

    grep no $flag "$input_file" "$input_file2" > "$grep_output_file"

    ./s21_grep no $flag "$input_file" "$input_file2" > "$s21_grep_output_file"

    if diff "$grep_output_file" "$s21_grep_output_file"
    then
        echo "success"
    else
        echo "fail"
    fi
    echo "--------------------------"
done

echo ""
echo ""

echo "Tests with 2 patterns"
for flag in "${flags[@]}"; do
    echo "Flag $flag:"

    grep -e no -e by $flag "$input_file" "$input_file2" > "$grep_output_file"

    ./s21_grep -e no -e by $flag "$input_file" "$input_file2" > "$s21_grep_output_file"

    if diff "$grep_output_file" "$s21_grep_output_file"
    then
        echo "success"
    else
        echo "fail"
    fi
    echo "--------------------------"
done

rm "$grep_output_file" "$s21_grep_output_file"