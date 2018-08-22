#include "lidar.h"



int openMirror(char* name){
  int fd;
  struct termios SerialPortSettings;
  size_t bytes_written;
  fd = open(name ,O_RDWR | O_NOCTTY);
  if(fd <0){
     printf("\n  Error! in Opening ttyUSB0\n");
     return(fd);
  }
  printf("\n  ttyUSB0 Opened Successfully\n");

  //get the port setting
  tcgetattr(fd, &SerialPortSettings);

  //set the i/o speed
  cfsetispeed(&SerialPortSettings,B115200);
  cfsetospeed(&SerialPortSettings,B115200);

  //set no parity
  SerialPortSettings.c_cflag &= ~PARENB;

  //set the stop bit =1
  SerialPortSettings.c_cflag &= ~CSTOPB;

  //set the data bits = 8
  SerialPortSettings.c_cflag &= ~CSIZE; /* Clears the Mask       */
  SerialPortSettings.c_cflag |=  CS8;   /* Set the data bits = 8 */

  //turnoff hardware based flow contrl
  SerialPortSettings.c_cflag &= ~CRTSCTS;

  //turn on the reader
  SerialPortSettings.c_cflag |= CREAD | CLOCAL;

  //turn off the software flow control
  SerialPortSettings.c_iflag &= ~(IXON | IXOFF | IXANY);
  SerialPortSettings.c_cflag |= CREAD | CLOCAL;//enable receiver
                                                              
  /* Setting Time outs */                                       
  SerialPortSettings.c_cc[VMIN]  = 10; /* Read 10 characters */  
  SerialPortSettings.c_cc[VTIME] = 0;  /* Wait indefinitely   */
  tcsetattr(fd,TCSANOW,&SerialPortSettings);

  /* Set the mirror for the terminal mode */
  bytes_written = write(fd, TERMMODE, strlen(TERMMODE));

  //

  if(bytes_written!=strlen(TERMMODE)){
    printf("error when enabling the mirror terminal mode");
  }
  
  /* Read and check if the term mode is enables */
  char termCheck[55];
  read(fd, &termCheck,51);
  printf("%s\n", termCheck);

  if(changeParamValue(fd, SETVD, VD_VAL))
    return ERRPARAM;
  if(changeParamValue(fd, SETVB, VB_VAL))
      return ERRPARAM;
  if(changeParamValue(fd, SETBW, BW_VAL))
    return ERRPARAM;
  return fd;
}



/* int changeParams(int fd){ */
/*   changeParamValue(fd, SETVD, VD_VAL); */
/*   changeParamValue(fd, SETVB, VB_VAL); */
/*   changeParamValue(fd, SETBW, BW_VAL); */
  
/*   return 0; */
/* } */

int changeParamValue(int fd, char* param, int data){

  char command[15] = "";
  char value[4] = "" ;
  strcat(command, param);
  intToStr(data, value, 3);
  strcat(command, value);
  strcat(command, "\n");
  write(fd, command, strlen(command));
  if(checkStatus(fd)){

    fprintf(stderr,"Error in changing the %s of the mirror\n", param);
    return ERRPARAM;
  }
  return 0;
}

int checkStatus(int fd){
  char status[10];
  read(fd, &status, strlen("MTI+OK\n"));
  if(strcmp(status, "MTI+OK\n"))
    
     return ERRCOMM;
  return 0;
}


int enableMirror(int fd){

  write(fd, ENABLEMIRROR, sizeof(ENABLEMIRROR));
  /* do a read for MTI+OK AND check if everything is okay */
  if(checkStatus(fd))
    return ERREN;
  return 0;
}
  
int changePosition(int fd, float x, float y){
  char command[20];
  char value[10];
  
  strcat(command, CHANGEPOS);
  ftoa(x, value, DECIMALPOS);
  strcat(command, value);
  strcat(command, " ");
  ftoa(y, value, DECIMALPOS);
  strcat(command, value);
  strcat(command, "\n");
  write(fd, command, strlen(command));
  if(checkStatus(fd)){
    printf("Error whcn changing the position in the mirror X: %f, Y: %f \n", x, y);
    return ERRPOS;
  }

  return 0;
}


float* getPosition(int fd);



int closeMirror(int fd){

  changePosition(fd, (float)0, (float) 0);

  write(fd, EXITMIRROR, sizeof(EXITMIRROR));
  close(fd);
  
  return 0;
}
