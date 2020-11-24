#include "ft_printf.h"

void      		init_flag(t_flags *tf)
{
	tf->minus = 0;
	tf->precision = 0;
	tf->width = 0;
	tf->zero = 0;
	tf->dot = 0;
	tf->wf = 0;
	tf->pf = 0;
}

char			set_star_as_flag(t_flags *fg, int star)
{
	if (fg->dot == 1)
	{
		if (star < 0)
		{
			fg->pf = 0;
			fg->precision = star;
			return (10);
		}
		fg->precision = star;
		fg->pf = 1;
	}
	else
	{
		if (star < 0)
		{
			fg->minus = 1;
			star *= -1;
		}
		fg->width = star;
		fg->wf = 1;
	}
	return ('*');
}

char			what_flag(t_flags *fg, char *fm, va_list ap)
{
	int			star;

	if (is_option(fm))
		return (0);
	else if (*fm == '*')
	{
		star = va_arg(ap, int);
		return (set_star_as_flag(fg, star));
	}
	else if (*fm == '.')
	{
		fg->dot = 1;
		return ('.');
	}
	else if ((*fm <= '9' && *fm >= '0') || *fm == '-')
		return (1);
	return (10);
}

void         set_flag(t_flags *fg ,char **fm, va_list ap)
{
 	char   	c;
	int		dot;

	dot = 0;
	while ((c = what_flag(fg, *fm, ap)))
	{
		if (c == '.')
			dot = 1;
      	else if (c == 1 && dot == 0 && fg->wf == 0)
      	{
        	fg->width = ft_atoi(fm);
        	fg->wf = 1;
      	}
      	else if (c == 1 && dot == 1 && fg->pf == 0)
      	{
        	fg->precision = ft_atoi(fm);
        	if (fg->precision < 0)
				fg->pf = 0;
			else
				fg->pf = 1;
		}
		(*fm)++;
	}
}