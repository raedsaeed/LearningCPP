#pragma once
#include "String.cpp"

class Printable {
public:
	virtual void printClassName() = 0;
};

class Entity : public Printable {
	String mName;

public:
	Entity() : mName("Unknow Entity") {} // constructor initilizer 
	Entity(const String& name) : mName(name) {}
	Entity(String&& name) : mName(std::move(name)){} // using Move Semantics
	virtual String& getName() { return mName; }

	//Inherited via Printable --> overriding printClassName method from Printable Interface
	virtual void printClassName() override
	{

	}

};

class Player : public Entity
{
public:
	Player() : Entity("Unknown Player") {
		getName().print();
	}

	~Player() {}

private:

};


class Enemy : public Entity
{
public:
	Enemy() {

	}
	~Enemy() {}

private:

};

