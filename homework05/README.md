Homework 05
===========

# Describe how you implemented the hulk.py script. In particular, briefly discuss:

- How you generated all the candidate password combinations.
  - For every letter in the alphabet, I made a recursive call to the permutations function with the previous list of permutations generated with the previous length. I yielded each list returned by the function but I also added the current letter I was on to each string in the list. My final base case was when length equaled one, since there can't be a list of length zero.

- How you filtered the candidates to only contain valid passwords.
  - I used a list comprehension to filter the list. I took each permutation with its proper prefix and for each permutation, I translated it to sha1 hash and checked if it was in the list by using an if in a list comprehension. If it was in the list, I returned it from the smash function.

- How you handled processing on multiple cores.
  - I used a prefix of length one run at the same time as the rest of the permutation. I used the alphabet as my length one prefix. I created a multprocessing object that called smash with these prefixes to check if they were in the hash list.

- How you verified that your code works properly.
  - I checked each function by printing out its output and running the given tests on it before moving on to the next to make sure it was working properly. I ran all the tests successfully on my laptop. I also printed all of my output before I used it in order to make sure I was using the proper data before I fed it to a function. Lastly, I got 6000 passwords from the list.

# Complete the following table for passwords of length 5:
# Processes	Time
- 1	          2m54.054s
- 2           0m34.426s
- 4           0m53.671s
- 6           1m14.964s
- 8           1m23.423s

- The length of processes exponentially decreased with the use of the first core but more cores than that caused a delay although still faster.

# From your experience in this project and recalling your Discrete Math knowledge, what would make a password more difficult to brute-force: more complex alphabet or longer password? Explain.
  - A longer password would make the password more difficult to crack because each increase in length increases the number of permutations exponentially. With each increase, it takes a great jump in time and memory to crack brute-force style. For example, the jump from length five to length six is five minutes to forty minutes.
