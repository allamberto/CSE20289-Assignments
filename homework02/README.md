Homework 02
===========

#Activity 1
1) To check for no arguments, I used a test that checked to see if the number of command line arugments was equal to zero. If that was the case, then there were no arguments passed and a usage message was displayed.
2)I went through the textbook and determine which type of files require tar/zip. For tar, I read that different types of files require different flags to extract them. The gzip required the z flag while a bizip2 required a j flag. The textbook thoroughly described each type of tar file by name and what is required to extract it.
3)The most challenging aspect of writing this code hoenstly was reading the problem and thinking "I have no idea how to do any of this." That is a terrifying feeling. But once I focused on each small part, the code began to come together and made more sense to me so I was able to understand what needed to go in each loop and what was needed to fix each failure.

#Activity 2
1) I created a here document, used the shuf command to shuffle it, used a -n 1 flag to only return one saying.
2) I used the trap commmand to trap certain signals and call a signal function when the signals were used. This command used a similar shuf process to pick a random message and return an exit code.
3) I read input using a read command and I put it in a while loop so that the while loop only ends when the input doesn't equal blank space.
4)The most challengig aspect of this code was trying to figure out exact synatxes. I understand the concepts and what the commands do but I had to research a lot of teh exact synatx that makes it work.

#Activity 3
1) The first thing I did was to scan "xavier.h4x0r.space" for a HTTP port. I limited my search to a specific range of ports.
command: $ nmap -Pn xavier.h4x0r.space -p 9000-9999
output: PORT     STATE SERVICE
9104/tcp open  jetdirect
9206/tcp open  unknown
9522/tcp open  unknown

There are three open ports in the 9000-9999 range. 

2) Next, I tried to connect to each port with the nc command and the 9522 port brought me to a cowsay asking for my name.
command: nc xavier.h4x0r.space 9522
output: cowsay

3)The cowsay asked me for a message and I wasn't sure so it told me to go back to the DOORMAN or the BOBBIT. I'll come back to the cow later.

4) Next, I tried to curl into all of the open ports and this brought me to what I think is the DOORMAN cowsay. He is telling me that I need to access my password in Prof. Bui's directory and unlock the lockbox before I can move on.
command: curl xavier.h4x0r.space:9104
output: "Halt! Who goes there?" Cowsay

5) Next, I found my lockbox in Prof. Bui's public directory using the find command. 
command: find ~pbui/pub/oracle/lockboxes | grep alamber2
output: /afs/nd.edu/user15/pbui/pub/oracle/lockboxes/99270a26/c6278058/4c68ef14/db4c4983/51ce0241/alamber2.lockbox

6) Next I used the string command to crack the lockbox by creating a loop that goes through every output from the strings command and tests it on the lockbox. This resulted in a single password.
command: for string in $(strings /afs/nd.edu/user15/pbui/pub/oracle/lockboxes/99270a26/c62780lamber2.lockbox); do /afs/nd.edu/user15/pbui/pub/oracle/lockboxes/99270a26/c6278058/4c68ef14/db4c4983/51ce0241/alamber2.lockbox $string; done
output: 7b1591c5326b85eaff654616fa2af70d15f52c7f

7) I tried this password on the cow, but that wasn't the message he was looking for.

command: nc xavier.h4x0r.space 9522 7b1591c5326b85eaff654616fa2af70d15f52c7f
output: still the wrong message

7) I forgot that the doorman said to go back. I redid the curl command but this time added the /alamber2/passcode to the end of the command and this brought me to a moose who says he has been waiting for me. This has been a wild ride so far.
command: curl xavier.h4x0r.space:9104/alamber2/7b1591c5326b85eaff654616fa2af70d15f52c7f
output: "message BOBBIT" cowsay

8) I messaged BOBBIT on slack and he told me to tell the Oracle the following message: bnluem9yZTI9MTUxNzU1MjY0Nw==

9) I returned to the cowsay asking for a message.
command: nc xavier.h4x0r.space 9522

10) I typed my name as Ana and tried to deliver the message from BOBBIT but that didn't work. Update: I finally figured out that the cowsay wanted my netID not my name. It has asked me why it took me so long to get here, maybe next time ask for my netID cowsay.

11) I reached the oracle and he gave me my message and now code is raining. (:

