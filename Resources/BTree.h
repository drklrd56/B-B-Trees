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
class BTree
{
	class BTreeNode
	{
	public:
		string Name;
		List<Key<T>> *keys;
		string *Children;
		int max_Capacity;
		int min_Capacity;
		int numKeys;
		bool isleaf;
		BTreeNode(int Degree,string Name)
		{
			this->Name = Name;
			isleaf = true;
			max_Capacity = 2 * ((Degree / 2) + 1) - 1;	// 2t+1 change it later ;comment
			min_Capacity = (Degree / 2 + 1) - 1;	// t-1
			numKeys = 0;
			Children = new string[max_Capacity + 1];
			keys = new List<Key<T>>[Degree];
		}
		void DiskWrite(string FolderName)
		{
			ofstream OutFile;
			string fileName ="../Resources/NodesBTree/"+FolderName+"/"+ Name+".txt";
			OutFile.open(fileName);
			if (OutFile.is_open())
			{
				// open a file in the folder to know about structuring
				OutFile << Name << endl;	
				Key<T> head;
				int index = 0;
				OutFile << isleaf << endl;
				OutFile << numKeys << endl;
				// write keys
				OutFile << "Keys : " << endl;
				while (index < numKeys)
				{
					for(List<Key<T>>::iterator Index=keys[index].begin(); Index.iterate();Index++)
					{
						head=*Index;
						OutFile <<index<<"|"<<head.ID_ELEMENT << "|" << head.path_Directory <<"|"<< head.linePointer;
						OutFile << '\n';
					}
					index++;
				}
				index = 0;
				// write Chidren
				OutFile << "Children : " << endl;
				while (index < numKeys+1)
				{
					if (Children[index] != "")
					{
						OutFile << Children[index];
						if (index  < numKeys)
							OutFile << ',';
					}
					index++;
				}
				OutFile <<endl<< "END";
				OutFile.close();
			}
			else
				cout << "ERROR.. Directory inaccessable." << endl;
		}
		void DiskRead(string Name)
		{
			ifstream inFile;
			inFile.open(Name);
			if (inFile.is_open())
			{

				string Line, ID;
				getline(inFile, Line, '\n');	// file Name
				this->Name = Line;
				getline(inFile, Line, '\n');	// isLeaf
				isleaf = stoi(Line);	
				getline(inFile, Line, '\n');	// numKeys
				numKeys = stoi(Line);
				getline(inFile, Line, '\n');	// Keys :
				int index = 0;
				int current_pos = 0;
				int spaceCount = 0;
				Key<T>obj;
				while (Line != "Children : ")	
				{
					getline(inFile, Line, '\n');	// a Keys of type index|ID|Path|Line
					if (Line == "Children : ")
						break;
					spaceCount = 0;
					index = -1;
					while (Line!="")
					{
						current_pos = Line.find("|");	// find line |
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
						keys[index].insert(obj);
				}
				getline(inFile, Line, '\n');
				index = 0;
				// read the children
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
		~BTreeNode()
		{
			for (int Index = 0; Index < numKeys; Index++)	// free list memory
				keys[Index].makeNull();
			delete[] keys;	// delete keys
			delete[] Children;	// delete Children
		}
	};
	BTreeNode *root;
	int TreeDegree;	
	int median;
	int nodeNumber;
	string IDFolder;
	List<string> Fields;
	BTreeNode* createNode(string Path)	// open the file path create a new Node return
	{
		BTreeNode* newNode = new BTreeNode(TreeDegree, Path);	
		Path += ".txt";
		newNode->DiskRead("../Resources/NodesBTree/"+ IDFolder+"/"+Path);
		return newNode;
	}
	void WriteRoot(BTreeNode *root, string folderName)	// tell about the node that is root its use in case the new degree is same as the previous
	{
		ofstream inFile;
		stringstream name;
		name<<"../Resources/NodesBTree/"<<folderName<<"/"<<TreeDegree<< "root.txt";
		inFile.open(name.str());	// File PATH
		if (inFile.is_open())
		{
			inFile << root->Name << "," << TreeDegree;	
			inFile.close();
		}
		else
			cout << "ROOT NOT WRITTEN." << endl;
	}
	void insert(BTreeNode* tree, Key<T>& insertValue)		// search check split in children insert at leaf or at index where key found(list)
	{
		if (tree->isleaf)		// insert in case leaf
		{
			int insertIndex = tree->numKeys - 1;
			bool equal=false;
			while (insertIndex >= 0) // find index where element can to inserted if it's equal to another array member
			{
				if (tree->keys[insertIndex] == insertValue)
				{
					tree->keys[insertIndex].insert(insertValue);
					equal = true;
					break;
				}
				insertIndex--;
			}
			if (equal == false)
			{
				insertIndex = tree->numKeys - 1;
				while (insertIndex >= 0 && tree->keys[insertIndex] > insertValue) // shift elements to make space for new element
				{
					tree->keys[insertIndex + 1] = tree->keys[insertIndex];
					insertIndex--;
				}
				tree->keys[insertIndex + 1].makeNull();
				tree->keys[insertIndex + 1].insert(insertValue);  //insert Element
				tree->numKeys++;
			}
			tree->DiskWrite(IDFolder);
		}
		else
		{    // if not leaf check in children find the apropriate position and recusive call
			int insertPoint = tree->numKeys - 1;
			while (insertPoint >= 0 && tree->keys[insertPoint] > insertValue)
			{
				if (tree->keys[insertPoint] == insertValue)	// if non leaf node == value insert in the list at this index of keys
				{
					tree->keys[insertPoint].insert(insertValue);	
					tree->DiskWrite(IDFolder);	// write the node to drive
					return;
				}
				insertPoint--;
			}
			// even and odd case
			int divide;
			if (TreeDegree % 2 == 0)	
				divide = 2 * median;
			else
				divide = 2 * median - 1;
			BTreeNode *newNode = createNode(tree->Children[insertPoint + 1]);	// read from disk at load children to memory
			if (newNode->numKeys == divide)	// full node === preActive split
			{
				// If the child is full, then split  
				split(tree, newNode, insertPoint + 1);	// split it
				if(!(tree->keys[insertPoint+1]==insertValue))
				{
					if(tree->keys[insertPoint+1]<insertValue)
						insertPoint++;
					newNode= createNode(tree->Children[insertPoint + 1]);
				}
			}
			insert(newNode, insertValue);	// recursive call
			delete newNode;	// free memory by remove all children
		}
	}
	void split(BTreeNode *parent, BTreeNode *child, int Index)
	{
		stringstream name;
		name<<TreeDegree<<"Node"<<nodeNumber;
		string nodeName=name.str();
		nodeNumber++;
		BTreeNode* newBTreeNode = new BTreeNode(TreeDegree,nodeName); // Create a tempBTreeNode
		newBTreeNode->isleaf = child->isleaf;
		newBTreeNode->numKeys = child->min_Capacity;
		int index = 0;
		int loopInVariant;
		if (TreeDegree % 2 == 0)
			loopInVariant = median;
		else
			loopInVariant = median-1;
		for (; index < loopInVariant; index++)
		{
			newBTreeNode->keys[index] = child->keys[index + median]; // copy the keys from or after the median to newNode (Even AND ODD case)
		}
		if (child->isleaf == false)
		{
			if (TreeDegree % 2 == 0)
				loopInVariant = median + 1;
			else
				loopInVariant = median;
			for (index = 0; index < loopInVariant; index++)
			{
				newBTreeNode->Children[index] = child->Children[index + median];	// copy the Children from or after the median to newNode (Even AND ODD case)
			}
		}
		child->numKeys = median - 1;	// if degree 3 median-1= 1  if child key == 1 2 3 after this its only 1
		for (index = parent->numKeys; index >= Index + 1; index--)
		{
			parent->Children[index + 1] = parent->Children[index];	//shift to make space for newChild
		}
		parent->Children[Index + 1] = newBTreeNode->Name;	// and the newNode to parent Children Child is already a child before coming in the function
		// Index == child and Index+1 == newNode 
		for (index = parent->numKeys - 1; index >= Index; index--)
		{
			parent->keys[index + 1] = parent->keys[index];	// shift the parent to make space for the key
		}
		// the median value goes to parent example child with 1 2 3 .. 2 moves to parent
		parent->keys[Index] = child->keys[median - 1];
		parent->numKeys += 1;	
		// Write PARENT<CHILDREN<NEWNODE to file
		child->DiskWrite(IDFolder);
		parent->DiskWrite(IDFolder);
		newBTreeNode->DiskWrite(IDFolder);
		delete newBTreeNode;
	}
	void inorder(BTreeNode* tree)
	{
		if (tree->isleaf)
		{
			for (int i = 0; i < tree->numKeys; i++)
			{
				tree->keys[i].DisplayList();
			}
		}
		else
		{
			for (int i = 0; i < tree->numKeys+1; i++)
			{
				inorder(tree->Children[i]);
				if (i < tree->numKeys)
					tree->keys[i].DisplayList();
			}
		}
	}
	void Display(List<Key<T>>& value,string condition="",int fieldNumber=0)
	{
		ifstream inFile;
		static const int max_line = 65536;
		string Line;
		Key<T> actualVal;
		cout<<"KEY FOUND AT : "<<endl<<endl;
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
			if(condition=="" && fieldNumber==0)
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
	bool find(string Line,int fieldNumber,string condition)
	{
		size_t current_pos = 0;
		string temp;
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
					temp=Line.substr(0, current_pos);
					if(condition == temp)
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
	bool findField(string Line, string condition)
	{
		size_t current_pos = 0;
		while (Line!="")
		{
			current_pos = Line.find(",");
			if (current_pos == string::npos)
			{
				
				if(Line==condition)
					return true;
				else
					return false;
				Line.erase(0, Line.length());
			}
			else
			{
				if(condition == Line.substr(0, current_pos))
					return true;
				Line.erase(0, current_pos + 1);
				if (Line[0] == '\"')
				{
					current_pos = Line.find("\",");
					Line.erase(0, current_pos + 2);
				}
			}
		}
		return false;
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
			while(Index_Main<file.length())
			{
				Line+=file[Index_Main];
				Index_Main++;
			}
			file=Line;
		}
		return returnCondition;
	}
	void search(BTreeNode *tree,Key<T> searchValue,string newValue="",string oldValue="",int fieldNumber=0,bool DisplayORUpdate=0)
	{
		int Index=0;
		for(;Index<tree->numKeys &&   tree->keys[Index] < searchValue && !(tree->keys[Index] == searchValue);)
		{
			Index++;
		}
		if(tree->numKeys>Index && tree->keys[Index]==searchValue)
		{
			if(DisplayORUpdate==false)
			{
				if(newValue=="")
					Display(tree->keys[Index]);
				else
					Display(tree->keys[Index],newValue,fieldNumber);
			}
			else 
				Update(tree->keys[Index],fieldNumber,newValue,oldValue);
		}
		else
		{
			if(tree->isleaf)
			{
				cout<<"No Path Found."<<endl;
				return ;
			}
			else
			{
				BTreeNode *newNode;
				newNode= createNode(tree->Children[Index]);
				search(newNode,searchValue,newValue,oldValue,fieldNumber,DisplayORUpdate);
				delete newNode;
			}
		}
	}
public:
	BTree(int Degree = 3)
	{
		if (Degree < 3)
			cout << "ERROR. Degree Not Valid" << endl;
		else
		{
			TreeDegree = Degree;
			if (Degree % 2 != 0)
				median = (Degree / 2) + 1;
			else
				median = (Degree / 2);
			root = NULL;
			nodeNumber = 1;
		}
	}
	void insertNode(Key<T> value,string ID)
	{
		if(IDFolder=="")
			IDFolder = "BIN"+ID;
		int divide;
		if (TreeDegree % 2 == 0)
			divide = 2 * median;
		else
			divide = 2 * median - 1;
		stringstream name;
		name<<TreeDegree<<"Node"<<nodeNumber;
		string nodeName=name.str();
		if (root == NULL)
		{
			root = new BTreeNode(TreeDegree,nodeName);
			nodeNumber++;
			//root->numKeys = 0;
			root->isleaf = true;
			root->keys[0].insert(value);
			root->numKeys = 1;
			root->DiskWrite(IDFolder);
		}
		else
		{
			if (root->numKeys >=divide)
			{
				//string nodeName = "Node" + to_string(nodeNumber);
				nodeNumber++;
				BTreeNode* newBTreeNode = new BTreeNode(TreeDegree,nodeName);
				newBTreeNode->Children[0] = root->Name;
				newBTreeNode->isleaf = false;
				split(newBTreeNode, root, 0);
				int Index = 0;
				if(!(newBTreeNode->keys[0]==value))
					if (newBTreeNode->keys[0] < value)
						Index++;
				BTreeNode *newNode = createNode(newBTreeNode->Children[Index]);
				insert(newNode, value);
				delete newNode;
				delete root;
				root = newBTreeNode;

			}
			else
				insert(root, value);
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
			bool insertFields=false;
			if(Fields.isEmpty())
				insertFields=true;
			bool found=false;
			while (Line != "")
			{
				current_pos = Line.find(",");
				if (current_pos == string::npos)
				{
					if(insertFields)
						Fields.insert(Line);
					if (IDON == Line.substr(0, current_pos))
						found=true;
					Line.erase(0, Line.length());
				}
				else
				{
					if (IDON == Line.substr(0, current_pos))
						found=true;
					if(insertFields)
						Fields.insert(Line.substr(0,current_pos));
					Line.erase(0, current_pos + 1);
				}
				if(found==false)
					idPoint++;
			}
			int linecount = 1, count = 0;
			while (getline(inFile, Line, '\n'))
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
		WriteRoot(root, IDFolder);
	}
	void searchKey(string value,string field="",string condition="")
	{
		if(root==NULL)
		{
			cout<<"No values Inserted Yet."<<endl;
			return;
		}
		else if(value=="")
		{
			cout<<"Passed value is Empty."<<endl;
			return ;
		}
		else
		{
			Key<T> obj;
			obj.ID_ELEMENT=value;
			if(condition!="")
			{
				int haha=Fields.Find(field);
				if(haha==0)
				{
					cout<<"InValid Field. "<<endl;
					return;
				}
				else
					search(root,obj,condition,"",haha);
			}
			else
				search(root,obj);
		}
	}
	void UpdateKey(string ID,string field,string oldValue,string newValue)
	{
		if(root==NULL)
		{
			cout<<"No values Inserted Yet."<<endl;
			return;
		}
		else if(ID=="" || field=="" || oldValue=="" ||  newValue=="")
		{
			cout<<"Passed value is Empty."<<endl;
			return ;
		}
		else
		{
			Key<T> obj;
			obj.ID_ELEMENT=ID;
			int HaHA=Fields.Find(field);
			if(HaHA==0)
			{
				cout<<"Field given Doesn't Exist."<<endl;
				return ;
			}
			search(root,obj,newValue,oldValue,HaHA,1);
		}
	}
	void Display()
	{
		inorder(root);
	}
	void readRoot(string Path,string FolderID)
	{
		string Line;
		this->IDFolder=FolderID;
		root=createNode(Path);
		Key<T> obj;
		ifstream inFile;
		obj.path_Directory = "../Resources/OriginalFiles/NCHS_-_Leading_Causes_of_Death__United_States_1.csv";
		inFile.open(obj.path_Directory);
		getline(inFile, Line, '\n');
		size_t current_pos = 0;
		bool found=false;
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
	}
	virtual ~BTree()
	{
		delete root;
	}
};
