#!/bin/bash

# Functions

usage() {
    cat <<EOF
Usage: $(basename $0) [rotation]

This program will read from stdin and rotate the text by the specified
rotation.  If none is specified, then the default value is 13.
EOF
    exit $1
}

LOWERCASE=abcdefghijklmnopqrstuvwxyz
UPPERCASE=ABCDEFGHIJKLMNOPQRSTUVWXYZ

# Parse command-line options

ROTATE=13

if [ "$#" -gt 0 ]; then
  if [ x"$1" = x"-h" ]; then
    usage 0
  else
    ROTATE=$(($1 % 26))
  fi
fi

source_set() {
  echo $LOWERCASE$UPPERCASE
}

target_set() {
  TAILLOWER=$(echo $(source_set) | cut -c 1-$ROTATE) #cut one thru mod
  HEADLOWER=$(echo $(source_set) | cut -c $(($ROTATE + 1))-26) #the rest of the lowercase alaphabet
  TAILUPPER=$(echo $(source_set) | cut -c 27-$((26 + $ROTATE))) #cut one thru mod
  HEADUPPER=$(echo $(source_set) | cut -c $((27 + $ROTATE))-52) #the rest of the uppercase alaphabet
  echo $HEADLOWER$TAILLOWER$HEADUPPER$TAILUPPER 
}

# Filter pipeline
tr $(source_set) $(target_set)
