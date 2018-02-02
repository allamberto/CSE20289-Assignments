#!/bin/sh
#Ana Luisa Lamberto

cowsay "Hello $USER, what question do you have for me today?"

signal(){
  shuf -n 1 << EOF | cowsay
  Bye Buddy. I hope you find your dad!
  BYE. BYE. BYE. (bye.. bye..)
  MOOOOOve on. Get out of here.
EOF
exit 1
}
trap signal INT TERM HUP

choose(){
  shuf -n 1 << EOF
    It is certain
    It is decidedly so
    Without a doubt
    Yes, definitely
    You may rely on it
    As I see it, yes
    Most likely
    Outlook good
    Yes
    Signs point to yes
    Reply hazy try again
    Ask again later
    Better not tell you now
    Cannot predict now
    Concentrate and ask again
    Don't count on it
    My reply is no
    My sources say no
    Outlook not so good
    Very doubtful
EOF
}

while true; do

  read QUESTION
  if [ "$QUESTION" != "" ]; then
    choose
    break
  fi
done
