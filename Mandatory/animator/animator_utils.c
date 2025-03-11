
#include <stdio.h>
#include "../include/animator.h"
#include "../include/gfx_manager.h"

void    anim_load_frames(t_animator *animator, t_list **graphics)
{
    int i;
    char framepath[53];
    char base_path[] = "Mandatory/textures/balrog_frames/idle/wp_frame_";

    i = 0;
    while (i < animator->max_frames)
    {
        snprintf(framepath, sizeof(framepath), "%s%i.png", base_path, i);
        animator->frames[i] = gfx_create_teximage(animator->mlx, graphics, framepath);
        i++;
    }
}