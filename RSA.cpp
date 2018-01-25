#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <iostream>
#include <string>
#include <iomanip> //std::setw(int w)
#include <fstream>   // ifstream, ofstream
#include <sstream>   // istringstream, ostringstream
#include <vector>
#include<string.h>
#include<unistd.h>

#define  P (LONG  )12671 //素数
#define  Q (LONG  )1009  //素数
#define  E (LONG  )6553  //公開鍵
#define  D (LONG  )14617 //

//login true or false
//sign up
//delete user
//

using namespace std;
typedef unsigned long long LONG;

class USERLIST{
	public:
		string login();
		string delete_user();
	private:
		LONG stoi(std::string str);
		string sign_up(vector<string> data_id, int rows, int first);
		string login_login(vector<string> data_id, vector<vector<LONG> > data_pass,
 						   int rows, vector<int> columns);
};

class RSA{
	private:
		LONG   getl(LONG   p,LONG   q);
		LONG   getd(LONG   p,LONG   q,LONG   e);

	public:
		LONG   Ec(LONG   ec, LONG   e, LONG   n);
		LONG   Dc(LONG   ec, LONG   p, LONG   q, LONG   e);
};

LONG RSA::Ec(LONG x, LONG power, LONG n){//x^power % n を求める
	LONG tmp = 1;
	if ( power > 0 ){
	  	tmp = Ec(x, power/2, n);
	  	tmp = ( tmp * tmp ) % n;
		if(power % 2 == 1) tmp = (tmp * x) % n; //Nが奇数なら
	}
	return tmp;
}

LONG   RSA::getl(LONG   p,LONG   q){//(p-1)と(q-1)の最小公倍数を求める
	LONG   t;
	LONG   m = (p - 1)*(q - 1);
	while (p % q != 0) { //ユークリッドの互除法で(p-1)と(q-1)の最大公約数を求める
		t = q;
		q = p % q;
		p = t;
	}
	return m / q; //(p-1)と(q-1)の積から最大公約数を割る
}


LONG RSA::getd(LONG   p,LONG   q,LONG   e){ //拡張ユークリッドの互除法
	LONG   lcm = getl(p,q);
	int x1 = 1, y1 = 0, z1 = lcm;
	int x2 = 0, y2 = 1, z2 = e;
	int x3, y3, z3;
	int a = 1;

	while(z2 > 0) {
		a = (LONG  )(z1 / z2);
		x3 = x1 - a * x2;
		y3 = y1 - a * y2;
		z3 = z1 - a * z2;
		x1 = x2;
		y1 = y2;
		z1 = z2;
		x2 = x3;
		y2 = y3;
		z2 = z3;
	}
	return (x1 > y1) ? x1 : y1;
}


LONG RSA::Dc(LONG   ee,LONG   p,LONG   q,LONG   e){
	//cout << "d = " << getd(p,q,e) << endl;
	return Ec(ee,D,p*q);
}

string USERLIST::login(){
	string buf;
	string token;
	int mode;
	vector<string> data_id(100); //全員のID
	vector<vector<LONG> > data_pass(100, vector<LONG>(5,0)); //全員のパスワード配列
	LONG temp;//暗号化パスワード格納用
	int rows = 0;//行
	vector<int> columns(100,0); //列
	string id;
	
	//入力ストリームの作成
    ifstream ifs("userlist.csv", ios::in);
    if (!ifs || !getline(ifs, buf)) { //ファイルがないもしくは空
		cout << "ファイルがないもしくは空のため、ユーザー登録をしてください" << endl;
		return sign_up(data_id, rows, 1);
	}
	do { //CSVファイルからIDと暗号化パスワードを配列に格納
        istringstream stream(buf);
        getline(stream,token,',');
        data_id[rows] = token;//ID格納
        while(getline(stream,token,',')){ // 区切り
            temp = stoi(token); //文字列で読み込まれるため、整数へ変換
            data_pass[rows][columns[rows]] = temp; // //パスワード格納
            columns[rows]++;
        }
        rows++;//行更新
  	} while(getline(ifs,buf));
  	/* デバッグ用表示
  	for(int i=0;i<rows;i++){
  		cout << data_id[i] << ",";
  		for(int j=0;j<columns[i];j++){
  			cout << data_pass[i][j];
  			if(j != columns[i] -1) cout << ",";
  		}
  		cout << endl;
  	}
  	*/
	cout << "ログインかユーザー登録か選んでください(ログイン:1　ユーザー登録:2)" << endl << "->";
	cin >> mode;
	while(1){
		if	   (mode == 1) return login_login(data_id, data_pass, rows, columns);
		else if(mode == 2) return sign_up(data_id, rows, 0);
		else			   cout << "入力が不適切です。" << endl;
	}
	return id;
}

