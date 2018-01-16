#include<iostream>
#include<string>
#include<vector>
#include"cardlist.hpp"
using namespace std;

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
}

void cardlist::remove_card(string name,string id){
	for(int i = 0;i < get_cardlist_size();i++){
		if(name==cards[i].name){
			if(cards[i].id.size == 1)cards.erase(cards.begin + i);
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
}

void cardlist::remove_user(string id){
	for(int i;i<get_cardlist_size();i++){
		for(int j;j<(int)cards[i].id.size();j++){
			if(id ==cards[i].id[j]){
				cards[i].id.erase(card[i].id.begin() + j);
				cards[i].correct_num - card[i].user_correct_num[j];
				cards[i].incorrect_num - card[i].user_incorrect_num[j];
				cards[i].user_correct_num.erase(card[i].user_correct_num.begin + j);
				cards[i].user_incorrect_num.erase(card[i].user_incorrect_num.begin + j);
			}
		}
	}
}

card cardlist::get_card(string name){
	for(int i = 0;i < get_cardlist_size();i++){
		if(name==cards[i].name)return cards[i];
	}
}

card cardlist::get_card(int num){
	return cards[i];
}

int cardlist::get_cardlist_size(){
	return (int) cards.size();
}

void cardlist::answer(string name,string id,bool result){
	card card = get_card(name)
	for(int i;i < (int)card.id.size();i++){
		if(id == card.id[i]){
			if(result == true){
				card.user_correct_num[i]++;
				card.correct_num++;
			}else{
				card.user_incorrect_num[i]++;
				card.incorrect_num++;
			}
		}
	}
}
