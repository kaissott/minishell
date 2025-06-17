/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludebion <ludebion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 22:06:24 by ludebion          #+#    #+#             */
/*   Updated: 2025/06/13 20:18:22 by ludebion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_my_substr(char *s, unsigned int start, size_t len)
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
	ft_my_strlcpy(sub, s + start, sub_len + 1);
	return (sub);
}

static char	*ft_my_strjoin(char *s1, const char *s2)
{
	char	*s;
	size_t	total_len;

	if (!s1 || !s2)
		return (NULL);
	total_len = ft_strlen(s1) + ft_strlen(s2);
	s = ft_calloc(total_len + 1, sizeof(char));
	if (!s)
		return (free(s1), NULL);
	ft_my_strlcpy(s, s1, ft_strlen(s1) + 1);
	ft_my_strlcpy(s + ft_strlen(s), s2, ft_strlen(s2) + 1);
	return (free(s1), s);
}

static char	*handle_newline(char *str, char *buf, char *newline_pos)
{
	char	*temp_substr;

	temp_substr = ft_my_substr(buf, 0, newline_pos - buf + 1);
	if (!temp_substr)
		return (free(str), NULL);
	str = ft_my_strjoin(str, temp_substr);
	if (!str)
		return (free(temp_substr), NULL);
	ft_my_strlcpy(buf, newline_pos + 1, BUFFER_SIZE + 1);
	return (free(temp_substr), str);
}

static char	*read_file(int fd, char *buf, char *str)
{
	char	*newline_pos;
	ssize_t	bytes_read;

	newline_pos = ft_strchr(buf, '\n');
	if (newline_pos)
		return (handle_newline(str, buf, newline_pos));
	str = ft_my_strjoin(str, buf);
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
	static char	buf[BUFFER_SIZE + 1] = "\0";

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	str = ft_calloc(1, sizeof(char));
	if (!str)
		return (NULL);
	return (read_file(fd, buf, str));
}

// int	main(void)
// {
// 	int		fd;
// 	char	*str;

// 	fd = open("mon_fichier.txt", O_RDONLY);
// 	if (fd == -1)
// 	{
// 		write(1, "Erreur d'ouverture\n", 19);
// 		return (1);
// 	}
// 	str = get_next_line(fd);
// 	while (str)
// 	{
// 		printf("line: %s", str);
// 		free(str);
// 		str = get_next_line(fd);
// 		if (!str)
// 			printf("EOF\n");
// 	}
// 	close(fd);
// 	return (0);
// }
