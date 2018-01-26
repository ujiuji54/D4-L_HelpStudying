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


LONG RSA::Dc(LONG   ee,LONG   p,LONG   q,LONG   e){
	//cout << "d = " << getd(p,q,e) << endl;
	return Ec(ee,getd(p,q,e),p*q);
}
/*
int main(void){
	RSA rsa;
	LONG key;
	LONG P, Q;
	//cout << "key -> " << key << endl;
	while(1){
		cout << "素数であろう数Pを入力してください" << endl << "-> ";
		cin >> P;
		while(rsa.primeNumber(P) == false){
			cout << "素数ではありません。もう1度入力してください" << endl << "-> ";
			cin >> P;
		}
		cout << "素数であろう数Qを入力してください" << endl << "-> ";
		cin >> Q;
		while(rsa.primeNumber(Q) == false){
			cout << "素数ではありません。もう1度入力してください" << endl << "-> ";
			cin >> Q;
		}
		if(P*Q > 4294967296){
			cout << "(P*Q)^2がunsigned long long内に収まらないので素数を小さい数にしてください" << endl;
		}else{
			break;
		}
	}
	LONG e = rsa.gete(P, Q);
	cout << P*Q-1 << "以内で暗号化したい数値を入力してください" << endl << "-> ";
	cin  >> key;
	cout << "暗号-> " << (key = rsa.Ec(key,e,P*Q)) << endl;
	cout << "復号-> " << rsa.Dc(key,P,Q,e) << endl;
	
	cout << endl << "素数P -> " << P << endl;
	cout << "素数Q -> " << Q << endl;
	cout << "公開鍵E" << " -> " << e << endl;
	cout << "秘密鍵D" << " -> " << rsa.getd(P, Q, e) << endl;

	return 0;
}
*/
