/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <aleung-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/05 10:38:50 by aleung-c          #+#    #+#             */
/*   Updated: 2015/08/06 14:46:23 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <stdio.h>

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
	ret = search_mem(size);
	return ((char *)ret);
}

void allocate_tiny(void)
{
	t_mem_chunk *ret;
	t_mem_chunk *tmp;

	ret = mmap(0, TINY, PROT_READ | PROT_WRITE,
				MAP_ANON | MAP_PRIVATE, -1, 0);
	ret->size_occupied = sizeof(t_mem_chunk);
	ret->nb_segs = 0;
	ret->first_memseg = NULL;
	ret->last_memseg = NULL;
	if (ret == MAP_FAILED)
		exit(-1);
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
}

void allocate_small(void)
{
	t_mem_chunk *ret;
	t_mem_chunk *tmp;

	ret = mmap(0, SMALL, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	ret->size_occupied = sizeof(t_mem_chunk);
	ret->nb_segs = 0;
	ret->first_memseg = NULL;
	ret->last_memseg = NULL;
	if (ret == MAP_FAILED)
		exit(-1);
	if (g_memzone.small == NULL)
	{
		ret->next = NULL;
		g_memzone.small = ret;
	}
	else
	{
		tmp = g_memzone.small;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = ret;
		ret->next = NULL;
	}
}

void allocate_big(size_t size)
{
	t_mem_chunk *ret;
	t_mem_chunk *tmp;

	ret = mmap(0, size + sizeof(t_mem_chunk), PROT_READ | PROT_WRITE,
				MAP_ANON | MAP_PRIVATE, -1, 0);
	ret->size_occupied = sizeof(t_mem_chunk);
	ret->nb_segs = 0;
	ret->first_memseg = NULL;
	ret->last_memseg = NULL;
	if (ret == MAP_FAILED)
		exit(-1);
	if (g_memzone.big == NULL)
	{
		ret->next = NULL;
		g_memzone.big = ret;
	}
	else
	{
		tmp = g_memzone.big;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = ret;
		ret->next = NULL;
	}
	ft_putendl("big chunk created."); //
}

void *add_seg_to_chunk(t_mem_chunk *chunk, size_t size_asked, size_t mem_type)
{
	t_mem_seg *tmp_segs;
	t_mem_seg *tmp_next;

	if (!chunk->first_memseg) // si no segments dans le chunk.
	{
		tmp_segs = (t_mem_seg *)((char *)chunk + sizeof(t_mem_chunk));
		tmp_segs->next = NULL;
		tmp_segs->free = 0;
		tmp_segs->size = size_asked;
		chunk->size_occupied += sizeof(t_mem_seg) + size_asked;
		chunk->first_memseg = tmp_segs;
		if ((size_t)(mem_type - chunk->size_occupied) > (size_t)sizeof(t_mem_seg))
		{
			// add segment freed en bout;
			// tmp_next = (t_mem_seg *)((char *)tmp_segs + sizeof(t_mem_seg) + size_asked);
			tmp_segs->next = (t_mem_seg *)((char *)tmp_segs + sizeof(t_mem_seg) + size_asked);
			tmp_segs->next->free = 1;
			tmp_segs->next->next = NULL;
			chunk->size_occupied += sizeof(t_mem_seg);
			tmp_segs->next->size = (size_t)(mem_type - chunk->size_occupied);
		}
		printf("seg added first = %p\n", (char *)((char *)tmp_segs + sizeof(t_mem_seg)));
		return ((char *)tmp_segs + sizeof(t_mem_seg));
	}
	else // il existe des segs. chercher le seg free.
	{
		tmp_segs = chunk->first_memseg;
		while (tmp_segs)
		{
			if (tmp_segs->free == 1 && tmp_segs->size > size_asked)
			{
				tmp_segs->free = 0;
				tmp_segs->size = size_asked;
				if (tmp_segs->next)
				{
					if ((char *)tmp_segs->next - ((char *)tmp_segs + sizeof(t_mem_seg) + size_asked) 
							> (long)sizeof(t_mem_seg)) // recup inter segment.
					{
						tmp_next = tmp_segs->next; // stock next;
						tmp_segs->next = (t_mem_seg *)((char *)tmp_segs + sizeof(t_mem_seg) + size_asked);
						tmp_segs->next->free = 1;
						tmp_segs->next->size = (char *)tmp_segs->next - ((char *)tmp_segs + sizeof(t_mem_seg) + size_asked);
						chunk->size_occupied -= tmp_segs->next->size;
						tmp_segs->next->next = tmp_segs->next;
					}
					printf("seg added inner = %p\n", (char *)((char *)tmp_segs + sizeof(t_mem_seg)));
					return ((char *)tmp_segs + sizeof(t_mem_seg));
				}
				else // le seg free en bout de chaine;
				{
					tmp_segs->free = 0;
					tmp_segs->size = size_asked;
					chunk->size_occupied += size_asked;
					if ((size_t)(mem_type - chunk->size_occupied) > (size_t)sizeof(t_mem_seg))
					{
						// add segment freed en bout
						tmp_segs->next = (t_mem_seg *)((char *)tmp_segs + sizeof(t_mem_seg) + size_asked);
						// tmp_segs->next = tmp_next;
						tmp_segs->next->free = 1;
						tmp_segs->next->next = NULL;
						chunk->size_occupied += sizeof(t_mem_seg);
						tmp_segs->next->size = (size_t)(mem_type - chunk->size_occupied);
						printf("seg added outer = %p\n", (char *)((char *)tmp_segs + sizeof(t_mem_seg)));
					}
					return ((char *)tmp_segs + sizeof(t_mem_seg));
				}
			}
			tmp_segs = tmp_segs->next;
		}
	}
	printf("NULL\n");
	return (NULL);
}

void *add_big_seg(size_t size_asked)
{
	t_mem_chunk *tmp;
	t_mem_seg *ret;

	tmp = g_memzone.big;
	while (tmp->next)
		tmp = tmp->next;
	ret = (t_mem_seg *)((char *)tmp + sizeof(t_mem_chunk));
	ret->size = size_asked;
	ret->next = NULL;
	ret->free = 0;
	tmp->first_memseg = ret;
	return ((char *)ret + sizeof(t_mem_seg));
}

int check_space(t_mem_chunk *chunk, size_t size, size_t mem_type)
{
	size_t free_space;
	t_mem_seg *tmp_segs;

	free_space = mem_type - chunk->size_occupied;
	if ((size + sizeof(t_mem_seg)) < free_space)
		return (1);
	else
	{
		tmp_segs = chunk->first_memseg;
		while (tmp_segs)
		{
			if (tmp_segs->free == 1 && size <= tmp_segs->size)
				return (1);
			tmp_segs = tmp_segs->next;
		}
	}
	return (0);
}

char *search_mem(size_t size)
{
	if (size + sizeof(t_mem_seg) < (TINY - sizeof(t_mem_chunk)))
		return((char *)search_tiny_zone(size));
	else if (size + sizeof(t_mem_seg) < (SMALL - sizeof(t_mem_chunk)))
		return((char *)search_small_zone(size));
	else
	{
		allocate_big(size);
		return ((char *)add_big_seg(size));
	}
	return (NULL);
}
