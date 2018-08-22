#include <gpib/ib.h>
#include <stdio.h>
#include <unistd.h>


#define DLY_BOARDID 0
#define DLY_PRIMARYADD 5
#define DLY_SECONDARYADD 0
#define DLY_TIMEOUT 10
#define DLY_EOS 1
#define DLY_EOT 0

int main(void){
  int fd;
  fd = ibdev(DLY_BOARDID, DLY_PRIMARYADD, DLY_SECONDARYADD, DLY_TIMEOUT, DLY_EOS, DLY_EOT);

  printf("connected to the delay at %d\n", fd);

  size_t written = ibwrt(fd, "DLY 10", 6);

  printf("written to the delay %d\n", written);
  ibonl(fd, 0);
  close(fd);


  return 0;
}
