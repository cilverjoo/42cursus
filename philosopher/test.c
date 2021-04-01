#include <sys/time.h>
#include <stdio.h>

int		main(void)
{
	int	time1;
	int time2;
	struct timeval tv;
	struct timeval tv2;

	gettimeofday(&tv, NULL);
	gettimeofday(&tv2, NULL);

	time1 = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	time2 = tv2.tv_sec * 1000 + tv2.tv_usec / 1000;
	printf("%10.5ld %.5ld\ndiff: %10.5d\n", time1, time2, time2-time1);
	return (0);
}
