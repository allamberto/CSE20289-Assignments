#!/bin/bash

WORKSPACE=/tmp/walk.$(id -u)
FAILURES=0

error() {
    echo "$@"
    [ -r $WORKSPACE/test ] && (echo; cat $WORKSPACE/test; echo)
    FAILURES=$((FAILURES + 1))
}

cleanup() {
    STATUS=${1:-$FAILURES}
    rm -fr $WORKSPACE
    rmdir walk.dir
    exit $STATUS
}

mkdir $WORKSPACE

trap "cleanup" EXIT
trap "cleanup 1" INT TERM

echo "Testing walk ..."

printf " %-40s ... " "walk (syscalls)"
if ! grep -q opendir walk.c || ! grep -q readdir walk.c || ! grep -q closedir walk.c || ! grep -q stat walk.c; then
    error "Failure"
else
    echo "Success"
fi

printf " %-40s ... " "walk (output)"
./walk | sort | diff -y - <(./walk.py | sort) > $WORKSPACE/test
if [ $? -ne 0 ]; then
    error "Failure"
else
    echo "Success"
fi

printf " %-40s ... " "walk (output w/ dir)"
mkdir walk.dir
./walk | sort | diff -y - <(./walk.py | sort) > $WORKSPACE/test
if [ $? -ne 0 ]; then
    error "Failure"
else
    echo "Success"
fi

printf " %-40s ... " "walk (valgrind)"
valgrind --leak-check=full ./walk &> $WORKSPACE/test
if [ "$(awk '/ERROR SUMMARY/ {print $4}' $WORKSPACE/test)" -ne 0 ]; then
    error "Failure"
else
    echo "Success"
fi

TESTS=$(($(grep -c Success $0) - 1))
echo "   Score $(echo "scale=2; ($TESTS - $FAILURES) / $TESTS.0 * 2.0" | bc | awk '{printf "%0.2f\n", $0}')"
echo
