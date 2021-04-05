#include <string>
#include <vector>
using namespace std;

struct Node
{
	string name;
	vector<string> tweets; 
	vector<int> likes; 
	vector<int> followers;
	vector<int> dates; //mmddyy
	string wing;

	Node()
	{
		name = "";
		wing = "";
	}

	Node(string _name, string _tweet, int _likes, int _followers, int _dates, string _wing)
	{
		name = _name;
		tweets.push_back(_tweet);
		likes.push_back(_likes);
		//finish
	}
};