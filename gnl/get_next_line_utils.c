/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimpa <jimpa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 12:17:38 by jiparcer          #+#    #+#             */
/*   Updated: 2025/01/21 14:09:03 by jimpa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "../ft_printf/libft/libft.h"


char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)(s + i));
	return (NULL);
}

char	*ft_strconc(const char *source, char *dest, int s_len, int d_len)
{
	int		i;
	int		j;
	char	*new_dest;

	new_dest = (char *)malloc(d_len + s_len + 1);
	if (!new_dest)
	{
		free(dest);
		return (NULL);
	}
	i = 0;
	while (i < d_len)
	{
		new_dest[i] = dest[i];
		i++;
	}
	j = 0;
	while (j < s_len)
	{
		new_dest[i + j] = source[j];
		j++;
	}
	new_dest[i + j] = '\0';
	free(dest);
	return (new_dest);
}

char	*ft_copy_til_bs(char *str)
{
	char	*copy;
	char	*newline_pos;
	int		i;

	i = 0;
	while (str[i] != '\n')
		i++;
	copy = (char *)malloc(sizeof(char) * i + 2);
	if (!copy)
		return (NULL);
	i = 0;
	while (str[i] != '\n')
	{
		copy[i] = str[i];
		i++;
	}
	copy[i] = '\n';
	copy[i + 1] = '\0';
	newline_pos = ft_strchr(str, '\n');
	if (newline_pos)
		ft_memmove(str, newline_pos + 1, ft_strlen(newline_pos));
	return (copy);
}

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	const char	*tmp;
	char		*dest;

	tmp = (char *)src;
	dest = (char *)dst;
	if (tmp < dest && dest < tmp + n)
	{
		while (n--)
			dest[n] = tmp[n];
	}
	else
		while (n--)
			*dest++ = *tmp++;
	return (dst);
}
