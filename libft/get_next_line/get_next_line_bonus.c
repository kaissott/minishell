/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludebion <ludebion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 21:17:18 by ludebion          #+#    #+#             */
/*   Updated: 2024/12/04 20:16:59 by ludebion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*ft_substr(char *s, unsigned int start, size_t len)
{
	size_t	sub_len;
	char	*sub;

	if (!s || start >= ft_strlen(s))
		return (ft_calloc(1, sizeof(char)));
	sub_len = ft_strlen(s) - start;
	if (sub_len > len)
		sub_len = len;
	sub = ft_calloc(sub_len + 1, sizeof(char));
	if (!sub)
		return (NULL);
	ft_strlcpy(sub, s + start, sub_len + 1);
	return (sub);
}

static char	*ft_strjoin(char *s1, const char *s2)
{
	char	*s;
	size_t	total_len;

	if (!s1 || !s2)
		return (NULL);
	total_len = ft_strlen(s1) + ft_strlen(s2);
	s = ft_calloc(total_len + 1, sizeof(char));
	if (!s)
		return (free(s1), NULL);
	ft_strlcpy(s, s1, ft_strlen(s1) + 1);
	ft_strlcpy(s + ft_strlen(s), s2, ft_strlen(s2) + 1);
	return (free(s1), s);
}

static char	*handle_newline(char *str, char *buf, char *newline_pos)
{
	char	*temp_substr;

	temp_substr = ft_substr(buf, 0, newline_pos - buf + 1);
	if (!temp_substr)
		return (free(str), NULL);
	str = ft_strjoin(str, temp_substr);
	if (!str)
		return (free(temp_substr), NULL);
	ft_strlcpy(buf, newline_pos + 1, BUFFER_SIZE + 1);
	return (free(temp_substr), str);
}

static char	*read_file(int fd, char *buf, char *str)
{
	char	*newline_pos;
	ssize_t	bytes_read;

	newline_pos = ft_strchr(buf, '\n');
	if (newline_pos)
		return (handle_newline(str, buf, newline_pos));
	str = ft_strjoin(str, buf);
	if (!str)
		return (NULL);
	bytes_read = read(fd, buf, BUFFER_SIZE);
	if (bytes_read < 0)
	{
		buf[0] = '\0';
		return (free(str), NULL);
	}
	if (bytes_read == 0)
	{
		buf[0] = '\0';
		if (*str)
			return (str);
		return (free(str), NULL);
	}
	buf[bytes_read] = '\0';
	return (read_file(fd, buf, str));
}

char	*get_next_line(int fd)
{
	char		*str;
	static char	buf[1024][BUFFER_SIZE + 1];

	if (fd < 0 || fd > 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	str = ft_calloc(1, sizeof(char));
	if (!str)
		return (NULL);
	return (read_file(fd, buf[fd], str));
}

// int	main(void)
// {
// 	int		fd;
// 	int		fd2;
// 	char	*str;
// 	int		i;

// 	fd = open("bible.txt", O_RDONLY);
// 	fd2 = open("coran.txt", O_RDONLY);
// 	if (fd == -1 || fd2 == -1)
// 	{
// 		write(1, "Erreur d'ouverture\n", 19);
// 		return (1);
// 	}
// 	i = 1;
// 	while (i < 10)
// 	{
// 		str = get_next_line(fd);
// 		if (!str)
// 			printf("EOF\n");
// 		printf("line %i: %s", i++, str);
// 		free(str);
// 	}
// 	while (i < 20)
// 	{
// 		str = get_next_line(fd2);
// 		if (!str)
// 			printf("EOF\n");
// 		printf("line %i: %s", i++, str);
// 		free(str);
// 	}
// 	while (i < 30)
// 	{
// 		str = get_next_line(fd);
// 		if (!str)
// 			printf("EOF\n");
// 		printf("line %i: %s", i++, str);
// 		free(str);
// 	}
// 	while (i < 40)
// 	{
// 		str = get_next_line(fd2);
// 		if (!str)
// 			printf("EOF\n");
// 		printf("line %i: %s", i++, str);
// 		free(str);
// 	}
// 	close(fd);
// 	close(fd2);
// 	return (0);
// }
