#include "..\headers\Log.h"
#include <stdlib.h>
#include "pch.h"
#include "Entity.cpp"
#include "Timer.cpp"

// 75 - Structured Binding
#include <tuple>


// 76 - How to Deal with OPTIONAL DATA in C++
#include <optional>
#include <fstream>

// 77 - Multiple Types of Data in SINGLE VARIABLE in C++
#include <variant>

// 78 - How to store ANY data in C++
#include <any>

// 79 - How to make C++ run faster (with std::async)
#include <future>

// 82 - Singleton
#include "Singleton.cpp"


// 91 = Array - Create Datastructers in C++
#include "Array.cpp"

// create tuple with a specfic values
std::tuple<std::string, int> CreatePerson() {
	return { "Raed", 27 };
}


std::mutex mGaurd;

std::optional<std::string> readFileAsString(const std::string& filePath) {
	std::lock_guard<std::mutex> lock(mGaurd);
	std::fstream stream(filePath);

	if (stream) {
		std::string result = "has data";
		stream.close();
		return result;
	}

	return {};
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


struct MemoryAllocationTracker {
	uint32_t memoryAllocated = 0;
	uint32_t memoryFreed = 0;


	uint32_t getCurrentUsage() {
		return memoryAllocated - memoryFreed;
	}

	void printCurrentUsage() {
		std::cout << "current memory usage " << getCurrentUsage() << " bytes\n";
	}
};

static MemoryAllocationTracker tracker;

// overload the new operator to detect memory allocations
void* operator new(size_t size) {
	tracker.memoryAllocated += size;
	return malloc(size);
}

// overload the delete operator to track freed memory
void operator delete(void* memory, size_t size) {
	tracker.memoryFreed += size;
	free(memory);
}

#define STRING_VIEW 1
#if STRING_VIEW
void printName(std::string_view name) {
	std::cout << name << std::endl;
}
#else
void printName(const std::string& name) {
	std::cout << name << std::endl;
}
#endif

// Lvalue and Rvalue
#define LVALUE_AND_RVALUE 1
#if LVALUE_AND_RVALUE 

// will take only lvalue unless I use (const int& val)
// if I used (const int& val) instead of (int& val) the C++ compiler will replace it buy identifying new 
// statement such as int temp = val and pass the new temp variable
void setValue(int& val) {

}

// will take only rvalue
void setValue(int&& val) {

}
#endif
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
	Vector2 v2(4, 4);`

	Vector2 result = v1 + v2;
	std::cout << "vector result " << result << std::endl;*/

	/********************************* Equality Operator in String file ***********************/


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
	double* doubleValueOfA = (double*)&a;
	std::cout << "Double value of integer a in Type punning : " << *doubleValueOfA << std::endl;

	//int b = 60;
	//int y = *(int*)((char*)&b + 4);

	/******************************************* Union ****************************************/
	std::cout << "------------------------------------------ Union With Vectors ---------------------------" << std::endl;

	Vect2 v2 = { 3, 4 };
	v2.a = 5.0f;

	Vect4 v4 = { 1, 2, 3, 5 };
	printVector(v4.x);
	printVector(v4.y);

	v4.b = 50;
	printVector(v4.x);
	printVector(v4.y);

	/******************************************* (69) Casting *****************************************/
	{
		std::cout << "-------------------------------------- Casting -------------------------------------" << std::endl;

		double value = 5.3;
		int valueInt = (int)value;  // C style casting

		valueInt = static_cast<int> (value); // C++ recommended style casting

		//float* dynamicValueInt = dynamic_cast<float*>(&valueInt); // dynamic cast takes only object pointer or object referenc to cast it to another object

		Player* player = new Player();

		Entity* correctStaticCastEntity = static_cast<Entity*> (player); // static cast will work because it's doing complile check and defind conversion already there
		std::cout << "Correct Static Cast Entity ";
		correctStaticCastEntity->getName().print();

		Entity* correctDynamicCast = dynamic_cast<Entity*> (player); // dynamic cast also will work
		std::cout << "Correct Dynamic Cast Entity ";
		correctStaticCastEntity->getName().print();

		try
		{
			Enemy* wrongDynamicCast = dynamic_cast<Enemy*>(player); // wrong cast it will return null if Enable Runtime Type Information and No or just throws an exception if RTI is yes
			if (wrongDynamicCast) {
				std::cout << "Correct Dynamic Cast Entity ";
				wrongDynamicCast->getName().print();
			}
			else {
				std::cout << "Dynamic cast result is null" << std::endl;
			}
		}
		catch (const std::exception&)
		{
			std::cout << "Wrong Cast" << std::endl;
		}

		int c = 1; // using character would give us a run time crash so I used int
		std::cout << "Memory address of c character " << &c << std::endl;
		int* cPointer = reinterpret_cast<int*> (&c);

		std::cout << "Value of cPointer " << cPointer << std::endl;

		*cPointer = 5;
		std::cout << "Internal value of cPointer " << *cPointer << std::endl;
	}


	/********************************************************** (72) Pre Compiled Headers ******************************/
	{
		// using pch.h and pch.cpp to be compiled
		std::cout << "---------------------------------------- Pre Compiled Headers -----------------------" << std::endl;
		int mValues = 0;

		{
			Timer timer;
			for (int i = 2; i < 10000000; i++)
			{
				mValues += i;
			}
		}

	}

	/************************************************ (75) Structured Binding *******************************************/
	std::cout << "---------------------------------------- Structured Binding ---------------------------- " << std::endl;

	// old way to get structured binding
	std::tuple<std::string, int> person = CreatePerson();

	{
		std::string name = std::get<0>(person);
		int age = std::get<1>(person);
		std::cout << "Old way to get tuples data\n" << "name : " << name << ", age : " << age << std::endl;
	}

	{
		std::cout << "Second way to get tuples data\n";
		std::string secondName;
		int secondAge;
		std::tie(secondName, secondAge) = person;
		std::cout << "name : " << secondName << ", age : " << secondAge << std::endl;
	}

	// C++ 17 version the new method using auto 
	{
		auto [name, age] = person;
		std::cout << "C++17 way to get tuples data\n" << "name : " << name << ", age : " << age << std::endl;
	}


	/************************************** (76) How to Deal with Optional Data in C++ ************************************/

	std::cout << "---------------------------------------- Optional Data --------------------------------------------\n ";
	// can use auto and will work just fine
	std::optional<std::string> fileData = readFileAsString("fakeData.txt");
	std::string alternativeFakeData = fileData.value_or("Not Exist");

	if (fileData.has_value()) {
std::cout << "Fake data already exit yay :)\n";
	}
	else
	{
	std::cout << alternativeFakeData << std::endl;
	std::cout << "Fake data has no value and doesn't exist\n";
	}

	/***************************************** (77) Mutliple Data TYPES in SINGLE VARIABLE in C++ ***************************/
	std::cout << "-------------------- Mutliple Data TYPES in SINGLE VARIABLE in C++ ---------------------------------\n";

	// how variant is work ?? it's working by specifiying the variables that can it holds. then by sepecefying these values
	// it would override the last value and getting it would be by the usage of get_if or get<type>

	std::variant<std::string, int> variantData;
	variantData = "Raed";
	std::cout << std::get<std::string>(variantData) << std::endl;
	variantData = 2;

	if (auto variantValue = std::get_if<std::string>(&variantData)) {
		std::string& vv = *variantValue;
		std::cout << vv << std::endl;
	}
	else
	{
		std::cout << "No available data in the current variant\n";
	}

	std::cout << std::get<int>(variantData) << std::endl;

	/********************************************* (78) How to store ANY data in C++ ****************************************/
	std::cout << "------------------------ How to store ANY data in C++ --------------------------------\n";
	std::any anyData;
	anyData = 3;
	anyData = std::string("Raed");

	std::string anyDataPtr = std::any_cast<std::string>(anyData);
	std::cout << "Value of any data ptr " << anyDataPtr << std::endl;

	/********************************************* (79) How to make C++ run faster (with std::async) **************************/
	{
		std::cout << "----------------------------- How to make C++ run faster (with std::async) --------------------------\n";
		std::vector<std::future<std::optional<std::string>>> tasks;

		for (int i = 0; i < 100; i++) {
			// please note you can't assing std::async return value to a variable and then push it, it will gives you a crash :) 
			//tasks.push_back(std::async(std::launch::async, readFileAsString, "fakeData.txt"));
		}
	}

	/********************************************** (80) How to make your STRINGS faster in C++ (80) ****************************/
	{
		std::cout << "------------------------------ How to make your STRINGS faster in C++ ----------------------\n";
		std::string myName = "Raed Saeed";
#if STRING_VIEW
		std::string_view vFirstName(myName.c_str(), 4);
		std::string_view vLastName(myName.c_str() + 5, 5);
		printName(vFirstName);
		printName(vLastName);
#else
		std::string firstName = myName.substr(0, 4);
		std::string lastName = myName.substr(5, 5);
		printName(firstName);
		printName(lastName);
#endif
	}


	/************************************************ (82) Singleton in C++ **********************************************/
	{
		std::cout << "-------------------------------- Singleton in C++ ------------------------------------\n";
		Singleton& singleton = Singleton::get();

		std::cout << "singleton value " << singleton.getMValue() << std::endl;
		tracker.printCurrentUsage();
	}


	/************************************************ (83) Small String Optimaization in C++ ******************************************/
	{
		//std::cout << "-------------------------------- Small String Optimization in C++ --------------------------------\n";
		// how it works ??? 
		// basically memory allocation will happen to strings with length equal or more than 15 bytes or 15 characters and will use heap allocation
		// on other hand it will not use any heap allocatoin and instead will use stack allocation for strings less than 15 characters or 15 bytes
	}

	/********************************************** (84) Track Memory Allocations the easy way in C++ **********************************/
	{
		std::cout << "---------------------------------- Track Memory Allocations the easy way in C++ ------------------------------\n";
		tracker.printCurrentUsage();

	}

	/********************************************* (85) Lvalue and Rvalue **********************************************************/
	{
		int ll = 10;			// ll variable is left value and 10 is right value which is knowen as temporary value 
		setValue(ll);			// will use first setValue method
		setValue(10);			// will use second setValue method
	}

	/********************************************* (88) Argument Evaluation Order in C++ ************************************/ 
	{
		// in Argument Evaluation Order (AEO) meaning if you passed parameter to functions and this parameter
		// setValue(val++, val++) // this is undefined behaviour 
	}

	/******************************************** (89) Move Semantics in C++ ****************************************************/
	/******************************************** (90) std::move and Move Assignement Operator in C++ ****************************************************/
	{
		String oneString = "Raed";
		String otherString;


		std::cout << "String : ";
		oneString.print();
		std::cout << "Other String : ";
		otherString.print();

		otherString = std::move(oneString);

		std::cout << "String : ";
		oneString.print();

		std::cout << "Other String : ";
		otherString.print();

		otherString = "Something";
		std::cout << "Other String : ";
		otherString.print();

	}

	/*************************************************** (91) Array - Create Data Structers in C++ ************************************/
	{
		Array<int, 5> array;
		/*const Array<int, 5> constArray;


		for (int i = 0; i < constArray.getSize(); i++) {
			std::cout << constArray[i] << std::endl;
		}*/

		for (int i = 0; i < array.getSize(); i++) {
			array[i] = 5;
			std::cout << array[i] << std::endl;
		}
	}

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
