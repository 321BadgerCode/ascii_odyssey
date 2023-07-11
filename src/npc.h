#pragma once

#include <iostream>
#include <cstring>
#include "./console.h"
#include "./vector.h"

using namespace std;

struct npc{
public:
	string name;
	ao::vector<int> pos;
	string* dialogue;

	npc(string name2,ao::vector<int> pos2,string dialogue2[]):name(name2),pos(pos2){
		size_t size=0;while(dialogue2[size++]!="");

		dialogue=new string[size];
		for(int a=0;a<size;a++){dialogue[a]=dialogue2[a];}
	}
	void talk(){
		size_t size=0;while(dialogue[++size]!="");

		for(int a=0;a<size;a++){
			cout<<dialogue[a]<<endl;
			cout<<"Type \"1\" to "+(string)(a<size-1?"continue.":"help "+name+".")<<endl;
			cout<<"Type \"2\" to leave."<<endl;
			int b1=0;cin>>b1;clear();
			if(b1==2){break;}
		}
	}
};