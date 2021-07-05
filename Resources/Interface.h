#pragma once 

#include <iostream>
#include <string>
#include "Resources\BPlusInterface.h"
#include "Resources\BInterface.h"

class Interface
{
	string ID;
	int Degree;
	bool haveRead;
public:
	Interface()
	{
		ID="";
		Degree=-1;
		haveRead="";
	}
	void useTrees()
	{
		cout<<"Which Tree you have to Use."<<endl;
		int type=-1;
		while(type<0 || type >2) 
		{
			cout<<"Enter 1 for BTree."<<endl;
			cout<<"Enter 2 for BPlusTree."<<endl;
			cin>>type;
			cin.ignore();
		}
		while(Degree<3) 
		{
			cout<<"Enter Tree Degree must be >3 ."<<endl;
			cin>>Degree;
			cin.ignore();
		}
		int Datatype=-1,inp=0;;
		while(Datatype<0 || Datatype>6)
		{
			cout<<"Enter 1 to index on ID."<<endl;
			cout<<"Enter 2 to index on Year."<<endl;
			cout<<"Enter 3 to index on Cause Name."<<endl;
			cout<<"Enter 4 to index on State."<<endl;
			cout<<"Enter 5 to index on Deaths."<<endl;
			cout<<"Enter 6 to index on Age-adjusted Death Rate."<<endl;
			cin>>Datatype;
			cin.ignore();
		}
		if(Datatype==1 || Datatype==2 || Datatype==5)
			inp=1;
		else if(Datatype==3 || Datatype==4)
			inp=2;
		else if(Datatype==6)
			inp=3;
		if(Datatype==1)
		{
			ID="ID";
		}
		else if(Datatype==2)
		{
			ID="Year";
		}
		else if(Datatype==3)
		{
			ID="Cause Name";
		}
		else if(Datatype==4)
		{
			ID="State";
		}
		else if(Datatype==5)
		{
			ID="Deaths";
		}
		else if(Datatype==6)
		{
			ID="Age-adjusted Death Rate";
		}
		if(type==1)
		{
			if(inp==1)
			{
				BInterface<int> BTreeMenu;
				BTreeMenu.Menu(Degree,ID);
			}
			if(inp==3)
			{
				BInterface<float> BTreeMenu;
				BTreeMenu.Menu(Degree,ID);
			}
			if(inp==2)
			{
				BInterface<string> BTreeMenu;
				BTreeMenu.Menu(Degree,ID);
			}

		}
		else if(type==2)
		{
			if(inp==1)
			{
				BPlusInterface<int> BPlusTreeMenu;
				BPlusTreeMenu.Menu(Degree,ID);
			}
			if(inp==3)
			{
				BPlusInterface<float> BPlusTreeMenu;
				BPlusTreeMenu.Menu(Degree,ID);
			}
			if(inp==2)
			{
				BPlusInterface<string> BPlusTreeMenu;
				BPlusTreeMenu.Menu(Degree,ID);
			}
		}
	}
};