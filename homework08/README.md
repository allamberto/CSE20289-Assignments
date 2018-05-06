Homework 08
===========

## Strace Output

### `duplicate`
% time     seconds  usecs/call     calls    errors syscall
------ ----------- ----------- --------- --------- ----------------
 73.33    0.000066           3        24        18 stat
 26.67    0.000024           3         9           read
  0.00    0.000000           0         7           write
  0.00    0.000000           0        27        24 open
  0.00    0.000000           0         4           close
  0.00    0.000000           0         2           fstat
  0.00    0.000000           0         2           lseek
  0.00    0.000000           0         8           mmap
  0.00    0.000000           0         3           mprotect
  0.00    0.000000           0         1           munmap
  0.00    0.000000           0         1           brk
  0.00    0.000000           0         1         1 access
  0.00    0.000000           0         1           execve
  0.00    0.000000           0         1           arch_prctl
------ ----------- ----------- --------- --------- ----------------
100.00    0.000090                    91        43 total


### `dd`

% time     seconds  usecs/call     calls    errors syscall
------ ----------- ----------- --------- --------- ----------------
 68.49    0.000150           3        49        41 open
 31.51    0.000069           3        24        18 stat
  0.00    0.000000           0        13           read
  0.00    0.000000           0        10           write
  0.00    0.000000           0        11           close
  0.00    0.000000           0         7           fstat
  0.00    0.000000           0         1           lseek
  0.00    0.000000           0        17           mmap
  0.00    0.000000           0         7           mprotect
  0.00    0.000000           0         2           munmap
  0.00    0.000000           0         3           brk
  0.00    0.000000           0         6           rt_sigaction
  0.00    0.000000           0         1           rt_sigprocmask
  0.00    0.000000           0         1         1 access
  0.00    0.000000           0         1           dup2
  0.00    0.000000           0         1           execve
  0.00    0.000000           0         1           getrlimit
  0.00    0.000000           0         1           arch_prctl
  0.00    0.000000           0         2         1 futex
  0.00    0.000000           0         1           set_tid_address
  0.00    0.000000           0         1           set_robust_list
------ ----------- ----------- --------- --------- ----------------
100.00    0.000219                   160        61 total


### `search`

% time     seconds  usecs/call     calls    errors syscall
------ ----------- ----------- --------- --------- ----------------
 79.34    0.000096           4        24        18 stat
 20.66    0.000025           3         8           mmap
  0.00    0.000000           0         1           read
  0.00    0.000000           0         2           write
  0.00    0.000000           0        27        25 open
  0.00    0.000000           0         2           close
  0.00    0.000000           0         2           fstat
  0.00    0.000000           0         1         1 lstat
  0.00    0.000000           0         3           mprotect
  0.00    0.000000           0         1           munmap
  0.00    0.000000           0         1           brk
  0.00    0.000000           0         1         1 access
  0.00    0.000000           0         1           execve
  0.00    0.000000           0         1           arch_prctl
------ ----------- ----------- --------- --------- ----------------
100.00    0.000121                    75        45 total


### `find`

% time     seconds  usecs/call     calls    errors syscall
------ ----------- ----------- --------- --------- ----------------
 50.72    0.000070           1        78        66 open
 49.28    0.000068           3        24        18 stat
  0.00    0.000000           0        10           read
  0.00    0.000000           0         4           write
  0.00    0.000000           0        14           close
  0.00    0.000000           0        10           fstat
  0.00    0.000000           0        24           mmap
  0.00    0.000000           0        13           mprotect
  0.00    0.000000           0         3           munmap
  0.00    0.000000           0         3           brk
  0.00    0.000000           0         2           rt_sigaction
  0.00    0.000000           0         1           rt_sigprocmask
  0.00    0.000000           0         2         1 ioctl
  0.00    0.000000           0         1         1 access
  0.00    0.000000           0         1           execve
  0.00    0.000000           0         1           uname
  0.00    0.000000           0         3           fchdir
  0.00    0.000000           0         1           getrlimit
  0.00    0.000000           0         1           statfs
  0.00    0.000000           0         1           arch_prctl
  0.00    0.000000           0         2         1 futex
  0.00    0.000000           0         1           set_tid_address
  0.00    0.000000           0         1         1 newfstatat
  0.00    0.000000           0         1           set_robust_list
------ ----------- ----------- --------- --------- ----------------
100.00    0.000138                   202        88 total


## Questions

1. Describe the differences you see between the number and type of system calls
   used by your utilities as compared to the standard Unix programs.

   The dd program makes more system calls than the duplicate code and it makes the same system calls plus extra ones that I don't recognize. The duplicate program has less errors, less system calls, and less time (almost three times less) than dd. Similar problems occur for find. Find takes twice as many system calls as search. It has double the errors and takes a few seconds longer. The main difference between the standard Unix programs is that most of their time is spent using the open system call, while search and duplicate focus primarily on stat.

2. Did you notice anything surprising about the trace of your utilities or the
   trace of the standard Unix programs? Which implementations are faster or
   more efficient?  Explain.

   It was surprising that I could write code more efficient than the standard Unix library. It was also surprising that stat took longer than every other system call combined for the system call programs and open took almost no time, but for the standard library it was vice versa. The system calls were faster and more efficient (way less errors) than the standard Unix commands because system calls are direct communication with the kernel while standard Unix programs have to span another level to communicate with the kernel by using system calls.
