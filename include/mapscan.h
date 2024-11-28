/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapscan.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 11:10:09 by helarras          #+#    #+#             */
/*   Updated: 2024/11/28 13:21:14 by helarras         ###   ########.fr       */
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

typedef struct s_entry {
    char    id;
    char    *value;
} t_entry;

typedef struct s_mapscan {
	t_list      *textures;
    char        *floor;
    char        *ceilling;
    char		**map;
	char        mapfd;
    
} t_mapscan;

t_mapscan	*init_mapscan(char *mapfile);

// map reader.
void	mp_loadmap(t_mapscan *mapscan);
bool	rdr_readtex(t_mapscan *mapscan, char *line);
bool	rdr_readsurfs(t_mapscan *mapscan, char *line);




#endif