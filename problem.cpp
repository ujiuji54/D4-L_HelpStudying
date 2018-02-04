#include<iostream>
#include<string>
#include<vector>
#include"cardlist.hpp"
#include"problem.hpp"
#include<stdio.h>
#include<stdlib.h>
using namespace std;

void problem::shuffle(vector<string>& array,vector<string>& array2, int size){
	int i;
	int j;

	 i=size;
	 while (i > 1) {
		 j = rand() % i;
		 i--;
		 string t = array[i];
		 array[i] = array[j];
		 array[j] = t;
		 string u = array2[i];
		 array2[i] = array2[j];
		 array2[j] = u;
	  }
}

void problem::shuffle2(int* array,int size){
	int i;
	int j;

	 i = size;
	 while (i > 1) {
		 j = rand() % i;
		 i--;
		 int t = array[i];
		 array[i] = array[j];
		 array[j] = t;
	 }
}

void problem::start(cardlist& cardlist,string id){
	int n;
	cout << "テスト形式を選んでください" << endl;
	cout << "**************************" << endl;
	cout << "1.public_test" << endl;
	cout << "2.private_test" << endl;
	cout << "3.メインメニューへ戻る" << endl;
	cin >> n;

	switch(n){
		case 1:
			cout << "パブリックテスト開始" << endl;
			make_public_problem(cardlist,id);
			break;

		case 2:
			cout << "プライベートテスト開始"<< endl;
			make_private_problem(cardlist,id);
			break;

		case 3:
			return;
			break;
	}
}

void problem::make_private_problem(cardlist& cardlist,string id){
	vector<string> word;
	vector<string> mean;
	string input;
	card card;
	int i,j;
	int size,input2;
	int correct=0;
	int incorrect=0;

	size=cardlist.get_cardlist_size();
	
	for(i=0;i<size;i++){
		for(j=0;j<(int)card.id.size();j++){
			if(cardlist.get_card(i).id[j]==id){
				word.push_back(cardlist.get_card(i).name);
				mean.push_back(cardlist.get_card(i).mean);
				break;
			}
		}
	}
	shuffle(word,mean,size);//shuffle

	cout << "\n";
	cout << "問題！！\n" << endl;
	cout << "以下に示される日本語の意味を持つ英単語を入力しなさい。\n" <<endl;


	for(i=0;i<size;i++){
		cout << "第"<< i+1 <<"問" << endl;
		cout << mean[i] << " -> ";
		cin >> input ;

		if(word[i]==input){
			cout << "\n正解！！\n" << endl;
			correct++;
			cardlist.answer(word[i],id,true);
		}else{
			cout << "\n不正解！！\n" << endl;
			incorrect++;
			cardlist.answer(word[i],id,false);
		}
	}
	cout << "正解数  " << correct << endl;
	cout << "不正解数 " << incorrect << endl;

}

void problem::make_public_problem(cardlist& cardlist,string id){
	vector<string> word;
	vector<string> mean;
	string input;
	int i,j;
	int size,input2;
	int select[4],save[4];
	int correct=0;
	int incorrect=0;

	for(j=0;j<4;j++){
		select[j]=j;
	}

	size=cardlist.get_cardlist_size();
	
	for(i=0;i<size;i++){
		word.push_back(cardlist.get_card(i).name);
		mean.push_back(cardlist.get_card(i).mean);
	}
	shuffle(word,mean,size);//shuffle

	cout << "\n";
	cout << "問題！！\n" << endl;
	cout << "以下に示される日本語の意味を持つ英単語を入力しなさい。\n" <<endl;


	for(i=0;i<size;i++){
		cout << "第"<< i+1 <<"問" << endl;
		cout << mean[i] << " -> ";
		cin >> input ;

		if(word[i]==input){
			cout << "\n正解！！\n" << endl;
			correct++;
			cardlist.answer(word[i],id,true);
		}else{
			cout << "\n不正解！！\n" << endl;
			incorrect++;
			cardlist.answer(word[i],id,false);
		}
	}
	cout << "正解数  " << correct << endl;
	cout << "不正解数 " << incorrect << endl;

	/*cout << "問題！！\n" << endl;
	cout << "以下に示される英単語の意味を選択肢から選び、数字で答えなさい。\n"<< endl;

	
	for(i=0;i<size;i++){
		cout << "第"<< i+1 <<"問" << endl;
		cout << word[i] << endl;

		shuffle2(select , 4);
		for(j=0;j<4;j++){
			save[j]=select[j]+i;
			cout << j+1 << "." << mean[save[j]];
		}
		cin >> input2 ;

		if(i==save[input2-1]){
			cout << "\n正解！！\n" << endl;
			correct++;
			cardlist.answer(mean[i],id,true);
		}else{
			cout << "\nはい、違ーう！！\nわっかりやすい間違いをしてくれてありがとう！！\n" << endl;
			incorrect++;
			cardlist.answer(mean[i],id,false);
		}
		cout << "正解数  " << correct << endl;
		cout << "不正解数 " << incorrect << endl;

	}*/
}
