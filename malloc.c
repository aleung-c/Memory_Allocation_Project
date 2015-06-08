/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <aleung-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/05 10:38:50 by aleung-c          #+#    #+#             */
/*   Updated: 2015/06/08 17:39:56 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_memzone g_memzone = { NULL, NULL, NULL };

void *ft_malloc(size_t size)
{
	void *ret;

	ret = allocate_mem(size);	
	return (ret);
}

void *allocate_tiny(size_t size)
{
	void *ret;
	t_mem_chunk *tmp;

	ret = (char *)mmap(0, TINY,
		PROT_READ | PROT_WRITE, MAP_ANON | MAP_SHARED, -1, 0);
	if (ret == MAP_FAILED)
	{
		ft_putendl_fd("ERROR - mmap", 2);
		return (NULL);
	}
	if (g_memzone.tiny == NULL)
	{
		((t_mem_chunk *)ret)->next = NULL;
		g_memzone.tiny = (t_mem_chunk *)ret;
		
	}
	else
	{
		tmp = g_memzone.tiny;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = (t_mem_chunk *)ret;
	}
	ft_putendl("tiny chunk created.");
	// cast pour remplir la zone chunk allouée et le nouveau segment.
	((t_mem_chunk *)ret)->size_occupied = size + sizeof(t_mem_chunk) + sizeof(t_mem_seg); // semble faux.
	((t_mem_chunk *)ret)->nb_segs = 1;
	((t_mem_chunk *)ret)->first_memseg = (((t_mem_seg *)ret) + sizeof(t_mem_chunk));
	((t_mem_chunk *)ret)->first_memseg->size = size;
	((t_mem_chunk *)ret)->first_memseg->free = 0;
	((t_mem_chunk *)ret)->first_memseg->next = NULL;
	ft_putstr("occupied size = ");
	ft_putnbr(((t_mem_chunk *)ret)->size_occupied);
	ft_putchar('\n');
	return (((t_mem_chunk *)ret)->first_memseg + sizeof(t_mem_seg));
}

void *allocate_mem(size_t size)
{
	void *ret;

	ret = NULL;
	if (size < TINY && g_memzone.tiny == NULL)
		ret = allocate_tiny(size);
	else
		ret = search_mem(size);
	return (ret);
}

void *add_seg_to_chunk(t_mem_chunk *chunk, size_t size) // !! manque acces aux segs freed.
{
	t_mem_seg *tmp_segs;

	tmp_segs = chunk->first_memseg;
	while (tmp_segs->next)
		tmp_segs = tmp_segs->next;
	tmp_segs->next = (t_mem_seg *)(tmp_segs + tmp_segs->size + sizeof(t_mem_seg));
	tmp_segs = tmp_segs->next;	
	tmp_segs->size = size;
	tmp_segs->free = 0;
	ft_putnbr(tmp_segs->size);
	ft_putchar('\n');
	tmp_segs->next = NULL;
	chunk->size_occupied += size + (sizeof(t_mem_seg));
	chunk->nb_segs += 1;
	return (tmp_segs + sizeof(t_mem_seg));
}

void *search_mem(size_t size) // chercher liste de zones allouées pour trouver de l'espace.
{
	t_mem_chunk *tmp;
	size_t free_space;
	void *ret;

	ret = NULL;
	if (size < TINY)
	{
		tmp = g_memzone.tiny;
		while (tmp)
		{
			free_space = TINY - tmp->size_occupied;
			ft_putstr("search mem :\nFree space = ");
			ft_putnbr(free_space);
			ft_putchar('\n');
			ft_putstr("occupied space = ");
			ft_putnbr(tmp->size_occupied);
			ft_putchar('\n');
			if ((size + sizeof(t_mem_seg)) < free_space)
			{
				ft_putendl("size OK");
				ret = add_seg_to_chunk(tmp, size);
				ft_putstr("add seg & = ");
				ft_putnbr((int)ret);
				ft_putchar('\n');
				return(ret);
			}
			tmp = tmp->next;
		}
	}
	return (ret);
}