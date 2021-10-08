#!/bin/bash

RED='\033[0;31m'
NC='\033[0m'

# Make sure file exists
if [ ! -f "binarycalc" ]; then
    echo "Run make to compile your code"
    exit 1
fi

# Run a test
run_test () {
    # Parameters
    FORMULA=$1 # Formula to run
    EXPECTED_A=`echo -e $2` # Expected output after completing part A
    EXPECTED_B=`echo -e $3` # Expected output after completing part B

    echo "*****************************************************"
    printf "%-40s%s" "$FORMULA"

    # Run binarycalc
    OUTFILE=$(mktemp /tmp/binarycalc_test.XXXXXX)
    ./binarycalc "$FORMULA" > $OUTFILE
    ACTUAL_A=`head -n 1 $OUTFILE | tr -d '\0'`
    ACTUAL_B=`tail -n +2 $OUTFILE | tr -d '\0'`

    grep -Pa "\x00" $OUTFILE > /dev/null
    if [ $? -eq 0 ]; then
	echo -e "FAILED: EXTRA NULL CHARS\n"
	grep -Pa "\x00" $OUTFILE | sed -e 's/\x00/\\0/g'
    elif [ "$ACTUAL_A" != "$EXPECTED_A" ]; then
        echo -e "PART A FAILED"
        echo -e "\nExpected output for part A:"
        echo "$EXPECTED_A"
        echo -e "\nActual output for part A:"
        echo "$ACTUAL_A"
    elif [ "$ACTUAL_B" != "$EXPECTED_B" ]; then 
        echo -e "PART B FAILED"
        echo -e "\nExpected output for part B:"
        echo "$EXPECTED_B"
        echo -e "\nActual output for part B:"
        echo "$ACTUAL_B"
    else
        echo -e "CORRECT"
    fi
    echo ""
    rm $OUTFILE
}

# Valid formulas
run_test "1 + 0" "00000001 + 00000000" "00000001 + 00000000\n00000001"
run_test "101 ^ 10" "00000101 ^ 00000010" "00000101 ^ 00000010\n00000111"
run_test "~111 & 000" "~00000111 & 00000000" "11111000 & 00000000\n00000000"
run_test "10101010 + -01010101" "10101010 + -01010101" "10101010 + 10101011\n01010101\nUnderflow"

run_test "1000000 + 1000000" "01000000 + 01000000" "01000000 + 01000000\n10000000\nOverflow"
run_test "~10101 & 1100" "~00010101 & 00001100" "11101010 & 00001100\n00001000"


# Invalid formulas
run_test "1+ 0" "Invalid binary formula" ""
run_test "111" "Invalid binary formula" ""
run_test "1 * 1" "Invalid binary formula" ""
run_test "11 ^ 0~0" "Invalid binary formula" ""
run_test "0 +" "Invalid binary formula" ""
run_test "0" "Invalid binary formula" ""
run_test "0 0" "Invalid binary formula" ""
run_test "0000000000 + 000" "Invalid binary formula" ""
run_test "00000 + 00011111111" "Invalid binary formula" ""
run_test "I love fragarances, it makes me very happy to smell unique fragrances, however, oddly enough, I don't have a favorite cologne." "Invalid binary formula" ""
