#ifndef CGYM_H
#define CGYM_H

#include <env.h>
//#include <mj_env.h>
#include <cassie_env.h>

/* Mujoco envs */
Environment create_ant_env();
Environment create_hopper_env();
Environment create_half_cheetah_env();
Environment create_humanoid_env();
Environment create_walker2d_env();

Environment create_cassie_env();

#endif
