
#ifndef ANIMATOR_H
# define ANIMATOR_H

# include "../../MLX42/include/MLX42/MLX42.h"
# include "../../libft/libft.h"

typedef enum e_state {
    IDLE,
    ATTACK1,
    ATTACK2
} t_state;

typedef struct s_animstate {
    mlx_image_t *frames[100];
    int max_frames;
    int current_frame;
    double frame_time;
    bool    is_looping;
} t_animstate;

typedef struct s_animator {
    mlx_t *mlx;
    t_animstate *current_animstate;
    t_animstate idle;
    t_animstate attack1;
    t_animstate attack2;
    int max_frames;
    double last_update_time;
    bool is_playing;
    bool is_hidden;
} t_animator;



t_animator *init_animator(mlx_t *mlx, bool is_looping);

void    anim_update(t_animator *animator);

void    anim_render(t_animator *animator);

void    anim_play(t_animator *animator);

void    anim_init_animstate(t_animstate *animstate, int max_frames, double frame_time, bool is_looping);

bool    anim_load_idle(t_animator *animator, t_list **graphics);

bool    anim_load_attack1(t_animator *animator, t_list **graphics);
bool    anim_load_attack2(t_animator *animator, t_list **graphics);

void    anim_set_state(t_animator *animator, t_state state);
#endif