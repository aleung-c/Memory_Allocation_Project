/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <aleung-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/05 10:38:50 by aleung-c          #+#    #+#             */
/*   Updated: 2015/06/09 16:56:59 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <stdio.h> //

t_memzone g_memzone = { NULL, NULL, NULL };

void *ft_malloc(size_t size)
{
	void *ret;

	ret = allocate_mem(size);	
	return (ret);
}

char *allocate_mem(size_t size)
{
	void *ret;

	ret = NULL;
	if ((size + sizeof(t_mem_seg)) < TINY && g_memzone.tiny == NULL)
		allocate_tiny();
	ret = search_mem(size);
	return ((char *)ret);
}

void allocate_tiny(void)
{
	t_mem_chunk *ret;
	t_mem_chunk *tmp;

	ret = mmap(0, TINY, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	// cast pour remplir la zone chunk allouée.
	ret->size_occupied = sizeof(t_mem_chunk);
	ret->nb_segs = 0;
	ret->first_memseg = NULL;
	ret->last_memseg = NULL;
	if (ret == MAP_FAILED)
	{
		ft_putendl_fd("ERROR - mmap", 2);
		exit(-1);
	}
	if (g_memzone.tiny == NULL)
	{
		ret->next = NULL;
		g_memzone.tiny = ret;
	}
	else
	{
		tmp = g_memzone.tiny;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = ret;
		ret->next = NULL;
	}
	ft_putendl("tiny chunk created.");
	
}

void *add_seg_to_chunk(t_mem_chunk *chunk, size_t size_asked) // !! manque acces aux segs freed.
{
	t_mem_seg *tmp_segs;

	if (!chunk->first_memseg) // si no segments dans le chunk.
	{
		tmp_segs = (t_mem_seg *)((char *)chunk + sizeof(t_mem_chunk));
		chunk->first_memseg = tmp_segs;
	}
	else
	{
		tmp_segs = chunk->first_memseg;
		while (tmp_segs->next) // ici a faire le check du free.
			tmp_segs = tmp_segs->next;
		tmp_segs->next = (t_mem_seg *)((char *)tmp_segs + tmp_segs->size + sizeof(t_mem_seg));
		tmp_segs = tmp_segs->next;
	}
	tmp_segs->size = size_asked;
	tmp_segs->free = 0;
	tmp_segs->next = NULL;
	chunk->size_occupied += size_asked + (sizeof(t_mem_seg));
	chunk->nb_segs += 1;
	printf("seg addr = %p\n", (char *)(tmp_segs + sizeof(t_mem_seg)));
	return (tmp_segs + sizeof(t_mem_seg));
}

char *search_mem(size_t size) // chercher liste de zones allouées pour trouver de l'espace.
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
				return((char *)ret);
			}
			tmp = tmp->next;
		}
		if (!tmp)
		{
			ft_putendl("no space in mem, create new alloc");
			allocate_tiny();
			ret = search_mem(size);
		}
	}
	return ((char *)ret);
}