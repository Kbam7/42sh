/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/09 12:37:20 by kbamping          #+#    #+#             */
/*   Updated: 2016/07/09 20:43:07 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*my_char_to_str(char c)
{
	char	*str;

	str = (char *)malloc(2);
	str[0] = c;
	str[1] = '\0';
	return (str);
}

static char	*my_recognise_arg(char c, va_list ap)
{
	if (c == 's')
		return (ft_strdup(va_arg(ap, char *)));
	if (c == 'd' || c == 'i')
		return (ft_itoa(va_arg(ap, int)));
	if (c == 'u')
		return (ft_uitoa(va_arg(ap, unsigned int)));
	if (c == 'o')
		return (ft_uitoa_base(va_arg(ap, unsigned int), 8));
	if (c == 'x')
		return (ft_uitoa_base(va_arg(ap, unsigned int), 16));
	if (c == 'X')
		return (ft_strtoupper(ft_uitoa_base(va_arg(ap, unsigned int), 16)));
	if (c == 'c')
		return (my_char_to_str(va_arg(ap, int)));
	if (c == 'p')
		return (ft_strjoin("0x",
			ft_uitoa_base((uintptr_t)va_arg(ap, void *), 16)));
		return (NULL);
}

static char	*get_next_percent(const char *format, char *str, size_t *offset)
{
	size_t	len;
	size_t	pos;
	char	*temp;
	char	*new_temp;

	len = 0;
	pos = *offset;
	while (format[*offset] != '%' && format[*offset] != '\0')
	{
		*offset += 1;
		len++;
	}
	temp = ft_strsub(format, pos, len);
	new_temp = ft_strjoin(str, temp);
	ft_strdel(&str);
	ft_strdel(&temp);
	return (new_temp);
}

int			ft_printf(const char *format, ...)
{
	va_list ap;
	char	*str;
	char	*temp;
	char	*new_temp;
	size_t	offset;

	va_start(ap, format);
	offset = 0;
	str = ft_strnew(1);
	while (format[offset] != '\0')
		if (format[offset] != '%')
			str = get_next_percent(format, str, &offset);
		else
		{
			temp = my_recognise_arg(format[offset + 1], ap);
			new_temp = ft_strjoin(str, temp);
			ft_strdel(&str);
			ft_strdel(&temp);
			str = new_temp;
			offset += 2;
		}
	ft_putstr(str);
	offset = (size_t)ft_strlen(str);
	ft_strdel(&str);
	return ((int)offset);
}
