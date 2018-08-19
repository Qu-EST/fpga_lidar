//#include "lidar.h"

#define DLY_BOARDID 0
#define DLY_PRIMARYADD 5
#define DLY_SECONDARYADD 0
#define DLY_TIMEOUT 10
#define DLY_EOS 1
#define DLY_EOT 0



/* delay functions */
int changeDelay(int fd, float dly);
float  getDelay(int fd);
int openDelay();
int closeDelay(int fd);
int ibwrite(int, char*, unsigned int);
