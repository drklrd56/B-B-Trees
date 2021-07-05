#pragma once

#include <string>
using namespace std;

template<typename T>
class Key
{
public:
	string ID_ELEMENT;
	string path_Directory;
	int linePointer;
	Key()
	{
		path_Directory = "";
		linePointer = -1;
	}
	Key(string ID_ELEMENT, string path_Directory, int linePointer)
	{
		this->ID_ELEMENT = ID_ELEMENT;
		this->path_Directory = path_Directory;
		this->linePointer = linePointer;
	}
	//change the Checks 
	bool operator > (Key<T> K2)
	{
		if (typeid(T) == typeid(int))
		{
			if (stoi(ID_ELEMENT) < stoi(K2.ID_ELEMENT))
				return false;
			return true;
		}
		if (typeid(T) == typeid(float))
		{
			if (stof(ID_ELEMENT) < stof(K2.ID_ELEMENT))
				return false;
			return true;
		}
		else 
		{
			if (ID_ELEMENT < K2.ID_ELEMENT)
				return false;
			return true;
		}
		
	}   
	bool operator >= (Key<T> K2)
	{
		if (typeid(T) == typeid(int))
		{
			if (stoi(ID_ELEMENT) < stoi(K2.ID_ELEMENT))
				return false;
			return true;
		}
		if (typeid(T) == typeid(float))
		{
			if (stof(ID_ELEMENT) < stof(K2.ID_ELEMENT))
				return false;
			return true;
		}
		else 
		{
			if (ID_ELEMENT < K2.ID_ELEMENT)
				return false;
			return true;
		}
		
	}
	bool operator < (Key<T> K2)
	{

		if (typeid(T) == typeid(int))
		{
			if (stoi(ID_ELEMENT) > stoi(K2.ID_ELEMENT))
				return false;
			return true;
		}
		if (typeid(T) == typeid(float))
		{
			if (stof(ID_ELEMENT) > stof(K2.ID_ELEMENT))
				return false;
			return true;
		}
		else
		{
			if (ID_ELEMENT > K2.ID_ELEMENT)
				return false;
			return true;
		}
	}
	bool operator <= (Key<T> K2)
	{

		if (typeid(T) == typeid(int))
		{
			if (stoi(ID_ELEMENT) > stoi(K2.ID_ELEMENT))
				return false;
			return true;
		}
		if (typeid(T) == typeid(float))
		{
			if (stof(ID_ELEMENT) > stof(K2.ID_ELEMENT))
				return false;
			return true;
		}
		else
		{
			if (ID_ELEMENT > K2.ID_ELEMENT)
				return false;
			return true;
		}
	}
	bool operator == (Key<T> K2)
	{
		if (typeid(T) == typeid(int))
		{
			if (stoi(ID_ELEMENT) == stoi(K2.ID_ELEMENT))
				return true;
			return false;
		}
		if (typeid(T) == typeid(float))
		{
			if (stof(ID_ELEMENT) == stof(K2.ID_ELEMENT))
				return true;
			return false;
		}
		else
		{
			if (ID_ELEMENT == K2.ID_ELEMENT)
				return true;
			return false;
		}
	}
	void operator = (Key<T> K2)
	{
		ID_ELEMENT = K2.ID_ELEMENT;
		path_Directory = K2.path_Directory;
		linePointer = K2.linePointer;
	}

};