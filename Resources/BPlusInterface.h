#pragma once 

#include <iostream>
#include <string>

#include "BPlusTree.h"

template<typename T>
class BPlusInterface
{
	BPlusTree<T>* simpleTree;
	int Degree;
	string ID;
	void readTree_Disk()
	{
		delete simpleTree;
		stringstream name;
		name<<"../Resources/NodesBPlusTree/BIN"<<ID<<"/"<<Degree<< "root.txt";
		cout<<name.str()<<endl;
		ifstream inFile;
		inFile.open(name.str());
		if(inFile.is_open())
		{
			cout<<"Tree remove From memory."<<endl;
			simpleTree=new BPlusTree<T>(Degree);
			stringstream name,name2;
			string Line;
			getline(inFile,Line,'\n');
			int Index=Line.find(',');
			if(Index!=string::npos)
			{
				name2<<"BIN"<<ID;
				Line=Line.substr(0,Index);
				simpleTree->readRoot(Line,name2.str());
			}
			cout<<"root is RAM."<<endl;
		}
		else
		{
			cout<<"Tree of Given Degree is not avialble in the Disk"<<endl;
		}
	}
	void rangeSearch()
	{
		int key;
		string value,value2,field,condition;
		cout<<"Press 1 to do field=key Search."<<endl;
		cout<<"Press anything for simple Search."<<endl;
		cin>>key;
		cin.ignore();
		if(key==1)
		{
			cout<<"Enter the Start Point."<<endl;
			getline(cin,value);
			cout<<"Enter the End Point."<<endl;
			getline(cin,value2);
			cout<<"Enter the field to Search."<<endl;
			getline(cin,field);
			cout<<"Enter the value to Search."<<endl;
			getline(cin,condition);
			simpleTree->searchKey(value,value2,field,condition);
		}
		else
		{
			
			cout<<"Enter the Start Point."<<endl;
			getline(cin,value);
			cout<<"Enter the End Point."<<endl;
			getline(cin,value2);
			simpleTree->searchKey(value,value2);
		}
	}
	void Update()
	{
		string value,value2,field,newValue,oldValue;
			cout<<"Enter the Start Point."<<endl;
			cin.ignore();
			getline(cin,value);
			cout<<"Enter the End Point."<<endl;
			getline(cin,value2);
			cout<<"Enter the field to Update."<<endl;
			getline(cin,field);
			cout<<"Enter the value to be Updated."<<endl;
			getline(cin,oldValue);
			cout<<"Enter the new value."<<endl;
			getline(cin,newValue);
		simpleTree->UpdateKey(value,value2,field,oldValue,newValue);
	}
	void readFiles()
	{
		simpleTree->BuildTree("../Resources/OriginalFiles/test_1.csv",ID);
		simpleTree->BuildTree("../Resources/OriginalFiles/test_2.csv",ID);
		/*simpleTree->BuildTree("../Resources/OriginalFiles/NCHS_-_Leading_Causes_of_Death__United_States_1.csv",ID);
		simpleTree->BuildTree("../Resources/OriginalFiles/NCHS_-_Leading_Causes_of_Death__United_States_2.csv",ID);
		simpleTree->BuildTree("../Resources/OriginalFiles/NCHS_-_Leading_Causes_of_Death__United_States_3.csv",ID);
		simpleTree->BuildTree("../Resources/OriginalFiles/NCHS_-_Leading_Causes_of_Death__United_States_4.csv",ID);
		simpleTree->BuildTree("../Resources/OriginalFiles/NCHS_-_Leading_Causes_of_Death__United_States_5.csv",ID);
		simpleTree->BuildTree("../Resources/OriginalFiles/NCHS_-_Leading_Causes_of_Death__United_States_6.csv", ID);
		simpleTree->BuildTree("../Resources/OriginalFiles/NCHS_-_Leading_Causes_of_Death__United_States_7.csv", ID);
		simpleTree->BuildTree("../Resources/OriginalFiles/NCHS_-_Leading_Causes_of_Death__United_States_8.csv", ID);
		simpleTree->BuildTree("../Resources/OriginalFiles/NCHS_-_Leading_Causes_of_Death__United_States_9.csv", ID);
		simpleTree->BuildTree("../Resources/OriginalFiles/NCHS_-_Leading_Causes_of_Death__United_States_10.csv", ID);*/
	}
public:
	void Menu(int Degree,string ID)
	{
		this->Degree=Degree;
		this->ID=ID;
		simpleTree =new BPlusTree<T>(Degree);
		bool haveShown=true;
		cout<<"Press 1 to read from disk"<<endl;
		cout<<"Press 2 for range search."<<endl;
		cout<<"Press 3 to Update files." <<endl;
		cout<<"Press 4 to read Tree from saved Files"<<endl;
		cout<<"Press 5 to change Degree."<<endl;
		cout<<"Press 6 to change ID."<<endl;
		cout<<"Press 7 to redisplay options."<<endl;
		cout<<"Enter 8 to exit."<<endl;
		int option=-1;
		while(1)
		{
			cin>>option;
			if(option==1)
			{
				readFiles();
				cout<<endl<<endl;
				cout<<"Press 1 to read from disk"<<endl;
				cout<<"Press 2 for range search."<<endl;
				cout<<"Press 3 to Update files." <<endl;
				cout<<"Press 4 to read Tree from saved Files"<<endl;
				cout<<"Press 5 to change Degree."<<endl;
				cout<<"Press 6 to change ID."<<endl;
				cout<<"Press 7 to redisplay options."<<endl;
				cout<<"Enter 8 to exit."<<endl;
			}
			else if(option==2)
			{
				rangeSearch();
				cout<<endl<<endl;
				cout<<"Press 1 to read from disk"<<endl;
				cout<<"Press 2 for range search."<<endl;
				cout<<"Press 3 to Update files." <<endl;
				cout<<"Press 4 to read Tree from saved Files"<<endl;
				cout<<"Press 5 to change Degree."<<endl;
				cout<<"Press 6 to change ID."<<endl;
				cout<<"Press 7 to redisplay options."<<endl;
				cout<<"Enter 8 to exit."<<endl;
			}
			else if(option==3)
			{
				Update();
				cout<<endl<<endl;
				cout<<"Press 1 to read from disk"<<endl;
				cout<<"Press 2 for range search."<<endl;
				cout<<"Press 3 to Update files." <<endl;
				cout<<"Press 4 to read Tree from saved Files"<<endl;
				cout<<"Press 5 to change Degree."<<endl;
				cout<<"Press 6 to change ID."<<endl;
				cout<<"Press 7 to redisplay options."<<endl;
				cout<<"Enter 8 to exit."<<endl;
			}
			else if(option==4)
			{
				readTree_Disk();
				cout<<endl<<endl;
				cout<<"Press 1 to read from disk"<<endl;
				cout<<"Press 2 for range search."<<endl;
				cout<<"Press 3 to Update files." <<endl;
				cout<<"Press 4 to read Tree from saved Files"<<endl;
				cout<<"Press 5 to change Degree."<<endl;
				cout<<"Press 6 to change ID."<<endl;
				cout<<"Press 7 to redisplay options."<<endl;
				cout<<"Enter 8 to exit."<<endl;
			}
			else if(option==5)
			{
				delete simpleTree;
				int newDegree=-1;
				while(newDegree<3)
				{
					cout<<"Enter new Degree."<<endl;
					cin >> newDegree;
				}
				simpleTree=new BPlusTree<T>(newDegree);
				readFiles();
				cout<<endl<<endl;
				cout<<"Press 1 to read from disk"<<endl;
				cout<<"Press 2 for range search."<<endl;
				cout<<"Press 3 to Update files." <<endl;
				cout<<"Press 4 to read Tree from saved Files"<<endl;
				cout<<"Press 5 to change Degree."<<endl;
				cout<<"Press 6 to change ID."<<endl;
				cout<<"Press 7 to redisplay options."<<endl;
				cout<<"Enter 8 to exit."<<endl;
			}
			else if(option==6)
			{
				delete simpleTree;
				ID="";
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
				simpleTree=new BPlusTree<T>(Degree);
				readFiles();
				cout<<endl<<endl;
				cout<<"Press 1 to read from disk"<<endl;
				cout<<"Press 2 for range search."<<endl;
				cout<<"Press 3 to Update files." <<endl;
				cout<<"Press 4 to read Tree from saved Files"<<endl;
				cout<<"Press 5 to change Degree."<<endl;
				cout<<"Press 6 to change ID."<<endl;
				cout<<"Press 7 to redisplay options."<<endl;
				cout<<"Enter 8 to exit."<<endl;
			}
			else if(option==7)
			{
				cout<<"Press 1 to read from disk"<<endl;
				cout<<"Press 2 for range search."<<endl;
				cout<<"Press 3 to Update files." <<endl;
				cout<<"Press 4 to read Tree from saved Files"<<endl;
				cout<<"Press 5 to change Degree."<<endl;
				cout<<"Press 6 to change ID."<<endl;
				cout<<"Press 7 to redisplay options."<<endl;
				cout<<"Enter 8 to exit."<<endl;
			}
			else if(option==8)
			{
				cout<<"Program ExiT."<<endl;
				delete simpleTree;
				return ;
			}
		}
	}
};