string USERLIST::login_login(vector<string> data_id, vector<vector<LONG> > data_pass,
 int rows, vector<int> columns){
	string id;
	string pass_id;
	int num_id;
	int flag_id;
	char str[256];
	while(1){
		cout << "ユーザーIDを入力してください" << endl << "->";
		cin >> id;
		flag_id = 0;
		for(int i = 0; i < rows; i++){
			if(id == data_id[i]){
				num_id = i;
				flag_id = 1;
				break;
			}
		}
		if(flag_id == 1) break;
		else{
			cout << "登録されていないIDです　もう一度入力してください。" << endl;
		}
	}
	cout << "パスワードを入力してください。" << endl;
	strcpy(str,getpass("(入力は画面に表示されません)\n"));
	pass_id = str;
	/*
	while(pass_id != data_pass[num_id]){
	    printf("一致しませんでした。もう1度入力してください\n");
	    strcpy(str,getpass("(入力は画面に表示されません)\n"));//scanf("%s",str);
	}
	*/
	cout << "ログインに成功しました。" << endl;
	return id;
}

string USERLIST::sign_up(vector<string> data_id, int rows, int first){
	string id;
	int flag_id;
	char str[256],str2[256];
	while(1){
		while(1){
			cout << "ユーザーIDを入力してください(任意の文字列)" << endl << "->";
			cin >> id;
			flag_id = 0;
			for(int i = 0; i < rows; i++){
				if(id == data_id[i]){
					cout << "既に登録されているIDです。別のIDにしてください。" << endl;
					flag_id = 1;
					break;
				}
			}
			if(flag_id == 0) break;
		}

		cout << "パスワードを入力してください。(4字以上)" << endl;
		strcpy(str,getpass("(入力は画面に表示されません)\n"));
		while(strlen(str) < 4){
		    printf("4字以上ではありません。もう1度入力してください。\n");
		    strcpy(str,getpass("(入力は画面に表示されません)\n"));//scanf("%s",str);
		}
		printf("確認のためもう1度入力してください。\n");
		strcpy(str2,getpass("(入力は画面に表示されません)\n"));//scanf("%s",str2);
		if(strcmp(str,str2)!=0){
		    printf("パスワードが一致しませんでした。登録し直してください。\n");
		}
		else{
			printf("登録が完了しました。\n");
			break;
		}
	}
	ofstream ofs("userlist.csv", ios::out | ios::app);//上書き出力or新規作成
	//if(first == 0) ofs << endl; //1行目の改行を防ぐ
	ofs << id << ',' << str;
	return id;
}

string USERLIST::delete_user(){
	string buf;
	string token;
	int mode;
	int flag_id, num_id, flag_delete;
	vector<string> data_id(100); //全員のID
	vector<vector<LONG> > data_pass(100, vector<LONG>(5,0)); //全員のパスワード配列
	LONG temp;//暗号化パスワード格納用
	int rows = 0;//行
	vector<int> columns(100,0); //列
	string id;
	
	//入力ストリームの作成
    ifstream ifs("userlist.csv", ios::in);
    if (!ifs || !getline(ifs, buf)) { //ファイルがないもしくは空
		cout << "ファイルがないもしくは空のため、ユーザー登録をしてください" << endl;
		return sign_up(data_id, rows, 1);
	}
	do { //CSVファイルからIDと暗号化パスワードを配列に格納
        istringstream stream(buf);
        getline(stream,token,',');
        data_id[rows] = token;//ID格納
        while(getline(stream,token,',')){ // 区切り
            temp = stoi(token); //文字列で読み込まれるため、整数へ変換
            data_pass[rows][columns[rows]] = temp; // //パスワード格納
            columns[rows]++;
        }
        rows++;//行更新
  	} while(getline(ifs,buf));
	cout << "削除したいユーザにログインしてください。" << endl;
	id = login_login(data_id, data_pass, rows, columns);
	for(int i = 0; i < rows; i++){
		if(id == data_id[i]) {
			num_id = i;
			break;
		}
	}
	while(1){
		cout << "本当に削除してよろしいですね？ Y:1 N:0" << endl;
		cin >> flag_delete;
		if(flag_delete == 0){
			cout << "削除を中止します。" << endl;
			break;
		}else if(flag_delete == 1){
			ofstream ofs("userlist.csv", ios::out );//新規作成
			for(int i = 0; i < rows; i++){
				if(i != num_id){
					ofs << data_id[i] << ",";
  					for(int j=0;j<columns[i];j++){
	  					ofs << data_pass[i][j];
	  					if(j != columns[i] -1) ofs << ",";
  					}
  					ofs << endl;
				}
  			}
			break;
		}else{
			cout << "入力が不適切です。" << endl;
		}
	}
	
	return id;
}

LONG USERLIST::stoi(string str){
	LONG ret;
	stringstream ss;
	ss << str;
	ss >> ret;
	return ret;
}

int main(void){
	RSA rsa;
	USERLIST userlist;
	userlist.login();
	userlist.delete_user();
	/*
	cout << "key -> " << key << endl;
	//cin  >> key >> endl;
	cout << "暗号-> " << (key = rsa.Ec(key,E,P*Q)) << endl;
	cout << "復号-> " << rsa.Dc(key,P,Q,E) << endl;
	*/
	
	return 0;
}

