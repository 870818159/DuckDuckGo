/**
 * @author Philip Zhang
 * @created on 08/11/2018
 */

//include all the c++ header source.
#include <bits/stdc++.h>

#include "FibonacciHeap.h"
 
using namespace std;

/**
 * Create relationship between keywords and the addresses of the node in Fibonacci heap by using hashtable.
 * @param	string buffer					format of the buffer is "keyword frequency".
 * @param	map<string, FibNode*> &table	hashtable used to store keywords and addresses of the node.
 * @param	FibHeap &fibHeap				class of Fibonacci Heap including the basic operation such as insert, removeMax, etc. of Fibonacci heap.
 * @return	void.
 */
void StoreInfo(string buffer, map<string, FibNode*> &table, FibHeap &fibHeap) {
	istringstream sin(buffer);
	string temp = "";
	string key = "";
	
	int i = 0;
	int freq = 0;
	
	while (sin >> temp) {
		if (i == 0)
			key = temp.substr(1);
		else
			freq = stoi(temp);
		++i;
	}
	
	if (table[key] == nullptr)
		table[key] = fibHeap.insert(key, freq);
	else
		fibHeap.update(table, key, freq);
	return;
}

/**
 * Write the most frequent n keywords into the outputfile.txt.
 * @param	string output_file					txt file used to store the most frequent n keywords.
 * @param	vector<pair<string, int>> temp		vector used to store keywords and frequency so that they can be written into the outputfile.txt.
 * @return	void.
 */
void WriteOutputFile(string output_file, vector<pair<string, int>> temp) {
	string data = "";
	ofstream out(output_file.c_str(), ios::out | ios::app);
	
	for (int i = 0; i < temp.size(); ++i) {
		data = data + temp[i].first + ",";
	}
	
	data.pop_back();
	out << data << endl;
	cout << "Data has been successfully written into output_file.txt!" << endl;
	out.close();
	return;
}

/**
 * Get the most frequent n keywords and write into the outputfile.
 * @param	map<string, FibNode*> &table	hashtable used to store keywords and addresses of the node.
 * @param	FibHeap &fibHeap				class of Fibonacci Heap including the basic operation such as insert, removeMax, etc. of Fibonacci heap.
 * @param	int query						the number of the most frequent keywords to get.
 * @return	void.
 */
void GetFrequentKeyword(map<string, FibNode*> &table, FibHeap &fibHeap, int query) {
	vector<pair<string, int>> temp;
	FibNode* ptr = nullptr;
	
	for (int i = 0; i < query; ++i) {
		ptr = fibHeap.removeMax();
		cout << ptr->key << "  " << ptr->freq << endl;
		temp.push_back(make_pair(ptr->key, ptr->freq));
	}
	
	for (int i = 0; i < query; ++i) {
		string key = temp[i].first;
		int freq = temp[i].second;
		table[key] = fibHeap.insert(key, freq);
	}
	
	string output_file = "output_file.txt";
	WriteOutputFile(output_file, temp);
	
	return;
}

/**
 * Read the inputfile and the answer will be put in the outputfile.
 * @param	string input_file	txt file used to get the frequency number of keywords.
 * @return	void.
 */
void Start(string input_file) {
	ifstream in(input_file.c_str(), ios::in);
	string buffer;
	
	if (!in.is_open()) {
		cout << "Open error!" << endl;
		exit(1);
	}
	
	map<string, FibNode*> table;
	FibHeap fibHeap;
	
	while(getline(in, buffer)) {
		if (buffer[0] == 's' || buffer[0] == 'S') {
			cout << "Program end!" << endl;
			return;
		}
		
		else if (buffer[0] >= '0' && buffer[0] <= '9'){
			int query = stoi(buffer);
			if (query > table.size()) {
				cout << "Query should be no more than keywords number!" << endl;
				return;
			}
			GetFrequentKeyword(table, fibHeap, query);
		}
		
		else {
			StoreInfo(buffer, table, fibHeap);
		}
	}
	
	in.close();
	return;
}

/**
 * Start by typing ./keywordcounter input_file.txt on linux environment.
 */
int main(int argc, char** argv) 
{
	if (argc == 2)
		Start(argv[1]);
	else
		cout << "Parameter error!" << endl;
	return 0;
}
