

#include "../include/animator.h"
#include "../include/game.h"

t_animator *init_animator(mlx_t *mlx, bool is_looping)
{
    t_animator *animator;

    animator = malloc(sizeof(t_animator));
    if (!animator)
        return (NULL);
    animator->mlx = mlx;
    animator->is_playing = false;
    animator->last_update_time = mlx_get_time();
    animator->is_looping = is_looping;
    anim_init_animstate(&animator->idle, 100, 0.04);
    anim_init_animstate(&animator->attack1, 18, 0.04);
    // anim_init_animstate(&animator->attack2, 37, 0.05, false);
    animator->current_animstate = &animator->idle;
    return (animator);
}

void    anim_update(t_animator *animator)
{
    t_animstate *animstate;
    double current_time;

    if (!animator->is_playing)
        return ;
    current_time = mlx_get_time();
    animstate = animator->current_animstate;
    if (current_time - animator->last_update_time >= animstate->frame_time)
    {
        animstate->current_frame++;
        animator->last_update_time = current_time;
    }
    if (animstate->current_frame >= animstate->max_frames)
    {
        animstate->current_frame = 0;
        if (!animator->is_looping)
            animator->is_playing = false;
    }
}

void    anim_render(t_animator *animator)
{
    t_animstate *animstate;
    mlx_image_t *frame;
    int previous_frame;

    animstate = animator->current_animstate;
    if (animator->is_hidden)
        return ;
    frame = animstate->frames[animstate->current_frame];
    if (!frame->count) {
        mlx_image_to_window(animator->mlx, frame, (WIDTH / 2) - (frame->width / 2), HEIGHT - frame->height);
    }
    else
        frame->enabled = true;
    previous_frame = animstate->current_frame - 1;
    if (previous_frame < 0)
        previous_frame = animstate->max_frames - 1;
    animstate->frames[previous_frame]->enabled = false;
}

void    anim_set_state(t_animator *animator, t_state state)
{
    t_animstate *current_anim;

    current_anim = animator->current_animstate;
    current_anim->frames[current_anim->current_frame]->enabled = false;
    current_anim->current_frame = 0;
    if (state == IDLE)
    animator->current_animstate = &animator->idle;
    if (state == ATTACK1)
    animator->current_animstate = &animator->attack1;
    if (state == ATTACK2)
        animator->current_animstate = &animator->attack2;
    
    animator->last_update_time = mlx_get_time();
}

void    anim_play(t_animator *animator)
{
    animator->is_hidden = false;
    animator->is_playing = true;
}
