#include<iostream>
#include"cardlist.hpp"
#include"userlist.hpp"
#include"problem.hpp"
using namespace std;

int main() {
	int a,b,c;
	c=1;
	cardlist cardlist;
	USERLIST userlist;
	problem problem;
	string name,mean,id;
	id=userlist.login();//ユーザ管理担当が作成
	cout << "ようこそ！　L班の完璧な英単語システムへ" <<endl;
	while(a!=4){
		cout << "使用項目を入力してください　1=データベース　2=テスト　3=ユーザーデータ削除　4=終了" <<endl;
		cin >> a;
		switch(a){
			case 1:
					cout << "使用する機能を選択してください　1=閲覧　2=単語追加　3=単語削除" << endl;
					cin >> b;
					switch(b){
						case 1:
							cout << "使用する項目を選択してください　1=共通　2=個人" << endl;
							cin >> b;
							if (b==1){ 
								cardlist.display();//データベース担当が作成
								break;
							}else{
								cardlist.display(id);//データベース担当が作成
								break;
							}
						case 2:
							while(c==1){
								cout << "登録したい単語を入力してください" << endl;
								cin >> name;
								cout << "登録したい単語の意味を入力してください" << endl;
								cin >> mean;
								cardlist.make_card(name,mean,id);
								cout << "単語登録を続けますか？　はい＝１　いいえ＝２" << endl;
								cin >> c;
								if(c>2){
									while(c>2){
										cout << "入力が不適格です。もう一度入力してください" << endl;
										cout << "はい＝１　いいえ＝２" << endl;
										cin >> c;
									}
								}
							}   c=1;
								break;
						case 3:
							while(c==1){
								cout << "消したい単語を入力してください" << endl;
								cin >> name;
								cardlist.remove_card(name,id);//指定した単語のcardを消す。引数(単語,ユーザのid)
								cout << "単語消去を続けますか？　はい＝１　いいえ＝２" << endl;
								cin >> c;
								if(c>2){
									while(c>2){
										cout << "入力が不適格です。もう一度入力してください" << endl;
										cout << "はい＝１　いいえ＝２" << endl;
										cin >> c;
									}
								}
							}   c=1;
							break;
					}
					break;
			case 2:
					problem.start(cardlist,id);//テスト担当が作成
					break;
			case 3:
					cout << "本当にユーザーデータを削除してよ、よろしいか？　1=よろしい 2=よろしくない" << endl;
					cin >> b;
					if (b==1){ 
						userlist.delete_user();//ユーザ管理担当が作成
						break;
					}else{
						cout << "データ削除をキャンセルします" << endl;
						break;
					}
			case 4:
					break;
			default:
					cout  << "ちーがーうーだーろー。違うだろぉ！！！" << endl;
					break; 
		}
	}
}
