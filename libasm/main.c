#include "libasm.h"

size_t		ft_strlen(const char *str);
char		*ft_strcpy(char *dst, const char *src);
int			ft_strcmp(const char *s1, const char *s2);
ssize_t		ft_write(int fd, const void *buf, size_t nbyte);
ssize_t		ft_read(int fd, void *buf, size_t nbyte);
char		*ft_strdup(const char *s1);

int main(void)
{
	char s_long[] = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna pipa.";
	char s_short[] = "pipa";
	char *s_ptr;
	char s_ft_strcpy[122];
	int fd = open("testfile", O_RDWR);
	char *s_ft_strcpy_ptr;
	char *s_strcpy_ptr;
	char s_read_buff[123] = {};
	char s_strcpy[122];
	int ft_bytes;

	printf("------- ft_strlen -------\nstr:		%s\noriginal:	%zu\nmy:		%zu\n",s_long, strlen(s_long), ft_strlen(s_long));
	printf("\nstr:		%s\noriginal:	%zu\nmy:		%zu\n\n",s_short, strlen(s_short), ft_strlen(s_short));
	printf("\nstr:		""\noriginal:	%zu\nmy:		%zu\n\n", strlen(""), ft_strlen(""));
	s_ft_strcpy_ptr = ft_strcpy(s_ft_strcpy, s_long); s_strcpy_ptr = strcpy(s_strcpy, s_long);
	printf("------- ft_strcpy -------\noriginal return:		%s\nmy return:			%s\noriginal:		%s\nmy:			%s\n",s_strcpy_ptr, s_ft_strcpy_ptr, s_strcpy, s_ft_strcpy);
	printf("------- ft_strcmp -------\nqwerfhjhg == qwerfhjhg\noriginal:		%d\nmy:			%d\n", strcmp("qwerfhjhg", "qwerfhjhg"), ft_strcmp("qwerfhjhg", "qwerfhjhg"));
	printf("\nqwerfhjhg != qwerbnm\noriginal:		%d\nmy:			%d\n", strcmp("qwerfhjhg", "qwerbnm"), ft_strcmp("qwerfhjhg", "qwerbnm"));
	printf("------- ft_write -------\n");
	ft_bytes = ft_write(1,s_short,4);
	printf("\nmy return:			%d\n",ft_bytes);
	ft_write(fd, s_long, ft_strlen(s_long));
	printf("------- ft_read -------\n");
	close(fd);
	fd = open("testfile", O_RDWR);
	ft_read(fd, s_read_buff, 121);
	printf("%s\n",s_read_buff);
	printf("------- ft_strdup -------\nmy:			%s\n", s_ptr = ft_strdup(s_long));
	free(s_ptr);
	printf("------- errno check -------\n");
	ft_write(-1, "test", 20);
	printf("errno:		%d\n", errno);
	ft_write(1, "test", -5);
	printf("errno:		%d\n", errno);
	return (0);
}
