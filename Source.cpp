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
			getline(stream, strdates, ','); //date created
			getline(stream, temp, ','); //harvested date
			getline(stream, temp, ','); //following
			getline(stream, strfollowers, ','); //followers
			getline(stream, strlikes, ','); //updates
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

			//convert date to mmddyy int format
			likes = stoi(strLikes);
			followers = stoi(strFollowers);


			if (nodes.count(name) > 0)
			{
				nodes[name].tweets.push_back(tweet);
				nodes[name].dates.push_back(dates);
				nodes[name].likes.push_back(likes);
				nodes[name].followers.push_back(followers);
			}
			else
			{
				Node node = new Node(name, tweet, likes, followers, dates, wing);
				nodes[name] = node;
			}
		}
	}
}