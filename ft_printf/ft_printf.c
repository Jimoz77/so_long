/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiparcer <jiparcer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 13:03:59 by jimi              #+#    #+#             */
/*   Updated: 2024/10/29 12:42:26 by jiparcer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_format2(va_list *args, char *format, int index)
{
	int	len;

	len = 0;
	if (format[index] == 'c')
	{
		for_char(args);
		return (1);
	}
	else if (format[index] == '%')
	{
		for_prcent();
		return (1);
	}
	if (len == 0)
		return (0);
	else
		return (len);
}

int	print_format(va_list *args, char *format, int index)
{
	int	len;

	len = 0;
	if (format[index] == 'c' || format[index] == '%')
	{
		print_format2(args, format, index);
		return (1);
	}
	else if (format[index] == 's')
		len = for_str(args);
	else if (format[index] == 'd' || format[index] == 'i')
		len = for_deci_int(args);
	else if (format[index] == 'u')
		len = for_un_int(args);
	else if (format[index] == 'x')
		len = for_exa(args);
	else if (format[index] == 'X')
		len = for_exa_up(args);
	else if (format[index] == 'p')
		len = for_pointer(args);
	if (len == 0)
		return (0);
	else
		return (len);
}

int	ft_printf(const char *str, ...)
{
	int		i;
	int		len;
	int		nbformat;
	va_list	args;

	va_start(args, str);
	i = 0;
	nbformat = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] == '%' && str[i + 1])
		{
			i++;
			len += print_format(&args, (char *)str, i);
		}
		else
		{
			ft_putchar(str[i]);
			nbformat++;
		}
		i++;
	}
	va_end(args);
	return (nbformat + len);
}
