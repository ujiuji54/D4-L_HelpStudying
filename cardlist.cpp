#include<iostream>
#include<string>
#include<vector>
#include"cardlist.hpp"
using namespace std;

int cardlist::search_card(string name){
    
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
}

void cardlist::remove_card(string name){
	
}

void cardlist::remove_user(string name){
	
}

card cardlist::get_card(int num){
	
}

int cardlist::get_cardlist_size(){

}

void cardlist::answer(string name,string id,bool result){

}
