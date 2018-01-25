#include<iostream>
#include"cardlist.hpp"
#include"userlist.hpp"
//#include"problem.hpp"
using namespace std;

int main() {
	int a,b;
	cardlist cardlist;
	USERLIST userlist;
	string id;
	id=userlist.login();//ユーザ管理担当が作成

	while(a!=4){
		cout << "ようこそ！　L班の完璧な英単語システムへ" <<endl;
		cout << "項目を入力してください　1=データベース閲覧　2=テスト　3=データ削除　4=終了" <<endl;
		cin >> a;
		switch(a){
			case 1:
					cout << "使用するデータベースを選択してください　1=共通　2=個人" << endl;
					cin >> b;
					if (b==1){ 
						cardlist.display();//データベース担当が作成
						break;
					}else{
						cardlist.display(id);//データベース担当が作成
						break;
					}
			case 2:
					//plobrem.start(id,cardlist);//テスト担当が作成
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
			default:
					cout  << "ちーがーうーだーろー。違うだろぉ！！！" << endl;
					break; 
				
		}
	}
	return 0;
}
