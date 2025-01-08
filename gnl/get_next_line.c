/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiparcer <jiparcer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 12:17:24 by jiparcer          #+#    #+#             */
/*   Updated: 2024/11/15 12:19:12 by jiparcer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

//pour utiliser read : read(fichier,destination, taille)
int	read_and_store(int fd, char **buf, char **sta)
{
	int	is_end;
	int	i;

	is_end = 1;
	while (is_end != 0)
	{
		i = 0;
		is_end = read(fd, *buf, BUFFER_SIZE);
		if (is_end == -1)
		{
			*sta = multifree(*sta, *buf);
			return (-1);
		}
		(*buf)[is_end] = '\0';
		*sta = ft_strconc(*buf, *sta, ft_strlen(*buf), ft_strlen(*sta));
		while ((*sta)[i])
		{
			if ((*sta)[i] == '\n')
				return (1);
			i++;
		}
	}
	return (0);
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*buffer;
	int			result;
	static char	*stash;

	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	if (stash == NULL)
		stash = ft_calloc(1, sizeof(char));
	result = read_and_store(fd, &buffer, &stash);
	if (result == -1)
		return (NULL);
	if (result == 1)
	{
		free(buffer);
		return (line = ft_copy_til_bs(stash));
	}
	if (stash[0])
	{
		line = ft_strdup(stash);
		stash = multifree(stash, buffer);
		return (line);
	}
	return (stash = multifree(stash, buffer));
}

char	*multifree(char *stash, char *buffer)
{
	if (stash)
	{
		free(stash);
	}
	if (buffer)
		free(buffer);
	return (NULL);
}

char	*ft_strdup(const char *str)
{
	int		i;
	char	*copy;

	i = 0;
	while (str[i])
		i++;
	copy = (char *)malloc(sizeof(char) * i + 1);
	if (!copy)
		return (NULL);
	i = 0;
	while (str[i])
	{
		copy[i] = str[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

void	*ft_calloc(size_t num, size_t size)
{
	unsigned char	*s;
	void			*slot;
	size_t			totalen;

	if (num != 0 && size > SIZE_MAX / num)
		return (NULL);
	slot = malloc(size * num);
	if (!slot)
		return (NULL);
	s = (unsigned char *)slot;
	totalen = num * size;
	while (totalen)
	{
		*s++ = '\0';
		totalen--;
	}
	return (slot);
}
