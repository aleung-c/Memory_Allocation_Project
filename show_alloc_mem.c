/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <aleung-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/05 15:50:03 by aleung-c          #+#    #+#             */
/*   Updated: 2015/06/09 17:02:31 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void		show_alloc_mem()
{
	t_mem_chunk		*chunks;
	t_mem_seg		*segs;

	chunks = g_memzone.tiny;
	if (!chunks)
		ft_putendl("No chunks");

	while (chunks)
	{
		ft_putstr("TINY : ");
		ft_putnbr((int)chunks);
		ft_putchar('\n');
		segs = chunks->first_memseg;
		while (segs)
		{
			
			ft_putnbr((int)segs);
			ft_putstr(" - ");
			ft_putnbr((int)segs +  segs->size);
			ft_putstr(" : ");
			ft_putnbr(segs->size);
			ft_putchar('\n');
			segs = segs->next;
		}
		chunks = chunks->next;
	}
	return ;
}