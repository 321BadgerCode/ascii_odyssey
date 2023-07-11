//get libraries & local header files.
#include <iostream>
#include <time.h>
#include <fstream>
#include <vector>
#include <fstream>
#include <limits>
#include <algorithm>
#include <random>
#include "./clr.h"
#include "./console.h"
#include "./enemy.h"
#include "./etc.h"
#include "./map.h"
#include "./name.h"
#include "./npc.h"
#include "./stats.h"
#include "./vector.h"

using namespace std;

int round_num=0;

//global object variables for player & enemies.
stats player("player",100,10);
stats enemy;
//stats enemies[(stats::type)((int)stats::type::math_teacher+1)];

//gets the option from the user on what action to do.
int get_option(){
	cout<<"||\t1: Attack\t\t\t\t\t||"<<endl;
	cout<<"||\t2: Heal\t\t\t\t\t\t||"<<endl;
	cout<<"||\t3: Skill\t\t\t\t\t||"<<endl;
	cout<<"||\t4: Flee\t\t\t\t\t\t||"<<endl;
	cout<<color::set_clr(player.get_health_bar(get_len2("||\t4: Flee\t\t\t\t\t\t||")-2),(new color::rgb(255,0,0))->get_lerp(new color::rgb(0,255,0),(float)player.health/(float)player.health_max))<<endl;

coda:
	cout<<"Answer: ";
	int option=0;
	try{
		cin>>option;
		if (cin.fail()) {
			cout<<"Invalid input. Please try again."<<endl;
			cin.clear(); //clear the error state
			cin.ignore(numeric_limits<streamsize>::max(),'\n'); //clear the input buffer
			goto coda;
		}
		cin.ignore();
	}
	catch(...){
		cerr<<"[._.]: ERROR; INVALID INPUT!"<<endl;
		goto coda;
	}
	clear();
	return option;
}

//displays UI box.
void ui(){
	string enemy_name_padded=pad_text(enemy.name,get_len2("||\t\t\t\t\t\t\t||"),4);
	string player_health_padded=pad_text(to_string(player.health),get_len2("Enemy Health"));
	string player_damage_padded=pad_text(to_string(player.damage),get_len2("Enemy Damage"));
	string enemy_health_padded=pad_text(to_string(enemy.health),get_len2("Enemy Health"));
	string enemy_damage_padded=pad_text(to_string(enemy.damage),get_len2("Enemy Damage"));

	//displays enemy ASCII art.
	ifstream file(string("../asset/enemy/")+type_strings[(int)enemy.type2]+string(".txt"));
	string line;
	while(getline(file,line)){
		cout<<line<<endl;
	}
	file.close();

	//displays UI box.
	cout<<endl;
	cout<<"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"<<endl;
	cout<<"||"<<color::set_clr(enemy_name_padded, color::yellow)<<"||"<<endl;
	cout<<"||======================================================||"<<endl;
	cout<<"||\tPlayer Health\t\tEnemy Health\t\t||"<<endl;
	cout<<"||\t"<<player_health_padded<<"\t\t"<<enemy_health_padded<<"\t\t||"<<endl;
	cout<<"||\tPlayer Damage\t\tEnemy Damage\t\t||"<<endl;
	cout<<"||\t"<<player_damage_padded<<"\t\t"<<enemy_damage_padded<<"\t\t||"<<endl;
	cout<<"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"<<endl;
}

//called when player is attacking enemy.
string fight(){
string out="";
coda:
	if(player.stun==0){
		int option=get_option();
		if(option==3&&player.skill_cool!=0){
			cout<<color::set_clr(player.name+string("'s "),color::yellow)<<color::set_clr(skill_strings[(int)player.skill2],color::orange)<<" skill is on cooldown currently."<<endl;
			cout<<"The skill will reactivate in "<<player.skill_cool<<" rounds."<<endl;
			cout<<"Choose another action."<<endl;
			goto coda;
		}
		switch(option){
			case 1:{
				int enemy_health=enemy.health;
				player.attack(enemy);
				out=("Player attacked enemy by "+to_string(enemy_health-enemy.health)+" points!");
				break;
			}
			case 2:{
				int player_health=player.health;
				player.heal();
				out=("Player healed by "+to_string(player.health-player_health)+" points!");
				break;
			}
			case 3:{
				player.use_skill(enemy);
				out=string("Player used ")+skill_strings[(int)player.skill2]+"!";
				break;
			}
			case 4:{
				cout<<"You have fled the battle!"<<endl;
				exit(0);
				break;
			}
		}
	}
	else{
		out="Player paralyzed!";
		player.stun-=1;
	}
	if(player.skill_cool!=0){
		player.skill_cool--;
	}
	return out;
}

