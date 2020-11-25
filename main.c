#include "ft_printf.h"

int		main(void)
{
	char	*str;

	str = "NULL";
	ft_printf("print this : %p\n", str);
	printf("print this : %p\n", str);

	ft_printf("print this : %x\n", 2837283);
	printf("print this : %x\n", 2837283);
	ft_printf("print this : %X\n", 2837283);
	printf("print this : %X\n", 2837283);
}
