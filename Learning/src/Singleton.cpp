#pragma once

class Singleton {
public:
	Singleton(const Singleton&) = delete;

	static Singleton& get() {
		static Singleton instance;
		return instance;
	}


	static float getMValue() { return get().IMValue(); }

private:
	Singleton() {}

	float mValue = 5;

	float IMValue() { return mValue; }
};