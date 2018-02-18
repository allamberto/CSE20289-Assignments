#!/bin/bash

SCRIPT=exists.py
WORKSPACE=/tmp/$SCRIPT.$(id -u)
FAILURES=0

error() {
    echo "$@"
    echo
    [ -r $WORKSPACE/test ] && cat $WORKSPACE/test
    echo
    FAILURES=$((FAILURES + 1))
}

cleanup() {
    STATUS=${1:-$FAILURES}
    rm -fr $WORKSPACE
    exit $STATUS
}

mkdir $WORKSPACE

trap "cleanup" EXIT
trap "cleanup 1" INT TERM

echo "Testing $SCRIPT ..."

printf " %-30s ... " "exists.py *"
./$SCRIPT * > /dev/null
if [ $? -ne 0 ]; then
    error "Failure"
else
    echo "Success"
fi

printf " %-30s ... " "exists.py * ASDF"
./$SCRIPT * ASDF > /dev/null
if [ $? -ne 1 ]; then
    error "Failure"
else
    echo "Success"
fi

echo "   Score $(echo "scale=2; (2 - $FAILURES) / 2.0 * 0.5" | bc)"
echo
