#include "libasm.h"

size_t		ft_strlen(const char *str);
char		*ft_strcpy(char *dst, const char *src);
int			ft_strcmp(const char *s1, const char *s2);
ssize_t		ft_write(int fd, const void *buf, size_t nbyte);
ssize_t		ft_read(int fd, void *buf, size_t nbyte);
char		*ft_strdup(const char *s1);

void check_strlen()
{
	char *empty = "";
	char *hello_world = "hello world!";
	char *alphabet = "akjsdfkalsjdf;aksdfj;adskfdfjaskdfa;jsdkflj;asldfkjsdfkkdfjs";


	printf("\n================================\n");
	printf("========== FT_STRLEN ===========\n");
	printf("================================\n\n");
	printf("%-20s: \"%s\"\n", "char *", empty);
	printf("%-20s: 0\n", "expected lenght");
	printf("%-20s: %zu\n", "libc", strlen(empty));	
	printf("%-20s: %zu\n", "libasm", ft_strlen(empty));
	printf("\n");
	printf("%-20s: \"%s\"\n", "char *", hello_world);
	printf("%-20s: 0\n", "expected lenght");
	printf("%-20s: %zu\n", "libc", strlen(hello_world));	
	printf("%-20s: %zu\n", "libasm", ft_strlen(hello_world));
	printf("\n");
	printf("%-20s: \"%s\"\n", "char *", alphabet);
	printf("%-20s: 0\n", "expected lenght");
	printf("%-20s: %zu\n", "libc", strlen(alphabet));	
	printf("%-20s: %zu\n", "libasm", ft_strlen(alphabet));
	printf("\n");
	
	// ------- NULL = SEGFAULT
	// printf("%-20s: \"%s\"\n", "char *", alphabet);
	// printf("%-20s: 0\n", "expected lenght");
	// printf("%-20s: %zu\n", "libc", strlen(NULL));	
	// printf("%-20s: %zu\n", "libasm", ft_strlen(NULL));
	// printf("\n");
}

void clear_buffer(char *buffer, int size)
{
	int i = 0;
	while (i < size)
		buffer[i++] = 0;
}

void check_strcpy()
{
	char buffer[1000];
	
	char *empty = "";
	char *hello_world = "Hello world !";
	char *alphabet = "sdfkjsadkfjs;eifjklsdjfa;sdfkjas;dfksdjf;askdfjsdk;afabcdefghijklmnopqrstuvwxyzajdfhalsdjfhasldfjkashdflasdfjldjslhalsdjfhasldfjhllasfd";
	
	printf("\n================================\n");
	printf("========== FT_STRCPY ===========\n");
	printf("================================\n\n");
	printf("%-20s: \"%s\"\n", "char []", empty);
	printf("%-20s: buffer[50]\n", "copy to");
	printf("%-20s: \"%s\"\n", "libc", strcpy(buffer, empty));	
	clear_buffer(buffer, 30);
	printf("%-20s: \"%s\"\n", "libasm", ft_strcpy(buffer, empty));	
	clear_buffer(buffer, 30);
	printf("\n");
	printf("%-20s: \"%s\"\n", "char []", hello_world);
	printf("%-20s: buffer[50]\n", "copy to");
	printf("%-20s: \"%s\"\n", "libc", strcpy(buffer, hello_world));	
	clear_buffer(buffer, 30);
	printf("%-20s: \"%s\"\n", "libasm", ft_strcpy(buffer, hello_world));	
	clear_buffer(buffer, 30);
	printf("\n");
	printf("%-20s: \"%s\"\n", "char []", alphabet);
	printf("%-20s: buffer[50]\n", "copy to");
	printf("%-20s: \"%s\"\n", "libc", strcpy(buffer, alphabet));	
	clear_buffer(buffer, 30);
	printf("%-20s: \"%s\"\n", "libasm", ft_strcpy(buffer, alphabet));
	clear_buffer(buffer, 30);
	printf("\n");

	// ------- NULL = SEGFAULT
	// printf("%-20s: \"%s\"\n", "char []", alphabet);
	// printf("%-20s: buffer[50]\n", "copy to");
	// printf("%-20s: \"%s\"\n", "libc", strcpy(NULL, NULL));	
	// clear_buffer(buffer, 30);
	// printf("%-20s: \"%s\"\n", "libasm", ft_strcpy(NULL, NULL));
	// clear_buffer(buffer, 30);
	// printf("\n");
}

void check_strcmp()
{
	char *empty = "";
	char *hello_world = "Hello world !";
	char *hello_human = "Hello human !";
	char *hello_world2 = "skfjas;kdfja;sdkfjas;dkfjas;dkfjas;kdfja;dkfajdfk;ajsdfasdkfj;sdfkj;kasjdf;askldfja;dsf";
	
	printf("\n================================\n");
	printf("========== FT_STRCMP ===========\n");
	printf("================================\n\n");
	printf("%-20s: \"%s\"\n", "char *", hello_world);
	printf("%-20s: \"%s\"\n", "compared to", hello_human);
	printf("%-20s: \"%d\"\n", "libc", strcmp(hello_world, hello_human));
	printf("%-20s: \"%d\"\n", "libasm", ft_strcmp(hello_world, hello_human));
	printf("\n");
	printf("%-20s: \"%s\"\n", "char *", hello_world);
	printf("%-20s: \"%s\"\n", "compared to", hello_world2);
	printf("%-20s: \"%d\"\n", "libc", strcmp(hello_world, hello_world2));
	printf("%-20s: \"%d\"\n", "libasm", ft_strcmp(hello_world, hello_world2));
	printf("\n");
	printf("%-20s: \"%s\"\n", "char *", hello_world2);
	printf("%-20s: \"%s\"\n", "compared to", empty);
	printf("%-20s: \"%d\"\n", "libc", strcmp(hello_world2, empty));
	printf("%-20s: \"%d\"\n", "libasm", ft_strcmp(hello_world2, empty));
	printf("\n");

	// ------- NULL = SEGFAULT
	// printf("%-20s: \"%s\"\n", "char *", hello_world2);
	// printf("%-20s: %s\n", "compared to", "NULL");
	// printf("%-20s: \"%d\"\n", "libc", strcmp(NULL, hello_world2));
	// printf("%-20s: \"%d\"\n", "libasm", ft_strcmp(NULL, empty));
	// printf("\n");
}

