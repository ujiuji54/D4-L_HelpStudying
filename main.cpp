#include<iostream>
#include<string>
#include"cardlist.hpp"
#include"userlist.hpp"
using namespace std;

int main() {
	cardlist cardlist;
	cout << "make 3cards and display" << endl;
	cardlist.make_card("banana","バナナ","114306");
	cardlist.make_card("tomato","トマト","114305");
	cardlist.make_card("orange","オレンジ","114307");
	cardlist.make_card("apple","リンゴ","114305");
	cardlist.display();
	cout << endl;
	cout << "display user cardlist" << endl;
	cardlist.display("114305");
	cout << endl;
	cout << "remove card and display" << endl;
	cardlist.remove_card("banana","114306");
	cardlist.display();
	cout << endl;
	cout << "remove user and display" << endl;
	cardlist.remove_user("114307");
	cardlist.display();
	cout << endl;
	cout << "get card from name and cout" << endl;
	card card=cardlist.get_card("tomato");
	cout << card.name <<" "<< card.mean <<endl;
	cout << endl;
	cout << "get card from num and cout" << endl;
	card=cardlist.get_card(0);
	cout << card.name <<" "<< card.mean <<endl;
	cout << endl;
	cout << "get cardlist size"<<endl;
	cout << cardlist.get_cardlist_size() <<endl;
	cout << "answer and display" <<endl;
	cardlist.answer("tomato","114305",true);
	cardlist.answer("apple","114305",false);
	cardlist.display();
	cout << endl;
}
