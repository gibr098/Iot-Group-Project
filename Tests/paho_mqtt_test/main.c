#include <stdio.h>




int main(void) { 
/*
  int n= 123;
  char arr[] = {'a', 'b', 'c', 'd', 't'}; 
  char cmd[1024] = {0}; // change this for more length
  char *base = "bash a.sh "; // note trailine ' ' (space) 
  sprintf(cmd, "%s", base);
  int i;
  for (i=0;i<sizeof(arr)/sizeof(arr[0]);i++) {
    sprintf(cmd, "%s%c ", cmd, arr[i]); 
  }
  system(cmd);
*/

  char n= 'n';
  char arr[] = {'a', 'b', 'c', 'd', n};
  //int arrint[]={1,2,3,4,5}; 
  char cmd[1024] = {0}; // change this for more length
  char *base = "python3 mqttClient.py "; // note trailine ' ' (space) 
  sprintf(cmd, "%s", base);
  int i;
  for (i=0;i<sizeof(arr)/sizeof(arr[0]);i++) {
    sprintf(cmd, "%s%c ", cmd, arr[i]); 
  }
  system(cmd);


}