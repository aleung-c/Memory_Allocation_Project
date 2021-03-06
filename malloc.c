/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <aleung-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/05 10:38:50 by aleung-c          #+#    #+#             */
/*   Updated: 2015/09/15 18:13:22 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <stdio.h>

t_memzone g_memzone = { NULL, NULL, NULL };

void		*malloc(size_t size)
{
	void *ret;

	ret = allocate_mem(size);
	return (ret);
}
