#include "stdio.h"
#include "stdlib.h"

#define DIR "bonjour"
#define MDIR "mkdir -p "DIR
#define TEST DIR"/test"
#define NB 3.
#define TNB "bonjour""NB"

int main(void)
{
	puts (DIR);
	puts (MDIR);
	puts (TEST);
	puts (TNB );
	return 0;
}