#!/bin/sh

# Functions

usage() {
  cat << EOF
  Usage: broify.sh

  -d DELIM    Use this as the comment delimiter.
  -W          Don't strip empty lines.
EOF
  exit $1
}

DELIM=\# #default deliminator
BLANK=1 #controls what sed is called

Space(){
  if [ "$1" -eq "0" ]; then
    sed -e "s|$DELIM.*||" -e "s|\s*$||" #replace everything after DELIM with nothing and change everything after spaces to nothing
  else
    sed -e "s|$DELIM.*||" -e "s|\s*$||" -e "/^\s*$/d" #same as above but also deletes returns
  fi
}

# Parse command-line options
while [ "$#" -gt 0 ]; do
  case "$1" in
    -h) #usage
      usage 0
      ;;
    -d) #change deliminator
      DELIM=$2
      shift
      ;;
    -W) #keep returns
      BLANK=0
      ;;
  esac
  shift
done

Space $BLANK
