#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <sstream>
#include <fstream>
#include <stack>
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
	int findSecondSlash = fullDate.find("/", findFirstSlash + 1);
	int findSpace = fullDate.find(" ");

	if (findFirstSlash != -1 && findFirstSlash == 1)
	{
		strDate += "0" + fullDate.substr(0, findFirstSlash);
	}
	else if (findFirstSlash != -1 && findFirstSlash == 2)
	{
		strDate += fullDate.substr(0, findFirstSlash);
	}
	else
	{
		return -1;
	}

	if (findSecondSlash != -1 && findSecondSlash == findFirstSlash + 2)
	{
		strDate += "0" + fullDate.substr(findFirstSlash + 1, findSecondSlash - findFirstSlash - 1);
	}
	else if (findSecondSlash != -1 && findSecondSlash == findFirstSlash + 3)
	{
		strDate += fullDate.substr(findFirstSlash + 1, findSecondSlash - findFirstSlash - 1);
	}
	else
	{
		return -1;
	}
	
	strDate += fullDate.substr(findSecondSlash + 1, findSpace - findSecondSlash - 1);

	return stoi(strDate);
}

void GetData(string fileName, map<string, Node>& nodes)
{
	ifstream file(fileName);
	int row = 2;
	if (file.is_open())
	{
		string lineFromFile;
		getline(file, lineFromFile);

		while (getline(file, lineFromFile))
		{
			istringstream stream(lineFromFile);

			string name, tweet, strLikes, strFollowers, strDates, wing, temp;
			int likes, followers, dates;

			/*
			if (row == 412)
			{
				throw "STOP";
			}
			*/

			getline(stream, temp, ','); //external_author_id
			getline(stream, name, ','); //username
			getline(stream, tweet, ','); //tweet content

			if (tweet[0] == '"' && tweet.find_last_of("\"") != tweet.length() - 1)
			{
				int quotations = 1;
				int index = 0;

				while (quotations % 2 == 1)
				{
					getline(stream, temp, ',');
					tweet += temp;

					while (tweet.find("\"", index + 1) != string::npos)
					{
						index = tweet.find("\"", index + 1);
						quotations++;
					}
				}

				/*
				while (tweet.find_last_of("\"") != tweet.length() - 1)
				{
					getline(stream, temp, ',');
					tweet += temp;
				}
				*/
			}

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

			followers = stoi(strFollowers);
			dates = changeDateFormat(strDates);
			likes = stoi(strLikes);
			
			if (dates == -1)
			{
				throw "Date exception!";
			}
			

			if (nodes.count(name) > 0)
			{
				nodes[name].tweets.push_back(tweet);
				nodes[name].likes.push_back(likes);
				nodes[name].followers.push_back(followers);
				nodes[name].dates.push_back(dates);
			}
			else
			{
				Node node(name, tweet, likes, followers, dates, wing);
				nodes[name] = node;
			}

			cout << row << " " << name << " " << tweet << " " << dates << " " << likes << " " << followers << endl;
			row++;
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