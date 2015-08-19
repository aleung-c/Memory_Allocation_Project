/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_seg_to_chunk.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <aleung-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/06 10:32:56 by aleung-c          #+#    #+#             */
/*   Updated: 2015/08/19 13:36:49 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void		*add_seg_to_chunk(t_mem_chunk *chunk,
							size_t size_asked, size_t mem_type)
{
	t_mem_seg *tmp_segs;

	if (!chunk->first_memseg)
		return ((char *)add_first_memseg(chunk, size_asked, mem_type));
	else
	{
		tmp_segs = chunk->first_memseg;
		while (tmp_segs)
		{
			if (tmp_segs->free == 1 && tmp_segs->size > size_asked)
			{
				tmp_segs->free = 0;
				tmp_segs->size = size_asked;
				if (tmp_segs->next)
					return ((char *)add_inner_memseg(tmp_segs,
					chunk, size_asked));
				else
					return ((char *)add_outer_memseg(tmp_segs,
						chunk, size_asked, mem_type));
			}
			tmp_segs = tmp_segs->next;
		}
	}
	return (NULL);
}

void		*add_first_memseg(t_mem_chunk *chunk, size_t size_asked,
								size_t mem_type)
{
	t_mem_seg *tmp_segs;

	tmp_segs = (t_mem_seg *)((char *)chunk + sizeof(t_mem_chunk));
	tmp_segs->next = NULL;
	tmp_segs->free = 0;
	tmp_segs->size = size_asked;
	chunk->size_occupied += sizeof(t_mem_seg) + size_asked;
	chunk->first_memseg = tmp_segs;
	if ((size_t)(mem_type - chunk->size_occupied) > (size_t)sizeof(t_mem_seg))
	{
		tmp_segs->next = (t_mem_seg *)((char *)tmp_segs + sizeof(t_mem_seg)
			+ size_asked);
		tmp_segs->next->free = 1;
		tmp_segs->next->next = NULL;
		chunk->size_occupied += sizeof(t_mem_seg);
		tmp_segs->next->size = (size_t)(mem_type - chunk->size_occupied);
	}
	return ((char *)tmp_segs + sizeof(t_mem_seg));
}

void		*add_inner_memseg(t_mem_seg *tmp_segs, t_mem_chunk *chunk,
						size_t size_asked)
{
	t_mem_seg *tmp_next;

	if ((char *)tmp_segs->next - ((char *)tmp_segs + sizeof(t_mem_seg)
		+ size_asked) > (long)sizeof(t_mem_seg))
	{
		tmp_next = tmp_segs->next;
		tmp_segs->next = (t_mem_seg *)((char *)tmp_segs + sizeof(t_mem_seg)
							+ size_asked);
		tmp_segs->next->free = 1;
		tmp_segs->next->size = (char *)tmp_segs->next -
					((char *)tmp_segs + sizeof(t_mem_seg) + size_asked);
		chunk->size_occupied -= tmp_segs->next->size;
		tmp_segs->next->next = tmp_next;
	}
	return ((char *)tmp_segs + sizeof(t_mem_seg));
}

void		*add_outer_memseg(t_mem_seg *tmp_segs, t_mem_chunk *chunk,
						size_t size_asked, size_t mem_type)
{
	tmp_segs->free = 0;
	tmp_segs->size = size_asked;
	chunk->size_occupied += size_asked;
	if ((size_t)(mem_type - chunk->size_occupied) > (size_t)sizeof(t_mem_seg))
	{
		tmp_segs->next = (t_mem_seg *)((char *)tmp_segs + sizeof(t_mem_seg)
							+ size_asked);
		tmp_segs->next->free = 1;
		tmp_segs->next->next = NULL;
		chunk->size_occupied += sizeof(t_mem_seg);
		tmp_segs->next->size = (size_t)(mem_type - chunk->size_occupied);
	}
	return ((char *)tmp_segs + sizeof(t_mem_seg));
}
