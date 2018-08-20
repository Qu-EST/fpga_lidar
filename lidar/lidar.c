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
  int count;
  for (float xItr = lp.xMin; xItr <= lp.xMax; xItr += lp.xStep){
    for(float yItr = lp.yMin; yItr <= lp.yMax; yItr += lp.yStep){
      changePosition(lfd.mirror, xItr, yItr);
      for(float zItr = lp.zMin; zItr <= lp.zMax; zItr += lp.zMicroStep){
	changeDelay(lfd.delay, zItr);
	write(lfd.tdcStart, "1", 1);
	read(lfd.tdcCount, &count, 4);
	fprintf(lfd.file1, "%f, %f, %f, %d\n", xItr, yItr, zItr, count);
      }
    }
  }

  return 0;
}

float getAdaptive(float x, float y, float zMin, float zMax){
  float adaptive =0;
 
  
  return adaptive;
}

void dlyCntMxChk(float x, float y, float z, lidarParams lp, lidar_fds, lfd, float *maxdly, int *maxcnt){
  int count;
  changeDelay(lfd, z);
   write(lfd.tdcStart, "1", 1);
  read(lfd.tdcCount, &count, 4);
  if (*maxcnt < count) {
    *maxcnt = count;
    *maxdly = dly;
  }
}

float getPeak(float x, float y, lidarParams lp, lidar_fds lfd){
  //float peak =0;
  delayNCount maxCount;
  maxCount.count = 0;
  maxCount.delay = 0;

  float zItr;
	// do the macrostep scan to locate where the peak might occur
  for (zItr = lp.zMin; zItr <= lp.zMax; zItr+=zMacroStep){
    
    dlyCntMxChk(x, y, zItr, lp, lfd, &maxCount.delay, &maxCount.count);
  }
	//check if this the real macro peak or if it's the side small peak
    dlyCntMxChk(x, y, maxCount.delay + lp.zPeakCheckStep, lp, lfd, &maxCount.delay, &maxCount.count);
  
  return maxCount.delay;

}
int adaptiveLidar(struct lidarParams lp, lidar_fd lfd){
  int count;
  float adaptive =0;

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



