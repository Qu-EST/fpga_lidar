#include "lidar.h"

int main(int argc, char* argv[]){
  int lidar = 0;
  lidarParams lp;
  lidar_fd lfd;
  lp->xMin = -0.5;
  lp->xMax = 0.5;
  lp->xStep = 0.1;
  lp->yMin = -0.5;
  lp->yMax = 0.5;
  lp->yStep = 0.1;
  lp->zMin = -150;
  lp->zMax = 150;
  lp->zMicroStep = 5;
  lp->zMacroStep = 2.5;
  lp->peakCheckStep = 20;
  lp-> verbose = 0;
  char filename[255] = "lidar.csv";
  char filename2[255] = "lidar2.csv";
  lp->tdcIntegrationTime = 10;

  lfd->file1 = 0;
  lfd->file2 = 0;
  lfd->mirror = 0;
  lfd->delay = 0;
  lfd->tdcStart = 0;
  lfd->tdcCount = 0;

  int opt;
  
  /* lp->fileName_fd = NULL; */
  /* lp->fileName_fd2 = NULL; */
  /* lp->mirror_fd = NULL; */
  /* lp->delay_fd = NU */
  while ((opt = getopt(argc, argv, "lx:X:s:y:Y:u:z:Z:m:M:vf:F:t:p:")) != -1){
    switch(opt){
    case 'l':
      int lidar = 1;
    case 'x':
      lp->xMin = atof(optarg);
    case 'X':
      lp->xMax = atof(optarg);
    case 'y':
      lp->yMin = atof(optarg);
    case 'Y':
      lp->yMax = atof(optarg);
    case 'u':
      lp->yStep = atof(optarg);
    case 's':
      lp->xStep = atof(optarg);
    case 'z':
      lp->zMin = atof(optarg);
    case 'Z':
      lp->zMax = atof(optarg);
    case 'm':
      lp->zMicroStep = atof(optarg);
    case 'M':
      lp->zMacroStep = atof(optarg);
    case 'v':
      lp->verbose =1;
    case 'f':
      strcat(filename, optarg);
    case 'F':
      strcat(filename2, optarg);
    case 't':
      lp->tdcIntegrationTime = atof(optarg);
    case 'p':
      lp->zPeakCheckStep = atof(optarg);
    }
  }




  /* open the files, mirror, delay and tdc streams */

  lfd->file1 = open(filename, O_WRONLY | O_CREAT);
  if(lfd->file1<0){
    printf("Unable to open the file to save the data. Error: %d\n", lfd->file1);
    exit(-1);
  }

  lfd->mirror = openMirror(MIRRORADDR);
  if(lfd->mirror<0){
    printf("Unable to open the mirror. Error: %d\n", lfd->mirror);
    closeAll_fd(lfd);
    exit(-1);
  }

  lfd->delay = openDelay();
  if(lfd->delay<0){
    printf("Unable to open the mirror. Error: %d\n", lfd->delay);
    closeAll_fd(lfd);
    exit(-1);
  }

  lfd->tdcStart = open(TDCSTARTADDR, O_RDWR);
  if(lfd->tdcStart<0){
    printf("Unable to open the mirror. Error: %d\n", lfd->tdcStart);
    closeAll_fd(lfd);
    exit(-1);
  }

  lfd->tdcCount = open(TDCCOUNTADDR, O_RDONLY);
  if(lfd->tdcCount<0){
    printf("Unable to open the mirror. Error: %d\n", lfd->tdcCount);
    closeAll_fd(lfd);
    exit(-1);
  }
  

  /* start the lidar or alidar */

  if(l)
    normalLidar(lp, lfd);
  else
    adaptiveLidar(lp, lfd);

  return 0;
}

/* close the connections */

int normalLidar(struct lidarParams lp, lidar_fd lfd){

  return 0;
}

int adaptiveLidar(struct lidarParams lp, lidar_fd lfd){

  return 0;
}

int closeAll_fd(lidar_fd lfd){

  if(lfd->file1)
    close(lfd->file1);

  if(lfd->file2)
    close(lfd->file2);

  if(lfd->mirror)
    closeMirror(lfd->mirror);

  if(lfd->delay)
    closeDelay(lfd->delay);

  if(lfd->tdcStart)
    close(lfd->tdcStart);

  if(lfd->tdcCount)
    close(lfd->tdcCount);
    
  return 0;
}


/* lidar code */
