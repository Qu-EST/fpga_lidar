#include "lidar.h"



int changeDelay(int fd, float dly){
  char command[15] = "";
  char value[10] = "";
  int write_len;
  strcat(command, "DLY ");
  ftoa(dly, value, 3);
  strcat(command, value);
  write_len = ibwrt(fd, command, strlen(command));
  if(write_len<0)
    return write_len;

  return 0;
}
float  getDelay(int fd);


int openDelay(){
  //  ibdev(
  int fd;
  fd = ibdev(DLY_BOARDID, DLY_PRIMARYADD, DLY_SECONDARYADD, DLY_TIMEOUT, DLY_EOS, DLY_EOT);
  if (fd <0) {
    printf("Unable to connect to the delay device\n");
    
  }


  return fd;
  
}
int closeDelay(int fd){
  ibonl(fd, 0);
  close(fd);

  return 0;
}


