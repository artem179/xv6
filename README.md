# **Project XV6**
-------------
## Student
Artem Shafarostov
- - - - - - - - - 
## Group
National Research University Higher School of Economics, Faculty of computer science, Applied Mathematics and Informatics, Group 144
* * * * * * * * * * * *
## The list of tasks for the second deadline
* To realize expansion of system call `exec()` for executable script files.
+ To realize system call `mkfifo()` 
* To renew the file `README.md`. Add new information about chosen tasks from the list ["Final Estimation"][id] with more detailed description. 
[id]: http://wiki.cs.hse.ru/%D0%9A%D0%A1:2015:%D0%9F%D1%80%D0%BE%D0%B5%D0%BA%D1%82:xv6#.D0.98.D1.82.D0.BE.D0.B3.D0.BE.D0.B2.D0.B0.D1.8F_.D0.BE.D1.86.D0.B5.D0.BD.D0.BA.D0.B0
---------------------------------------------------
## The list of tasks which i did
* I implemented an expansion of system call `exec()`. Now it supports executing script files and link to script file. Also i added a check on depth of recursion, in order to interrupt the program if depth of recursion will become too big.(when there aren't enough memory for correct system work).
Some examples of working system call `exec()`:
```
$ cat > 1
#!cat
Jhon
$ 1
#!cat
Jhon
```

```
$ cat > 2
#!echo file
what?
$ 2
file 2
```

```
$ cat > 2
#!echo file
what?
$ 2
file 2
```

```
$ cat > 3
#!4
$ cat > 4
#!cat
Hello
$ 3
#!cat
Hello
#!4
```

```
$ cat > 3
#!4
$ cat > 4
#!3
$ 3
exec 3 failed
$ 4
exec 4 failed
```
+ I implemented system call `mkfifo()`. For it I used xv6-unnamed-pipe. I added new type of file like a FIFO and also added a block, which will work till the opponent connects to another end of pipe. I fixed a bug, which occured when user wrote command `ls` (for example) after created FIFO file. Just added one more flag named NONBLOCK and `if()` which passed 'FIFO-part of code'.
Some examples of working system call `mkfifo()`:
```
$ mkfifo NamedPipe
$ echo Hi all > NamedPipe &
$ wc < NamedPipe
zombie!
1 2 7
```   
*************************************
##The list of tasks for the last deadline
* To add file system permissions (without group of users), to implement enter to the system by password (hash), safe change user password.
+ To implement virtual catalogue (`/proc`).
* To implement mechanism unreliable signals.
----------------------------------------------------------------------------- 
##DEADLINE
* I fixed bug in mkfifo, now it works correct.
Some examples of working system call `mkfifo()`:
```
$ mkfifo NamedPipe
$ echo Hi all > NamedPipe &
$ wc < NamedPipe
zombie!
1 2 7
$ echo Hi all > NamedPipe &
$ wc < NamedPipe
zombie!
1 2 7
```
+ I implemented system calls `up()` and `down()` for binary semaphore. I made 10 mutexs, which can take only two states: up and down. Also I created test for checking mutex work ( [[`Testsem.c` | Testsem.c]] ).
Some examples of working mutex:
```
$ Testsem
1 0
1 1
1 2
1 3
1 4
1 5
1 6
1 7
1 8
1 9
1 10
1 11
1 12
1 13
1 14
1 15
1 16
1 17
1 18
1 19
1 20
1 21
1 22
1 23
1 24
1 25
1 26
1 27
1 28
1 29
1 30
1 31
1 32
1 33
1 34
1 35
1 36
1 37
1 38
1 39
1 40
1 41
1 42
1 43
1 44
1 45
1 46
1 47
1 48
1 49
1 50
1 51
1 52
1 53
1 54 
1 55
1 56
1 57
1 58
1 59
1 60
1 61
1 62
1 63
1 64
1 65
1 66
1 67
1 68
1 69
1 70
1 71
1 72
1 73
1 74
1 75
1 76
1 77
1 78
1 79
1 80
1 81
1 82
1 83
1 84
1 85
1 86
1 87
1 88
1 89
1 90
1 91
1 92
1 93
1 94
1 95
1 96
1 97
1 98
1 99
2 0
2 1
2 2
2 3
2 4
2 5
2 6
2 7
2 8
2 9
2 10
2 11
2 12
2 13
2 14
2 15
2 16
2 17
2 18
2 19
2 20
2 21
2 22
2 23
2 24
2 25
2 26
2 27
2 28
2 29
2 30
2 31
2 32
2 33
2 34
2 35
2 36
2 37
2 38
2 39
2 40
2 41
2 42
2 43
2 44
2 45
2 46
2 47
2 48
2 49
2 50
2 51
2 52
2 53
2 54
2 55
2 56
2 57
2 58
2 59
2 60
2 61
2 62
2 63
2 64
2 65
2 66
2 67
2 68
2 69
2 70
2 71
2 72
2 73
2 74
2 75
2 76
2 77
2 78
2 79
2 80
2 81
2 82
2 83
2 84
2 85
2 86
2 87
2 88
2 89
2 90
2 91
2 92
2 93
2 94
2 95
2 96
2 97
2 98
2 99
zombie!
zombie!
$
```
*****************************************************************************
+ I realxv6 is a re-implementation of Dennis Ritchie's and Ken Thompson's Unix
Version 6 (v6).  xv6 loosely follows the structure and style of v6,
but is implemented for a modern x86-based multiprocessor using ANSI C.

ACKNOWLEDGMENTS

xv6 is inspired by John Lions's Commentary on UNIX 6th Edition (Peer
to Peer Communications; ISBN: 1-57398-013-7; 1st edition (June 14,
2000)). See also http://pdos.csail.mit.edu/6.828/2012/v6.html, which
provides pointers to on-line resources for v6.

xv6 borrows code from the following sources:
    JOS (asm.h, elf.h, mmu.h, bootasm.S, ide.c, console.c, and others)
    Plan 9 (entryother.S, mp.h, mp.c, lapic.c)
    FreeBSD (ioapic.c)
    NetBSD (console.c)

The following people have made contributions:
    Russ Cox (context switching, locking)
    Cliff Frey (MP)
    Xiao Yu (MP)
    Nickolai Zeldovich
    Austin Clements

In addition, we are grateful for the bug reports and patches contributed by
Silas Boyd-Wickizer, Peter Froehlich, Shivam Handa, Anders Kaseorg, Eddie
Kohler, Yandong Mao, Hitoshi Mitake, Carmi Merimovich, Joel Nider, Greg Price,
Eldar Sehayek, Yongming Shen, Stephen Tu, and Zouchangwei.

The code in the files that constitute xv6 is
Copyright 2006-2014 Frans Kaashoek, Robert Morris, and Russ Cox.

ERROR REPORTS

If you spot errors or have suggestions for improvement, please send
email to Frans Kaashoek and Robert Morris (kaashoek,rtm@csail.mit.edu). 

BUILDING AND RUNNING XV6

To build xv6 on an x86 ELF machine (like Linux or FreeBSD), run "make".
On non-x86 or non-ELF machines (like OS X, even on x86), you will
need to install a cross-compiler gcc suite capable of producing x86 ELF
binaries.  See http://pdos.csail.mit.edu/6.828/2014/tools.html.
Then run "make TOOLPREFIX=i386-jos-elf-".

To run xv6, install the QEMU PC simulators.  To run in QEMU, run "make qemu".

To create a typeset version of the code, run "make xv6.pdf".  This
requires the "mpage" utility.  See http://www.mesa.nl/pub/mpage/.