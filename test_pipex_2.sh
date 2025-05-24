#!/bin/bash

BIN=./pipex_bonus
GREEN="\033[0;32m"
RED="\033[0;31m"
NC="\033[0m"

pass() {
    echo -e "${GREEN}[OK] $1${NC}"
}

fail() {
    echo -e "${RED}[FAIL] $1${NC}"
}

check_output() {
    if diff "$1" "$2" > /dev/null ; then
        pass "$3"
    else
        fail "$3"
        echo "Expected:"
        cat "$2"
        echo "Got:"
        cat "$1"
    fi
    rm -f "$1" "$2"
}

# Test 1: multiple commands
echo "one two three" > infile
$BIN infile "cat" "tr a-z A-Z" "wc -w" outfile
echo "3" > expected
cut -d' ' -f1 outfile > result
check_output result expected "Test multiple pipes with infile"

# Test 2: here_doc with transformation
rm -f outfile
$BIN here_doc END "tr a-z A-Z" "rev" outfile << EOF
hola mundo
esto es una prueba
END
EOF

cat > expected << EOF
ODNUM ALOH
ABEURP ANU SE OTSE
EOF

cp outfile result
check_output result expected "Test here_doc with multiline transformation"

# Test 3: bad command handling
echo "dummy" > infile
$BIN infile "badcommand" "wc -l" outfile 2> err.txt
if grep -Ei "not found|no such file|se encontró el comando|command not found" err.txt > /dev/null ; then
    pass "Test bad command error handling"
else
    fail "Test bad command error handling"
    cat err.txt
fi
rm -f err.txt infile outfile expected result

echo -e "\n${GREEN}All done.${NC} ✔️"
