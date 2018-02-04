#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<sstream>
#include"cardlist.hpp"
using namespace std;

vector<string> cardlist::split(string& input, char delimiter){
	istringstream stream(input);
	string field;
	vector<string> result;
	while(getline(stream, field, delimiter)){
		result.push_back(field);
	}
	return result;
}

cardlist::cardlist(){
	ifstream file("cardlist.csv");
	if (!file) {
		cout << "入力元のcsvファイルの読み込みに失敗" << endl;
		return;
	}

	card card;
	string line;
	vector<string> tokens;

	while(getline(file, line)){
		//名前、意味、合計正解数、合計不正解数
		tokens = split(line, ',');
		card.name=tokens[0];
		card.mean=tokens[1];
		card.correct_num=stoi(tokens[2]);
		card.incorrect_num=stoi(tokens[3]);
		
		//id
		getline(file, line);
		tokens = split(line, ',');
		for(int i=0;i<(int)tokens.size();i++){
			card.id.push_back(tokens[i]);	
		}
		
		//user_correct_num
		getline(file, line);
		tokens = split(line, ',');
		for(int i=0;i<(int)tokens.size();i++){
			card.user_correct_num.push_back(stoi(tokens[i]));	
		}
		
		//user_incorrect_num
		getline(file, line);
		tokens = split(line, ',');
		for(int i=0;i<(int)tokens.size();i++){
			card.user_incorrect_num.push_back(stoi(tokens[i]));	
		}
		cards.push_back(card);
	}

	file.close();
}

cardlist::cardlist(cardlist cardlist, string id){
	for(int i=0;i<cardlist.get_cardlist_size();i++){
		for(int j=0;j<cardlist.cards[i].id.size();j++){
			if(cardlist.cards[i].id[j]==id){
				make_card(cardlist.cards[i].name,cardlist.cards[i].mean,id);	
			}
		}
	}
}

void cardlist::file_out(){
	ofstream file("cardlist.csv");
	if (!file) {
		cout << "出力先のcsvファイルの読み込みに失敗" << endl;
		return;
	}
	for (int i = 0; i < get_cardlist_size(); i++){
		file << cards[i].name << ", " << cards[i].mean << ", " << cards[i].correct_num << ", " << cards[i].incorrect_num << endl;

		for(int j = 0;j<(int)cards[i].id.size()-1;j++){
			file << cards[i].id[j] << ", ";
		}
		file << cards[i].id[cards[i].id.size()-1] << endl;

		for(int j = 0;j<(int)cards[i].id.size()-1;j++){
			file << cards[i].user_correct_num[j] << ", ";
		}
		file << cards[i].user_correct_num[cards[i].id.size()-1] << endl;

		for(int j = 0;j<(int)cards[i].id.size()-1;j++){
			file << cards[i].user_incorrect_num[j] << ", ";
		}
		file << cards[i].user_incorrect_num[cards[i].id.size()-1] << endl;

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
		else cout << "カードが見つかりません" << endl;
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

