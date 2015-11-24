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
*I realized an expansion of system call `exec()`. Now it supports executing script files and link to script file. Also i added a check on depth of recursion, in order to interrupt the program if depth of recursion will become too big.(when there aren't enough memory for correct system work).
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
+Jhon

*************************************
+I real
xv6 is a re-implementation of Dennis Ritchie's and Ken Thompson's Unix
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