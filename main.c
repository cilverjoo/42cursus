#include "ft_printf.h"

int		main(void)
{
	char	*str = "this";

	ft_printf("%.*p\n", -3, 0);
	printf("%.*p\n", -3, 0);
}
