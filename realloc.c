/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <aleung-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/11 12:47:52 by aleung-c          #+#    #+#             */
/*   Updated: 2015/09/15 18:25:24 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*realloc(void *ptr, size_t size)
{
	t_mem_seg		*tmp;
	char			*recup;

	recup = malloc(size);
	if (!ptr)
		return (malloc(size));
	if (ptr_isinlist(ptr) == 0)
		return (NULL);
	tmp = (t_mem_seg *)((char *)ptr - sizeof(t_mem_seg));
	return (realloc_action(ptr, tmp, recup, size));
}

void	*realloc_action(void *ptr, t_mem_seg *tmp, char *recup, size_t size)
{
	void			*new_alloc;

	if (size <= tmp->size)
	{
		ft_memcpy(recup, (char *)ptr, size);
		free(ptr);
		new_alloc = malloc(size);
		ft_memcpy(new_alloc, recup, size);
		return ((char *)new_alloc);
	}
	else if (size > tmp->size)
	{
		new_alloc = malloc(size);
		ft_memcpy(new_alloc, ptr, size);
		free(ptr);
		return ((char *)new_alloc);
	}
	return (NULL);
}
