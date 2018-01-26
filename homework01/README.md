Homework 01 (Collaborated w/ Angie Franco)
===========
#Activity 1

| Command                             | Elapsed Time  |
|-------------------------------------|---------------|
| cp ...                              | .135 seconds     |
| mv ...                              | .001 seconds     |
| mv ...                              | .041 seconds     |
| rm ...                              | .007 seconds     |

1) When the mv command is used to rename a file, it only deals with the single folder name and replacing the name attribute in the Inode. However when the program moves an entire folder, it must do so recursively, moving every file individually. Because the mv command must deal with each individual file instead of the single folder, the mv command takes longer the second time.

2) When you remove a file, you are only deleting the pointer to the file and not actually deleting a file. However when you move a file, the computer has to individually move each file. Deleting just a pointer to a file is faster than dealing with the actual file when you move it from one location to another.
#Activity 2
1) bc < math.txt
2) bc < math.txt > results.txt
3) bc < math.txt 2> /dev/null > results.txt
4) cat math.txt | bc 
When you use a pipeline, there are multiple commands that take an input and output for each command, resulting in a less efficient process. Redirection only takes one input and passes that output to another command, resulting in less input/output exchanges.

#Activity 3
1) cat /etc/passwd | grep /sbin/nologin | wc -l
answer: 50

2)ps e | grep bash | wc -l
answer: 3

3)du -a /etc/ 2> /dev/null | sort -g | tail -n5
answer: 
8284	/etc/selinux/targeted/policy
8556	/etc/gconf
8932	/etc/selinux/targeted
8952	/etc/selinux
39332	/etc/


4) who | sort | uniq | cut -d ' ' -f 1 | wc -l
answer: 26

#Activity 4
1)
a) First, I tried to control-c out of the program, but as the dragon said, "no dice." I tried running kill commands but I realized that I needed to get my command line back before I could run commands. I also tried killall TROLL but the program was still running.
b) Control-z was able to suspend the program. Then, I was able to use the ps command partnered with the grep TROLL command to get the PIDs of the TROLL program. Then, I used kill -9 PID to terminate all the TROLLs.

2) 
a) ps ux | grep TROLL | awk '{print $2}' | xargs kill -9 
The ps, grep, awk combo searchs for TROLL in all the programs running and isolates the PIDs. The xargs command takes this input, translates it into a list, and passes this list to the kill command to end them all.
b) killall -KILL TROLL 
The killall command sends signals to multiple processes matching the TROLL program. The KILL flag specifies that I want to terminate the program and TROLL is the name of the program that killall looks for.

3) killall -10 TROLL makes the program rain numbers. killall -7 TROLL makes it sing the wheel on the bus goes round and round. killall -14 plays WHAM's greatest hits. 

