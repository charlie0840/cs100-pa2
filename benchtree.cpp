/******************************************************************************
 								Yiming Yu
								cs100feu

								Xiaoju Guo
								xig061
				
								CSE100 FA2015
				Assignemnt 2
File Name:	benchtree.cpp
Description:  	permits benchmarking the performance of a RST implementation, 
		an ordinary BST implementation, and the C++ STL std::set 
		structure (red-black tree).
******************************************************************************/
#include "RST.hpp"
#include "countint.hpp"
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <random>
#include <iomanip>
#include <algorithm>
#include <ctime>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

int main(int argc, char** argv) {
	if(argc!=5)
	{
		cout<<"wrong number of arguments!"<<endl;
		return 0;
	}
	

	//seed according to time
	srand(static_cast<unsigned int>(time(NULL)));
	//get four arguments from command line
	string kind = argv[1];
	string order = argv[2];
	string SIZE = argv[3];
	string NUM = argv[4];
	//change them from string to int
	int size = atoi(SIZE.c_str());
	int numofRun = atoi(NUM.c_str());
	int N;
	int power;
	string STR_RST = "rst";
	string STR_BST = "bst";
	string SET = "set";
	string ORDER = "sorted";
	string SHUFFLE = "shuffled";
	if(order != ORDER && order != SHUFFLE)
	{
		cout<<"wrong second argument!"<<endl;
		return 0;
	}	
	if(kind !=  STR_RST && kind != SET && kind != STR_BST)
	{
		cout<<"wrong first argument!"<<endl;
		return 0;
	}	
	cout<<
	"# Benchmarking average number of comparisons for successful find"
		<<endl;
	cout<<"# Data structure: "<<kind<<endl;
	cout<<"# Data: "<<order<<endl;
	cout<<"# N is powers of 2, minus 1, from 1 to "<<size<<endl;
	cout<<"# Averaging over "<<numofRun<<" runs for each N"<<endl;
	cout<<"#"<<endl;
	cout<<"# N"<<setw(15)<<"avgcomps"<<setw(15)<<"stdev"<<endl;

	//loop, N is power of 2 minus 1, from first one to last one in range
	for(N = 1, power = 1;N < size;N = pow(2,power+1)-1,++power)
	{
	    double avgComp = 0;
	    double avgSqrComp = 0; 
	    double getCount = 0;
	    double avgcomps = 0;
	    double sqrcomps = 0;
	    //loop number according to user input( number of runs )
	    for(int counter = 1; counter <= numofRun; counter++)
	    {
		vector<countint> v;
		v.clear();
		for(int i=0;i<N;++i)
		{
			v.push_back(i);
		}
	
		//if shuffled, randomize the elements
		if(order == SHUFFLE)
		{
			random_shuffle(v.begin(),v.end());
		}
		std::vector<countint>::iterator vit = v.begin();
		std::vector<countint>::iterator ven = v.end();
		//get the kind of implementatino.	
		if(kind == STR_RST)
		{
			RST<countint> r;
			//insert
			for(vit = v.begin(); vit != ven; ++vit)
			{
				r.insert(*vit);
			}

			//reset the count
			countint::clearcount();

			//find every element in the tree
			for(vit = v.begin(); vit != ven; ++vit)
			{
				r.find(*vit);
			}
		}
		
		else if(kind == STR_BST)
		{
			BST<countint> b;
			for(vit = v.begin(); vit != ven; ++vit)
			{
				b.insert(*vit);
			}
			countint::clearcount();
			for(vit = v.begin(); vit != ven; ++vit)
			{
				b.find(*vit);
			}
		}

		else if(kind == SET)
		{
			set<countint> s;
			for(vit = v.begin(); vit != ven; ++vit)
			{
				s.insert(*vit);
			}
			countint::clearcount();
			for(vit = v.begin(); vit != ven; ++vit)
			{
				s.find(*vit);
			}
			s.clear();			
		}
		
		getCount = countint::getcount();
		avgcomps = getCount/(double)N;
		sqrcomps = pow(avgcomps,2);
		avgComp += avgcomps;		
		avgSqrComp += sqrcomps;    
	    }
		avgSqrComp /= (double)numofRun;
		avgComp /= (double)numofRun;
		double variation = avgSqrComp - pow(avgComp,2); 
		double stdev = sqrt(abs(variation));
		cout<<setw(5)<<N<<setw(15)<<avgcomps<<setw(15)<<stdev<<endl;
	}
    return 0;
}

