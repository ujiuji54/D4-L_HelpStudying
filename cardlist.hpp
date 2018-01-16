#pragma once

#include<iostream>
#include<string>
#include<vector>
using namespace std;

class card{
public:
	string name;
	string mean;
	int correct_num;
	int incorrect_num;
	vector<string> id;
	vector<int> user_correct_num;
	vector<int> user_incorrect_num;
};

class cardlist{
private:
	vector<card> cards;
public:
	void make_card(string name,string mean,string id);
	void remove_card(string name);
	void remove_user(string id);
	card get_card(string name);
	card get_card(int num);
	int get_cardlist_size();
	void answer(string name,string id,bool result);
};
