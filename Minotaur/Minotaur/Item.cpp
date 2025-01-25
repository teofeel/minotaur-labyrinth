#pragma once
#include "stdafx.h"
#include "Item.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

Item::Item(string name) {
	this->name = name;
	this->lifespan = 3;
}


string Item::getName() {
	return this->name;
}

int Item::getLifespan() {
	return this->lifespan;
}


void Item::shorten_lifespan() {
	this->lifespan--;
}


ostream& operator<<(ostream& stream, const Item& obj) {
	stream << "Name: " << obj.name << " | Moves Left: " << obj.lifespan << endl;

	return stream;
}

bool operator==(const Item& obj1, const Item& obj2) {
	return obj1.name == obj2.name;
}

bool operator==(const Item& obj1, const string& n) {
	return obj1.name == n;
}