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
	cin >> n;
	switch(n){
		case 1:
			make_problem(cardlist);
			break;

		case 2:
			make_problem(cardlist,id);
			break;
}

void problem::make_problem(){
		
}

int main(){
	string word["apple","banana","cow","egg","orange"];
	string mean["りんご","ばなな","うし","たまご","おれんじ"];
	string input;
	int i,correct,incorrect;

	for(i=0;i<5;i++){
		cout << "第",i,"問" << endl;
		cout << mean[i] <<endl;
		cout << "上記の意味に応じた英単語を入力してください。" <<endl;
		cin >> input;
		if(word[i]==input){
			cout << "正解！！" << endl;
			correct++;
		}else{
			cout << "はい、違ーう！！\nわっかりやすい間違いをしてくれてありがとう！！" << endl;
			incorrect++;
		}
	}
	cout << "正解数  ",correct << endl;
	cout << "不正解数",incorrect << endl;
	return 0;
}
