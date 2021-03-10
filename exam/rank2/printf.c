#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX(a,b) (a > b ? a : b)
#define MIN(a,b) (a < b ? a : b)

typedef struct  s_flags
{
	int width;
	int precision;
	int dot;
	int skip;
	char type;
}				t_flags;

void    init_struct(t_flags *flags)
{
	flags->width = 0;
	flags->precision = 0;
	flags->dot = 0;
	flags->skip = 0;
	flags->type = 0;
}

int    ft_strlen(char *str)
{
	int i = 0;

	while (str[i])
		i++;
	return (i);
}

int    ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

char   *ft_itoa(unsigned int n, int baselen)
{
	char *base = "0123456789abcdef";
	int i = 0;
	int numlen = 0;
	char *ret;
	int tmp = n;

	while (tmp)
	{
		tmp /= baselen;
		numlen++;
	}
	ret = (char *)malloc(numlen + (!n) + 1);
	ret[numlen + (!n)] = '\0';
	if (!n)
		ret[0] = '0';
	while (n)
	{
		ret[--numlen] = base[n % baselen];
		n /= baselen;
	}
	return (ret);
}

void    ft_parser(char *str, t_flags *flags)
{
	int i = 0;

	while (ft_isdigit(str[i]) || str[i] == '.')
	{
		if (str[i] == '.')
			flags->dot = 1;
		else if (flags->dot)
			flags->width = flags->width * 10 + str[i] - '0';
		else
			flags->precision = flags->precision * 10 + str[i] - '0';
		i++;
	}
	if (str[i] == 'd' || str[i] == 'x' || str[i] == 's')
		flags->type = str[i];
	flags->skip = i;
}

int    ft_process_d(t_flags *flags, int n)
{
	int ret = 0;
	unsigned int tmp = (n < 0 ? -n : n);
	char *num = ft_itoa(tmp, 10);
	int len = ft_strlen(num);

	if (flags->dot)
	{
		if (!flags->precision && !n)
		{
			while (flags->width--)
				ret += write(1, " ", 1);
		}
		else
		{
			while (flags->width-- > MAX(len + (n < 0), flags->precision))
				ret += write(1, " ", 1);
			if (n < 0)
				ret += write(1, "-", 1);
			while (flags->precision-- > len)
				ret += write(1, "0", 1);
			ret += write(1, num, len);
		}
	}
	else
	{
		while (flags->width-- > len + (n < 0))
			ret += write(1, " ", 1);
		if (n < 0)
			ret += write(1, "-", 1);
		ret += write(1, num, len);
	}
	free(num);
	return (ret);
}

int    ft_process_x(t_flags *flags, unsigned int n)
{
	int ret = 0;
	unsigned int tmp = (n < 0 ? -n : n);
	char *num = ft_itoa(tmp, 16);
	int len = ft_strlen(num);

	if (flags->dot)
	{
		if (!flags->precision && !n)
		{
			while (flags->width--)
				ret += write(1, " ", 1);
		}
		else
		{
			while (flags->width-- > MAX(len + (n < 0), flags->precision))
				ret += write(1, " ", 1);
			if (n < 0)
				ret += write(1, "-", 1);
			while (flags->precision-- > len)
				ret += write(1, "0", 1);
			ret += write(1, num, len);
		}
	}
	else
	{
		while (flags->width-- > len + (n < 0))
			ret += write(1, " ", 1);
		if (n < 0)
			ret += write(1, "-", 1);
		ret += write(1, num, len);
	}
	free(num);
	return (ret);
}

int    ft_process_s(t_flags *flags, char *str)
{
	int ret = 0;
	int len = 0;
	
	if (!str)
		str = "(null)";
	len = ft_strlen(str);
	if (!flags->dot)
	{
		while (flags->width-- > len)
			ret += write(1, " ", 1);
		ret += write(1, str, len);
	}
	else
	{
		while (flags->width-- > MIN(len, flags->precision))
			ret += write(1, " ", 1);
		ret += write(1, str, MIN(len, flags->precision));
	}
	return (ret);
}

int    ft_preprocessor(t_flags *flags, va_list ap)
{
	int  ret;

	if (flags->type == 'd')
		ret = ft_process_d(flags, va_arg(ap, int));
	else if (flags->type == 'x')
		ret = ft_process_x(flags, va_arg(ap, unsigned int));
	else
		ret = ft_process_s(flags, va_arg(ap, char *));
	return (ret);
}

int    ft_printf(const char *format, ...)
{
	va_list ap;
	t_flags flags;
	char    *str;
	int     i = 0;
	int     ret = 0;

	str = (char *)format;
	va_start(ap, format);

	while(str[i])
	{
		init_struct(&flags);
		if (str[i] != '%')
		{
			ret = write(1, &str[i], 1);
		}
		else
		{
			ft_parser(&str[i + 1], &flags);
			i += flags.skip;
			ret += ft_preprocessor(&flags, ap);
		}
		i++;
	}
	return (ret);
}

int    main(void)
{
	int a = 0;
	int b = 0;

	a = ft_printf("%6.5s$\n", "this");
	printf("a : %d\n", a);
	b = printf("%6.5s$\n", "this");
	printf("b : %d\n", b);
	return (0);
}