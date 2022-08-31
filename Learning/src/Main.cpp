#include <iostream>
#include "..\headers\Log.h"
#include <stdlib.h>
#include <string>
#include "String.cpp"
#include <vector>
#include <GLFW/glfw3.h>

std::ostream& operator << (std::ostream& stream, const String& string) {
	std::cout << string.mBuffer << std::endl;
	return stream;
}


/************************************************ Function Pointers **********************/
void helloWorld(int a) {
	std::cout << "Hello World! " << a << std::endl;
}

struct Vect2 {
	int a, b;
};


struct Vect4 {
	union
	{
		struct {
			int a, b, c, d;
		};

		struct {
			Vect2 x, y;

		};

	};
};


void printVector(Vect2& v) {
	std::cout << v.a << ", " << v.b << std::endl;
}

int main()
{

	// checking the asci characters utf-8, utf-16 and utf-32
	//const wchar_t* name = L"رائد";
	//std::cout << "Name in arabic is " << name << std::endl;


	// reference lesson
	/*int var = 4;
	int* ptr = &var;
	*ptr = 10;
	log(var);*/


	// lamda lesson
	// lamda function where passing [=] means pass by value
	// passing [&] means pass by reference
	// if I want to change the x value without touching it's main value I should pass
	// by reference and use mutable keyword in order to able to change the x value

	int x = 8;
	auto f = [=]() mutable {
		x++;
		std::cout << "x " << x << std::endl;
	};
	f();
	std::cout << "old x " << x << std::endl;



	// write custom struct with operators such as + and *
	/*Vector2 v1(1, 1);
	Vector2 v2(4, 4);

	Vector2 result = v1 + v2;
	std::cout << "vector result " << result << std::endl;*/

	/********************************* Equality Operator ***********************/
	//String first = "Raed";
	//String second = "Raed";

	//std::cout << first;
	//std::cout << second;

	//std::cout << "Is equals " << (first == second) << std::endl;


	/*************************************** Vectors ***********************************/
	//std::vector<String> strings;

	//strings.push_back("Raed");
	//strings.push_back("Nasser");
	//strings.push_back("Saeed");

	//for (String& s : strings) {
	//	std::cout << s;
	//}


	/*************************************** Importing Libraries **************************/
	int library = glfwInit();
	std::cout << library << std::endl;

	/****************************************** Function Pointers **********************************/
	typedef void(*helloWorldFunction)(int);			// use typedef to define the type of function instead of defining as void(*func)(int)
	helloWorldFunction function = helloWorld;		// or auto func = helloWorld;
	function(5);

	/******************************************* Type puning **********************************/

	int a = 50;
	double value = *(double*)&a;
	//int b = 60;
	//int y = *(int*)((char*)&b + 4);

	/******************************************* Union ****************************************/

	Vect2 v2 = { 3, 4 };
	v2.a = 5.0f;

	Vect4 v4 = { 1, 2, 3, 5};
	printVector(v4.x);
	printVector(v4.y);

	std::cout << "------------------------------------------" << std::endl;
	v4.b = 50;
	printVector(v4.x);
	printVector(v4.y);

	std::cin.get();
}





// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
