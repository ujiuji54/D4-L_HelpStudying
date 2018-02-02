#pragma once

#include<iostream>
#include<string>
#include"cardlist.hpp"
using namespace std;

class problem{
private:
	void shuffle(vector<string>& array , vector<string>& array2 , int size);
	void shuffle2(int* array , int size);
public:
	void start(cardlist& cardlist,string id);
	void make_public_problem(cardlist& cardlist,string id);
	void make_private_problem(cardlist& cardlist,string id);
};
