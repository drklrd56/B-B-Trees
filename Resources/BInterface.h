#pragma once 

#include <iostream>
#include <string>

#include "BTree.h"
template<typename T>
class BInterface
{
	BTree<T>* simpleTree;
	int Degree;
	string ID;
	void readTree_Disk()
	{
		stringstream name,name2;
		name<<"../Resources/NodesBTree/BIN"<<ID<<"/"<<Degree<< "root.txt";
		ifstream inFile;
		inFile.open(name.str());
		if(inFile.is_open())
		{
			delete simpleTree;
			cout<<"Tree remove From memory."<<endl;
			simpleTree=new BTree<T>(Degree);
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
	void pointSeach()
	{
		int key;
		string value,field,condition;
		cout<<"Press 1 to do field=key Search."<<endl;
		cout<<"Press anything for simple Search."<<endl;
		cin>>key;
		cin.ignore();
		if(key==1)
		{
			cout<<"Enter the key to Search."<<endl;
			getline(cin,value);
			cout<<"Enter the field to Search."<<endl;
			getline(cin,field);
			cout<<"Enter the value to Search."<<endl;
			getline(cin,condition);
			simpleTree->searchKey(value,field,condition);
		}
		else
		{
			
			cout<<"Enter value to Search."<<endl;
			getline(cin,value);
			//cin.ignore();
			simpleTree->searchKey(value);
		}
	}
	void Update()
	{
		string indexKey,field,oldValue,newValue;
		cout<<"Enter the index key to Update."<<endl;
		cin.ignore();
		getline(cin,indexKey);
		cout<<"Enter the field to Update."<<endl;
		getline(cin,field);
		cout<<"Enter the Old value to Update."<<endl;
		getline(cin,oldValue);
		cout<<"Enter the new Value."<<endl;
		getline(cin,newValue);
		simpleTree->UpdateKey(indexKey,field,oldValue,newValue);
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
		simpleTree =new BTree<T>(Degree);
		bool haveShown=true;
		cout<<"Press 1 to read from disk"<<endl;
		cout<<"Press 2 for point search."<<endl;
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
				cout<<"Press 2 for point search."<<endl;
				cout<<"Press 3 to Update files." <<endl;
				cout<<"Press 4 to read Tree from saved Files"<<endl;
				cout<<"Press 5 to change Degree."<<endl;
				cout<<"Press 6 to change ID."<<endl;
				cout<<"Press 7 to redisplay options."<<endl;
				cout<<"Enter 8 to exit."<<endl;
			}
			else if(option==2)
			{
				pointSeach();
				cout<<endl<<endl;
				cout<<"Press 1 to read from disk"<<endl;
				cout<<"Press 2 for point search."<<endl;
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
				cout<<"Press 2 for point search."<<endl;
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
				cout<<"Press 2 for point search."<<endl;
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
				simpleTree=new BTree<T>(newDegree);
				readFiles();
				cout<<endl<<endl;
				cout<<"Press 1 to read from disk"<<endl;
				cout<<"Press 2 for point search."<<endl;
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
				simpleTree=new BTree<T>(Degree);
				readFiles();
				cout<<endl<<endl;
				cout<<"Press 1 to read from disk"<<endl;
				cout<<"Press 2 for point search."<<endl;
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
				cout<<"Press 2 for point search."<<endl;
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