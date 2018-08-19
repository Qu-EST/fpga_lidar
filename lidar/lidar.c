#include "lidar.h"

int main(int argc, char* argv[]){
  int lidar = 0;
  lidarParams lp;
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


  return 0;
}



/* lidar code */
