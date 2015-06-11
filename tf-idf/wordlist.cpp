#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

int users = 5551;
int items = 16980;

int main(){
	ifstream infile("ready-data.txt");
	int index;
	vector<string> wordlist;
	string str;
	while(!infile.eof()){
		infile >> index;
		while(true){
			infile >> str;
			if(str == "hahahaha")
				break;
			vector<string>::iterator iter = find(wordlist.begin(), wordlist.end(), str);
			if(iter == wordlist.end())
				wordlist.push_back(str);
		}
	}
	infile.close();
	ofstream outfile("whole-wordlist.txt");
	for(int i = 0; i < wordlist.size(); i++)
		outfile << wordlist[i] << '\n';
	outfile.close();
}
