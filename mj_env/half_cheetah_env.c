#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <mj_env.h>
#define ALIVE_BONUS 0.0f

static float step(Environment env, float *action){
  Data *tmp = ((Data*)env.data);
  mjData *d = tmp->data;
  mjModel *m = tmp->model;

  float posbefore = d->qpos[0];

  mjtNum simstart = d->time;
  for(int i = 0; i < env.action_space; i++)
    d->ctrl[i] = action[i];
  
  for(int i = 0; i < env.frameskip; i++)
    mj_step(m, d);

  for(int i = tmp->qpos_start; i < m->nq; i++)
    env.state[i - tmp->qpos_start] = d->qpos[i];

  for(int i = 0; i < m->nv; i++)
    env.state[i + m->nq - tmp->qpos_start] = d->qvel[i];

  for(int i = 0; i < env.observation_space; i++){
    if(isnan(env.state[i])){
      printf("\nWARNING: NaN in observation vector - aborting episode early.\n");
      *env.done = 1;
      return 0;
    }
  }

  /* REWARD CALCULATION: Identical to OpenAI's */
  
  float reward_run = (d->qpos[0] - posbefore) / (d->time - simstart);

  float reward_ctrl = 0;
  for(int i = 0; i < env.action_space; i++)
    reward_ctrl -= 0.1 * action[i] * action[i];

  float reward = reward_ctrl + reward_run;

  return reward;
}

Environment create_half_cheetah_env(){

#ifndef MJASSETS
  fprintf(stderr, "Please #define the folder in which to find mujoco xml files with MJASSETS.\n");
  exit(1);
#endif

#ifndef WIN32
  char buff[strlen(def2str(MJASSETS)) + strlen("/half_cheetah.xml") + 1];
  strcpy(buff, def2str(MJASSETS));
  strcat(buff, "/half_cheetah.xml");

#else
  printf("Add windows filepath support!\n");
#endif
  Environment ret = create_mujoco_env(buff, step, 1);
  ret.alive_bonus = 0.0f;
  ret.frameskip = 5;
  return ret;
}


