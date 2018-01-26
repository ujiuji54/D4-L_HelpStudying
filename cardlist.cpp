#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include"cardlist.hpp"
using namespace std;

cardlist::cardlist(){
	ifstream file("cardlist.csv");
	if (!file) {
		cout << "���͌���csv�t�@�C���̓ǂݍ��݂Ɏ��s" << endl;
		return;
	}
	card card;
	int usersize;
	string line,token;
	stringstream ss;
	
	while(getline(file, line)){
		getline(file,token,',');
		card.name=token;
		getline(file,token,',');
		card.mean=token;
		getline(file,token,',');
		ss << token;
		card.correct_num = ss;
		getline(file,token,',');
		ss << token;
		ss >> card.incorrect_num;
		getline(file, token);
		ss << token;
		ss >> usersize;
		for(int i=0 ;i<usersize;i++){
			getline(file ,token, ',');
			card.id.push_back(token);
			getline(file ,token, ',');
			card.user_correct_num.push_back(token);
			getline(file ,token, ',');
			card.user_incorrect_num.push_back(token);
		}
		cards.push_back(card);
	}

	file.close();
}

void cardlist::file_out(){
	ofstream file("cardlist.csv");
	if (!file) {
		cout << "�o�͐��csv�t�@�C���̓ǂݍ��݂Ɏ��s" << endl;
		return;
	}
	for (int i = 0; i < get_cardlist_size(); i++){
		file << cards[i].name << ", " << cards[i].mean << ", " << cards[i].correct_num << ", " << cards[i].incorrect_num << endl;
		file << cards[i].id.size() << endl;
		for(int j = 0;j<(int)cards[i].id.size();j++){
			file << cards[i].id[j] <<", "<< cards[i].user_correct_num[j] <<", "<< cards[i].user_incorrect_num[j] << endl;
		}
		file << endl;
	}
	file.close();
}

void cardlist::make_card(string name,string mean,string id){
	card Newcard;
	Newcard.name = name;
	Newcard.mean = mean;
	Newcard.correct_num = 0;
	Newcard.incorrect_num = 0;
	Newcard.id.push_back(id);
	Newcard.user_correct_num.push_back(0);
	Newcard.user_incorrect_num.push_back(0);
	cards.push_back(Newcard);
	file_out();
}

void cardlist::display(){
	for (int i = 0; i < get_cardlist_size(); i++)cout << i <<" "<< cards[i].name << " " << cards[i].mean << " " << cards[i].correct_num << " " << cards[i].incorrect_num << endl;
}

void cardlist::display(string id) {
	for (int i = 0; i < get_cardlist_size(); i++) {
		for(int j = 0;j < (int)cards[i].id.size() ; j++){
			if(cards[i].id[j]==id)cout << i << " " << cards[i].name << " " << cards[i].mean << " " << cards[i].user_correct_num[j] << " " << cards[i].user_incorrect_num[j] << endl;
		}
	}
}

void cardlist::remove_card(string name,string id){
	for(int i = 0;i < get_cardlist_size();i++){
		if(name==cards[i].name){
			if(cards[i].id.size() == 1)cards.erase(cards.begin() + i);
			else{
				for(int j = 0;j<(int)cards[i].id.size();j++){
					if(id == cards[i].id[j]){
						cards[i].id.erase(cards[i].id.begin() + j);
						cards[i].user_correct_num.erase(cards[i].user_correct_num.begin() + j);
						cards[i].user_incorrect_num.erase(cards[i].user_incorrect_num.begin() + j);
					}
				}
			}
		}
	}
	file_out();
}

void cardlist::remove_user(string id){
	for(int i = 0;i<get_cardlist_size();i++){
		for(int j = 0;j<(int)cards[i].id.size();j++){
			if(id ==cards[i].id[j]){
				cards[i].id.erase(cards[i].id.begin() + j);
				cards[i].correct_num - cards[i].user_correct_num[j];
				cards[i].incorrect_num - cards[i].user_incorrect_num[j];
				cards[i].user_correct_num.erase(cards[i].user_correct_num.begin() + j);
				cards[i].user_incorrect_num.erase(cards[i].user_incorrect_num.begin() + j);
				if(cards[i].id.size()==0)cards.erase(cards.begin() + i);
			}
		}
	}
	file_out();
}

card cardlist::get_card(string name){
	for(int i = 0;i < get_cardlist_size();i++){
		if(name==cards[i].name)return cards[i];
		else cout << "�J�[�h��������܂���" << endl;
	}
}

card cardlist::get_card(int num){
	return cards[num];
}

int cardlist::get_card_num(string name){
	for(int i=0;i<get_cardlist_size();i++){
		if(name == cards[i].name)return i;
	}
	return -1;
}

int cardlist::get_cardlist_size(){
	return (int) cards.size();
}

void cardlist::answer(string name,string id,bool result){
	int num = get_card_num(name);
	for(int i = 0;i < (int)cards[num].id.size();i++){
		if(id == cards[num].id[i]){
			if(result == true){
				cards[num].user_correct_num[i]++;
				cards[num].correct_num++;
			}else{
				cards[num].user_incorrect_num[i]++;
				cards[num].incorrect_num++;
			}
		}
	}
	file_out();
}
