
#include <stdio.h>
#include "../include/animator_bonus.h"
#include "../include/gfx_manager_bonus.h"

bool    anim_load_idle(t_animator *animator, t_list **graphics)
{
    int i;
    char framepath[80];
    char base_path[] = "Bonus/textures/zombie/idle/frame_";
    t_animstate *idle_state;

    idle_state = &animator->idle;
    i = 0;
    while (i < idle_state->max_frames)
    {
        snprintf(framepath, sizeof(framepath), "%s%i.png", base_path, i);
        idle_state->frames[i] = gfx_create_teximage(animator->mlx, graphics, framepath);
        if (!idle_state->frames[i])
            return (false);
        i++;
    }
    return (true);
}

bool    anim_load_attack1(t_animator *animator, t_list **graphics)
{
    int i;
    char framepath[80];
    char base_path[] = "Bonus/textures/zombie/attack1/frame_";
    t_animstate *attack1_state;

    attack1_state = &animator->attack1;
    i = 0;
    while (i < attack1_state->max_frames)
    {
        snprintf(framepath, sizeof(framepath), "%s%i.png", base_path, i);
        attack1_state->frames[i] = gfx_create_teximage(animator->mlx, graphics, framepath);
        if (!attack1_state->frames[i])
            return (false);
        i++;
    }
    return (true);
}

bool    anim_load_attack2(t_animator *animator, t_list **graphics)
{
    int i;
    char framepath[80];
    char base_path[] = "Bonus/textures/zombie/attack2/frame_";
    t_animstate *attack2_state;
    
    attack2_state = &animator->attack2;
    i = 0;
    while (i < attack2_state->max_frames)
    {
        snprintf(framepath, sizeof(framepath), "%s%i.png", base_path, i);
        attack2_state->frames[i] = gfx_create_teximage(animator->mlx, graphics, framepath);
        if (!attack2_state->frames[i])
            return (false);
        i++;
    }
    return (true);
}

void    anim_init_animstate(t_animstate *animstate, int max_frames, double frame_time, bool is_looping)
{
    animstate->max_frames = max_frames;
    animstate->current_frame = 0;
    animstate->frame_time = frame_time;
    animstate->is_hidden = true;
    animstate->is_looping = is_looping;
}