#include <unistd.h>
#include <stdarg.h>

char* digit = "0123456789abcdef";

int ft_strlen(char* str)
{
	int idx = 0;
	if(str)
		while(str[idx])
			idx++;
	return idx;
}

char	*ft_strchr(char* str, char c)
{
	int idx = 0;
	while (str[idx] != c)
	{
		if(str[idx] == 0)
			return 0;
		idx++;
	}
	return &str[idx];
}

int	outstring(char* str, int len)
{
	write(1,str,len);
	return len;
}

int is_num(char c)
{
	if (c >= '0' && c <= '9')
		return 1;
	return 0;
}

int make_int(char** str)
{
	int res = 0;
	while( is_num(**str) )
	{
		res *= 10;
		res += **str - '0';
		(*str)++;
	}
	return res;
}

int max_val(int a, int b)
{
	if (a>b)
		return a;
	return b;
}

int print_pad(int pad, int len)
{
	char c;
	int idx = 0;

	c = (char)pad;
	while (idx < len)
	{
		write(1, &c, 1);
		idx++;
	}
	return len;
}

int	processing(char** fmt,va_list ap)
{
	int is_nega = 0;
	int done = 0;
	int prec = -1;
	int width = -1;
	int base = 0;
	int len;
	int pad = ' ';
	char* word;
	long long int temp_num;
	unsigned long long num;

	(*fmt)++;
	if( is_num(**fmt) )
	{
		width = make_int(fmt);
	}
	if (**fmt == '.')
	{
		(*fmt)++;
		if(is_num(**fmt))
		{
			prec = make_int(fmt);
		}
		else
			prec = -2;
	}
	if (**fmt == 's')
	{
		word = va_arg(ap, char*);
		if( word == 0)
			word = "(null)";
		len = ft_strlen(word);
		if (prec >= 0 && (prec < len))
			len = prec;
		if (prec == -2)
			len = 0;
		width = max_val(0, width - len);
		done += print_pad(pad, width);
		done += outstring(word, len);
	}
	else
	{
		if (**fmt == 'd')
		{
			temp_num = va_arg(ap, int);
			base = 10;
			is_nega = (temp_num < 0 ? 1 : 0);
			num = (is_nega == 1 ? -1* temp_num :temp_num);
		}
		else 
		{
			num = va_arg(ap, unsigned int);
			base = 16;
		}

		if (num == 0)
		{
			if(prec == -2 || prec == 0)
			{
				word = "";
				len = 0;
			}
			else
			{
				word = "0";
				len = 1;
			}
		}
		else
		{
			word = (char[21]){};
			len = 20;
			while (num > 0)
			{
				word[len--] = digit[num%base];
				num /= base;
			}
			word = &word[len + 1];
			len = 20 - len;
		}
		if (is_nega == 1)
		{
			width--;
		}
		prec = max_val(0, prec - len);
		width = max_val(0, width - (prec + len));
		done += print_pad(pad, width);
		if(is_nega == 1)
			done += outstring("-",1);
		pad = '0';
		done += print_pad(pad , prec);
		done += outstring(word, len);
	}
	(*fmt)++;
	return done;
}

int ft_printf(const char* fmt, ...)
{
	va_list ap;
	va_start(ap,fmt);
	char* start;
	char* target;
	int done = 0;
	start = (char*)fmt;
	while ((target = ft_strchr(start,'%')))
	{
		done += outstring(start, target - start);
		done += processing(&target,ap);
		start = target;
	}
	done +=outstring(start, ft_strlen(start));
	va_end(ap);
	return done;
}

#include <stdio.h>
int main()
{
	printf("$$%10.8d\n", 2147483647);
	ft_printf("$$%10.8d\n", 2147483647);

	printf("$$%20.8d\n", -2147483648);
	ft_printf("$$%20.8d\n", -2147483648);


	printf("$$%20.0d\n", 0);
	ft_printf("$$%20.0d\n", 0);

	printf("$$%20.2d\n", 0);
	ft_printf("$$%20.2d\n", 0);

	printf("$$%20.2s\n", NULL);
	ft_printf("$$%20.2s\n", NULL);
	
	printf("$$%%%%20.2s\n", NULL);
	ft_printf("$$%%%%20.2s\n", NULL);
}