#include "pch.h"

class String
{
private:
	char* mBuffer;
	unsigned int mSize;

public:
	String() {}

	String(const char* buffer) {
		std::cout << "Created : " << buffer << std::endl;
		mSize = strlen(buffer);
		mBuffer = new char[mSize + 1];
		memcpy(mBuffer, buffer, mSize);
		mBuffer[mSize] = 0;
	}

	String(const String& other) : mSize(other.mSize) {
		std::cout << "Copied\n";
		createCopy(other);
	}


	// using Move Semantics 
	String(String&& other) noexcept {
		mBuffer = other.mBuffer;
		mSize = other.mSize;

		other.mBuffer = nullptr;
		other.mSize = 0;
	}

	~String() {
		delete[] mBuffer;
	}

	friend std::ostream& operator << (std::ostream& stream, const String& string);

	char& operator [] (unsigned int index) {
		return mBuffer[index];
	}

	bool operator == (const String& other) {
		if (mSize == other.mSize) {
			int currentSize = mSize - 1;
			while (currentSize >= 0) {
				if (mBuffer[currentSize] != other.mBuffer[currentSize]) return false;
				currentSize--;
			}
			return true;
		}
		return false;
	}


	String& operator = (String&& other) noexcept {
		if (this != &other) {
			delete[] mBuffer;
			mBuffer = other.mBuffer;
			mSize = other.mSize;

			other.mSize = 0;
			other.mBuffer = nullptr;
		}
		return *this;
	}

	void print() {
		if (mBuffer == nullptr || mSize == 0) {
			std::cout << std::endl;
			return;
		}

		std::cout << mBuffer << std::endl;
	}

private:
	void createCopy(const String& other) {
		mSize = other.mSize;
		mBuffer = new char[mSize + 1];
		memcpy(mBuffer, other.mBuffer, mSize);
		mBuffer[mSize] = 0;
	}
};


//int main() {
//	std::cout << "Operator Lessons" << std::endl;
//	String first = "Raed";
//	String second = "Raed";
//
//	std::cout << first;
//	std::cout << second;
//
//	std::cout << "Is equals " << (first == second) << std::endl;
//	std::cout << "End Operator Lesson" << std::endl;
//}