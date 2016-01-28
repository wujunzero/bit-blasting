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
#include"bitblasting.h"

/**
 * [get_substr description]
 * @param  s   [description]
 * @param  ptr [description]
 * @return     [description]
 */
string get_substr(string s, int &ptr) {
	string str = "";
	int len = s.length();
	while (ptr < len && s[ptr] == ' ')
		ptr++;
	if (s[ptr] == '(') {
		ptr++;
	}
	else if (s[ptr] == ')') {
		ptr++;
		return ")";
	}
	else {
		while (ptr < len && s[ptr] != ' ' && s[ptr] != '(' && s[ptr] != ')') {
			str += s[ptr];
			ptr++;
		}

		if (str == "assert") {
			ptr++;
			return str = "";
		}
	}
	return str;
}

/**
 * [generTree description]
 * @param expr [description]
 * @param p    [description]
 */
void generTree(string expr, Node*& p) {
	string line = expr;
	string str = "", tmp_str;
	stack<string> oprstack;
	stack<Node*> datastack;
    int ptr = 0;
	int i = 0, j = 0;
	while (ptr < line.length()) {
		str = get_substr(line, ptr);
		if (str != " "&&str != "") {
			if (str == "=") {
				oprstack.push(str);
			}
			else if (str == "bvadd") {
				oprstack.push(str);
			}
			else if (str == "bvand") {
				oprstack.push(str);
			}
			else if (str == "bvmul") {
				oprstack.push(str);
			}
			else if (str == "bvdiv") {
				oprstack.push(str);
			}
			else if (str == "bvor") {
				oprstack.push(str);
			}
			else if (str == "bvxor") {
				oprstack.push(str);
			}
			else if (str == "bvnot") {
				oprstack.push(str);
			}
			else if (str == "bvshr") {
				oprstack.push(str);
			}
			else if (str == "bvshl") {
				oprstack.push(str);
			}
			else if (str == "bvlshr") {
				oprstack.push(str);
			}
			else if (str == "bvneg") {
				oprstack.push(str);
			}
			else if (str == "bvurem") {
				oprstack.push(str);
			}
			else if (str == "bvult") {
				oprstack.push(str);
			}
			else if (str == "distinct") {
				oprstack.push(str);
			}
			else if (str == ")"&&oprstack.size()) {
				tmp_str = oprstack.top();
				oprstack.pop();
				opr.push_back(tmp_str);
				p = new Node(0, j);
				if (tmp_str == "bvnot") {
					if (datastack.size()) {
						p->right = datastack.top();
						datastack.pop();
					}
				}
				else {
					if (datastack.size()) {
						p->right = datastack.top();
						datastack.pop();
					}
					if (datastack.size()) {
						p->left = datastack.top();
						datastack.pop();
					}
				}
				j++;
				datastack.push(p);
			}
			else {
				if (str != ")") {
					bvdata.push_back(str);
					p = new Node(1, i);
					datastack.push(p);
					i++;
				}
			}
		}
	}
	p = datastack.top();
	datastack.pop();
}

/**
 * [postOrderTraverse description]
 * @param p    [description]
 * @param post [description]
 */
void postOrderTraverse(Node *p, int post) {
	if (p != NULL) {
		postOrderTraverse(p->left, post);
		postOrderTraverse(p->right, post);
		if (p->oprtype) {
			cout << '(' << p->oprtype << ',' << data1[post][p->index] << ')' << ' ';
			//cout<<'('<<p->oprtype<<','<<p->index<<')'<<' ';
		}
		else {
			cout << '(' << p->oprtype << ',' << opr1[post][p->index] << ')' << ' ';
			//cout<<'('<<p->oprtype<<','<<p->index<<')'<<' ';
		}
	}
}

/**
 *  [sourcelist description]
 *  @return [description]
 */
vector<string> sourcelist() {
	fstream fin("test.smt2");
	string line, str = "", str0;
	vector<string> sList;
	int ptr = 0;
	bool flag = 1;
	while (getline(fin, line)) {
		if (line.length()>0) {
			for (int i = 1;i<7;i++) {
				str += line[i];
			}
			if (str == "declar" & flag) {
				while (ptr<line.length()) {
					str0 = get_substr(line, ptr);
					if (isdigit(str0[0])) {
						bitnum = atoi(str0.c_str());
						break;
					}
				}
				flag = 0;
			}
			if (str == "assert") {
				sList.push_back(line);
			}
			str = "";
		}
	}
	return sList;
}

/**
 * [breadthFirstSearch description]
 * @param root [description]
 */
