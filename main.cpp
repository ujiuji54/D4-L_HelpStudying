#include<iostream>
#include"cardlist.hpp"
#include"userlist.hpp"
#include"problem.hpp"
using namespace std;

int main() {
	int a,b;
	cardlist cardlist;
	USERLIST userlist;
	problem problem;
	string name,mean,id;
	id=userlist.login();//ユーザ管理担当が作成

	while(a!=4){
		cout << "ようこそ！　L班の完璧な英単語システムへ" <<endl;
		cout << "項目を入力してください　1=データベース　2=テスト　3=データ削除　4=終了" <<endl;
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
							cout << "名前　意味　IDの順に入力してください" << endl;
							cin >> name;
							cin >> mean;
							cin >> id;
							cardlist.make_card(name,mean,id);
							break;
						case 3:
							cout << "名前　IDの順に入力してください" << endl;
							void remove_card(string name,string id);//指定した単語のcardを消す。引数(単語,ユーザのid)
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
	return 0;
}
