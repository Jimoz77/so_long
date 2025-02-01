/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiparcer <jiparcer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 12:15:06 by jiparcer          #+#    #+#             */
/*   Updated: 2025/02/01 17:43:32 by jiparcer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

char	*ft_strconc(const char *source, char *dest, int s_len, int d_len);
char	*ft_copy_til_bs(char *str);
char	*get_next_line(int fd);
void	*ft_memmove(void *dst, const void *src, size_t len);
char	*ft_strdup(const char *str);
void	*ft_calloc(size_t num, size_t size);
char	*multifree(char *stash, char *buffer);

#endif