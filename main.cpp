#include<iostream>
#include"cardlist.hpp"
#include"userlist.hpp"
#include"problem.hpp"
using namespace std;
int a;

int main() {
	userlist userlist;	
	string name;
	string id;
	id=userlist.login(name,id);

	while(a!=3){
		cout << "項目を入力してください　1=データベース閲覧　2=テスト　3=終了" <<endl;
		cin >> a;
		switch(a){
			case 1:
					cardlist(id);
					break;
			case 2:
					plobrem.start(id);
					break;
			case 3:
					break;
				}
	}

}
