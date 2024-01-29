/*
  Name: Matt Burton
  Class: CSC-4210 Spring 2023
  
  Testing the system call, helloworld – system call 451
  
  To compile
  gcc hello_SCT.c
  To execute
  ./a.out
*/
#include<stdio.h>
#include<stdlib.h>
#include<error.h>
#include<unistd.h>
#include<sys/syscall.h>
#include<linux/unistd.h>

int main(void)
{
   syscall(451);
   return 0;
}
