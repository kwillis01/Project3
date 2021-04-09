#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <sstream>
#include <fstream>
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
		followers.push_back(_followers);
		dates.push_back(_dates);
		wing = _wing;
	}
};

int changeDateFormat(string fullDate)
{
	string strDate = "";

	int findFirstSlash = fullDate.find("/");
	int findSecondSlash = fullDate.find("/", findFirstSlash);
	int findSpace = fullDate.find(" ");

	if (findFirstSlash != -1 && findSecondSlash != -1 && findSpace != -1)
	{
		strDate += fullDate.substr(0, findFirstSlash);
		strDate += fullDate.substr(findFirstSlash, findSecondSlash) + fullDate.substr(findSecondSlash, findSpace);
	}

	return -1;
}

void GetData(string fileName, map<string, Node>& nodes)
{
	ifstream file(fileName);

	if (file.is_open())
	{
		string lineFromFile;
		getline(file, lineFromFile);

		while (getline(file, lineFromFile))
		{
			istringstream stream(lineFromFile);

			string name, tweet, strLikes, strFollowers, strDates, wing, temp;
			int likes, followers, dates;

			getline(stream, temp, ','); //external_author_id
			getline(stream, name, ','); //username
			getline(stream, tweet, ','); //tweet content
			getline(stream, temp, ','); //region
			getline(stream, temp, ','); //language
			getline(stream, strDates, ','); //date created
			getline(stream, temp, ','); //harvested date
			getline(stream, temp, ','); //following
			getline(stream, strFollowers, ','); //followers
			getline(stream, strLikes, ','); //updates
			getline(stream, temp, ','); //post type (blank if normal tweet)
			getline(stream, wing, ','); //wing
			getline(stream, temp, ','); //if its a retweet
			getline(stream, temp, ','); //account category
			getline(stream, temp, ','); //if the tweet was newer
			getline(stream, temp, ','); //alternate external id
			getline(stream, temp, ','); //tweet id
			getline(stream, temp, ','); //url
			getline(stream, temp, ',');
			getline(stream, temp, ',');
			getline(stream, temp);

			dates = changeDateFormat(strDates);
			likes = stoi(strLikes);
			followers = stoi(strFollowers);


			if (nodes.count(name) > 0)
			{
				cout << name << " " << tweet << " " << strDates << " " << likes << " " << followers << endl;
				nodes[name].tweets.push_back(tweet);
				nodes[name].likes.push_back(likes);
				nodes[name].followers.push_back(followers);
			}
			else
			{
				Node node(name, tweet, likes, followers, dates, wing);
				nodes[name] = node;
			}
		}
	}
	else
	{
		cout << "File did not open!" << endl;
	}
}


	int main()
	{
		map<string, Node> nodes;
		string file = "russian-troll-tweets-master/IRAhandle_tweets_1.csv";

		GetData(file, nodes);
	}