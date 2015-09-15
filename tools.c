/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <aleung-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/19 13:05:25 by aleung-c          #+#    #+#             */
/*   Updated: 2015/09/15 18:26:44 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char const *s)
{
	int i;

	i = 0;
	while (s[i] != '\0')
		i++;
	write(1, s, i);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char *d;

	if (dst == NULL || src == NULL || dst == src)
		return (dst);
	if (n)
	{
		d = dst;
		while (n)
		{
			*d++ = *(char *)src++;
			n--;
		}
		return (dst);
	}
	return (dst);
}

void	ft_putnbr(int n)
{
	if (n < 0)
	{
		ft_putchar('-');
		n = -n;
	}
	if (n >= 10)
	{
		ft_putnbr(n / 10);
		ft_putnbr(n % 10);
	}
	else
		ft_putchar(48 + n);
}

void	ft_putendl(char const *s)
{
	ft_putstr(s);
	ft_putchar('\n');
}
