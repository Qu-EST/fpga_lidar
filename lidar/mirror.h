

/* mirror commands */

#define TERMMODE "$MTI$\n"
#define SETVD "MTI+VD "
#define SETVB "MTI+VB "
#define SETBW "MTI+BW "
#define ENABLEMIRROR "MTI+EN\n"
#define CHANGEPOS "MTI+GT "
#define EXITMIRROR "MTI+EX\n"


#define VD_VAL 125
#define VB_VAL 80
#define BW_VAL 140

#define ERROPEN -1
#define ERRPARAM -2
#define ERRPOS -3
#define ERRCOMM -4
#define ERREN -5

#define DECIMALPOS 3

#define MTIOK 0
#define MTICON 1
#define MTIEX 2
#define MTIERR -6

/* create a structure for the mirror parameters */
struct mirrorParams{
  int vB;
  int vD;
  int BW;
}mp;


/* mirror functions */
int openMirror(char*);
int changeParams(int fd);
int changeParamValue(int fd, char* param, int data);
int enableMirror(int fd);
int changePosition(int fd, float x, float y);
float* getPosition(int fd);
int closeMirror(int fd);
int checkStatus(int);
