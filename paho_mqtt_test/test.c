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
/*
  char n= 'n';
  int x=12;
  //char arr[] = {'a', 'b', 'c', 'd', 'r'};
  int arr[] = {11,x};
  char cmd[1024] = {0}; // change this for more length
  char *base = "python3 mqttClient.py "; // note trailine ' ' (space) 
  sprintf(cmd, "%s", base);

  sprintf(cmd, "%s%d ", cmd, x); 
 
  system(cmd);
  */
 char buf[100];
 sprintf(buf,"python3 mqttClient.py %d", 15);
 system(buf);
}