void breadthFirstSearch(Node* root) {
	queue<Node *> nodeQueue;
	nodeQueue.push(root);
	Node *node;
	while (!nodeQueue.empty()) {
		node = nodeQueue.front();
		nodeQueue.pop();
		//cout<<"("<<node->oprtype<<","<<node->index<<")";
		if (node->oprtype) {
			cout << '(' << node->oprtype << ',' << bvdata[node->index] << ')' << ' ';
		}
		else {
			cout << '(' << node->oprtype << ',' << opr[node->index] << ')' << ' ';
		}
		if (node->left) {
			nodeQueue.push(node->left);  //ÏÈ½«×ó×ÓÊ÷Èë¶Ó
		}
		if (node->right) {
			nodeQueue.push(node->right);  //ÔÙ½«ÓÒ×ÓÊ÷Èë¶Ó
		}
		//cout<<endl;
	}
}

/**
 * [tostring description]
 * @param  s [description]
 * @return   [description]
 */
string tostring(char* s) {
	string var = s;
	stringstream ss;
	ss << var_num;
	//string x = ss.str();
	var += ss.str();
	var_num++;
	return var;
}

/**
 * [createAddTree description]
 * @param p     [description]
 * @param index [description]
 * @param pos   [description]
 */
void createAddTree(Node* p, int index, int pos) {
	//Node* bp = p; //获取左右操作数

	for (int i = 0; i < bitnum; i++) {

		string a = tostring("a");
		data1[pos].push_back(a);
	}
	for (int i = 0; i < bitnum; i++) {

		string b = tostring("b");
		data1[pos].push_back(b);
	}for (int i = 0; i < bitnum; i++) {

		string c = tostring("c");
		data1[pos].push_back(c);
	}for (int i = 0; i < bitnum; i++) {

		string m = tostring("m");
		data1[pos].push_back(m);
	}
	constant.push_back(0);
	cout<<index<<endl;

	for (int i = 0; i < bitnum; i++) {
		//建树

		//m0
		
		int constant_index = constant.size()-1;

		Node* bp,*bl,*br,*head;
		opr1[pos].push_back("=");
		bp = new Node(0,opr1[pos].size());
		//data1[pos].push_back();
		bl = new Node(1,index+3*bitnum);
		br = new Node(1,constant_index);
		bp->left = bl;
		bp->right = br;
		head = bp;
		//cout << pos << endl;

		while (head!=NULL){
			cout << head->oprtype << ',' << head->index << ' ';
			cout << bl->oprtype << ',' << bl->index << ' ';
			cout << br->oprtype << ',' << br->index << ' ';
			head = NULL;
		}
		cout << endl;
		//bp->index = index;
		//bp->oprtype = 0;
	}


}

/**
 * [bvAdd description]
 * @param  root [description]
 * @param  pos  [description]
 * @return      [description]
 */
Node* bvAdd(Node* root, int pos) { 
	Node* p = root;
	//string strL, strR;
	//strL = data1[pos][p->left->index];
	//strR = data1[pos][p->right->index];

	string pNode = tostring("v");
	data1[pos].push_back(pNode);
	int index = data1[pos].size();

	createAddTree(p, index, pos);

	p->oprtype = 1;
	p->index = index-1;
	p->left = NULL;
	p-> right = NULL;


	return p;
}

/**
 * [findAOpr description]
 * @param root [description]
 * @param pos  [description]
 */
void findAOpr(Node* root, int pos) {
	Node* p = root;
	Node* proot;
	int n = root->index;
	while (p != NULL) {
		if (p->left->oprtype == 0 && p->left->left != NULL) {
			proot = p;
			p = p->left;
		}
		else if (p->right->oprtype == 0 && p->right->left != NULL) {
			proot = p;
			p = p->right;
		}
		else {
			if (opr1[pos][p->index] == "bvadd") {
				bvAdd(p, pos);
			}

			return;//
		}
	}
}

/**
 * [main description]
 * @return [description]
 */
int main()
{
	Node* p;
	vector<string> sourceList = sourcelist();
	int i = sourceList.size();

	for (i = 0;i<sourceList.size();++i) {
		generTree(sourceList[i], p);
		rootvector.push_back(p);
		data1.push_back(bvdata);
		opr1.push_back(opr);
		p = NULL;
		bvdata.clear();
		opr.clear();
	}
	for (int i = 0;i<rootvector.size();++i) {
		//postOrderTraverse(rootvector[174],174);

		findAOpr(rootvector[i],i);
		//cout << endl;
		//cout<<endl;
	}
	system("pause");
	return 0;
}
