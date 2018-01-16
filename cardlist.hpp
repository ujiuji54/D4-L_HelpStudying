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
	void make_card(string name,string mean,string id);//cardを作成する。引数(単語,意味,ユーザのid)
	void remove_card(string name);//指定した単語のcardを消す。引数(単語)
	void remove_user(string id);//指定したuserをcardlistから消す。引数(ユーザーのid)
	card get_card(string name);//指定した単語のcardを返す。引数(単語)
	card get_card(int num);//指定した番号のcardを返す。引数(番号)
	int get_cardlist_size();//cardlistのcard数を返す。
	void answer(string name,string id,bool result);//ユーザの回答の合否を保存する。引数(単語,ユーザのid,合否(true | false))
};
