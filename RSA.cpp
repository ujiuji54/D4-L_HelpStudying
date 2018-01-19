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
		int scan_userlist();
		string sign_up();
		string login_login();
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
	string id;
	int mode;
	vector<string> data_id(100); //全員のID
	vector<vector<LONG> > data_pass(100, vector<LONG>(5,0)); //全員のパスワード配列
	LONG temp;//パスワード格納用
	int rows = 0;//行
	vector<int> columns(100,0); //列
	
	//入力ストリームの作成
    ifstream ifs("userlist.csv", ios::in);
    if (!ifs || !getline(ifs, buf)) { //ファイルがないもしくは空
		cout << "ファイルがないもしくは空のため、ユーザー登録をしてください" << endl;
		return sign_up();
	}
	do {
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
		if	   (mode == 1) return login_login();
		else if(mode == 2) return sign_up();
		else			   cout << "入力が不適切です。" << endl;
	}
	return id;
}

string USERLIST::login_login(){
	string id;
	cout << "ユーザーIDを入力してください" << endl << "->";
	cin >> id;
	cout << id << endl;
	return id;
}

string USERLIST::sign_up(){
	string id;
	cout << "ユーザーIDを入力してください" << endl << "->";
	cin >> id;
	cout << id << endl;
	return id;
}

vector<string> split(string& input, char delimiter){
    istringstream stream(input);
    string field;
    vector<string> result;
    while (getline(stream, field, delimiter)) {
        result.push_back(field);
    }
    return result;
}

LONG USERLIST::stoi(std::string str){
	LONG ret;
	std::stringstream ss;
	ss << str;
	ss >> ret;
	return ret;
}

int main(void){
	RSA rsa;
	USERLIST userlist;
	userlist.login();
	/*
	cout << "key -> " << key << endl;
	//cin  >> key >> endl;
	cout << "暗号-> " << (key = rsa.Ec(key,E,P*Q)) << endl;
	cout << "復号-> " << rsa.Dc(key,P,Q,E) << endl;
	*/
	
	return 0;
}

