#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> 
#include<sys/wait.h>
#include <unistd.h>
#include <pthread.h>
 
void *avg1(void *str);
void *min1(void *ptr);
void *max1(void *ptr);

double avg;        
int min,max;

typedef struct data{
int s;
int * v;
}data;

main(int a, char *a1[]){
while(a <=1){
printf("No arguments entered.\n");
printf("Please enter one or more inputs.\n");
exit(0);
}
int i = 0;
int copy[a-1];
for(i; i < (a -1); i++){
copy[i] = atoi(a1[i+1]);
}
pthread_t thread1, thread2, thread3;
const char *m1 = "This is Thread 1";
const char *m2 = "This is Thread 2";
const char *m3 = "This is Thread 3";
int  t1, t2, t3;
printf("Running: %s\n\n", a1[0]);
data ds = {a - 1, copy};
t1 = pthread_create(&thread1, NULL, (void *) avg1, (void *) &ds);
if(t1){
fprintf(stderr,"Error - pthread_create() return code: %d\n", t1);
exit(EXIT_FAILURE);
}
t2 = pthread_create(&thread2, NULL, (void *) min1, (void *) &ds);
if(t2){
fprintf(stderr,"Error - pthread_create() return code: %d\n",t2);
exit(EXIT_FAILURE);
}
t3 = pthread_create(&thread3, NULL, (void *) max1, (void *) &ds);
if(t3){
fprintf(stderr,"Error - pthread_create() return code: %d\n", t3);
exit(EXIT_FAILURE);
}
 
printf("pthread_create() for Thread 1 returns: %d\n",t1);
printf("pthread_create() for Thread 2 returns: %d\n",t2);
printf("pthread_create() for Thread 3 returns: %d\n\n",t3);
pthread_join(thread1, NULL);
pthread_join(thread2, NULL);
pthread_join(thread3, NULL);
printf("The average:  %g\n", avg);
printf("The minimum:  %d\n", min);
printf("The maximum:  %d\n", max);
exit(EXIT_SUCCESS);
}
 
void *avg1(void *ptr){
data * copy;
copy = (data *) ptr;
int sz = copy->s;
int i;
for(i = 0; i < sz; i++){
avg += (copy->v[i]);    
}                               
avg = (int)(avg / sz);         
}

void *min1(void *ptr){
data * copy;
copy = (data *) ptr;
int sz = copy->s;
int i;
min = (copy->v[0]);
for(i = 1; i < sz; i++){
if(min > (copy->v[i])){
min = (copy->v[i]);
}
}
}

void *max1(void *ptr){
data * copy;
copy = (data *) ptr;
int sz = copy->s;
int i;
max = copy->v[0];
for(i = 1; i < sz; i++){
if(max < copy->v[i]){
max = copy->v[i];
}
}
}
