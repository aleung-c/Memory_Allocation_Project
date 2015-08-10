/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <aleung-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/05 15:50:03 by aleung-c          #+#    #+#             */
/*   Updated: 2015/08/06 13:52:57 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <stdio.h> //

void to_hex(char *buffer, size_t size, unsigned n)
{
	size_t i;
	size_t j;
	char c;
	unsigned digit;

	for (i = 0; i < size - 1; ++i)
	{
		digit = n & 0xf;
		buffer[i] = digit < 10 ? digit + '0' : digit - 10 + 'A';
		n >>= 4;
		if (n == 0)
			break;
	}
	buffer[i + 1] = 0;
	for (j = 0; j < i / 2; ++j)
	{
		c = buffer[j];
		buffer[j] = buffer[i - j];
		buffer[i - j] = c;
	}
}

void		show_alloc_mem()
{
	t_mem_chunk		*chunks;
	t_mem_seg		*segs;
	int total_size;
	char output[12];

	total_size = 0;
	// -------- TINY ----------- //
	chunks = g_memzone.tiny;
	if (!chunks)
		ft_putendl("No chunks tiny");
	while (chunks)
	{
		ft_putstr("TINY : ");
		to_hex(output, 12, (int)chunks);
		ft_putstr("0x");
		ft_putstr(output);
		ft_putchar('\n');
		segs = chunks->first_memseg;
		while (segs)
		{
			if (segs->free == 0)
			{
				to_hex(output, 12, (int)segs);
				// ft_putnbr((int)segs);
				ft_putstr("0x");
				ft_putstr(output);
				ft_putstr(" - ");
				to_hex(output, 12, (int)segs + segs->size);
				ft_putstr("0x");
				ft_putstr(output);
				// ft_putnbr((int)segs +  segs->size);
				ft_putstr(" : ");
				ft_putnbr(segs->size);
				total_size += segs->size;
				ft_putstr(" octets");
				ft_putchar('\n');
			}
			segs = segs->next;
		}
		chunks = chunks->next;
	}
	// -------- SMALL ----------- //
	chunks = g_memzone.small;
	if (!chunks)
		ft_putendl("No chunks small");
	while (chunks)
	{
		ft_putstr("SMALL : ");
		to_hex(output, 12, (int)chunks);
		ft_putstr("0x");
		ft_putstr(output);
		ft_putchar('\n');
		segs = chunks->first_memseg;
		while (segs)
		{
			if (segs->free == 0)
			{
				to_hex(output, 12, (int)segs);
				// ft_putnbr((int)segs);
				ft_putstr("0x");
				ft_putstr(output);
				ft_putstr(" - ");
				to_hex(output, 12, (int)segs + segs->size);
				ft_putstr("0x");
				ft_putstr(output);
				// ft_putnbr((int)segs + segs->size);
				ft_putstr(" : ");
				ft_putnbr(segs->size);
				total_size += segs->size;
				ft_putstr(" octets");
				ft_putchar('\n');
			}
			segs = segs->next;
		}
		chunks = chunks->next;
	}
	// -------- BIG ----------- //
	chunks = g_memzone.big;
	if (!chunks)
		ft_putendl("No chunks big");
	while (chunks)
	{
		ft_putstr("BIG : ");
		to_hex(output, 12, (int)chunks);
		ft_putstr("0x");
		ft_putstr(output);
		ft_putchar('\n');
		segs = chunks->first_memseg;
		while (segs)
		{
			if (segs->free == 0)
			{
				to_hex(output, 12, (int)segs);
				// ft_putnbr((int)segs);
				ft_putstr("0x");
				ft_putstr(output);
				ft_putstr(" - ");
				to_hex(output, 12, (int)segs + segs->size);
				ft_putstr("0x");
				ft_putstr(output);
				// ft_putnbr((int)segs + segs->size);
				ft_putstr(" : ");
				ft_putnbr(segs->size);
				total_size += segs->size;
				ft_putstr(" octets");
				ft_putchar('\n');
			}
			segs = segs->next;
		}
		chunks = chunks->next;
	}
	// --------- TOTAL -------- //
	ft_putstr("Total : ");
	ft_putnbr(total_size);
	ft_putstr(" octets");
	ft_putchar('\n');
	return ;
}

