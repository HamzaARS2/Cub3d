

#include "../include/animator.h"
#include "../include/game.h"

t_animator *init_animator(mlx_t *mlx, int max_frames, bool is_looping, bool is_hidden)
{
    t_animator *animator;

    animator = malloc(sizeof(t_animator));
    if (!animator)
        return (NULL);
    animator->mlx = mlx;
    animator->max_frames = max_frames;
    animator->is_looping = is_looping;
    animator->is_hidden = is_hidden;
    animator->current_frame = 0;
    animator->frame_count = 0;
    animator->frame_rate = 5;
    animator->is_playing = false;
}

void    anim_update(t_animator *animator)
{
    if (!animator->is_playing)
        return ;
    if (++animator->frame_count >= animator->frame_rate)
    {
        animator->current_frame++;
        animator->frame_count = 0;
    }
    if (animator->current_frame >= animator->max_frames)
    {
        animator->current_frame = 0;
        if (!animator->is_looping)
            animator->is_playing = false;
    }
}

void    anim_render(t_animator *animator)
{
    mlx_image_t *frame;
    int previous_frame;

    if (animator->is_hidden)
        return ;
    frame = animator->frames[animator->current_frame];
    if (!frame->count)
        mlx_image_to_window(animator->mlx, frame, 0, HEIGHT / 2);
    else
        frame->enabled = true;
    previous_frame = animator->current_frame - 1;
    if (previous_frame < 0)
        previous_frame = animator->max_frames - 1;
    animator->frames[previous_frame]->enabled = false;
}

void    anim_play(t_animator *animator)
{
    animator->is_hidden = false;
    animator->is_playing = true;
}
