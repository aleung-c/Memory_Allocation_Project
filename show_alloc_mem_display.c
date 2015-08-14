/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem_display.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <aleung-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/14 10:44:14 by aleung-c          #+#    #+#             */
/*   Updated: 2015/08/14 11:00:55 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	to_hex(char *buffer, size_t size, unsigned n)
{
	size_t		i;
	size_t		j;
	char		c;
	unsigned	digit;

	i = 0;
	while (i < size)
	{
		digit = n & 0xf;
		buffer[i] = digit < 10 ? digit + '0' : digit - 10 + 'A';
		n >>= 4;
		if (n == 0)
			break ;
		i++;
	}
	buffer[i + 1] = 0;
	j = 0;
	while (j < i / 2)
	{
		c = buffer[j];
		buffer[j] = buffer[i - j];
		buffer[i - j] = c;
		++j;
	}
}

void	display_chunk(char *type, t_mem_chunk *chunks)
{
	char output[12];

	ft_putstr(type);
	ft_putstr(" : ");
	to_hex(output, 12, (int)chunks);
	ft_putstr("0x");
	ft_putstr(output);
	ft_putchar('\n');
}

void	display_seg(t_mem_seg *segs)
{
	char output[12];

	to_hex(output, 12, (int)segs);
	ft_putstr("0x");
	ft_putstr(output);
	ft_putstr(" - ");
	to_hex(output, 12, (int)segs + segs->size);
	ft_putstr("0x");
	ft_putstr(output);
	ft_putstr(" : ");
	ft_putnbr(segs->size);
	ft_putstr(" octets");
	ft_putchar('\n');
}
