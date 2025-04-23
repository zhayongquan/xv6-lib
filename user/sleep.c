#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  if(argc <= 1){
    fprintf(2, "Usage: sleep <ticks>\n");
    exit(1);
  }

  int ticks = atoi(argv[1]);
  if(ticks < 0){
    fprintf(2, "sleep: invalid number of ticks: %s\n", argv[1]);
    exit(1);
  }

    printf("start: ticks=%d\n", uptime());
    sleep(ticks * 10);
    printf("end: ticks=%d\n", uptime());
    exit(0);
}
