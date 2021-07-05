#pragma once

#include <iostream>
#include <string>

using namespace std;

template<typename T>
class List
{
	class Node
	{
	public:
		T value;
		Node *next;
		Node *previous;
	};
	Node *head;
	Node *tail;
	int numItems;
public:
	class iterator;
	class iterator
	{
		friend class Node;
		Node* currentNode;
	public:
		iterator(Node* head)
		{
			currentNode=head;
		}
		void operator++()
		{
			currentNode=currentNode->next;
		}
		void operator--()
		{
			currentNode=currentNode->previous;
		}
		bool iterate()
		{
			if(currentNode==NULL)
				return false;
			return true;
		}
		T& operator*()
		{
			return currentNode->value; 
		}
	};
	List()
	{
		head = NULL;
		numItems = 0;
		tail = NULL;
	}
	~List()
	{
		makeNull();
	}
	void makeNull()
	{
		Node* currNode = head;
		Node* nextNode = NULL;
		while (currNode != NULL)
		{
			nextNode = currNode->next;
			delete currNode;
			currNode = nextNode;
		}
		tail = NULL;
		head = NULL;
		numItems = 0;
	}
	Node* begin()
	{
		return head;
	}
	Node* end()
	{
		return tail;
	}
	bool isEmpty()
	{
		return head == NULL;
	}
	template<typename T>
	bool insertNode(T& newDataItem, int index)
	{
		if (index <= 0)
			return false;
		int currentIndex = 2;
		Node* currentNode = head;
		while (currentNode != NULL && currentIndex < index)
		{
			currentNode = currentNode->next;
			currentIndex++;
		}
		if (index > 1 && currentNode == NULL)
			return false;
		Node *newNode = new Node();
		newNode->value = newDataItem;
		newNode->next = NULL;
		if (index == 1)
		{
			if (head != NULL)
				head->previous = newNode;
			newNode->next = head;
			newNode->previous = NULL;
			head = newNode;
			numItems++;
			if (tail == NULL)
				tail = newNode;
			tail->next = NULL;
		}
		else
		{
			if (tail == currentNode)
				tail = newNode;
			newNode->next = currentNode->next;
			newNode->previous = currentNode;
			if (currentNode->next != NULL)
				currentNode->next->previous = newNode;
			currentNode->next = newNode;
			currentNode = newNode;
			numItems++;
		}
	}
	void insert(T& newDataItem)
	{
		Node* newNode = new Node();
		newNode->value = newDataItem;
		newNode->next = NULL;
		newNode->previous = NULL;
		if (head != NULL)
		{
			newNode->previous = tail;
			tail->next = newNode;
			tail = newNode;
			tail->next = NULL;
		}
		else
		{
			head = newNode;
			tail = head;
			tail->next = NULL;
			head->next = NULL;
		}
		numItems++;
	}
	int Find(T DataItem)
	{
		int currentIndex = 1;
		Node* currentNode = head;
		while (currentNode != NULL && currentNode->value != DataItem)
		{
			currentNode = currentNode->next;
			currentIndex++;
		}
		if (currentNode != NULL)
			return currentIndex;
		return 0;
	}
	bool operator<(T value)
	{
		return head->value<value;
	}
	void operator=(List<T>& list2)
	{
		this->makeNull();
		Node* currentNode = list2.head;
		while (currentNode != NULL)
		{
			this->insert(currentNode->value);
			currentNode = currentNode->next;
		}
	}
	bool operator>(T value)
	{
		return head->value>value;
	}
	bool operator==(T value)
	{
		return head->value == value;
	}
	T& FindData(const int Index)
	{
		int currentIndex = 1;
		Node* currentNode = head;
		while (currentNode != NULL && currentIndex != Index)
		{
			currentNode = currentNode->next;
			currentIndex++;
		}
		if (currentNode != NULL)
		{
			return currentNode->value;
		}
	}
	int getLength()
	{
		return numItems;
	}
	T getHeadValue()
	{
		if(head!=NULL)
			return head->value;
	}
	bool DeleteIndex(int Index)
	{
		int currentIndex = 1;
		Node* currentNode = head;
		while (currentNode != NULL && currentIndex != Index)
		{
			currentNode = currentNode->next;
			currentIndex++;
		}
		if (currentNode)
		{
			if (currentNode->previous)
			{
				//T retValue=currentNode->value;
				Node* oldNode;
				oldNode = currentNode;
				oldNode->previous->next = oldNode->next;
				if (oldNode->next != NULL)
					oldNode->next->previous = currentNode->previous;
				if (oldNode == tail)
					tail = oldNode->previous;
				currentNode = oldNode->previous;
				delete oldNode;
				numItems--;
				return currentIndex;
			}
			else
			{
				//T retValue=currentNode->value;
				if (currentNode->next != NULL)
					currentNode->next->previous = NULL;
				head = currentNode->next;
				if (currentNode == tail)
					tail = NULL;
				delete currentNode;
				numItems--;
				return currentIndex;
			}
		}
		return 0;
	}
	void swap(int IndexHigher, int IndexLower)
	{
		if (this->numItems > 1)
		{
			Node* firstElement = head;
			int currentIndex = 1;
			while (currentIndex != IndexHigher)
			{
				firstElement = firstElement->next;
				currentIndex++;
			}
			Node* secondElement = head;
			currentIndex = 1;
			while (currentIndex != IndexLower)
			{
				secondElement = secondElement->next;
				currentIndex++;
			}
			T temp = firstElement->value;
			firstElement->value = secondElement->value;
			secondElement->value = temp;
		}
	}
	int Delete(T DataItem)
	{
		int currentIndex = 1;
		Node* currentNode = head;
		while (currentNode != NULL && currentNode->value != DataItem)
		{
			currentNode = currentNode->next;
			currentIndex++;
		}
		if (currentNode)
		{
			if (currentNode->previous)
			{
				Node* oldNode;
				oldNode = currentNode;
				oldNode->previous->next = oldNode->next;
				if (oldNode->next != NULL)
					oldNode->next->previous = currentNode->previous;
				if (oldNode == tail)
					tail = oldNode->previous;
				currentNode = oldNode->previous;
				delete oldNode;
				numItems--;
				return currentIndex;
			}
			else
			{
				if (currentNode->next != NULL)
					currentNode->next->previous = NULL;
				head = currentNode->next;
				if (currentNode == tail)
					tail = NULL;
				delete currentNode;
				numItems--;
				return currentIndex;
			}
		}
		return 0;
	}
	// Change it Later //memo
	void DisplayList()
	{
		int num = 0;
		Node* currNode = head;
		while (currNode != NULL)
		{
			cout << currNode->value.ID_ELEMENT << " ";
			currNode = currNode->next;
			num++;
		}
	}
};