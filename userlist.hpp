#pragma once

#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <iostream>
#include <string>
#include <iomanip> 
#include <fstream> 
#include <sstream> 
#include <vector>
#include<string.h>
#include<unistd.h>
#include "RSA.hpp"

#define  P (LONG  )12671 //素数
#define  Q (LONG  )245681  //素数
#define  E (LONG  )247906583  //公開鍵
#define  D (LONG  )85529767 //秘密鍵

using namespace std;
typedef unsigned long long LONG;

class USERLIST{
	public:
		string login();
		string delete_user();
	private:
		vector<LONG> change_to_LONG(string pass);
		string change_to_string(vector<LONG> data_pass);
		LONG stoi(string str);
		string sign_up(vector<string> data_id, int rows, int first);
		string login_login(vector<string> data_id, vector<vector<LONG> > data_pass, int rows);
		int change_63(char str);
		char change_char(int val);
};

string USERLIST::login(){
	string buf;
	string token;
	int mode;
	vector<string> data_id(100); //全員のID
	vector<vector<LONG> > data_pass(100, vector<LONG>(4,0)); //全員のパスワード配列
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
        for(int i = 0; i < 4; i++){
			getline(stream,token,','); // 区切り
            temp = stoi(token); //文字列で読み込まれるため、整数へ変換
            data_pass[rows][i] = temp; // //パスワード格納
        }
        rows++;//行更新
  	} while(getline(ifs,buf));
  	/*
  	// デバッグ用表示
  	for(int i=0;i<rows;i++){
  		cout << data_id[i] << ",";
  		for(int j=0;j<4;j++){
  			cout << data_pass[i][j];
  			if(j != 3) cout << ",";
  		}
  		cout << endl;
  	}
  	*/
	cout << "ログインかユーザー登録か選んでください(ログイン:1　ユーザー登録:2)" << endl << "->";
	cin >> mode;
	while(1){
		if	   (mode == 1) return login_login(data_id, data_pass, rows);
		else if(mode == 2) return sign_up(data_id, rows, 0);
		else			   cout << "入力が不適切です。" << endl;
	}
	return id;
}

string USERLIST::login_login(vector<string> data_id, vector<vector<LONG> > data_pass,
 int rows){
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
	RSA rsa;
	for(int i = 0; i < 4; i++){
		data_pass[num_id][i] = rsa.Dc(data_pass[num_id][i],P,Q,E);
	}
	while(pass_id != change_to_string(data_pass[num_id])){
	    printf("一致しませんでした。もう1度入力してください\n");
	    strcpy(str,getpass("(入力は画面に表示されません)\n"));//scanf("%s",str);
		pass_id = str;
		for(int i = 0; i < 4; i++){
			data_pass[num_id][i] = rsa.Dc(data_pass[num_id][i],P,Q,E);
		}
	}
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

		cout << "パスワードを入力してください。(4字以上20文字以内)" << endl;
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
	FILE* stream;
	char c,c1;
	if((stream = fopen("userlist.csv", "r"))){
    	while (EOF != (c = fgetc(stream))) c1 = c;
    }
    fclose(stream);
	
	ofstream ofs("userlist.csv", ios::out | ios::app);//上書き出力or新規作成
	RSA rsa;
	string pass_id = str;
	vector<LONG> data_pass(4,0);
	data_pass = change_to_LONG(pass_id);
	if(c1 != '\n') ofs << endl;
	ofs << id;
	for(int i = 0; i < 4; i++){
		ofs << "," << (data_pass[i] = rsa.Ec(data_pass[i],E,P*Q));
	}
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
        for(int i = 0; i < 4; i++){
			getline(stream,token,','); // 区切り
            temp = stoi(token); //文字列で読み込まれるため、整数へ変換
            data_pass[rows][i] = temp; // //パスワード格納
        }
        rows++;//行更新
  	} while(getline(ifs,buf));
	cout << "削除したいユーザにログインしてください。" << endl;
	id = login_login(data_id, data_pass, rows);
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
  					for(int j=0;j<4;j++){
	  					ofs << data_pass[i][j];
	  					if(j != 3) ofs << ",";
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

vector<LONG> USERLIST::change_to_LONG(string pass){ //63進数の5個の配列に変換
	vector<LONG> data_pass(4,0);
	int len = pass.length();
	char pass_c[len+1];
	strcpy(pass_c,pass.c_str());
	for(int i = 0; i < 1 + (len - 1) / 5; i++){
		for(int j = i*5; j < i*5 + 5; j++){
			data_pass[i] += change_63(pass_c[j]) * pow(63, j % 5);//63進数に変換
			if(j == len) break;
		}
	}
	return data_pass;
}

string USERLIST::change_to_string(vector<LONG> data_pass){
	char str[21];
	string pass;
	int j;
	for(int i = 0; i < 4; i++){
		for(j = i * 5;; j++){
			str[j] = change_char(data_pass[i] % 63); //char型に変換
			data_pass[i] /=  63;
			if(data_pass[i] == 0){
				if(j == i*5 && str[j] == 0) str[j] = '\0';
				else		 str[j+1] = '\0';
				break;
			}
		}
		if(j == i*5 || j < i*5 + 5 - 1) break;
	}
	str[21] = '\0';
	pass = str; //string型に変換
	return pass;
}

int USERLIST::change_63(char str){
	if(str >= '0' && str <= '9'){
		return str - '0' + 1;
	}
	else if(str >= 'A' && str <= 'Z'){
		return str - 'A' + 11;
	}
	else if(str >= 'a' && str <= 'z'){
		return str - 'a' + 37;
	}
}

char USERLIST::change_char(int val){
	if(val == 0){
		return 0;
	}
	if(val <= 10){
		return '0' + val - 1;
	}else if(val <= 36){
		return 'A' + val - 11;
	}else{
		return 'a' + val - 37;
	}
}

LONG USERLIST::stoi(string str){
	LONG ret;
	stringstream ss;
	ss << str;
	ss >> ret;
	return ret;
}

/*
int main(void){
	RSA rsa;
	USERLIST userlist;
	
	string pass = "zzzzzzzzzzzzzzzzzzzz";
	vector<LONG> data_pass(4,0);
	data_pass = userlist.change_to_LONG(pass);
	cout << pass << endl;
	for(int i = 0; i < 4; i++){
		cout << data_pass[i] << ", ";
	}
	cout << endl;
	cout << "暗号" << endl;
	for(int i = 0; i < 4; i++){
		cout << (data_pass[i] = rsa.Ec(data_pass[i],E,P*Q)) << ", ";
	}
	cout<< endl;
	cout << "復号" << endl;
	for(int i = 0; i < 4; i++){
		cout << (data_pass[i] = rsa.Dc(data_pass[i],P,Q,E)) << ", ";
	}
	cout<< endl;
	cout << userlist.change_to_string(data_pass) << endl;

	userlist.login();
	userlist.delete_user();

	return 0;
}
*/
