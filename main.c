#include "project_1.h"
#include "memory.h"
#include <stdio.h>

#ifdef frdm
#pragma GCC poison printf
#endif

int main()
{
	/* checking for the compile time switch PROJECT_1 */
	#ifdef PROJECT_1
		project_1_report();

	#else

		printf("PROJECT_1 compile time switch not given!!\n");

	#endif

	return 0;
}
