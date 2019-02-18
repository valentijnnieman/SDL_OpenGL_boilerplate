#pragma once
#include <iostream>

class Debug
{
public:
	template<class msg>
	static void Log(msg msg) { std::cout << msg << std::endl; }
};