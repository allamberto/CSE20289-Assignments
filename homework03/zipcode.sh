#!/bin/bash

# Functions

usage() {
  cat << EOF
  Usage: zipcode.sh

  -c      CITY    Which city to search
  -s      STATE   Which state to search (Indiana)

If no CITY is specified, then all the zip codes for the STATE are displayed.
EOF
}

doSearch(){
  if [ "$1" = "0" ]; then
    curl -sL http://www.zipcodestogo.com/$STATE/ | grep -b -1 ">$CITY<" | grep -Po ">\d{5}<" | grep -Po "\d{5}" | sort | uniq
  else #find 5 digit numbers surrounded by ><, replace >< with nothing
    curl -sL http://www.zipcodestogo.com/$STATE/ | grep -Po ">\d{5}<" | grep -Po "\d{5}" | sort | uniq
  fi
}

# Parse command-line options
STATE='Indiana'

CHOICE=1 #controls what type of grep is called

while [ $# -gt 0 ]; do
  case "$1" in
    -h)
      usage 0
      ;;
    -c)
      CITY=$2
      CHOICE=0
      shift
      ;;
    -s)
      STATE=$2
      STATE="$(sed s/' '/%20/ <<<$STATE)"
      shift
      ;;
    esac
    shift
done

doSearch $CHOICE
