#include "types.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "defs.h"
#include "x86.h"
#include "elf.h"

int Myexec(char *, char**, struct inode *, int depth);

int depth = 0;

int
exec(char *path, char **argv)
{
  char *s, *last;
  int i, off;
  uint argc, sz, sp, ustack[3+MAXARG+1];
  struct elfhdr elf;
  struct inode *ip;
  struct proghdr ph;
  pde_t *pgdir, *oldpgdir;

  begin_op();
  if((ip = namei(path)) == 0){
    end_op();
    return -1;
  }
  ilock(ip);
  pgdir = 0;

  // Check ELF header
  if(readi(ip, (char*)&elf, 0, sizeof(elf)) < sizeof(elf)) {
    return Myexec(path, argv, ip, ++depth);
  }
  if(elf.magic != ELF_MAGIC) {
    return Myexec(path, argv, ip, ++depth);
  }

  if((pgdir = setupkvm()) == 0)
    goto bad;

  // Load program into memory.
  sz = 0;
  for(i=0, off=elf.phoff; i<elf.phnum; i++, off+=sizeof(ph)){
    if(readi(ip, (char*)&ph, off, sizeof(ph)) != sizeof(ph))
      goto bad;
    if(ph.type != ELF_PROG_LOAD)
      continue;
    if(ph.memsz < ph.filesz)
      goto bad;
    if((sz = allocuvm(pgdir, sz, ph.vaddr + ph.memsz)) == 0)
      goto bad;
    if(loaduvm(pgdir, (char*)ph.vaddr, ip, ph.off, ph.filesz) < 0)
      goto bad;
  }
  iunlockput(ip);
  end_op();
  ip = 0;

  // Allocate two pages at the next page boundary.
  // Make the first inaccessible.  Use the second as the user stack.
  sz = PGROUNDUP(sz);
  if((sz = allocuvm(pgdir, sz, sz + 2*PGSIZE)) == 0)
    goto bad;
  clearpteu(pgdir, (char*)(sz - 2*PGSIZE));
  sp = sz;

  // Push argument strings, prepare rest of stack in ustack.
  for(argc = 0; argv[argc]; argc++) {
    if(argc >= MAXARG)
      goto bad;
    sp = (sp - (strlen(argv[argc]) + 1)) & ~3;
    if(copyout(pgdir, sp, argv[argc], strlen(argv[argc]) + 1) < 0)
      goto bad;
    ustack[3+argc] = sp;
  }
  ustack[3+argc] = 0;

  ustack[0] = 0xffffffff;  // fake return PC
  ustack[1] = argc;
  ustack[2] = sp - (argc+1)*4;  // argv pointer

  sp -= (3+argc+1) * 4;
  if(copyout(pgdir, sp, ustack, (3+argc+1)*4) < 0)
    goto bad;

  // Save program name for debugging.
  for(last=s=path; *s; s++)
    if(*s == '/')
      last = s+1;
  safestrcpy(proc->name, last, sizeof(proc->name));

  // Commit to the user image.
  oldpgdir = proc->pgdir;
  proc->pgdir = pgdir;
  proc->sz = sz;
  proc->tf->eip = elf.entry;  // main
  proc->tf->esp = sp;
  switchuvm(proc);
  freevm(oldpgdir);
  depth = 0;
  return 0;

 bad:
  if(pgdir)
    freevm(pgdir);
  if(ip){
    iunlockput(ip);
    end_op();
  }
  depth = 0;
  return -1;
}

int Myexec(char *path, char **argv, struct inode *ip, int depth) {
    char *buf = kalloc();
    if(depth > 5)
         goto bad;
    int readn;
    readn = readi(ip, buf, 0, PGSIZE);
    if(!((readn >= 2) && (buf[0] == '#') && (buf[1] == '!'))){
        //cprintf("pop");
        goto bad;
    }
    int offsets[MAXARG];
    int first_ind = 1;
    int index = 0;
    int i;
    for(i = 2; (i < PGSIZE); ++i) {
        if((buf[i] != ' ') && (first_ind)) {
            if(index > MAXARG)
                goto bad;
            offsets[index] = i;
            ++index;
            first_ind = 0;
        } else {
            if(buf[i] == ' ') {
                buf[i] = '\0';
                first_ind = 1;
            } else {
                if(buf[i] == '\n') {
                    buf[i] = '\0';
                    break;
                }
            }
        }
    } // For example offsets[0] - it's offset from begin of string buf to begin of path to intr
    //Insert first elements to the massive argum
    int OffSize = index;

    int argc = 0;
    for(; argv[argc]; ++argc);

    if(argc + OffSize >= MAXARG) {
        //cprintf("pop2");
        goto bad;
    }

    for(i = argc - 1; i > -1; --i)
        argv[i + OffSize] = argv[i];
    argv[argc + OffSize] = 0;
    for(i = 0; i < OffSize; ++i) {
        argv[i] = buf + offsets[i];
      //  cprintf("%s\n", argv[i]);
    }
    iunlockput(ip);
    end_op();
    ip = 0;
   // cprintf("lol");
    int res;
   // cprintf("%s\n", argv[0]);
    res = exec(argv[0], argv); //Глеб говорит на 5
    kfree(buf);
    depth = 0;
    return res;
    bad:
        if(ip){
            iunlockput(ip);
            end_op();
        }
        kfree(buf);
        depth = 0;
        return -1;
}
