# makefile for scheduling program
#
# make rr - for round-robin scheduling
# make fcfs - for FCFS scheduling
# make sjf - for SJF scheduling
# make priority - for priority scheduling
# make priority_rr - for priority with round robin scheduling
#
# make clean - remove all executables and .o files

CC=gcc
CFLAGS=-Wall -g

clean:
	rm -rf *.o
	rm -rf fcfs
	rm -rf sjf
	rm -rf rr
	rm -rf priority
	rm -rf priority_rr

rr: driver.o queue.o CPU.o schedule_rr.o
	$(CC) $(CFLAGS) -o rr driver.o schedule_rr.o queue.o CPU.o

sjf: driver.o queue.o CPU.o schedule_sjf.o
	$(CC) $(CFLAGS) -o sjf driver.o schedule_sjf.o queue.o CPU.o

fcfs: driver.o queue.o CPU.o schedule_fcfs.o
	$(CC) $(CFLAGS) -o fcfs driver.o schedule_fcfs.o queue.o CPU.o

priority: driver.o queue.o CPU.o schedule_priority.o
	$(CC) $(CFLAGS) -o priority driver.o schedule_priority.o queue.o CPU.o

schedule_fcfs.o: schedule_fcfs.c
	$(CC) $(CFLAGS) -c schedule_fcfs.c

priority_rr: driver.o queue.o CPU.o schedule_priority_rr.o
	$(CC) $(CFLAGS) -o priority_rr driver.o schedule_priority_rr.o queue.o CPU.o

driver.o: driver.c
	$(CC) $(CFLAGS) -c driver.c

schedule_sjf.o: schedule_sjf.c
	$(CC) $(CFLAGS) -c schedule_sjf.c

schedule_priority.o: schedule_priority.c
	$(CC) $(CFLAGS) -c schedule_priority.c

schedule_rr.o: schedule_rr.c
	$(CC) $(CFLAGS) -c schedule_rr.c

queue.o: queue.c queue.h
	$(CC) $(CFLAGS) -c queue.c

CPU.o: CPU.c cpu.h
	$(CC) $(CFLAGS) -c CPU.c
