#include <stdio.h>
#include <string.h>

int main(void)
{
  char str1[100] = "bonjour" ;

  size_t t1 = sizeof(str1);
  size_t t2 = strlen(str1);

  printf("string : %s  \n",str1);
  printf("sizeof : %lu \n",t1);
  printf("strlen : %lu \n",t2);

  return 0;
}
