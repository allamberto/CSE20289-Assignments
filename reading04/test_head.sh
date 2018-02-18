#!/bin/bash

SCRIPT=head.py
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

printf " %-30s ... " "Usage"
./$SCRIPT -h 2>&1 | grep -i usage 2>&1 > /dev/null
if [ $? -ne 0 ]; then
    error "Failed Usage Test"
else
    echo "Success"
fi

for path in /etc/hosts /etc/passwd; do
    printf " %-30s ... " "Head on $path"
    ./$SCRIPT $path | diff -y - <(head $path) > $WORKSPACE/test
    if [ $? -ne 0 ]; then
	error "Failed on $path!"
    else
    	echo "Success"
    fi
done
    
printf " %-30s ... " "Head on stdin (implicit)"
cat /etc/passwd | ./$SCRIPT | diff -y - <(cat /etc/passwd | head) > $WORKSPACE/test
if [ $? -ne 0 ]; then
    error "Failed on $path!"
else
    echo "Success"
fi

printf " %-30s ... " "Head on stdin (explicit)"
cat /etc/passwd | ./$SCRIPT - | diff -y - <(cat /etc/passwd | head -) > $WORKSPACE/test
if [ $? -ne 0 ]; then
    error "Failed on $path!"
else
    echo "Success"
fi

for i in $(seq 10); do
    printf " %-30s ... " "Head -n $i"
    ./$SCRIPT -n $i /etc/passwd | diff -y - <(head -n $i /etc/passwd) > $WORKSPACE/test
    if [ $? -ne 0 ]; then
	error "Failed on $path!"
    else
	echo "Success"
    fi
done

echo "   Score $(echo "scale=2; (15 - $FAILURES) / 15.0 * 2.5" | bc)"
echo
