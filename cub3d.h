/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czghoumi <czghoumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 23:09:16 by czghoumi          #+#    #+#             */
/*   Updated: 2025/11/22 11:33:07 by czghoumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <stdio.h>
# include <stdint.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdbool.h>
# include "libft/libft.h"
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 50
# endif

typedef struct rgb
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
}	t_rgb;

typedef struct s_pars
{
	char	**map;
	t_rgb	*floor;
	t_rgb	*ceil;
	char	*no;
	char	*so;
	char	*ea;
	char	*we;
	bool	stop;
}	t_pars;

char	*get_next_line(int fd);
int		ft_found(const char *str, char c);
char	*ft_char_front(char *s);
char	*ft_read(char *str, char *buffer, int fd);
char	*ft_char_back(char *s);
void	ft_copy(char *dest, const char *src, size_t src_len);
int		fill_mapst(char *line, t_pars *my_map);
char	*firs_word(char *line);
int		ft_count(char const *s);
char	*last_word(char *line);
void	free_mymap(t_pars *my_map);
t_rgb	*colors_parce(char *word);
char	*trim_line(char *line);

#endif