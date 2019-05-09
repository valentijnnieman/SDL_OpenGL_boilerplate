#pragma once
#include <iostream>

class Debug
{
public:
	template<class message>
	static void Log(message msg) { std::cout << msg << std::endl; }
};