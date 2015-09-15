/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_checkptr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <aleung-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/15 14:30:56 by aleung-c          #+#    #+#             */
/*   Updated: 2015/09/15 18:18:25 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int		ptr_isinlist(void *ptr)
{
	if (ptr_isintiny(ptr) == 1 || ptr_isinsmall(ptr) == 1
		|| ptr_isinbig(ptr) == 1)
		return (1);
	return (0);
}

int		ptr_isintiny(void *ptr)
{
	t_mem_chunk		*tmp_chunk;
	t_mem_seg		*segs;

	tmp_chunk = g_memzone.tiny;
	if (!tmp_chunk)
		return (0);
	segs = tmp_chunk->first_memseg;
	while (tmp_chunk)
	{
		segs = tmp_chunk->first_memseg;
		while (segs)
		{
			if ((char *)segs + sizeof(t_mem_seg) == (char *)ptr)
				return (1);
			segs = segs->next;
		}
		tmp_chunk = tmp_chunk->next;
	}
	return (0);
}

int		ptr_isinsmall(void *ptr)
{
	t_mem_chunk		*tmp_chunk;
	t_mem_seg		*segs;

	tmp_chunk = g_memzone.small;
	if (!tmp_chunk)
		return (0);
	segs = tmp_chunk->first_memseg;
	while (tmp_chunk)
	{
		segs = tmp_chunk->first_memseg;
		while (segs)
		{
			if ((char *)segs + sizeof(t_mem_seg) == (char *)ptr)
				return (1);
			segs = segs->next;
		}
		tmp_chunk = tmp_chunk->next;
	}
	return (0);
}

int		ptr_isinbig(void *ptr)
{
	t_mem_chunk		*chunks;
	t_mem_seg		*segs;

	chunks = g_memzone.big;
	if (!chunks)
		return (0);
	while (chunks)
	{
		segs = chunks->first_memseg;
		while (segs)
		{
			if ((char *)segs + sizeof(t_mem_seg) == ptr)
				return (1);
			segs = segs->next;
		}
		chunks = chunks->next;
	}
	return (0);
}
