#include "lidar.h"


int main(void){
  int delay;
  if((delay=openDelay())<0){
    printf("Unable to connect to the delay\n");
    exit(-1);

  }

  for(float i =0; i< 10; i+=0.1){

    printf("Changing the delay to %f\n", i);
    
    changeDelay(delay, i);
  }

  
  return 0;
}
