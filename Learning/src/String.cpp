#include <string>
#include <ostream>

class String
{
private:
	char* mBuffer;
	unsigned int mSize;

public:
	String(const char* buffer) {
		mSize = strlen(buffer);
		mBuffer = new char[mSize + 1];
		memcpy(mBuffer, buffer, mSize);
		mBuffer[mSize] = 0;
	}

	String(const String& other) : mSize(other.mSize) {
		createCopy(other);
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

	/*String& operator = (String& other) {
		return createCopy(other);
	}*/

private:
	void createCopy(const String& other) {
		mSize = other.mSize;
		mBuffer = new char[mSize + 1];
		memcpy(mBuffer, other.mBuffer, mSize);
		mBuffer[mSize] = 0;
	}
};


//std::ostream& operator << (std::ostream& stream, const String& string) {
//	std::cout << string.mBuffer << std::endl;
//	return stream;
//}