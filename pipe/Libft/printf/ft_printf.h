/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 03:34:57 by karamire          #+#    #+#             */
/*   Updated: 2024/11/29 09:41:55 by karamire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <limits.h>

char	*base(char c);
char	*ft_itoa(int n);
int		ftputstr(va_list ap);
int		ftputchar(va_list ap);
int		ftpercent(void);
int		basetenconv(va_list ap);
int		printnumber(char *num);
int		putnbr_unsigned(unsigned int n);
int		putnbr_base(unsigned int n, char x);
int		ft_adress_base(void *ptr);
int		ft_printf(const char *format, ...);
size_t	ft_strlen(const char *s);

#endif
