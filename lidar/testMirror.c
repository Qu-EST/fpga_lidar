#include "lidar.h"

int main(void){
  int mirror;
  mirror = openMirror(MIRRORADDR);

  if(mirror<0){
    printf("Error while opening the mirror\n");
    exit(-1);
  }

  if(changeParams(mirror)<0){
    printf("Unable to change the parameters of the mirror\n");
    exit(-1);
    
  }


  for(float x = 0; x < 1; x++){
    for(float y = 0; y < 1; y++){

      printf("Changing the mirror to X: %f, Y: %f\n", x, y);
      
      if(changePosition(mirror, x, y)<0){

	
	printf("Error when changing the position of the mirror\n");
	exit(-1);
      }
    }
  }

  closeMirror(mirror);
  
  return 0;
}
