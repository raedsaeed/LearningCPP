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
	virtual String getName() { return mName; }

	// Inherited via Printable
	virtual void printClassName() override
	{
		
	}

};