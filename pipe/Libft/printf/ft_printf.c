/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 03:29:46 by karamire          #+#    #+#             */
/*   Updated: 2024/12/15 03:19:43 by karamire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

int	ft_checkconv(const char c, va_list ap)
{
	void	*adress;

	if (c == 's')
		return (ftputstr(ap));
	else if (c == 'c')
		return (ftputchar(ap));
	else if (c == '%')
		return (ftpercent());
	else if (c == 'i' || c == 'd')
		return (basetenconv(ap));
	else if (c == 'u')
		return (putnbr_unsigned(va_arg(ap, unsigned int)));
	else if (c == 'x' || c == 'X')
		return (putnbr_base(va_arg(ap, unsigned int), c));
	else if (c == 'p')
	{
		adress = va_arg(ap, void *);
		if (adress == NULL)
			return (write(1, "(nil)", 5));
		return (write(1, "0x", 2) + ft_adress_base(adress));
	}
	return (-1);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		printlen;
	int		i;
	int		check;

	va_start(ap, format);
	i = 0;
	printlen = 0;
	if (format == NULL)
		return (-1);
	while (format[i])
	{
		if (format[i] == '%')
		{
			check = ft_checkconv(format[i + 1], ap);
			if (check < 0)
				return (-1);
			printlen += check;
			i++;
		}
		else
			printlen += write(1, &format[i], 1);
		i++;
	}
	return (va_end(ap), printlen);
}

/* int    main(void)
{
    int                d;
    void            *p;
    char            c;
    char            *s;

	s = "hey";
    char            *s_null;
    int                i;
    unsigned int    u;
    unsigned int    x;
    unsigned int    X;

    s_null = NULL;
    c = 'a';
    s = "hey";
    d = 69;
    i = -6969;
    u = -10;
    x = -2147483646;
    X = -2147483646;
    p = &d;
    ft_printf("My ft_printf %% %c %s %d %i %u %x %X %p %a\n",
	c, s, d, i, u, x, X, p);
    printf("The   printf %% %c %s %d %i %u %x %X %p %a\n", c,
	s, d, i, u, x, X, p);
    //---------------------------------------------------------------------
    printf("len : %d\n", ft_printf("ft_printf %% %c %s %d %i %u
	%x %X %p\n", c, s, d, i, u, x, X, p));
    printf("len : %d\n", printf("ft_printf %% %c %s %d %i %u %x
	%X %p\n", c, s, d, i, u, x, X, p));
    printf("%d\n", printf(NULL));
    ft_printf("%d\n", ft_printf(NULL));
    printf("%d\n", printf("Hello %"));
    //ft_printf("%d\n", ft_printf("Hello %"));
    // printf("%d\n", printf("hey %"));
    ft_printf("%d\n", ft_printf("hey %d %s", s, s));
     printf("len : %d\n", printf("%p", NULL));
    ft_printf("len : %d\n", ft_printf("%p", NULL));
    printf("len : %d\n", printf("%s", s_null));
    ft_printf("len : %d\n", ft_printf("%s", s_null));
    return (0);
} */
