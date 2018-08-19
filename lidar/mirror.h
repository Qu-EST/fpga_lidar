

/* mirror commands */

#define TERMMODE "$MTI$"
#define SETVD "MTI+VD "
#define SETVB "MTI+VB "
#define SETBW "MTI+BW "
#define ENABLEMIRROR "MTI+EN"
#define CHANGEPOS "MTI+GT "
#define EXITMIRROR "MTI+EX"





/* create a structure for the mirror parameters */
struct mirrorParams{
  int vB;
  int vD;
  int BW;
}mp;


/* mirror functions */
int openMirror(char*);
int changeParams(int fd, struct mirrorParams params);
int changeParamValue(int fd, char* param, int data);
int enableMirror(int fd);
int changePosition(int fd, float x, float y);
float* getPosition(int fd);
int closeMirror(int fd);
int checkStatus(int);
