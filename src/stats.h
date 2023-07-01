#pragma once

#include "./etc.h"

using namespace std;

const char* skill_strings[]={"paralyze","seduce","pilfer","trolls_blood","howl","hell_fire","fail"};
const char* type_strings[]={"unique","goblin","troll","werewolf","vampire","dragon","lich","math teacher"};

//data structure to store values for player & enemies.
struct stats{
public:
	enum skill{paralyze,seduce,pilfer,trolls_blood,howl,hell_fire,fail};
	enum type{unique,goblin,troll,werewolf,vampire,dragon,lich,math_teacher};
	string name="";
	int health_max=0;
	int health=0;
	int damage=0;
	float power_scale=1;
	int stun=0;
	int skill_cool=0;
	skill skill2;
	type type2;

	stats(){}
	stats(string name,int health_max,int damage2,float power_scale=1,skill skill22=(skill)0,type type2=(type)0):name(name),health_max(health_max),health(health_max),damage(damage2),power_scale(power_scale),skill2(skill22),type2(type2){
		switch((int)type2){
			case (int)stats::type::goblin:{
				health=50;
				damage=10;
				skill2=stats::skill::pilfer;
				break;
			}
			case (int)stats::type::troll:{
				health=100;
				damage=20;
				skill2=stats::skill::trolls_blood;
				break;
			}
			case (int)stats::type::werewolf:{
				health=175;
				damage=35;
				skill2=stats::skill::howl;
				break;
			}
			case (int)stats::type::vampire:{
				health=350;
				damage=50;
				skill2=stats::skill::seduce;
				break;
			}
			case (int)stats::type::dragon:{
				health=500;
				damage=60;
				skill2=stats::skill::hell_fire;
				break;
			}
			case (int)stats::type::lich:{
				health=700;
				damage=70;
				skill2=stats::skill::paralyze;
				break;
			}
			case (int)stats::type::math_teacher:{
				health=999;
				damage=99;
				skill2=stats::skill::fail;
				break;
			}
		}
		health*=power_scale;
		damage*=power_scale;
	}
	stats(string name,float power_scale,type type2):name(name),power_scale(power_scale),type2(type2){
		*this=stats(name,0,0,power_scale,(skill)0,type2);
	}
	void attack(stats& character){
		int min=damage-(damage/4);
		int damageTaken=get_random(min,min+damage);
		character.health-=damageTaken;
	}
	void heal(){
		int max=(int)(health_max/5);
		int health_given=get_random(max/2,max);
		health+=health_given;
	}
	//skill action.
	void use_skill(stats& character){
		switch((int)skill2){
			case (int)skill::paralyze:{
				character.stun+=2;
				skill_cool+=4;
				break;
			}
			case (int)skill::seduce:{
				character.stun+=1;
				health+=health_max/4;
				skill_cool+=4;
				break;
			}
			case (int)skill::pilfer:{
				character.health-=(damage*3/4);
				health+=(damage*2/4);
				skill_cool+=3;
				break;
			}
			case (int)skill::trolls_blood:{
				health=health_max;
				skill_cool+=4;
				break;
			}
			case (int)skill::howl:{
				character.damage-=(damage/10);
				damage+=(damage/10);
				skill_cool+=3;
				break;
			}
			case (int)skill::hell_fire:{
				character.health-=(damage*2);
				skill_cool+=4;
				break;
			}
			case (int)skill::fail:{
				character.health-=(damage*3);
				character.damage-=(character.damage/20);
				skill_cool+=5;
				break;
			}
		}
	}
	string get_health_bar(const unsigned len=25){
		int numBars=(health*len)/health_max;
		string healthBar="[";
		for(int i=0;i<len;i++){
			if(i<numBars){
				healthBar+="#";
			}
			else{
				healthBar+=".";
			}
		}
		healthBar+="]";
		return healthBar;
	}
	operator string() const {
		return "Name: "+color::set_clr(name,color::yellow)+
		"\nHealth: "+to_string(health)+
		"\nDamage: "+to_string(damage)+
		"\nSkill: "+skill_strings[(int)skill2]+
		"\nType: "+type_strings[(int)type2];
	}
};