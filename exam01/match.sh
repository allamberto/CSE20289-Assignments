#!/bin/sh

# Functions

usage() {
    cat <<EOF
Usage: $(basename $0) [-n NUMBER -p PATTERN -s]

    -n NUMBER	Number of items to output (default is 10).
    -p PATTERN	Pattern to match.
    -s		Output items in sorted order.

  Extracts up to te first NUMBER items from STDIN that match specified PATTERN.
EOF
  exit $1
}

NUMBER=10
PATTERN="0"
CHOICE=0

action(){
  if [ $PATTERN == "0" ]; then
    usage 1
  elif [ "$1" -eq "1" ]; then
    grep -Eo "$PATTERN" | sort | head -n $NUMBER
  else
    grep -Eo "$PATTERN" | head -n $NUMBER
  fi
}

while [ "$#" -gt 0 ]; do
  case "$1" in
    -h) #usage
      usage 0
      ;;
    -p)
      PATTERN=$2
      shift
      ;;
    -n)
      NUMBER=$2
      shift
      ;;
    -s)
      CHOICE=1
      ;;
    -*)
      usage 1
      ;;
  esac
  shift
done

action $CHOICE

