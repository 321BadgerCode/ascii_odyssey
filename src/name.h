#pragma once

using namespace std;

vector<string> read_file(const string& filename){
	vector<string> items;
	ifstream infile(filename);
	if(infile){
		string line;
		while(getline(infile,line)){
			if(!line.empty()){
				items.push_back(line);
			}
		}
	}
	return items;
}

//function to generate a random enemy name with alliteration.
string generate_enemy_name(const vector<string>& names,const vector<string>& adjectives){
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> name_dist(0,names.size()-1);
	string name=get_capitalize(names[name_dist(gen)]);

	//get list of adjectives with matching first letter as name.
	vector<string> matching_adjectives;
	for(const auto& adj:adjectives){
		if(!adj.empty()&&toupper(adj[0])==name[0]){
			matching_adjectives.push_back(adj);
		}
	}

	//if no matching adjectives found, use any adjective.
	if(matching_adjectives.empty()){
		uniform_int_distribution<> adj_dist(0,adjectives.size()-1);
		string adj=get_capitalize(adjectives[adj_dist(gen)]);
		return name+" the "+adj;
	}

	//select a matching adjective at random.
	uniform_int_distribution<> adj_dist(0,matching_adjectives.size()-1);
	string adj=get_capitalize(matching_adjectives[adj_dist(gen)]);
	return name+" the "+adj;
}