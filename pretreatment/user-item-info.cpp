#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int users = 5551;
int items = 16980;

int main(){
	ifstream infile("user-info-train.txt");
	if(!infile){
		cout << "can't open file" << endl;
		return 0;
	}
	int a,b;
	char c;
	vector<vector<int> > user_info;
	vector<vector<int> > item_info;
	user_info.resize(users+5);
	item_info.resize(items+5);
	while(!infile.eof()){
		infile >> a >> c >> b;
		user_info[a-1].push_back(b-1);
		item_info[b-1].push_back(a-1);
	}
	infile.close();
	ofstream user_file("user.txt");
	ofstream item_file("item.txt");
	for(int i = 0; i < users; i++){
		user_file << user_info[i].size();
		for(int j = 0; j < user_info[i].size(); j++)
			user_file << " " << user_info[i][j];
		user_file << '\n';
	}
	user_file.close();
	for(int i = 0; i < items; i++){
		item_file << item_info[i].size();
		for(int j = 0; j < item_info[i].size(); j++)
			item_file << " " << item_info[i][j];
		item_file << '\n';
	}
	item_file.close();
}
