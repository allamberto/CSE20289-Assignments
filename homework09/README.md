Homework 09
===========
# Question 1

- No arguments passed to moveit.
  If I took out my usage trap for no arguments, the first system call to fail would be fork because the path would be NULL since I wasn't able to write anything from the files to a temporary variables and pass it to edit files. This is why we check to make sure files isn't null after we fill it.

- $EDITOR environmental variable is not set.
  If there is no environmental variable, getenv() would return NULL. This is why we check if the value returned by getenv is null and replace it's current value with an editor of our choice.

- User has run out of processes.
  If the user has run out of processes, the user would not be able to fork() a clone process because a new one can't be created. This is why we check if fork failed by checking if the pid returned is less than one and returning failure.

- $EDITOR program is not found.
  If editor isn't found, exec would fail because the command passed would be NULL. To catch this, we use underscore-exit(EXIT_FAILURE) to catch if the exec fails so it will only be called if the exec fails.

- Temporary file is deleted before moving files.
  If the temporary file is deleted, then the fdopen system callwould fail since a stream can't be opened from a NULL file. This is why we check if fdopen fails and returns zero.

- Destination path is not writable.
  As Professor Bui said in class exec may fail when given a bad path but it isn't guaranteed. If exec doesn't fail, rename will definitely since the old path does not exist. In order to avoid this, we check to make sure pass exists in our main before passing it to edit files.

# Question 2
- This isn't a good idea because as Bui says, never share. By connecting these two processes, unnecessary connections have been made that could cause the process to fail if any of its parts fail. For example, what if alarm fails? It also removes the concurrency from the program, which could cause gridlock, circular dependencies, and race conditions. What if I know Professor Bui says to be lazy, but this would be too lazy. 
