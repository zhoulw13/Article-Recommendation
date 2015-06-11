#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <set>
#include <cmath>
using namespace std;

int items = 16980;
int each_item = 2;

struct tfidf{
	string str;
	int n;
	float tf;
	float idf;
	float score;
	bool operator<(tfidf other) const{
        return score > other.score;
    };
};

bool MatchMember(tfidf m1, tfidf m2){
	return (m1.str == m2.str);
}


int main(){
	ifstream wordlist_file("whole-wordlist.txt");
	vector<tfidf> wordlist;
	tfidf temp;
	temp.n = 0;
	temp.score = 0;
	while(!wordlist_file.eof()){
		wordlist_file >> temp.str;
		wordlist.push_back(temp);
	}
	wordlist_file.close();
	
	ifstream infile("ready-data.txt");
	int index;
	string str;
	while(!infile.eof()){
		infile >> index;
		set<string> temp;
		while(true){
			infile >> str;
			if(str == "hahahaha")
				break;
			temp.insert(str);
		}
		tfidf x;
		x.n = 0;
		x.score = 0;
		vector<tfidf> y;
		y.push_back(x);
		for(set<string>::iterator iter = temp.begin(); iter != temp.end(); iter++){
			y[0].str = *iter;
			vector<tfidf>::iterator iter2 = search(wordlist.begin(), wordlist.end(), y.begin(), y.end(), MatchMember);
			if(iter2 != wordlist.end())
				(iter2->n)++;
		}
		temp.clear();
	}
	infile.close();

	for(int i = 0; i < wordlist.size(); i++)
		wordlist[i].idf = log(double(items)/double(1+wordlist[i].n));

	
	infile.open("ready-data.txt");
	set<string> vocab;
	
	tfidf x;
	x.n = 1;
	x.score = 0;
	vector<tfidf> y;
	y.push_back(x);
	while(!infile.eof()){
		infile >> index;
		vector<tfidf> temp;
		while(true){
			infile >> str;
			if(str == "hahahaha")
				break;
			y[0].str = str;
			vector<tfidf>::iterator iter = search(temp.begin(), temp.end(), y.begin(), y.end(), MatchMember);
			if(iter == temp.end())
				temp.push_back(y[0]);
			else
				(iter->n)++;
		}
		int max = -1;
		for(int i = 0; i < temp.size(); i++)
			if(temp[i].n > max)
				max = temp[i].n;
		for(int i = 0; i < temp.size(); i++){
			temp[i].tf = 0.5+0.5*temp[i].n/max;
			y[0].str = temp[i].str;
			vector<tfidf>::iterator iter = search(wordlist.begin(), wordlist.end(), y.begin(), y.end(), MatchMember);
			if (iter != wordlist.end())
				temp[i].score = (iter->idf)*temp[i].tf;
			else
				temp[i].score = 0;
		}
		sort(temp.begin(), temp.end());
		int size = (each_item < temp.size() ? each_item : temp.size());
		for(int i = 0; i < size; i++)
			vocab.insert(temp[i].str);
		temp.clear();
	}
	ofstream outfile("vocab.txt");
	for(set<string>::iterator iter = vocab.begin(); iter != vocab.end(); iter++)
		outfile << *iter << '\n';
}
