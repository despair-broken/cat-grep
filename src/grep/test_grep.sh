#!/bin/bash

SUCCESS=0
FAIL=0
COUNTER=0
DIFF=""

all_flags=("-e" "-i" "-v" "-c" "-l" "-n")
bonus_flag=("-i" "-v" "-c" "-l" "-n")
dop_flags=("-iv" "-vi" "-ci" "-ic" "-in" "-ni" "-il" "-li" "-vc" "-cv" "-vl" "-lv" "-vn" "-nv" "-cl" "-lc" "-cn" "-nc" "-ln" "-nl")
f_pat=("test/pattern_1.txt" "test/pattern_2.txt")
patterns=("Depp" "english")
input_files=("test/test_1.txt" "test/test_2.txt")

echo " "
echo " ONE FILES "
echo " "
for flags in "${all_flags[@]}"
do
    for pattern in "${patterns[@]}"
    do
        for input_file in "${input_files[@]}"
        do
            echo "$flags $pattern $input_file :"
            ./s21_grep "$flags" "$pattern" "$input_file" > your_output.txt
            grep "$flags" "$pattern" "$input_file" > original_output.txt
            
            if diff -q your_output.txt original_output.txt >/dev/null 2>&1;
            then
                let "COUNTER++"
                let "SUCCESS++"
                echo "\033[92m$COUNTER\033[0m - Success"
            else 
                let "COUNTER++"
                let "FAIL++"
                echo "\033[31m$FAIL\033[0m - Fail"
            fi

            rm your_output.txt
            rm original_output.txt
        done
    done
done

echo " "
echo " TWO FILES "
echo " "
for flags in "${all_flags[@]}"
do
    for pattern in "${patterns[@]}"
    do
        for file_1 in "${input_files[@]}"
        do
            for file_2 in "${input_files[@]}"
            do
                if [ $file_1 != $file_2 ]
                then
                    echo "$flags $pattern $file_1 $file_2:"
                    ./s21_grep "$flags" "$pattern" "$file_1" "$file_2"> your_output.txt
                    grep "$flags" "$pattern" "$file_1" "$file_2" > original_output.txt
                    
                    if diff -q your_output.txt original_output.txt >/dev/null 2>&1;
                    then
                        let "COUNTER++"
                        let "SUCCESS++"
                        echo "\033[92m$COUNTER\033[0m/ - Success"
                    else 
                        let "COUNTER++"
                        let "FAIL++"
                        echo "\033[91m$COUNTER\033[0m/ - Fail"
                    fi

                    rm your_output.txt
                    rm original_output.txt
                fi
            done
        done
    done
done

                        echo "Total: $COUNTER, Success: $SUCCESS, Fail: $FAIL"