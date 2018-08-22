CDEBUG = -c -g
DEBUG = -g

lidar : cc lidar.c mirror.o delay.o ftoa.o lidar.h -o lidar


#test 

testMirror : testMirror.c mirror.o lidar.h ftoa.o
	cc $(DEBUG) testMirror.c mirror.o lidar.h ftoa.o -lm -o testMirror

testDelay: testDelay.c delay.h ftoa.o delay.o lidar.h
	cc $(DEBUG) testDelay.c delay.h ftoa.o delay.o lidar.h -lgpib -lm -o testDelay



delay.o: delay.c lidar.h delay.h ftoa.o
	cc $(CDEBUG) delay.c lidar.h delay.h -lgpib

mirror.o: mirror.c lidar.h mirror.h
	cc $(CDEBUG)  mirror.c lidar.h mirror.h 


ftoa.o:	ftoa.c lidar.h
	cc $(CDEBUG) ftoa.c lidar.h -lm

clean:	*.o
	rm *.o  
