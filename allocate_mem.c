/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate_mem.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <aleung-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/14 10:22:34 by aleung-c          #+#    #+#             */
/*   Updated: 2015/08/14 10:25:20 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

char		*allocate_mem(size_t size)
{
	void *ret;

	ret = NULL;
	ret = search_mem(size);
	return ((char *)ret);
}

void		allocate_tiny(void)
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

void		allocate_small(void)
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

void		allocate_big(size_t size)
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
}

void		*add_big_seg(size_t size_asked)
{
	t_mem_chunk		*tmp;
	t_mem_seg		*ret;

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
