#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

int users = 5551;
int items = 16980;
int dims = 200;
int candidates = 251;
int get_num = 4;

struct unit{
	int index;
	double grade;
	bool operator<(unit other) const{
        return grade > other.grade;
    }
};


double Inner_product(vector<double>& vec1, vector<double>& vec2){
	double result = 0;
	for(int i = 0; i < dims; i++)
		result += vec1[i]*vec2[i];
	return result;
}

int main(){
	/*ifstream user_file("final-U.dat");
	vector<double> user_1;
	user_1.resize(dims);
	for(int i = 0; i < dims; i++)
		user_file >> user_1[i];
	user_file.close();*/
	
	ifstream user_file("final-U.dat");
	vector<vector<double> > user;
	user.resize(users);
	for(int i = 0; i < users; i++){
		user[i].resize(dims);
		for(int j = 0; j < dims; j++)
			user_file >> user[i][j];
	}
	user_file.close();
	
	ifstream item_file("final-V.dat");
	vector<vector<double> > item;
	item.resize(items);
	for(int i = 0; i < items; i++){
		item[i].resize(dims);
		for(int j = 0; j < dims; j++)
			item_file >> item[i][j];
	}
	item_file.close();

	/*vector<unit> u;
	u.resize(items);
	for(int i = 0; i < items; i++){
		u[i].index = i;
		u[i].grade = Inner_product(user_1, item[i]);
	}
	sort(u.begin(), u.end());
	
	ofstream outfile("recommendation_1.txt");
	for(int i = 0; i < items; i++)
		outfile << u[i].index << " " << u[i].grade << '\n';*/

	ifstream test_file("user-info-test.txt");
	ofstream result("result.txt");
	vector<unit> u;
	u.resize(candidates);
	for(int i = 0; i < users; i++){
		int a, b;
		char c;
		for(int j = 0; j < candidates; j++){
			test_file >> a >> c >> b;
			u[j].index = b;
			u[j].grade = Inner_product(user[i], item[b-1]);
		}
		sort(u.begin(), u.end());
		result << i+1 << ",";
		for(int k = 0; k < get_num; k++)
			result << u[k].index << ";";
		result << u[get_num].index << '\n';
	}
	test_file.close();
	result.close();
}
