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
	vector<struct card> card;
public:
	void make_card();
	void remove_card();
	void remove_user();
	string get_word(int num);
	string get_mean(int num);
};
