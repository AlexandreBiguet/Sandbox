#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int catstr (char *str , const char *str1 , const char *str2)
{
  size_t size1 = strlen(str1);
  size_t size2 = strlen(str2);
  size_t tot   = size1 + size2 ;
  
  int res = sprintf(str,"%s%s",str1,str2);
    if ( res < 0)
      {
	printf("string concantenation did notn work");
	exit(-1);
      }
  return res ;
}


int main(void)
{
  char t[200] = "test " ; 
  strcat ( t , "de la conca" );
  strcat ( t , "tenation ! ");
  printf("%s",t);
  
  printf("test de catstr \n");

  char te[100];
  catstr(te,"bonjour ","je suis alexandre");

  printf("%s",te);

  return 0;

}
