/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapscan_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 11:10:09 by helarras          #+#    #+#             */
/*   Updated: 2025/04/19 12:31:05 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAPSCAN_BONUS_H
# define MAPSCAN_BONUS_H

# include "../../libft/libft.h"
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>

typedef enum e_mperror
{
	NO_ERROR,
	ERR_EMPTY,
	ERR_INVALID_CHAR,
	ERR_DUPLICATED_DATA,
	ERR_INVALID_DATA,
	ERR_MISSING_DATA,
	ERR_MISSING_COLOR,
	ERR_INVALID_COLOR,
	ERR_MAP_NOT_CLOSED,
	ERR_MULTIPLE_START,
	ERR_NO_START,
	ERR_INVALID_MAP,
	ERR_MAP_NOT_FOUND,
	ERR_FILE_READ,
	ERR_FILE_FORMAT
}				t_mperror;

typedef struct s_point
{
	int			x;
	int			y;
}				t_point;

typedef struct s_entry
{
	char		id;
	char		*value;
}				t_entry;

typedef struct s_texpath
{
	char		*north_tex;
	char		*south_tex;
	char		*east_tex;
	char		*west_tex;
}				t_texpath;

typedef struct s_colors
{
	char		*fcolor_str;
	char		*ccolor_str;
	int			fcolor;
	int			ccolor;
}				t_colors;

typedef struct s_mapscan
{
	t_texpath	texpaths;
	t_mperror	error;
	t_colors	colors;
	char		**map;
	char		mapfd;
	t_point		start_pos;
	t_point		mapsize;
	char		c_direction;
}				t_mapscan;

t_mapscan		*init_mapscan(char *mapfile);
bool			mp_verifymap(t_mapscan *mapscan);
void			mp_clearmap(t_mapscan *mapscan);

// map reader.
void			mp_loadmap(t_mapscan *mapscan);
bool			rdr_readtex(t_mapscan *mapscan, char *line);
bool			rdr_readsurfs(t_mapscan *mapscan, char *line);
bool			rdr_read_data(t_mapscan *mapscan);
char			**rdr_readmap(t_mapscan *mapscan);
bool			mp_post_error(t_mperror error);

// checker.
bool			chk_format(char *mapfile);
bool			chk_color(char *fcolor, int *color);
bool			chk_map(t_mapscan *mapscan);
// utils
char			**ump_create_map(t_list *maplst, t_point mapsize);
void			ump_clear(void *content);
bool			ump_is_empty_line(char *line);
bool			ump_color_toint(char *color_str, char **rgb, int *color);
bool			ump_is_mpcomponent(char c);
#endif