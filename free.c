/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <aleung-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/11 12:37:50 by aleung-c          #+#    #+#             */
/*   Updated: 2015/08/06 12:02:09 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	ft_free(void *ptr)
{
	t_mem_seg *tmp;
	// t_mem_chunk *tmp_chunk;
	// t_mem_chunk *tmp_chunk_big;
	// t_mem_seg *tmp_seg;

	if (!ptr)
		return ;
	tmp = (t_mem_seg *)((char *)ptr - sizeof(t_mem_seg));
	tmp->free = 1;
	if (tmp->size <= TINY)
	{
		free_tiny(tmp);
		// tmp_chunk = g_memzone.tiny;
		// while (tmp_chunk)
		// {
		// 	tmp_seg = (t_mem_seg *)((char *)tmp_chunk + sizeof(t_mem_chunk));
		// 	while (tmp_seg != tmp)
		// 		tmp_seg = tmp_seg->next;
		// 	if (tmp_seg == tmp)
		// 		tmp_chunk->size_occupied -= tmp->size;
		// 	tmp_chunk = tmp_chunk->next;
		// }
		// ft_bzero((char *)tmp + sizeof(t_mem_seg), tmp->size);
	}
	else if (tmp->size <= SMALL)
	{
		free_small(tmp);
		// tmp_chunk = g_memzone.small;
		// while (tmp_chunk)
		// {
		// 	tmp_seg = (t_mem_seg *)((char *)tmp_chunk + sizeof(t_mem_chunk));
		// 	while (tmp_seg != tmp)
		// 		tmp_seg = tmp_seg->next;
		// 	if (tmp_seg == tmp)
		// 		tmp_chunk->size_occupied -= tmp->size;
		// 	tmp_chunk = tmp_chunk->next;
		// }
		// ft_bzero((char *)tmp + sizeof(t_mem_seg), tmp->size);
	}
	else
	{
		free_big(tmp, ptr);
		// tmp_chunk_big = (t_mem_chunk *)((char *)ptr - sizeof(t_mem_seg)
		// 				- sizeof(t_mem_chunk));
		// tmp_chunk = g_memzone.big;
		// if (!tmp_chunk->next)
		// 	g_memzone.big = NULL;
		// else
		// {
		// 	while (tmp_chunk)
		// 	{
		// 		if (tmp_chunk->next == tmp_chunk_big)
		// 			tmp_chunk->next = tmp_chunk_big->next;
		// 		tmp_chunk = tmp_chunk->next;
		// 	}
		// }
		// munmap((char *)ptr - sizeof(t_mem_seg) - sizeof(t_mem_chunk), tmp->size);
	}
	ptr = NULL;
}

void free_tiny(t_mem_seg *tmp)
{
	t_mem_chunk *tmp_chunk;
	t_mem_seg *tmp_seg;

	tmp_chunk = g_memzone.tiny;
	while (tmp_chunk)
	{
		tmp_seg = (t_mem_seg *)((char *)tmp_chunk + sizeof(t_mem_chunk));
		while (tmp_seg != tmp)
			tmp_seg = tmp_seg->next;
		if (tmp_seg == tmp)
			tmp_chunk->size_occupied -= tmp->size;
		tmp_chunk = tmp_chunk->next;
	}
	ft_bzero((char *)tmp + sizeof(t_mem_seg), tmp->size);
}

void free_small(t_mem_seg *tmp)
{
	t_mem_chunk *tmp_chunk;
	t_mem_seg *tmp_seg;

	tmp_chunk = g_memzone.small;
	while (tmp_chunk)
	{
		tmp_seg = (t_mem_seg *)((char *)tmp_chunk + sizeof(t_mem_chunk));
		while (tmp_seg != tmp)
			tmp_seg = tmp_seg->next;
		if (tmp_seg == tmp)
			tmp_chunk->size_occupied -= tmp->size;
		tmp_chunk = tmp_chunk->next;
	}
	ft_bzero((char *)tmp + sizeof(t_mem_seg), tmp->size);
}

void free_big(t_mem_seg *tmp, void *ptr)
{
	t_mem_chunk *tmp_chunk;
	t_mem_chunk *tmp_chunk_big;

	tmp_chunk_big = (t_mem_chunk *)((char *)ptr - sizeof(t_mem_seg)
					- sizeof(t_mem_chunk));
	tmp_chunk = g_memzone.big;
	if (!tmp_chunk->next)
		g_memzone.big = NULL;
	else
	{
		while (tmp_chunk)
		{
			if (tmp_chunk->next == tmp_chunk_big)
				tmp_chunk->next = tmp_chunk_big->next;
			tmp_chunk = tmp_chunk->next;
		}
	}
	munmap((char *)ptr - sizeof(t_mem_seg) - sizeof(t_mem_chunk), tmp->size);
}

