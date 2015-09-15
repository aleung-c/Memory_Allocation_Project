/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <aleung-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/05 15:50:03 by aleung-c          #+#    #+#             */
/*   Updated: 2015/09/15 18:10:13 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void		show_alloc_mem(void)
{
	int total_size;

	total_size = 0;
	show_tiny_mem(&total_size);
	show_small_mem(&total_size);
	show_big_mem(&total_size);
	ft_putstr("Total : ");
	ft_putnbr(total_size);
	ft_putstr(" octets");
	ft_putchar('\n');
	return ;
}

void		show_tiny_mem(int *total_size)
{
	t_mem_chunk		*chunks;
	t_mem_seg		*segs;

	chunks = g_memzone.tiny;
	if (!chunks)
		return ;
	while (chunks)
	{
		display_chunk("TINY", chunks);
		segs = chunks->first_memseg;
		while (segs)
		{
			if (segs->free == 0)
			{
				display_seg(segs);
				*total_size += segs->size;
			}
			segs = segs->next;
		}
		chunks = chunks->next;
	}
}

void		show_small_mem(int *total_size)
{
	t_mem_chunk		*chunks;
	t_mem_seg		*segs;

	chunks = g_memzone.small;
	if (!chunks)
		return ;
	while (chunks)
	{
		display_chunk("SMALL", chunks);
		segs = chunks->first_memseg;
		while (segs)
		{
			if (segs->free == 0)
			{
				display_seg(segs);
				*total_size += segs->size;
			}
			segs = segs->next;
		}
		chunks = chunks->next;
	}
}

void		show_big_mem(int *total_size)
{
	t_mem_chunk		*chunks;
	t_mem_seg		*segs;

	chunks = g_memzone.big;
	if (!chunks)
		return ;
	while (chunks)
	{
		display_chunk("LARGE", chunks);
		segs = chunks->first_memseg;
		while (segs)
		{
			if (segs->free == 0)
			{
				display_seg(segs);
				*total_size += segs->size;
			}
			segs = segs->next;
		}
		chunks = chunks->next;
	}
}
