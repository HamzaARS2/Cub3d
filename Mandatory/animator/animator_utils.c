
#include <stdio.h>
#include "../include/animator.h"
#include "../include/gfx_manager.h"

void    anim_load_frames(t_animator *animator, t_list **graphics)
{
    int i;
    char framepath[60];
    char base_path[] = "Mandatory/textures/balrog_frames/idle/frame_";

    i = 0;
    while (i < animator->max_frames)
    {
        snprintf(framepath, sizeof(framepath), "%s%i.png", base_path, i);
        animator->frames[i] = gfx_create_teximage(animator->mlx, graphics, framepath);
        i++;
    }
}

void    anim_load_idle(t_animator *animator, t_list **graphics)
{
    int i;
    char framepath[60];
    char base_path[] = "Mandatory/textures/balrog_frames/idle/frame_";
    i = 0;
    while (i < animator->idle.max_frames)
    {
        snprintf(framepath, sizeof(framepath), "%s%i.png", base_path, i);
        animator->idle.frames[i] = gfx_create_teximage(animator->mlx, graphics, framepath);
        i++;
    }
}

void    anim_load_attack1(t_animator *animator, t_list **graphics)
{
    int i;
    char framepath[60];
    char base_path[] = "Mandatory/textures/balrog_frames/attack1/frame_";

    i = 0;
    while (i < animator->attack1.max_frames)
    {
        snprintf(framepath, sizeof(framepath), "%s%i.png", base_path, i);
        animator->attack1.frames[i] = gfx_create_teximage(animator->mlx, graphics, framepath);
        i++;
    }
}

void    anim_load_attack2(t_animator *animator, t_list **graphics)
{
    int i;
    char framepath[60];
    char base_path[] = "Mandatory/textures/balrog_frames/attack2/frame_";
    t_animstate *attack2_state;
    
    attack2_state = &animator->attack2;
    i = 0;
    while (i < animator->attack2.max_frames)
    {
        snprintf(framepath, sizeof(framepath), "%s%i.png", base_path, i);
        animator->attack2.frames[i] = gfx_create_teximage(animator->mlx, graphics, framepath);
        i++;
    }
}

void    anim_init_animstate(t_animstate *animstate, int max_frames, double frame_time, bool is_looping)
{
    animstate->max_frames = max_frames;
    animstate->current_frame = 0;
    animstate->frame_time = frame_time;
    animstate->is_hidden = true;
    animstate->is_looping = is_looping;
}