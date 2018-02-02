#pragma once

#include<iostream>
#include<string>
#include<vector>
using namespace std;

struct card{
	string name;//単語の名前
	string mean;//単語の意味
	int correct_num;//ユーザ全員の正解数
	int incorrect_num;//ユーザ全員の不正解数
	vector<string> id;//単語を登録しているユーザidのリスト
	vector<int> user_correct_num;//ユーザ毎の正解数のリスト
	vector<int> user_incorrect_num;//ユーザ毎の不正解数のリスト
};

class cardlist{
private:
	vector<card> cards;
	vector<string> split(string&, char delimiter);
	void file_out();//ファイルにデータを保存する。
public:
	cardlist();//コンストラクタ，ファイルからデータを取得する。
	void display();//単語帳の全単語カードを表示する。
	void display(string id);//単語帳のユーザのカードを表示：。
	void make_card(string name,string mean,string id);//cardを作成する。引数(単語,意味,ユーザのid)
	void remove_card(string name,string id);//指定した単語のcardを消す。引数(単語,ユーザのid)
	void remove_user(string id);//指定したuserをcardlistから消す。引数(ユーザーのid)
	card get_card(string name);//指定した単語のcardを返す。引数(単語)
	card get_card(int num);//指定した番号のcardを返す。引数(番号)
	int get_card_num(string name);//指定した単語の番号を返す。引数(単語)
	int get_cardlist_size();//cardlistのcard数を返す。
	void answer(string name,string id,bool result);//ユーザの回答の合否を保存する。引数(単語,ユーザのid,合否(true | false))
};
