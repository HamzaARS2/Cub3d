/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapscan.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 11:10:09 by helarras          #+#    #+#             */
/*   Updated: 2024/12/22 15:14:58 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAPSCAN_H
# define MAPSCAN_H

# include <fcntl.h>
# include <stdio.h>
# include <stdbool.h>
# include "../libft/libft.h"
# include "get_next_line.h"

typedef enum e_mperror {
	NO_ERROR,			// Map is valid
    ERR_EMPTY,          // Map is empty
    ERR_INVALID_CHAR,   // Map contains invalid characters
    ERR_DUPLICATED_DATA, // duplicated data.
    ERR_INVALID_DATA, // Invalid texture path format
    ERR_MISSING_DATA, // Missing data (Texture, Color)
    ERR_MISSING_COLOR,  // Missing floor or ceiling color definition
    ERR_INVALID_COLOR,  // Invalid color format (e.g., incorrect RGB values)
    ERR_MAP_NOT_CLOSED, // Map is not surrounded by walls
    ERR_MULTIPLE_START, // Multiple player start positions
    ERR_NO_START,       // No player start position
    ERR_INVALID_MAP,    // General invalid map layout or format
    ERR_MAP_NOT_FOUND,    // No map can be found
    ERR_FILE_READ,      // Error reading the map file
    ERR_FILE_FORMAT     // Incorrect map file format
} t_mperror;

typedef struct s_vector2 {
	int x;
	int y;
} t_vector2;

typedef struct s_entry {
    char    id;
    char    *value;
} t_entry;

typedef struct s_textures {
    char *north_tex;
    char *south_tex;
    char *east_tex;
    char *west_tex;
} t_textures;

typedef struct s_colors {
    char    *fcolor_str;
    char    *ccolor_str;
    int     fcolor;
    int     ccolor;
} t_colors;

typedef struct s_mapscan {
	t_textures  textures;
    t_mperror    error;
    t_colors    colors;
    char		**map;
	char        mapfd;
    t_vector2   start_pos;
} t_mapscan;

t_mapscan	*init_mapscan(char *mapfile);
bool        mp_verifymap(t_mapscan *mapscan);
void	    mp_clearmap(t_mapscan *mapscan);

// map reader.
void	mp_loadmap(t_mapscan *mapscan);
bool	rdr_readtex(t_mapscan *mapscan, char *line);
bool	rdr_readsurfs(t_mapscan *mapscan, char *line);
bool	rdr_read_data(t_mapscan *mapscan);
char	**rdr_readmap(t_mapscan *mapscan);
bool	mp_post_error(t_mperror error);

// checker.
bool        chk_format(char *mapfile);
bool	    chk_color(char *fcolor, int *color);
bool	    chk_map(t_mapscan *mapscan);
// utils
char	**ump_create_map(t_list *maplst, int mapsize);
void	ump_clear(void *content);
bool	ump_is_empty_line(char *line);
bool	ump_color_toint(char *color_str, char **rgb, int *color);
bool	ump_is_mpcomponent(char c);
#endif