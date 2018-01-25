#include<iostream>
#include<string>
#include<vector>
#include"cardlist.hpp"
#include"problem.hpp"
#include<stdio.h>
#include<stdlib.h>
using namespace std;

//int GetRandom(int min , int max);　まだ使用しないためコメントアウト

void problem::start(cardlist cardlist,string id){
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
			make_problem(cardlist);
			break;

		case 2:
			cout << "プライベートテスト開始"<< endl;
			make_problem(cardlist,id);
			break;

		case 3:
			return;
			break;
	}
}

void problem::make_problem(/*cardlist cardlist,string id　実装前のためコメントアウト*/){
	
	vector<string> word{"apple","banana","cow","dog","egg","fish","green","hospital","internet","japan"};
	vector<string> mean{"りんご","ばなな","うし","いぬ","たまご","さかな","みどりいろ","びょういん","いんたーねっと","にほん"};
	string input;
	int i;
	int correct=0;
	int incorrect=0;

	/*for(i=0;i<10;i++){
		word[i]=cardlist.get_card(GetRandom(1,get_cardlist_size())).name;
		mean[i]=cardlist.get_card(GetRandom(1,get_cardlist_size())).mean;
	}*///実装前のためコメントアウト

	cout << "\n";
	cout << "問題！！\n" << endl;
	cout << "以下に示される日本語の意味を持つ英単語を入力しなさい。\n" <<endl;


	for(i=0;i<10;i++){
		cout << "第"<< i+1 <<"問" << endl;
		cout << mean[i] << " -> ";
		cin >> input ;

		if(word[i]==input){
			cout << "\n正解！！\n" << endl;
			correct++;
			//answer(word[i],id,true); 実装前のためコメントアウト
		}else{
			cout << "\n不正解！！\n" << endl;
			incorrect++;
			//answer(word[i],id,false); 実装前のためコメントアウト
		}
	}
	cout << "正解数  " << correct << endl;
	cout << "不正解数 " << incorrect << endl;

	/*cout << "問題！！\n" << endl;
	cout << "以下に示される日本語の意味を持つ英単語を選択肢から選び、数字で答えなさい。\n"<< endl;

	
	for(i=0;i<5;i++){
		cout << "第"<< i+1 <<"問" << endl;
		cout << mean[i] << " -> ";
		cin >> input ;

		if(word[i]==input){
			cout << "\n正解！！\n" << endl;
			correct++;
		}else{
			cout << "\nはい、違ーう！！\nわっかりやすい間違いをしてくれてありがとう！！\n" << endl;
			incorrect++;
		}
	}　まだ完成していないのでコメントアウト*/
}

/*int GetRandom(int min , int max){
	return min + (int)(rand()*(max-min+1.0)/(1.0+RAND_MAX));
} まだ使用しないのでコメントアウト*/
