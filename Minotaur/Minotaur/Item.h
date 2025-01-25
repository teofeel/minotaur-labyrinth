#pragma once
#ifndef ITEM_H
#define ITEM_H
#include <iostream>
#include <string>

using namespace std;

class Item {
private:
	string name;
	int lifespan;
public:
	Item(string name);

	string getName();
	int getLifespan();

	void shorten_lifespan();

	friend ostream& operator<<(ostream& stream, const Item& obj);
	friend bool operator==(const Item& obj1, const Item& obj2);
	friend bool operator==(const Item& obj1, const string& n);
};

#endif