void check_write()
{
	char *hello_world = "Good to see you\0";
	char *empty = "";

	printf("\n================================\n");
	printf("========== FT_WRITE ============\n");
	printf("================================\n\n");
	printf("%-20s: \"%s\"\n", "char *", hello_world);
	printf("%-20s: \n", "answer");
	write(1, hello_world, strlen(hello_world));
	printf("\n");
	printf("%-20s: \n", "Libasm");
	ft_write(1, hello_world, strlen(hello_world));
	printf("\n");
	printf("%-20s: \"%s\"\n", "char *", empty);
	printf("%-20s: \n", "answer");
	write(1, empty, strlen(empty));
	printf("%-20s: \n", "Libasm");
	ft_write(1, empty, strlen(empty));
	printf("\n");
	printf("when giving wrong fd and length\n");
	printf("%-20s: \"%s\"\n", "char *", hello_world);
	printf("%-20s: \n", "answer");
	write(-7, NULL, 7);
	printf("\n");
	printf("%-20s: \n","libasm");
	ft_write(-7, NULL, 7);
	printf("\n");
}

void check_read()
{
	int fd1 = open("testfile", O_RDONLY);
	int fd2 = open("testfile2", O_RDONLY);
	char buff1[101];
	char buff2[101];
	int ret =0;

	printf("\n================================\n");
	printf("========== FT_READ =============\n");
	printf("================================\n\n");
	printf("%-20s: \n", "answer");
	ret = read(fd1, buff1, 100);
	buff1[ret] = 0;
	printf("[return : %d]\n|%s|\n", ret, buff1);
	printf("\n");
	clear_buffer(buff1, 100);
	printf("%-20s: \n", "libasm");
	ret = ft_read(fd2, buff2, 100);
	buff2[ret] = 0;
	printf("[return : %d]\n|%s|\n", ret, buff2);
	printf("\n");
	clear_buffer(buff2, 100);
	printf("%-20s: \n", "answer");
	ret = read(fd1, buff1, 100);
	buff1[ret] = 0;
	printf("[return : %d]\n|%s|\n", ret, buff1);
	printf("\n");
	clear_buffer(buff1, 100);
	printf("%-20s: \n", "libasm");
	ret = ft_read(fd2, buff2, 100);
	buff2[ret] = 0;
	printf("[return : %d]\n|%s|\n", ret, buff2);
	printf("\n");
	clear_buffer(buff2, 100);
	close(fd1);
	close(fd2);
}

void check_strdup()
{
	char *hello_world = "Hello world !";
	char *empty = "";
	char *long_str = "dkfjs;dkfajs;dfkasd;fjaskdfja;sdfkajsd;fksadlfjsa;dfsad;lfadf";
	char *save;
	char *save2;
	char *save3;
	
	printf("\n================================\n");
	printf("========== FT_STRDUP ===========\n");
	printf("================================\n\n");
	printf("%-20s: \"%s\"\n", "char *", hello_world);
	save = strdup(hello_world);
	printf("%-20s: \"%s\"\n", "libc", save);
	free(save);
	save = NULL;
	save2 = ft_strdup(hello_world);
	printf("%-20s: \"%s\"\n", "libasm", save2);
	free(save2);
	save2 = NULL;
	printf("\n");

	printf("%-20s: \"%s\"\n", "char *", empty);
	save = strdup(empty);
	printf("%-20s: \"%s\"\n", "libc", save);
	free(save);
	save = NULL;
	save2 = ft_strdup(empty);
	printf("%-20s: \"%s\"\n", "libasm", save2);
	free(save2);
	save2 = NULL;
	printf("\n");

	printf("%-20s: \"%s\"\n", "char *", long_str);
	save3 = strdup(long_str);
	printf("%-20s: \"%s\"\n", "libc", save3);
	free(save3);
	save3= NULL;
	save = ft_strdup(long_str);
	printf("%-20s: \"%s\"\n", "libasm", save);
	free(save);
	save = NULL;

	// ------- NULL = SEGFAULT
	// printf("%-20s: NULL\n", "char *");
	// save = strdup(NULL);
	// printf("%-20s: \"%s\"\n", "libc", save);
	// free(save);
	// save = NULL;
	// save2 = ft_strdup(NULL);
	// printf("%-20s: \"%s\"\n", "libasm", save2);
	// free(save2);
	// save2 = NULL;
	// printf("\n");
}

int main(void)
{
	char	*str;

	while (1)
	{
		printf("which test? : ");
		scanf("%s", str);
		if (strcmp(str, "ft_strlen") == 0)
			check_strlen();
		else if (strcmp(str, "ft_strcpy") == 0)
			check_strcpy();
		else if (strcmp(str, "ft_strcmp") == 0)
			check_strcmp();
		else if (strcmp(str, "ft_write") == 0)
			check_write();
		else if (strcmp(str, "ft_read") == 0)
			check_read();
		else if (strcmp(str, "ft_strdup") == 0)
			check_strdup();
		else if (strcmp(str, "exit") == 0)
			break ;
		else
		{
			printf("wrong format\n");
			continue ;
		}
	}
}

