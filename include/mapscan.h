/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapscan.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 11:10:09 by helarras          #+#    #+#             */
/*   Updated: 2024/11/25 13:11:06 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAPSCAN_H
# define MAPSCAN_H

# include <fcntl.h>
# include <stdio.h>
# include "include/utils.h"
# include "include/get_next_line.h"

typedef enum e_mperror {
	NO_ERROR,			// Map is valid
    ERR_EMPTY,          // Map is empty
    ERR_INVALID_CHAR,   // Map contains invalid characters
    ERR_MISSING_TEXTURE, // Missing texture path (NO, SO, WE, EA)
    ERR_INVALID_TEXTURE, // Invalid texture path format
    ERR_MISSING_COLOR,  // Missing floor or ceiling color definition
    ERR_INVALID_COLOR,  // Invalid color format (e.g., incorrect RGB values)
    ERR_MAP_NOT_CLOSED, // Map is not surrounded by walls
    ERR_MULTIPLE_START, // Multiple player start positions
    ERR_NO_START,       // No player start position
    ERR_INVALID_MAP,    // General invalid map layout or format
    ERR_TOO_LARGE,      // Map exceeds allowed size
    ERR_FILE_READ,      // Error reading the map file
    ERR_FILE_FORMAT     // Incorrect map file format
} t_mperror;


typedef struct s_maplst {
	char			*line;
	struct s_maplst	*next;
} t_maplst;

typedef struct s_mapscan {
	t_maplst	*textures;
	t_maplst	*surfaces;
	t_mperror	error;
	char		**map;
	char		*line;
	int			i;
} t_mapscan;

t_mapscan	*init_mapscan(char *mapfile);

// map reader.
t_maplst	*rdr_readtex(char *mapfile);
t_maplst	*rdr_readsurfs(char *mapfile);
bool		rdr_readmap(t_mapscan *mapscan, char *mapfile);







#endif