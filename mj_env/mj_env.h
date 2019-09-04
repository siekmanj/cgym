#ifndef MJ_ENV_H
#define MJ_ENV_H

#include <mujoco.h>
#include <glfw3.h>
#include <env.h>
#include <stdio.h>

typedef struct data {
  mjModel *model;
  mjData *data;
  mjvCamera camera;
  mjvOption opt;
  mjvScene scene;
  mjrContext context;
  GLFWwindow *window;
  int render_setup;
  int qpos_start;
} Data;


Environment create_mujoco_env(const char *, float (*step)(Environment, float *), int);

#endif
