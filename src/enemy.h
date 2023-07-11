#pragma once

#include "./stats.h"

using namespace std;

//FIXME: revert back to testing newer enemies for campaign mode rather than the arena mode.
/*stats grimm_reaper("Grimm Reaper",.5,stats::type::lich);
stats potato("POTATO!!!",1000,100,1,stats::skill::seduce,stats::type::unique);
stats enemies[]={stats(),grimm_reaper,potato};*/
stats enemies[(int)stats::type::math_teacher];