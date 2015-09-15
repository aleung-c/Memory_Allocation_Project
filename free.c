/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <aleung-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/11 12:37:50 by aleung-c          #+#    #+#             */
/*   Updated: 2015/09/15 18:13:15 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	free(void *ptr)
{
	t_mem_seg	*tmp;

	if (!ptr || ptr_isinlist(ptr) == 0)
		return ;
	tmp = (t_mem_seg *)((char *)ptr - sizeof(t_mem_seg));
	tmp->free = 1;
	if (tmp->size <= TINY_MAXALLOC)
		free_tiny(tmp);
	else if (tmp->size <= SMALL_MAXALLOC)
		free_small(tmp);
	else
		free_big(tmp, ptr);
	ptr = NULL;
}

void	free_tiny(t_mem_seg *tmp)
{
	t_mem_chunk		*tmp_chunk;
	t_mem_seg		*tmp_seg;

	tmp_chunk = g_memzone.tiny;
	while (tmp_chunk)
	{
		tmp_seg = (t_mem_seg *)((char *)tmp_chunk + sizeof(t_mem_chunk));
		while (tmp_seg)
		{
			if (tmp_seg == tmp)
			{
				tmp_chunk->size_occupied -= tmp->size;
				tmp_chunk->nb_segs--;
				return ;
			}
			tmp_seg = tmp_seg->next;
		}
	}
}

void	free_small(t_mem_seg *tmp)
{
	t_mem_chunk		*tmp_chunk;
	t_mem_seg		*tmp_seg;

	tmp_chunk = g_memzone.small;
	while (tmp_chunk)
	{
		tmp_seg = (t_mem_seg *)((char *)tmp_chunk + sizeof(t_mem_chunk));
		while (tmp_seg)
		{
			if (tmp_seg == tmp)
			{
				tmp_chunk->size_occupied -= tmp->size;
				tmp_chunk->nb_segs--;
				return ;
			}
			tmp_seg = tmp_seg->next;
		}
		tmp_chunk = tmp_chunk->next;
	}
}

void	free_big(t_mem_seg *tmp, void *ptr)
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
	munmap((char *)ptr - sizeof(t_mem_seg) - sizeof(t_mem_chunk),
	tmp->size);
}
