#pragma once

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
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

using namespace std;
typedef unsigned long long LONG;

class RSA{
	private:
		LONG   getl(LONG   p,LONG   q);
	public:
		LONG   Ec(LONG   ec, LONG   e, LONG   n);
		LONG   Dc(LONG   ec, LONG   p, LONG   q, LONG   e);
		LONG   gete(LONG   p,LONG   q);
		LONG   getd(LONG   p,LONG   q,LONG   e);
		bool   primeNumber(LONG n);
		vector<LONG> change_to_LONG(string pass);
		string change_to_string(vector<LONG> data_pass);
        int change_63(char str);
		char change_char(int val);
};

bool RSA::primeNumber(LONG n){
    if(n < 2) return false;
    else{
        for(int i = 2; i * i <= n; i++){
            if(n % i == 0) return false;
        }
        return true;
    }
}

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
	p -= 1;
	q -= 1;
	while ((t = p % q) != 0) { //ユークリッドの互除法で(p-1)と(q-1)の最大公約数を求める
		p = q;
		q = t;
	}
	return m / q; //(p-1)と(q-1)の積から最大公約数を割る
}

LONG RSA::gete(LONG p, LONG q){
	LONG e1, gcdEL = 0;
	LONG L = getl(p, q);
	LONG x, y, r;
	while(gcdEL != 1){
		e1 = 0;
		while(e1 <= 1){
			e1 = rand() % L; //公開鍵はLより小さい数
		}
		x = e1;
		y = L;
		while((r = x % y) != 0){ //LとLより小さい数の最大公約数が１であればE
			x = y;
			y = r;
		}
		gcdEL = y;
	}
	return e1;
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

vector<LONG> RSA::change_to_LONG(string pass){ //63進数の5個の配列に変換
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

string RSA::change_to_string(vector<LONG> data_pass){
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

int RSA::change_63(char str){
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

char RSA::change_char(int val){
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


LONG RSA::Dc(LONG   ee,LONG   p,LONG   q,LONG   e){
	//cout << "d = " << getd(p,q,e) << endl;
	return Ec(ee,getd(p,q,e),p*q);
}