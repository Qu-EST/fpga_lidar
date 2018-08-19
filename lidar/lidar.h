#include "delay.h"
#include "mirror.h"
#include "ib.h"
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>  /* File Control Definitions          */
#include <termios.h>/* POSIX Terminal Control Definitions*/
#include <errno.h>  /* ERROR Number Definitions          */



void reverse(char *str, int len);
int intToStr(int x, char str[], int d);
void ftoa(float n, char *res, int afterpoint);
float atof(const char*);

struct lidarParams{

  float xMin;
  float xMax;
  float xStep;
  float yMin;
  float yMas;
  float yStep;
  float zMin;
  float zMax;
  float zMicroStep;
  float zMacroStep;
  float zPeakCheckStep;
  int verbose;
  int fileName_fd;
  int fileName_fd2;
  int tdcIntegrationTime;
  int mirror_fd;
  int delay_fd;
  int tdcStart_fd;
  int tdcCount_fd;
};


                  /*  */
