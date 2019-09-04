#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <stdlib.h>

/*
 * Use this struct to interface an environment.
 *
 */
typedef struct env_ {
  float *state;
  void *data;
  
  size_t action_space;
  size_t observation_space;

  size_t frameskip;
  float alive_bonus;

  int *done;

  void (*dispose)(struct env_ env);
  void (*reset)(struct env_ env);
  void (*seed)(struct env_ env);
  void (*render)(struct env_ env);
  void (*close)(struct env_ env);
  float (*step)(struct env_ env, float *action);
  
} Environment;

/* Mujoco envs */
Environment create_ant_env(const char *);
Environment create_hopper_env(const char *);
Environment create_half_cheetah_env(const char *);
Environment create_humanoid_env(const char *);
Environment create_walker2d_env(const char *);

#endif

