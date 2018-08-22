#include "delay.h"
#include "mirror.h"
#include <gpib/ib.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>  /* File Control Definitions          */
#include <termios.h>/* POSIX Terminal Control Definitions*/
#include <errno.h>  /* ERROR Number Definitions          */

#define MIRRORADDR "mirroraddr"
#define TDCSTARTADDR "tdcstartaddr"
#define TDCCOUNTADDR "tdccountaddr"

void reverse(char *str, int len);
int intToStr(int x, char str[], int d);
void ftoa(float n, char *res, int afterpoint);
/* float atof(const char*); */

struct delayNCount{
  int count;
  float delay;
};

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
  int tdcIntegrationTime;
};
struct lidar_fd{
  int file1;
  int file2;
  int mirror;
  int delay;
  int tdcStart;
  int tdcCount;
};

int normalLidar(struct lidarParams lp,struct lidar_fd lfd);
int adaptiveLidar(struct lidarParams lp, struct lidar_fd lfd);
int closeAll_fd(struct lidar_fd lfd); 

                  /*  */
