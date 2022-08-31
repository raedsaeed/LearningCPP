#include <ostream>

struct Vector2 {
	float x, y;

	Vector2(float x, float y) : x(x), y(y) {}

	Vector2 operator + (Vector2& other) {
		return Vector2(x + other.x, y + other.y);
	}

	Vector2 operator * (Vector2& other) {
		return Vector2(x * other.x, y * other.y);
	}

	bool operator== (Vector2& other) {
		return x == other.x && y == other.y;
	}

	bool operator!= (Vector2& other) {
		return !(*this == other);
	}
};

//std::ostream& operator << (std::ostream& stream, const Vector2& other) {
//	stream << other.x << ", " << other.y << std::endl;
//	return stream;
//}