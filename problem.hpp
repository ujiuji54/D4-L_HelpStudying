#pragma once

#include<iostream>
#include<string>
#include"cardlist.hpp"
using namespace std;

class problem{
private:
	int GetRandom(int min , int max);
public:
	void start(cardlist cardlist,string id);
	void make_problem(cardlist cardlist,string id);
};
