Ana Luisa Lamberto

Activity 1

1) To parse command line arguments, I used a while loop that ran through each command line arguments
and check if it was a -h flag. If it wasn't, then the code calculates the modulus since the only other command line argument is a rotation number.

2) The source set was just a combination of the uppercase and lowercase variables.

3) The target set is constructed of four variables. The first is every lower case number between one through the rotation number calculated earlier. The second is the letter after the rotation variable until the end of the lower case alphabet. The uppercase variables start at 27, after the lower case variables end. It goes until 27 + rotation variable so the uppercase set matches the lowercase set. The second uppercase variable goes from one after this rotation variable to 52, the end of both alphabet's combined.

4) By tr-ing the two sets, the proper letters match up and replace it each other.

Activity 2

1) If arguments were passed at the command line, they were caught in a while statement. Once in the while statement, I used a switch case to catch each flag. I also used shift to control the variables so I could dave the arguments after the flag.

2) I used a sed to remove the comments. I replaced the delimiter and everything after it was nothing using the replacement function in sed.

3) I removed the empty lines using the delete function in sed. I checked where space was the first and last character in the line and I removed the entire line.

4) The delimiter is defaulted as # but if -d is passed the user can change this variable. If the -W flag is passed, the BLANK variable changes, causing the function to use a different version of sed that doesn't remove return spaces.

Activity 3

1) If arguments were passed at the command line, they were caught in a while statement. Once in the while statement, I used a switch case to catch each flag. The usage flag calls the usage function with the proper exit code. The -c catches the city name. It also checks to see if the argument after the current argument is a word. If it is, it adds it on to the current city name. It also removes all the " " using sed and adds an extra shift to account for this variable add-on. The -s flag first checks if the variable will be two words by checking if the first word is North, South, or New. If so, it takes both words and saves them into the State variable. Else, it just saves the one word.

2) I used sed by specifying five digits inside ><. This required the -P advanced flag.

3) Without the city, I searched for 5 numbers inside ><. I then used sed to remove the >< and -o to only print the numbers. With the city, I searched for the HTML code including the city and the zip. I then used sed to remove the city and everything else leading up to >.
