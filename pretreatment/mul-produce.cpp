#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int users = 5551;
int items = 16980;
int vocabsize = 8000;

int main(){
	// read vocabulary
	ifstream vocab("vocab.txt");
	vector<string> dict;
	string temp;
	while(!vocab.eof()){
		vocab >> temp;
		dict.push_back(temp); 
	}
	vocab.close();

	ifstream infile("ready-data.txt");
	if(!infile){
		cout << "can't open file" << endl;
		return 0;
	}
	int index;
	string str;
	ofstream mult("mult.txt");
	while(!infile.eof()){
		infile >> index;
		vector<string> item_vocab;
		vector<int> item_index;
		vector<int> times;
		while(true){
			infile >> str;
			if(str == "hahahaha")
				break;
			vector<string>::iterator iter2 = find(item_vocab.begin(), item_vocab.end(), str);
			if(iter2 != item_vocab.end())
				times[iter2-item_vocab.begin()]++;
			else{
				vector<string>::iterator iter = find(dict.begin(), dict.end(), str);
				if(iter != dict.end()){
					item_vocab.push_back(str);
					times.push_back(1);
					item_index.push_back(iter-dict.begin());
				}
			}	
		}
		mult << item_index.size();
		for(int i = 0; i < item_index.size(); i++)
			mult << " " << item_index[i] << ":" << times[i];
		mult << '\n';
	}
}
