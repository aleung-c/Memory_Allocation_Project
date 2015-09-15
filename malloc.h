/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <aleung-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/22 13:41:52 by aleung-c          #+#    #+#             */
/*   Updated: 2015/09/15 18:42:43 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <stdlib.h>
# include <unistd.h>
# include <sys/mman.h>

# define TINY  2
# define TINY_MAXALLOC 54
# define SMALL 50
# define SMALL_MAXALLOC 1024

typedef struct				s_mem_seg
{
	char					free;
	size_t					size;
	struct s_mem_seg		*next;
}							t_mem_seg;

typedef struct				s_mem_chunk
{
	t_mem_seg				*first_memseg;
	t_mem_seg				*last_memseg;
	size_t					size_occupied;
	int						nb_segs;
	struct s_mem_chunk		*next;
}							t_mem_chunk;

typedef struct				s_memzone
{
	t_mem_chunk				*tiny;
	t_mem_chunk				*small;
	t_mem_chunk				*big;
}							t_memzone;

extern t_memzone			g_memzone;

/*
** Functions prototypes.
*/

void						free(void *ptr);
void						free_tiny();
void						free_small();
void						free_big(t_mem_seg *tmp, void *ptr);
void						check_chunk_tiny(t_mem_chunk *chunk);
void						check_chunk_small(t_mem_chunk *chunk);

void						*malloc(size_t size);
char						*allocate_mem(size_t size);

int							check_space(t_mem_chunk *chunk, size_t size,
								size_t mem_type);
void						allocate_tiny(void);
void						allocate_small(void);
void						allocate_big(size_t size);
void						*add_big_seg(size_t size_asked);

char						*search_mem(size_t size);
void						*search_tiny_zone(int size);
void						*search_small_zone(int size);

void						*add_seg_to_chunk(t_mem_chunk *chunk,
								size_t size_asked, size_t mem_type);
void						*add_first_memseg(t_mem_chunk *chunk,
								size_t size_asked, size_t mem_type);
void						*add_inner_memseg(t_mem_seg *tmp_segs,
								t_mem_chunk *chunk, size_t size_asked);
void						*add_outer_memseg(t_mem_seg *tmp_segs,
								t_mem_chunk *chunk, size_t size_asked,
								size_t mem_type);

void						*realloc(void *ptr, size_t size);
void						*realloc_action(void *ptr, t_mem_seg *tmp,
								char *recup, size_t size);

void						show_alloc_mem();
void						show_tiny_mem(int *total_size);
void						show_small_mem(int *total_size);
void						show_big_mem(int *total_size);
void						to_hex(char *buffer, size_t size, unsigned n);
void						display_chunk(char *type, t_mem_chunk *chunks);
void						display_seg(t_mem_seg *segs);

void						ft_putchar(char c);
void						ft_putstr(char const *s);
void						*ft_memcpy(void *dst, const void *src, size_t n);
void						ft_putnbr(int n);
void						ft_putendl(char const *s);

int							ptr_isinlist(void *ptr);
int							ptr_isintiny(void *ptr);
int							ptr_isinsmall(void *ptr);
int							ptr_isinbig(void *ptr);

#endif
