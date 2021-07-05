#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <typeinfo>
#include <sstream>
#include "Key.h"
#include "List.h"

using namespace std;

template<typename T>
class BPlusTree
{
private:
	class BPlusNode
	{
	public:
		string Name;
		int numKeys;
		bool isleaf;
		int min_Keys;
		int max_Keys;
		BPlusNode()
		{
			max_Keys=-1;
			min_Keys=-1;
			isleaf=(false);
		}
		BPlusNode(int Degree,bool isleaf)
		{
			max_Keys=2(Degree/2)+1;
			min_Keys=max_Keys-1;
			isleaf=(false);
		}
		virtual bool isleafNode()=0;
		virtual void readNode(string Name)=0;
		virtual void writeNode(string FolderName)=0;
	};
	class InternalNode:public BPlusNode
	{
	public:
		string *pointerKeys;
		string *Children;
		InternalNode(int Degree)
		{
			max_Keys=2*(Degree/2)+1;
			min_Keys=(max_Keys-1);
			numKeys=0;
			isleaf=(false);
			pointerKeys=new string[Degree];
			Children=new string[Degree+1];
		}
		bool isleafNode()
		{
			return false;
		}
		void writeNode(string FolderName)
		{
			ofstream OutFile;
			string fileName ="../Resources/NodesBPlusTree/"+FolderName+"/"+ Name+".txt";
			OutFile.open(fileName);
			if (OutFile.is_open())
			{
				OutFile << Name << endl;
				int Index = 0;
				OutFile << isleaf << endl;
				OutFile << numKeys << endl;
				OutFile << "Keys : " << endl;
				for(Index=0;Index<numKeys;Index++)
				{
					OutFile<<Index<<"|"<<pointerKeys[Index]<<endl;
				}
				
				Index = 0;
				OutFile << "Children : " << endl;
				while (Index < numKeys+1)
				{
					if (Children[Index] != "")
					{
						OutFile << Children[Index];
						if (Index  < numKeys)
							OutFile << ',';
					}
					Index++;
				}
				OutFile <<endl<< "END";
				OutFile.close();
			}
			else
				cout << "ERROR.. Directory inaccessable." << endl;
		}
		void readNode(string Name)
		{
			ifstream inFile;
			inFile.open(Name);
			if (inFile.is_open())
			{

				string Line, ID;
				getline(inFile, Line, '\n');
				this->Name = Line;
				getline(inFile, Line, '\n');
				isleaf = stoi(Line);
				getline(inFile, Line, '\n');
				numKeys = stoi(Line);
				getline(inFile, Line, '\n');
				int index = 0;
				int current_pos = 0;
				int spaceCount = 0;
				string Key;
				while(getline(inFile, Line, '\n'))
				{
					if(Line=="Children : ")
						break;
					while (Line!="")
					{
						current_pos = Line.find("|");
						if (current_pos == string::npos)
						{
							Key = Line.substr(0, current_pos);
							pointerKeys[index]=Key;
							Line.erase(0, Line.length());
						}
						else
						{
							index=stoi(Line.substr(0, current_pos));
							Line.erase(0, current_pos + 1);
						}
					}
				}
				getline(inFile, Line, '\n');
				index = 0;
				while (Line!="")
				{
					current_pos = Line.find(",");
					if (current_pos==string::npos)
					{
						Children[index] = Line.substr(0, current_pos);
						Line.erase(0, Line.length());
					}
					else
					{
						Children[index] = Line.substr(0, current_pos);
						index++;
						Line.erase(0, current_pos + 1);
					}
				}
			}
			else
				cout << "FILE PATH NOT FOUND." << endl;
		}
		~InternalNode()
		{
			delete[] pointerKeys;
			delete[] Children;
		}
	};
	class leafNode:public BPlusNode
	{
	public:
		List<Key<T>> *DataKeys;
		string nextFile;
		//string prevFile;
		leafNode(int Degree)
		{
			DataKeys=new List<Key<T>>[Degree];
			nextFile="";
			//prevFile="";
			max_Keys=2*(Degree/2)+1;
			min_Keys=(max_Keys-1);
			numKeys=0;
			isleaf=(true);
		}
		bool isleafNode()
		{
			return true;
		}
		void writeNode(string FolderName)
		{
			ofstream OutFile;
			string fileName ="../Resources/NodesBPlusTree/"+FolderName+"/"+ Name+".txt";
			OutFile.open(fileName);
			if (OutFile.is_open())
			{
				OutFile << Name << endl;
				Key<T> head;
				int index = 0;
				OutFile << isleaf << endl;
				OutFile << numKeys << endl;
				OutFile << "Keys : ";
				while (index < numKeys)
				{
					for(List<Key<T>>::iterator Index=DataKeys[index].begin(); Index.iterate();Index++)
					{
						head=*Index;
						OutFile << '\n';
						OutFile <<index<<"|"<<head.ID_ELEMENT << "|" << head.path_Directory <<"|"<< head.linePointer;
					}
					index++;
				}
				index = 0;
				OutFile <<endl<< "nextFile : " << endl;
				OutFile <<nextFile<<endl;
				OutFile.close();
			}
			else
				cout << "ERROR.. Directory inaccessable." << endl;
		}
		void readNode(string Name)
		{
			ifstream inFile;
			inFile.open(Name);
			if (inFile.is_open())
			{

				string Line, ID;
				getline(inFile, Line, '\n');
				this->Name = Line;
				getline(inFile, Line, '\n');
				isleaf = stoi(Line);
				getline(inFile, Line, '\n');
				numKeys = stoi(Line);
				getline(inFile, Line, '\n');
				int index = 0;
				int current_pos = 0;
				int spaceCount = 0;
				Key<T>obj;
				while (Line != "nextFile : ")
				{
					getline(inFile, Line, '\n');
					if (Line == "nextFile : ")
						break;
					spaceCount = 0;
					index = -1;
					while (Line!="")
					{
						current_pos = Line.find("|");
						if (current_pos == string::npos)
						{
							obj.linePointer = stoi(Line.substr(0, current_pos));
							Line.erase(0, Line.length());
						}
						else
						{
							if (spaceCount == 0)
								index = stoi(Line.substr(0, current_pos));
							if(spaceCount==1)
								obj.ID_ELEMENT = Line.substr(0, current_pos);
							if(spaceCount==2)
								obj.path_Directory = Line.substr(0, current_pos);
							Line.erase(0, current_pos + 1);
							spaceCount++;
						}
					}
					if (index>-1)
						DataKeys[index].insert(obj);
				}
				getline(inFile, Line, '\n');
				nextFile=Line;
			}
			else
				cout << "FILE PATH NOT FOUND." << endl;
		}
		~leafNode()
		{
			for(int Index=0;Index<numKeys;Index++)
				DataKeys[Index].makeNull();
			delete[] DataKeys;
		}
	};
	BPlusNode *root;	
	int TreeDegree;	
	int median;		// copypoint in split
	int NodeNumber;	// numbering of nodes
	string FolderID;
	List<string> Fields;
	BPlusNode* createNode(string fileName)
	{
		if(fileName[fileName.length()-1]=='L')	// if leaf node read leaf type data
		{	
			BPlusNode *newNode=new leafNode(TreeDegree);
			leafNode *pointer=dynamic_cast<leafNode *>(newNode);
			pointer->readNode("../Resources/NodesBPlusTree/"+ FolderID+"/"+fileName+".txt");
			return newNode;
		}
		else if(fileName[fileName.length()-1]=='N')	// if non leaf read non leaf type data
		{
			BPlusNode* newNode=new InternalNode(TreeDegree);
			InternalNode *pointer=dynamic_cast<InternalNode *>(newNode);
			pointer->readNode("../Resources/NodesBPlusTree/"+ FolderID+"/"+fileName+".txt");
			return newNode;
		}
	}
	void WriteRoot(string idFolder)
	{
		ofstream inFile;
		stringstream name;
		name<<"../Resources/NodesBTree/"<<idFolder<<"/"<<TreeDegree<< "root.txt";
		inFile.open(name.str());	// File PATH
		if (inFile.is_open())
		{
			inFile << root->Name << "," << TreeDegree;
			inFile.close();
		}
		else
			cout << "ROOT NOT WRITTEN." << endl;
	}
	void insert(BPlusNode *tree,Key<T> insertValue)
	{
		if(tree->isleafNode())
		{
			leafNode *newNode=dynamic_cast<leafNode*>(tree);
			bool isSame=false;
			for(int Index=0;Index<tree->numKeys;Index++)
			{
				if(newNode->DataKeys[Index]==insertValue)
				{
					newNode->DataKeys[Index].insert(insertValue);
					isSame=true;
					break;
				}
			}
			if(isSame==false)
			{
				int Index=tree->numKeys-1;
				for(; Index>=0 && newNode->DataKeys[Index]>insertValue ;Index--)
				{
					newNode->DataKeys[Index + 1] = newNode->DataKeys[Index];
				}
				newNode->DataKeys[Index + 1].makeNull();
				newNode->DataKeys[Index + 1].insert(insertValue);  //insert Element
				newNode->numKeys++;
			}
			newNode->writeNode(FolderID);
		}
		else
		{
			int insertPoint = tree->numKeys - 1;
			Key<T> obj;
			InternalNode *newNode=dynamic_cast<InternalNode*>(tree);
			while (insertPoint >= 0)
			{
				obj.ID_ELEMENT=newNode->pointerKeys[insertPoint];
				if(obj < insertValue)
					break;
				else if(obj == insertValue)
					break;
				insertPoint--;
			}
			int divide;
			if (TreeDegree % 2 == 0)
				divide = 2 * median;
			else
				divide = 2 * median - 1;

			BPlusNode *tempNode = createNode(newNode->Children[insertPoint + 1]);
			if (tempNode->numKeys == divide)
			{
				if(tempNode->isleaf)
					tempNode=splitLeaf(newNode, tempNode, insertPoint + 1,insertValue);
				else
					tempNode=splitNonLeaf(newNode, tempNode, insertPoint + 1,insertValue);
			}
			//cout<<tempNode->Name<<endl;
			insert(tempNode, insertValue);
			delete tempNode;
		}
	}
	BPlusNode* splitLeaf(BPlusNode *parent,BPlusNode *child,int Index,Key<T> pointRight)
	{
		stringstream name;
		name<<TreeDegree<<"Node"<<NodeNumber;
		string nodeName=name.str();
		NodeNumber++;
		nodeName+="L";
		leafNode* newNode=new leafNode(TreeDegree);
		newNode->Name=nodeName;
		int index = 0;
		int loopInVariant;
		loopInVariant = median-1;
		leafNode *tempNode=dynamic_cast<leafNode*>(child);
		for (; index < median; index++)
		{
			newNode->DataKeys[index] = tempNode->DataKeys[index + loopInVariant];
			newNode->numKeys++;
		}
		if(TreeDegree%2==0)
		{
			newNode->DataKeys[newNode->numKeys] = tempNode->DataKeys[tempNode->numKeys-1];
			newNode->numKeys++;
		}
		child->numKeys=median-1;
		InternalNode *parentPointer=dynamic_cast<InternalNode*>(parent);
		for (index = parent->numKeys; index >= Index + 1; index--)
		{
			parentPointer->Children[index + 1] = parentPointer->Children[index];
		}
		parentPointer->Children[Index + 1] = newNode->Name;
		for (index = parent->numKeys - 1; index >= Index; index--)
		{
			parentPointer->pointerKeys[index + 1] = parentPointer->pointerKeys[index];
		}
		parentPointer->pointerKeys[Index] = tempNode->DataKeys[median - 1].getHeadValue().ID_ELEMENT;
		parentPointer->numKeys += 1;
		string tempName=tempNode->nextFile;
		tempNode->nextFile=newNode->Name;
		newNode->nextFile=tempName;
		tempNode->writeNode(FolderID);
		parentPointer->writeNode(FolderID);
		newNode->writeNode(FolderID);
		Key<T> obj;
		obj.ID_ELEMENT=parentPointer->pointerKeys[Index];
		if(pointRight==obj)
			return newNode;
		else if(pointRight>obj)
			return newNode;
		else
			return tempNode;
	}
	BPlusNode* splitNonLeaf(BPlusNode *parent,BPlusNode *child,int Index,Key<T> pointRight)
	{
		stringstream name;
		name<<TreeDegree<<"Node"<<NodeNumber;
		string nodeName=name.str();
		nodeName+="N";
		NodeNumber++;
		InternalNode* newNode=new InternalNode(TreeDegree);
		newNode->Name=nodeName;
		int index = 0;
		int loopInVariant;
		if (TreeDegree % 2 == 0)
			loopInVariant = median;
		else
			loopInVariant = median-1;
		InternalNode *tempNode=dynamic_cast<InternalNode*>(child);
		for (; index < loopInVariant; index++)
		{
			newNode->pointerKeys[index] = tempNode->pointerKeys[index + median];
			newNode->numKeys++;
		}
		
		if (child->isleaf == false)
		{
			if (TreeDegree % 2 == 0)
				loopInVariant = median + 1;
			else
				loopInVariant = median;
			for (index = 0; index < loopInVariant; index++)
			{
				newNode->Children[index] = tempNode->Children[index + median];
			}
		}
		child->numKeys=median-1;
		InternalNode *parentPointer=dynamic_cast<InternalNode*>(parent);
		for (index = parent->numKeys; index >= Index + 1; index--)
		{
			parentPointer->Children[index + 1] = parentPointer->Children[index];
		}
		parentPointer->Children[Index + 1] = newNode->Name;
		for (index = parent->numKeys - 1; index >= Index; index--)
		{
			parentPointer->pointerKeys[index + 1] = parentPointer->pointerKeys[index];
		}
		parentPointer->pointerKeys[Index] = tempNode->pointerKeys[median - 1];
		parentPointer->numKeys += 1;

		tempNode->writeNode(FolderID);
		parentPointer->writeNode(FolderID);
		newNode->writeNode(FolderID);
		Key<T> obj;
		obj.ID_ELEMENT=parentPointer->pointerKeys[Index];
		if(pointRight == obj)
			return newNode;
		else if(pointRight > obj)
			return newNode;
		else
			return tempNode;
	}
	void Display(List<Key<T>>& value,int fieldNumber=0, string condition="")
	{
		ifstream inFile;
		static const int max_line = 65536;
		string Line;
		Key<T> actualVal;
		for(List<Key<T>>::iterator a=value.begin(); a.iterate(); a++)
		{
			actualVal=*a;
			if(actualVal.path_Directory!="")
			{
				inFile.open(actualVal.path_Directory);
				for(int Index=0;Index<actualVal.linePointer;Index++)
					inFile.ignore(max_line, '\n');
				getline(inFile,Line,'\n');
			}
			actualVal.ID_ELEMENT="";
			actualVal.linePointer=-1;
			actualVal.path_Directory="";
			inFile.close();
			if(condition=="")
				cout<<Line<<endl;
			else
			{
				if(find(Line,fieldNumber,condition)==true)
					cout<<Line<<endl;
			}
		}
	}
 	void Update(List<Key<T>>& value,int fieldNumber,string newValue,string oldValue)
	{
		ifstream inFile;
		ofstream outFile;
		string Line;
		Key<T> actualVal;
		bool isClosed=false,isChanged=false;
		for(List<Key<T>>::iterator a=value.begin(); a.iterate(); a++)
		{
			actualVal=*a;
			isClosed=false;
			Line="";
			if(actualVal.path_Directory!="")
			{
				inFile.open(actualVal.path_Directory);
				getline(inFile,Line,'\0');
				isChanged=replace(Line,fieldNumber,newValue,oldValue,actualVal.linePointer);
				if(isChanged==true)
				{
					//cout<<Line<<endl;
					inFile.clear();
					inFile.close();
					outFile.open(actualVal.path_Directory);
					outFile<<Line;
					outFile.close();
					isClosed=true;
				}
			}
			actualVal.ID_ELEMENT="";
			actualVal.linePointer=-1;
			actualVal.path_Directory="";
			if(isClosed==false)
				inFile.close();
		}
	}
	bool replace(string& file,int fieldNumber,string newValue,string oldValue,int lineNumber)
	{
		static const int max_line = 65536;
		string Line="";int Index_Main=0,Index=0;
		while(1)
		{
			Line+=file[Index_Main];
			if(file[Index_Main]=='\n')
				Index++;
			if(Index==lineNumber)
				break;
			Index_Main++;
		}
		string temp="";string temp2="";
		Index=Index_Main+1;
		bool returnCondition=false;
		while(file[Index]!='\n'&& file[Index]!='\0')
		{
			temp+=file[Index];
			Index++;
			if(Index>=file.length())
				break;
		}
		if(find(temp,fieldNumber,oldValue)==false)
			return false;
		Index_Main+=temp.length();
		size_t current_pos = 0;
		while (temp!="")	
		{
			current_pos = temp.find(",");
			if (current_pos == string::npos)
			{
				
				if(oldValue==temp.substr(0,temp.length()))
				{
					temp2+=newValue;
					returnCondition=true;
				}
				else
					temp2+=temp.substr(0,temp.length());
				temp.erase(0, temp.length());
			}
			else
			{
				if(temp.substr(0,current_pos)==oldValue)
				{
					returnCondition=true;
					temp2+=newValue+",";
				}
				else
					temp2+=temp.substr(0,current_pos+1);
				temp.erase(0, current_pos + 1);
				if (temp[0] == '\"')
				{
					current_pos = temp.find("\",");
					temp2+=temp.substr(0, current_pos + 2);
					temp.erase(0, current_pos + 2);
				}
			}
		}
		if(returnCondition==true)
		{
			Index=0;
			while(Index<temp2.length())
			{
				Line+=temp2[Index];
				Index++;
			}
			Index_Main++;
			while(Index_Main<file.length()-1)
			{
				Line+=file[Index_Main];
				Index_Main++;
			}
			file=Line;
		}
		return returnCondition;
	}
	bool find(string Line,int fieldNumber,string condition)
	{
		size_t current_pos = 0;
		int count = 1;
		while (Line!="")
		{
			current_pos = Line.find(",");
			if (current_pos == string::npos)
			{
				if (count == fieldNumber)
				{
					if(Line==condition)
						return true;
					else
						return false;
				}
				Line.erase(0, Line.length());
			}
			else
			{
				if (count == fieldNumber)
				{
					if(condition == Line.substr(0, current_pos))
						return true;
				}
				Line.erase(0, current_pos + 1);
				if (Line[0] == '\"')
				{
					current_pos = Line.find("\",");
					Line.erase(0, current_pos + 2);
					count++;
				}
			}
			count++;
		}
		return false;
	}
	void search(BPlusNode *tree,Key<T> searchValue,Key<T> stop,bool UpdateORNot=0,int fieldNumber=0,string newValue="",string oldValue="")
	{
		int Index=0;
		if(tree->isleaf)
		{
			leafNode* leafPointer=dynamic_cast<leafNode*>(tree);
			Key<T> compare;
			while(Index<tree->numKeys && leafPointer->DataKeys[Index] < searchValue && !(leafPointer->DataKeys[Index] == searchValue))
			{
				Index++;
			}
			bool yamate=false;
			if(tree->numKeys>Index && leafPointer->DataKeys[Index]==searchValue)
			{
				yamate=true;
				while(1)
				{
					for(int index=Index;index<tree->numKeys;index++)
					{
						if(UpdateORNot==false)
						{
							if(newValue=="")
								Display(leafPointer->DataKeys[index]);
							else
								Display(leafPointer->DataKeys[index],fieldNumber,newValue);
						}
						else 
						{
							Update(leafPointer->DataKeys[index],fieldNumber,newValue,oldValue);
						}
					}
					tree=createNode(leafPointer->nextFile);
					leafPointer=dynamic_cast<leafNode *>(tree);
					compare=leafPointer->DataKeys[Index].getHeadValue();
					if(compare.ID_ELEMENT==stop.ID_ELEMENT)
					{
						for(int index=Index;index<tree->numKeys;index++)
						{
							if(UpdateORNot==false)
							{
								if(newValue=="")
									Display(leafPointer->DataKeys[index]);
								else
									Display(leafPointer->DataKeys[index],fieldNumber,newValue);
							}
							else 
							{
								Update(leafPointer->DataKeys[index],fieldNumber,newValue,oldValue);
							}
						}
						break;
					}
				}
			}
			if(yamate==false)
			{
				cout<<"No Path Found."<<endl;
				return ;
			}
		}
		else
		{
			InternalNode *internalPointer=dynamic_cast<InternalNode *>(tree);
			Key<T> compare;
			while(Index<tree->numKeys)
			{
				 compare.ID_ELEMENT=internalPointer->pointerKeys[Index];
				if(!(compare < searchValue))
					break;
				if(compare==searchValue)
				{	
					Index++;
					break;
				}
				Index++;
			}
			BPlusNode *newNode;
			newNode= createNode(internalPointer->Children[Index]);
			search(newNode,searchValue,stop,UpdateORNot,fieldNumber,newValue,oldValue);
			delete newNode;
		}
	}

public:
	BPlusTree(int Degree)
	{
		if(Degree<3)
			cout<<"INValid Degree."<<endl;
		else
		{
			TreeDegree = Degree;
			if (Degree % 2 != 0)
				median = (Degree / 2) + 1;
			else
				median = (Degree / 2);
			root = NULL;
			NodeNumber = 1;
		}
	}
	void insertNode(Key<T> value,string ID)
	{
		cout<<value.ID_ELEMENT<<endl;
		if(FolderID=="")
			FolderID = "BIN"+ID;
		stringstream name;
		name<<TreeDegree<<"Node"<<NodeNumber;
		string nodeName=name.str();
		int divide;
		if (TreeDegree % 2 == 0)	// Handles the even and odd split and insert cases
			divide = 2 * median;
		else
			divide = 2 * median - 1;
		if(root==NULL)	// if root is NULL initialize the root inert value at 0 index by dynamic cast
		{
			NodeNumber++;
			root= new leafNode(TreeDegree);
			leafNode* newNode=dynamic_cast<leafNode*>(root);	// to access the keys in the drieved class
			newNode->DataKeys[0].insert(value);	
			nodeName+="L";	// indication in file system that its a leaf node
			newNode->Name=nodeName;
			newNode->numKeys++;
		}
		else
		{
			if(root->numKeys==divide)	
			{
				NodeNumber++;
				InternalNode* newNode=new InternalNode(TreeDegree);	// newNode will only have keys
				newNode->Children[0]=root->Name;		// it's Child be root
				nodeName+="N";	// indication in file system that its a internal node
				newNode->Name=nodeName;
				if(root->isleafNode())
					splitLeaf(newNode, root, 0,value);	// if root == leaf split == 1 internal 2 leaf 
				else
					splitNonLeaf(newNode, root, 0,value);	// if root == nonleaf== 3 internalnodes	
				int Index = 0;
				Key<T> obj;
				obj.ID_ELEMENT=newNode->pointerKeys[0];
				if (obj < value)
						Index++;
				BPlusNode *tempNode = createNode(newNode->Children[Index]);
				insert(tempNode, value);
				delete tempNode;
				delete root;
				root = newNode;
			}
			else
			{
				insert(root,value);
			}
		}
	}
	void BuildTree(string Path,string IDON)
	{
		cout << Path << endl;
		ifstream inFile;
		inFile.open(Path);
		if (inFile.is_open())
		{
			string Line;
			Key<T> obj;
			obj.path_Directory = Path;
			getline(inFile, Line, '\n');
			int idPoint = 0;
			size_t current_pos = 0;
			bool found=false;
			while (Line != "")
			{
				current_pos = Line.find(",");
				if (current_pos == string::npos)
				{
					Fields.insert(Line);
					if (IDON == Line.substr(0, current_pos))
						found=true;
					Line.erase(0, Line.length());
				}
				else
				{
					if (IDON == Line.substr(0, current_pos))
						found=true;
					Fields.insert(Line.substr(0,current_pos));
					Line.erase(0, current_pos + 1);
				}
				if(found==false)
					idPoint++;
			}
			int linecount = 1, count=0,i=0;
			while (getline(inFile, Line, '\n') )//&& i<=72 )
			{
				count = 0;
				while (Line!="")
				{
					current_pos = Line.find(",");
					if (current_pos == string::npos)
					{
						if (count == idPoint)
						{
							obj.ID_ELEMENT = Line.substr(0, current_pos);
							break;
						}
						Line.erase(0, Line.length());
					}
					else
					{
						if (count == idPoint)
						{
							obj.ID_ELEMENT = Line.substr(0, current_pos);
							break;
						}
						Line.erase(0, current_pos + 1);
						if (Line[0] == '\"')
						{
							current_pos = Line.find("\",");
							Line.erase(0, current_pos + 2);
							count++;
						}
					}
					count++;
				}
				current_pos=obj.ID_ELEMENT.find(",");
				if (current_pos != string::npos)
				{
					obj.ID_ELEMENT = obj.ID_ELEMENT.substr(0, current_pos);
				}
				obj.linePointer = linecount;
				linecount++;
				insertNode(obj,IDON);
				//i++;
				
			}
		}
		else
		{
			cout << "ERROR.GIVEN PATH NOT FOUND." << endl;
		}
		WriteRoot(FolderID);
	}
	void searchKey(string value,string value2,string field="",string condition="")
	{
		if(root==NULL)
		{
			cout<<"No values Inserted Yet."<<endl;
			return;
		}
		else
		{
			Key<T> obj;
			obj.ID_ELEMENT=value;
			Key<T> obj2;
			obj2.ID_ELEMENT=value2;
			if(condition=="")
			{
				if(obj2>obj)
					search(root,obj,obj2);
				else
					search(root,obj2,obj);
			}
			else
			{
				int HaHA=Fields.Find(field);
				if(HaHA==0)
				{
					cout<<"Field given Doesn't Exist."<<endl;
					return ;
				}
				if(obj2>obj)
					search(root,obj,obj2,0,HaHA,condition);
				else
					search(root,obj2,obj,0,HaHA,condition);
			}
		}
	}
	void UpdateKey(string value,string value2,string field,string oldValue,string newValue)
	{
		if(root==NULL)
		{
			cout<<"No values Inserted Yet."<<endl;
			return;
		}
		else
		{
			Key<T> obj;
			obj.ID_ELEMENT=value;
			Key<T> obj2;
			obj2.ID_ELEMENT=value2;
			int HaHA=Fields.Find(field);
			if(HaHA==0)
			{
				cout<<"Field given Doesn't Exist."<<endl;
				return ;
			}
			if(obj2>obj)
					search(root,obj,obj2,1,HaHA,newValue,oldValue);
				else
					search(root,obj2,obj,1,HaHA,newValue,oldValue);

		}
	}
	void readRoot(string Path,string FolderID)
	{
		string Line;
		Key<T> obj;
		ifstream inFile;
		obj.path_Directory ="../Resources/OriginalFiles/NCHS_-_Leading_Causes_of_Death__United_States_1.csv";
		getline(inFile, Line, '\n');
		size_t current_pos = 0;
		while (Line != "")
		{
			current_pos = Line.find(",");
			if (current_pos == string::npos)
			{
				Fields.insert(Line);
				Line.erase(0, Line.length());
			}
			else
			{
				Fields.insert(Line.substr(0,current_pos));
				Line.erase(0, current_pos + 1);
			}
		}
		this->FolderID=FolderID;
		root=createNode(Path);
	}
	//virtual ~BPlusTree();
};

