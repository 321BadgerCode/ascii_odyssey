#pragma once

using namespace std;

/*int get_random(const unsigned int min,const unsigned int max){
	srand(time(NULL)); //initialize random seed
	return rand()%(max-min)+min;
}*/
int get_random(const unsigned int min,const unsigned int max){
	srand(time(NULL)); //initialize random seed
	mt19937 generator(random_device{}());
	uniform_int_distribution<int> distribution(min,max);
	return distribution(generator);
}

//return the size of the given parameter.
template<typename T>short int get_len(T& a1){
	//cout<<*(&a1+1)-a1<<endl;
	//cout<<sizeof(a1)/sizeof(T)<<endl;
	//cout<<sizeof(a1)/sizeof(a1[0])<<endl;
	return sizeof(a1)/sizeof(a1[0]);
}
//return the number of characters in a string where tabs are converted to their # of equivalent spaces.
int get_len2(const string str){
	int count=0;
	int pos=0;
	for(char c:str){
		if(c=='\t'){
			//calculate the number of spaces to the next tab stop based on the current position.
			int spaces=8-(pos%8);
			count+=spaces;
			pos+=spaces;
		}
		else{
			count++;
			pos++;
		}
		//reset position if a newline character is encountered.
		if(c=='\n'){
			pos=0;
		}
	}
	return count;
}

//formats text for UI.
string pad_text(string text,int width,int pad=0,char padding_char=' '){
	int text_length=get_len2(text);
	int padding_length=width-text_length;
	padding_length-=pad;
	if(padding_length<=0){
		return text;
	}
	int left_padding_length=padding_length/2;
	int right_padding_length=padding_length-left_padding_length;
	string left_padding=string(left_padding_length,padding_char);
	string right_padding=string(right_padding_length,padding_char);
	return left_padding+text+right_padding;
}

//slowly types text.
void slow_type(string msg,float delay=.05){
	for(char c:msg){
		cout<<c<<flush;
		sleep(delay);
	}
}

//return the given string to be all lower case.
string to_lower_case(const string& s){
	string result=s;
	transform(s.begin(),s.end(),result.begin(),[](unsigned char c){return tolower(c);});
	return result;
}

//capitalize the first letter of a string and return it.
string get_capitalize(string txt){
	return (char)toupper(txt[0])+to_lower_case(txt.substr(1,get_len(txt)));
}