//called when enemy is attacking player.
string enemy_fight(){
string out="";
coda:
	int option=0;
	if(enemy.stun==0){
		option=get_random(1,3);
		if(option==3&&enemy.skill_cool!=0){
			goto coda;
		}
		string out="";
		switch(option){
			case 1:{
				int player_health=player.health;
				enemy.attack(player);
				out=("Enemy attacked player by "+to_string(player_health-player.health)+" points!");
				break;
			}
			case 2:{
				int enemy_health=enemy.health;
				enemy.heal();
				out=("Enemy healed itself by "+to_string(enemy.health-enemy_health)+" points!");
				break;
			}
			case 3:{
				enemy.use_skill(player);
				out=(string("Enemy used ")+skill_strings[(int)enemy.skill2]+string("!"));
				break;
			}
		}
		return out;
	}
	else{
		out="Enemy paralyzed!";
		enemy.stun-=1;
	}
	if(enemy.skill_cool!=0){
		enemy.skill_cool--;
	}
	return out;
}

//main function called when program runs.
int main(int argc,char** argv){
	//display logo for game.
	ifstream file("../asset/txt/logo.txt");
	string line;
	int a=0;
	while(getline(file,line)){
		cout<<color::set_clr(line,color::type::fg,a+1)<<'\n';
		a++;
	}
	file.close();

	//display info. for game.
	cout<<endl;
	cout<<"Welcome to "+color::set_clr("ASCII Odyssey",color::yellow)+"! In this game, you take on the role of a brave warrior who must battle fierce monsters to emerge victorious. Your goal is to defeat each monster you encounter without dying or fleeing the battle. Only by defeating all the monsters can you emerge victorious. Good luck, warrior!"<<endl;
	cout<<endl;
	cout<<"Skill info:"<<endl;
	cout<<	color::set_clr("Paralyze:",color::red)+" The player/enemy uses a paralyzing attack that temporarily incapacitates the opponent, reducing their ability to attack or defend for a certain number of turns.\n"<<
		color::set_clr("Seduce:",color::orange)+" The player/enemy uses their charm to distract the opponent, causing them to lose focus and miss their next attack.\n"<<
		color::set_clr("Pilfer:",color::yellow)+" The player/enemy takes away the opponent's health and adds onto its health.\n"<<
		color::set_clr("Troll's Blood:",color::green)+" The player/enemy consumes a potion made from troll's blood, instantly restoring a significant amount of health.\n"<<
		color::set_clr("Howl:",color::blue)+" The player/enemy lets out a deafening howl that lowers the enemy's damage and adds onto its damage.\n"<<
		color::set_clr("Hell Fire:",color::violet)+" The player/enemy unleashes a powerful fire attack that deals massive damage to the opponent.\n"<<
		color::set_clr("Fail:",color::red)+" The player/enemy takes away health and damage from the opponent."<<endl;
	cout<<endl;

setup:
	//TODO: implement rather than just using for testing.
	/////////////////////////////////////////
	/*map m1("../asset/map/2.txt");
	while(true){
		clear();
		cout<<(string)m1<<endl;

		string input;
		cin>>input;

		switch(input.c_str()[0]){
			case 'w': //up
				m1.move_player(ao::vector<int>(-1,0));
				break;
			case 's': //down
				m1.move_player(ao::vector<int>(1,0));
				break;
			case 'a': //left
				m1.move_player(ao::vector<int>(0,-1));
				break;
			case 'd': //right
				m1.move_player(ao::vector<int>(0,1));
				break;
		}
	}*/
	//npc n1("Billy",ao::vector<int>(5,5),new string[6]{"Howdy there "+player.name+"!","These lands are spooky.","I saw a ghostly figure creep 'round the treachurous tree :O","I don't like ghosts.","Could you defeat the ghost for me?",""});
	//n1.talk();
	/////////////////////////////////////////
	//get input from user such as player name & skill.
	try{
		slow_type("Player name: ");cin.clear();cin>>player.name;
		//easter egg ;)
		if(player.name=="fence"||player.name=="potato"||player.name=="enemy"){
			throw(player.name);
		}
		player.name=get_capitalize(player.name);

		//display available skills & give player the selected skill.
		for(int a=0;a<get_len(skill_strings);a++){
			cout<<a+1<<". "<<color::set_clr(skill_strings[a],color::type::fg,a+1)<<endl;
		}
skill:
		int p_skill;
		slow_type("Choose skill: ");cin.ignore(numeric_limits<streamsize>::max(),'\n');cin>>p_skill;
		if(p_skill<1||p_skill>get_len(skill_strings)){
			cout<<"[._.]: INVALID SKILL!"<<endl;
			goto skill;
		}
		player.skill2=((stats::skill)(p_skill-1));
	}
	catch(string name){
		cerr<<"[._.]: NO,YOU CANNOT NAME YOURSELF \""+name+"\"!!!"<<endl;
		exit(0);
	}
	catch(...){
		cout<<"[._.]: INVALID INPUT!"<<endl;
		goto setup;
	}

	cout<<endl;
	cout<<(string)player<<endl;
	cout<<color::set_clr("Enemies that you will face, ",color::red)+color::set_clr(player.name,color::yellow)+color::set_clr(":",color::red)<<endl;
	cout<<endl;

	vector<string> names=read_file("../asset/name/name.txt");
	vector<string> adjectives=read_file("../asset/name/adj.txt");

	//set enemies' stats.
	//FIXME: only for arena mode, not campaign.
	for(int a=1;a<get_len(enemies);a++){
		stats e1(generate_enemy_name(names,adjectives)+" "+get_capitalize(type_strings[a]),(float)1,(stats::type)a);
		enemies[a]=e1;
		cout<<(string)e1<<endl;
		cout<<endl;
	}

	cout<<"[._.]: Press any key to continue...";cin.ignore();cin.get();
	clear();

	//iterate through each enemy, so player can fight each 1.
	for(int a=1;a<get_len(enemies);a++){
		enemy=enemies[a];
		player.health=player.health_max;
		round_num=0;
		ui();

		//player fights the given enemy.
		while(true){
			round_num++;
			cout<<"||	Round: "<<round_num<<"					||"<<endl;

			enemies[a].health=enemy.health;

			string self=pad_text(fight(),get_len2("||\t\t\t\t\t\t\t||"),4);
			string monster="";
			if(enemy.health>0){
				monster=pad_text(enemy_fight(),get_len2("||\t\t\t\t\t\t\t||"),4);
			}

			clear();
			ui();
			cout<<"||"+self+"||"<<endl;
			cout<<"||"+monster+"||"<<endl;

			//determines if player is dead or if enemy is.
			if(player.health<=0){
				cout<<color::set_clr("Oh no! You have died! Better luck next time :)",color::red)<<endl;
				return 0;
			}
			else if(enemy.health<=0){
				clear();
				cout<<color::set_clr("Woohoo! Congratulations warrior!",color::green)<<endl;
				if(a<get_len(enemies)-1){
					cout<<"A NEW ENEMY HAS APPROACHED!!!"<<endl;
				}
				else{
					cout<<color::set_clr("WOW! GREAT JOB! YOU HAVE WON THE GAME!!!",color::yellow)<<endl;
					cout<<endl;
					ifstream file("../asset/txt/win.txt");
					string line;
					int a=0;
					while(getline(file,line)){
						cout<<color::set_clr(line,color::type::fg,a+1)<<'\n';
						a++;
					}
					file.close();
				}
				player.health_max+=20*a;
				player.damage+=10*a;
				break;
			}
		}
	}
	return 0;
}
//region-based map w/ different regions in 1 map.
//enemies & NPC's in maps.
//dialogue?
//map w/ correlating # to file line #(potato\n###\n#1#\n### : potato is line 1, so when player get to coordinate of '1', displays line 1 at top).
//add multiple maps together w/ diff. names & detect which map player is on.