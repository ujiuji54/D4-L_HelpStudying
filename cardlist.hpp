#pragma once

#include<iostream>
#include<string>
#include<vector>
using namespace std;

struct card{
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
	vector<struct card> cards;
public:
	int search_card(string name);
	void make_card(string name,string mean,string id);
	void remove_card(string name);
	void remove_user(string name);
	struct card get_card(int num);
};
