/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_mem.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <aleung-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/06 10:00:03 by aleung-c          #+#    #+#             */
/*   Updated: 2015/08/14 10:31:33 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int			check_space(t_mem_chunk *chunk, size_t size, size_t mem_type)
{
	size_t			free_space;
	t_mem_seg		*tmp_segs;

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

char		*search_mem(size_t size)
{
	if (size + sizeof(t_mem_seg) < (TINY - sizeof(t_mem_chunk)))
		return ((char *)search_tiny_zone(size));
	else if (size + sizeof(t_mem_seg) < (SMALL - sizeof(t_mem_chunk)))
		return ((char *)search_small_zone(size));
	else
	{
		allocate_big(size);
		return ((char *)add_big_seg(size));
	}
	return (NULL);
}

void		*search_tiny_zone(int size)
{
	t_mem_chunk		*tmp;
	void			*ret;

	ret = NULL;
	tmp = g_memzone.tiny;
	while (tmp)
	{
		if (check_space(tmp, size, TINY) == 1)
		{
			ret = add_seg_to_chunk(tmp, size, TINY);
			return ((char *)ret);
		}
		tmp = tmp->next;
	}
	if (!tmp)
	{
		allocate_tiny();
		ret = search_mem(size);
	}
	return (ret);
}

void		*search_small_zone(int size)
{
	t_mem_chunk		*tmp;
	void			*ret;

	ret = NULL;
	tmp = g_memzone.small;
	while (tmp)
	{
		if (check_space(tmp, size, SMALL) == 1)
		{
			ret = add_seg_to_chunk(tmp, size, SMALL);
			return ((char *)ret);
		}
		tmp = tmp->next;
	}
	if (!tmp)
	{
		allocate_small();
		ret = search_mem(size);
	}
	return (ret);
}
