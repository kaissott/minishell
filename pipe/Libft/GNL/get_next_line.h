/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 23:34:14 by kaissramire       #+#    #+#             */
/*   Updated: 2025/03/24 17:51:01 by karamire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

char	*ft_strjoingnl(char *s1, char *s2);
char	*get_next_line(int fd, int stop);
char	*ft_strchr(const char *s, int c);
size_t	ft_slen(char *s);
void	*ftmemcpy(void *dst, const void *src, size_t n);

#endif
