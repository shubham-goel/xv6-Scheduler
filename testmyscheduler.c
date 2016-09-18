#include "param.h"
#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"
#include "fcntl.h"
#include "syscall.h"
#include "traps.h"
#include "memlayout.h"

void CPUbound() {
  int j=0;
  for (int i = 0; i < 20000000000; ++i)
  {
    j*=j;
  }
}

void newprocess(int prio) {
  int f = fork();
  if (f<0) {
    printf(1, "%d Priority: ??, ERROR in FORK:%d\n", getpid(), f);
  }

  if (f==0) {// Child
    printf(1, "%d Priority: ??, began at %d\n", getpid(), uptime());
    CPUbound();
    printf(1, "%d Ended at : %d\n", uptime());
    exit();
  }
}

int
main(int argc, char *argv[])
{
  printf(1, "\nStarted testmyscheduler(%d) at %d\n\n\n", getpid(), uptime());

  newprocess(2);
  sleep(20);
  newprocess(3);
  sleep(20);
  newprocess(4);
  sleep(20);
  newprocess(5);
  sleep(20);

  while(wait()!=-1);

  exit();
}
