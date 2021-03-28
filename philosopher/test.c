#include <sys/time.h>
#include <stdio.h>

int		main(void)
{
	int	time;
	struct timeval tv;

	time = gettimeofday(&tv, NULL);
	printf("%ld %ld\n", tv.tv_sec * 1000, tv.tv_usec / 1000);
	return (0);
}
