/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 23:34:07 by kaissramire       #+#    #+#             */
/*   Updated: 2025/03/24 17:54:16 by karamire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*resetbuff(char *saveline)
{
	size_t	i;

	i = 0;
	if (saveline == NULL)
		return (NULL);
	while (saveline[i] != '\n' && saveline[i])
		i++;
	if (saveline[i] == '\n')
		i++;
	if (saveline[i] == '\0')
		return (free(saveline), NULL);
	ftmemcpy(saveline, saveline + i, ft_slen(saveline) - i + 1);
	return (saveline);
}

char	*lineres(char *saveline)
{
	char	*str;
	size_t	i;

	i = 0;
	if (!saveline)
		return (NULL);
	while (saveline[i] != '\n' && saveline[i])
		i++;
	if (saveline[i] != '\n')
		i--;
	str = malloc((i + 2) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (saveline[i] != '\n' && saveline[i])
	{
		str[i] = saveline[i];
		i++;
	}
	if (saveline[i] == '\n')
		str[i++] = '\n';
	str[i] = '\0';
	return (str);
}

char	*readline(int fd, char *saveline)
{
	char	*buffer;
	ssize_t	i;

	i = 1;
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (free(saveline), NULL);
	while (!ft_strchr(saveline, '\n') && i != 0)
	{
		i = read(fd, buffer, BUFFER_SIZE);
		if (i < 0)
			return (free(buffer), free(saveline), saveline = NULL, NULL);
		if (i == 0)
		{
			if (*saveline)
				return (free(buffer), saveline);
			return (free(buffer), free(saveline), NULL);
		}
		buffer[i] = '\0';
		saveline = ft_strjoingnl(saveline, buffer);
		if (!saveline)
			return (free(buffer), NULL);
	}
	return (free(buffer), saveline);
}

char	*get_next_line(int fd, int stop)
{
	static char	*saveline;
	char		*line;

	if (stop == 1)
		return (free(saveline), NULL);
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (saveline == NULL)
	{
		saveline = malloc(1 * sizeof(char));
		if (!saveline)
			return (NULL);
		saveline[0] = '\0';
	}
	saveline = readline(fd, saveline);
	if (!saveline)
		return (NULL);
	line = lineres(saveline);
	if (!line)
	{
		free(saveline);
		return (saveline = NULL, NULL);
	}
	saveline = resetbuff(saveline);
	return (line);
}
