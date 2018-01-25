#include<iostream>
#include<string>
#include"problem.hpp"
#include"cardlist.hpp"
using namespace std;

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
			return 0;
			break;
	}
}

void problem::make_problem(){
		
}
