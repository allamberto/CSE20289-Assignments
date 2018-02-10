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
    #find zipcode with city, replace everything before > with nothing, replace evreything after < with nothing
    curl -s http://www.zipcodestogo.com/$STATE/ | grep -Po "/$CITY/.*>\d{5}<" | sed -e "s|/$CITY/.*>||" -e 's|<||' | sort | uniq
  else #find 5 digit numbers surrounded by ><, replace >< with nothing
    curl -s http://www.zipcodestogo.com/$STATE/ | grep -Po '>\d{5}<' | sed -e 's|>||' -e 's|<||' | sort | uniq
  fi
}

# Parse command-line options
STATE='Indiana'

CHOICE=1 #controls what type of grep is called

while [ $# -gt 0 ]; do
  case "$1" in
    -h) #usage
      usage 0
      ;;
    -c) #search by city
      CITY=$2
      CHOICE=0
      shift
      if [[ $2 == [[:alpha:]]* ]]; then #if next argument is another word, add to city name
        CITY="$CITY $2"
        #echo $CITY | sed "s/\"//" #remove " "
        shift
      fi
      ;;
    -s) #search by state
      if [[ $2 == *New ]]; then
        STATE="$2%20$3"
        echo $STATE
        shift
      elif [[ $2 == *North ]]; then
        STATE="$2%20$3"
        shift
      elif [[ $2 == *South ]]; then #check for two name states
        STATE="$2%20$3" #change to %20 for URL
        shift
      #echo $STATE | sed "s/\"//" #remove " "
      else #if state is one word
        STATE=$2
        #| sed -e "s/^\"//" -e "s/\"$//" #remove " "
      fi
      shift
      ;;
  esac
  shift
done

doSearch $CHOICE
