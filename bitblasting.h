/*++
Copyright (c) 2016

Module Name:

main.cpp

Abstract:

bit-blasting

Author:

Wu Jun & Zhang Yongfei 2016-01-29

Notes:

--*/

#pragma once

#ifndef _BIT_BLASTING_H
#define _BIT_BLASTING_H

#include<iostream>
#include<string>
#include<stack>
#include<vector>
#include<fstream>
#include<queue>
#include<list>
#include<map>
#include<stdlib.h>
#include<sstream>

using namespace std;

class Node {
public:
	int oprtype;
	int index;
	Node *left;
	Node *right;
	Node() :oprtype(0), index(0), left(NULL), right(NULL) {}
	Node(int opr, int index) :oprtype(opr), index(index), left(NULL), right(NULL) {}
};


vector<string> bvdata;
vector<string> opr;
vector<vector<string> > data1;
vector<vector<string> > opr1;
vector<Node*> rootvector;
vector<bool> constant;
vector<Node*> childtree;

int bitnum;
int var_num = 0, bvar_num = 0; //新生成变量计数

string get_substr(string s, int &ptr);
void generTree(string expr, Node*& p);
void postOrderTraverse(Node *p, int post);
vector<string> sourcelist();
void breadthFirstSearch(Node* root);
string tostring(char* s);
void createAddTree(Node* p, int index, int pos);
Node* bvAdd(Node* root, int pos);
void findAOpr(Node* root, int pos);

#endif // !_BIT_BLASTING_H

