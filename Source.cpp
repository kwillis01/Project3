#include <string>
#include <vector>
#include <map>
#include <queue>
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
	vector<string> dates; //mmddyy
	string wing;
	Node* right;
	Node* left;

	Node()
	{
		name = "";
		wing = "";
	}

	Node(string _name, string _tweet, int _likes, int _followers, string _dates, string _wing)
	{
		name = _name;
		tweets.push_back(_tweet);
		likes.push_back(_likes);
		followers.push_back(_followers);
		dates.push_back(_dates);
		wing = _wing;
	}
};

//changes the date into mmddyy format
string changeDateFormat(string fullDate)
{
	string strDate = "";

	//find the slashes that separates the month day and year as well as the space that separates the date from the time
	int findFirstSlash = fullDate.find("/");
	int findSecondSlash = fullDate.find("/", findFirstSlash + 1);
	int findSpace = fullDate.find(" ");

	//gets the month
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
		return "-1";
	}

	//gets the day
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
		return "-1";
	}
	
	//gets the year
	strDate += fullDate.substr(findSecondSlash + 1, findSpace - findSecondSlash - 1);

	return strDate;
}

//parses through all the data to make the tree
void GetData(string fileName, vector<Node*>& nodes)
{
	ifstream file(fileName);
	//int row = 2; //for debugging purposes
	int index = 0;

	if (file.is_open())
	{
		//gets the header
		string lineFromFile;
		getline(file, lineFromFile);

		while (getline(file, lineFromFile))
		{
			istringstream stream(lineFromFile);

			//all the variables needed to parse through the data
			//the temp is used for any data we do not need, but is included in the csv
			string name, tweet, strLikes, strFollowers, dates, wing, temp;
			int likes, followers;

			// STARTS PARSING
			getline(stream, temp, ','); //external_author_id
			getline(stream, name, ','); //username
			getline(stream, tweet, ','); //tweet content

			//if there is a comma in the tweet, make sure that the whole tweet is recieved
			if (tweet[0] == '"')
			{
				int quotations = 1;
				int index = 0;
				
				//checks the quotations to make sure they are even meaning there is opening and closing quotations
				while (quotations % 2 == 1)
				{
					//finds all the quotations
					while (tweet.find("\"", index + 1) != string::npos)
					{
						index = tweet.find("\"", index + 1);
						quotations++;
					}

					if (quotations % 2 == 0)
						break;

					//gets the nexet part of the tweet
					getline(stream, temp, ',');
					tweet += temp;
				}
			}

			getline(stream, temp, ','); //region
			getline(stream, temp, ','); //language
			getline(stream, dates, ','); //date created
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
			
			//change string variables to int ones
			followers = stoi(strFollowers);
			dates = changeDateFormat(dates);
			likes = stoi(strLikes);
			
			//throws an exception if the date is not parsed in correctly
			if (dates == "-1")
			{
				throw "Date exception!";
			}
			
			//makes a new node or adds to new information to the node
			if (!nodes.empty() && nodes.at(index)->name == name)
			{
				nodes.at(index)->tweets.push_back(tweet);
				nodes.at(index)->likes.push_back(likes);
				nodes.at(index)->followers.push_back(followers);
				nodes.at(index)->dates.push_back(dates);
			}
			else
			{
				if (!nodes.empty())
					index++;
				
				Node* node = new Node(name, tweet, likes, followers, dates, wing);
				nodes.push_back(node);
			}

			//commented out part is for debugging
			//cout << row << " " << name << " " << tweet << " " << dates << " " << likes << " " << followers << endl;
			//row++;
		}
		//cout << nodes.size();
	}
	else
	{
		cout << "File did not open!" << endl;
	}
}

Node* BinaryInsert(vector<Node*>& nodes, int startIndex, int endIndex)
{
	int mid = (endIndex + startIndex) / 2;

	if (startIndex > endIndex)
	{
		return nullptr;
	}

	Node* root = nodes.at(mid);
	root->left = BinaryInsert(nodes, startIndex, mid - 1);
	root->right = BinaryInsert(nodes, mid + 1, endIndex);
	return root;
}

void WingBFS(vector<Node*>& wings, Node* root, string specifiedWing)
{
	queue<Node*> q;

	if (root != nullptr)
	{
		q.push(root);
	}

	while (!q.empty())
	{
		if (q.front()->wing == specifiedWing)
			wings.push_back(q.front());

		if (q.front()->left)
			q.push(q.front()->left);

		if (q.front()->right)
			q.push(q.front()->right);

		q.pop();
	}
}

void WingDFS(vector<Node*>& wings, Node* root, string specifiedWing)
{
	if (root != nullptr)
	{
		if (root->wing == specifiedWing)
			wings.push_back(root);
		
		WingBFS(wings, root->left, specifiedWing);
		WingBFS(wings, root->right, specifiedWing);
	}
	
}

int main()
{
	vector<Node*> nodes;
	string file = "russian-troll-tweets-master/IRAhandle_tweets_2.csv";

	GetData(file, nodes);
	Node* root = BinaryInsert(nodes, 0, nodes.size() - 1);
	
	vector<Node*> specifiedWing1;
	vector<Node*> specifiedWing2;
	
	WingBFS(specifiedWing1, root, "Left");
	WingDFS(specifiedWing2, root, "Left");

	if (specifiedWing1.size() == specifiedWing2.size())
	{
		cout << "true" << endl;
	}
	else
		cout << "false" << endl;
	
}