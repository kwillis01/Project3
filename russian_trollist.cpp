#include <string>
#include <vector>
#include <map>
#include <queue>
#include <iostream>
#include <sstream>
#include <fstream>
#include <stack>
#include <chrono>
#include <set>
using namespace std;
using namespace std::chrono;

//Node class
struct Node
{
    string name;
    vector<string> tweets;
    vector<int> likes;
    vector<int> followers;
    vector<string> dates; //mmddyyyy
    string wing;
    Node* left; 
    Node* right;

    Node()
    {
        name = "";
        wing = "";
        left = nullptr;
        right = nullptr;
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

//------Helper Functions------

//changes date from mm/dd/yy to mmddyy
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

//checks if string is a substring of another string
bool isSubstring(string str, string substr){
    int length = 0, index, num = str.length() - substr.length();
    for(int i = 0; i <= num; i++){
        index = i;
        length = 0;
        for(int j = 0; j < substr.length(); j++){
            if(str[index] == substr[j]){
                index++;
                length++;
            }
            else
                break;
        }
        if(length == substr.length())
            return true;
    }
    return false;
}

//prints the data contained in the top 20 nodes
void printTweets(vector<string> &names, vector<string> &tweets, vector<string> &wing, vector<int> &likes, vector<int> &followers)
{
    set<int> prevIndices;
    int index = 0;

    if(names.size() > 5){
        for(int i= 0; i < 5; i++){
            index = rand() % names.size();
            while (prevIndices.count(index) > 0)
            {
                index = rand() % names.size();
            }
            prevIndices.insert(index);

            cout << "Author: @" << names[index] << endl;
            cout << "Tweet: ' " << tweets[index] << " '"<< endl;
            cout << "Number of Likes: " << likes[index] << endl;
            cout << "Followers: " << followers[index] << endl;
            cout << "Wing: " << wing[index] << endl << endl;
        }
    }
    else{
        for(int i = 0; i < names.size(); i++){
            index = rand() % names.size();
            while (prevIndices.count(index) > 0)
            {
                index = rand() % names.size();
            }
            prevIndices.insert(index);

            cout << "Author: @" << names[index] << endl;
            cout << "Tweet: ' " << tweets[index] << " '"<< endl;
            cout << "Number of Likes: " << likes[index] << endl;
            cout << "Followers: " << followers[index] << endl;
            cout << "Wing: " << wing[index] << endl << endl;
        }
    }
}
void printTweets(vector<Node*> &nodes){
    set<int> prevIndices;
    int index = 0;

    if(nodes.size() > 5){
        for(int i= 0; i < 5; i++){
            index = rand() % nodes.size();
            while (prevIndices.count(index) > 0)
            {
                index = rand() % nodes.size();
            }
            prevIndices.insert(index);

            cout << "Author: @" << nodes[index]->name << endl;
            cout << "Tweet: ' " << nodes[index]->tweets[0] << " '"<< endl;
            cout << "Number of Likes: " << nodes[index]->likes[0] << endl;
            cout << "Followers: " << nodes[index]->followers[0] << endl;
            cout << "Wing: " << nodes[index]->wing << endl << endl;
        }
    }
    else{
        for(int i = 0; i < nodes.size(); i++){
            index = rand() % nodes.size();
            while (prevIndices.count(index) > 0)
            {
                index = rand() % nodes.size();
            }
            prevIndices.insert(index);

            cout << "Author: @" << nodes[index]->name << endl;
            cout << "Tweet: ' " << nodes[index]->tweets[0] << " '"<< endl;
            cout << "Number of Likes: " << nodes[index]->likes[0] << endl;
            cout << "Followers: " << nodes[index]->followers[0] << endl;
            cout << "Wing: " << nodes[index]->wing << endl << endl;
        }
    }
}

//creates BST
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

//------ Data Parsing-------

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
		}
	}
	else
	{
		cout << "File did not open!" << endl;
	}
}

//------Searching Algorigthms------

//Depth First Search by date
void DepthFirstDate(string date, Node* root, vector<string> &names, vector<string> &tweets, vector<string> &wing, vector<int> &likes, vector<int> &followers)
{
    if (root == nullptr){
        return;
    }
    int count = 0;
    for (int i = 0; i < root->dates.size(); i++){
        if (root->dates[i] == date){
            names.push_back(root->name);
            tweets.push_back(root->tweets[i]);
            wing.push_back(root->wing);
            likes.push_back(root->likes[i]);
            followers.push_back(root->followers[i]);
        }
    }
    DepthFirstDate(date, root->left, names, tweets, wing, likes, followers);
    DepthFirstDate(date, root->right, names, tweets, wing, likes, followers);
}

//Breadth First Search by date
void BreadthFirstDate(string date, Node* root, vector<string> &names, vector<string> &tweets, vector<string> &wing, vector<int> &likes, vector<int> &followers)
{
    queue<Node *> q;
    Node *node;
    int len;
    if (root == nullptr){
        return;
    }
    q.push(root);
    while (!q.empty()){
        len = q.size();
        for (int i = 0; i < len; i++){
            node = q.front();
            if (node->left != nullptr){
                q.push(node->left);
            }
            if (node->right != nullptr){
                q.push(node->right);
            }
            q.pop();
            for (int i = 0; i < node->dates.size(); i++){
                if (node->dates[i] == date){
                    names.push_back(node->name);
                    tweets.push_back(node->tweets[i]);
                    wing.push_back(node->wing);
                    likes.push_back(node->likes[i]);
                    followers.push_back(node->followers[i]);
                }
            }
        }
    }
}

//Depth  First Search by Phrase function
void DepthFirstPhrase(string phrase, Node* head, vector<string>& content, vector<string>& name, vector<string>& wing, vector<int>& updates, vector<int>& followers){
    if(!head)
        return;
    for(int i = 0; i < head->tweets.size(); i++){
        if(isSubstring(head->tweets[i], phrase)){
            content.push_back(head->tweets[i]);
            name.push_back(head->name);
            wing.push_back(head->wing);
            updates.push_back(head->likes[i]);
            followers.push_back(head->followers[i]);
        }
    }
    DepthFirstPhrase(phrase, head->left, content, name, wing, updates, followers);
    DepthFirstPhrase(phrase, head->right, content, name, wing, updates, followers);
}

//Breadth First Search by Phrase function
void BreadthFirstPhrase(string phrase, Node* head, vector<string>& content, vector<string>& name, vector<string>& wing, vector<int>& updates, vector<int>& followers){
    queue<Node*> q;
    int num;
    Node* temp;
    if(!head)
        return;
    q.push(head);
    while(!q.empty()){
        num = q.size();
        for(int i = 0; i < num; i++){
            temp = q.front();
            if(temp->left)
                q.push(temp->left);
            if(temp->right)
                q.push(temp->right);
            q.pop();
            for(int i = 0; i < temp->tweets.size(); i++){
                if(isSubstring(temp->tweets[i], phrase)){
                    content.push_back(temp->tweets[i]);
                    name.push_back(temp->name);
                    wing.push_back(temp->wing);
                    updates.push_back(temp->likes[i]);
                    followers.push_back(temp->followers[i]);
                }
            }
        }
    }
}

//Depth First Search by Wing
void WingDFS(vector<Node*>& wings, Node* root, string specifiedWing)
{
	if (root != nullptr)
	{
		if (root->wing == specifiedWing)
			wings.push_back(root);
		
		WingDFS(wings, root->left, specifiedWing);
		WingDFS(wings, root->right, specifiedWing);
	}
}

//Breadth First Search by Wing
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

//------MAIN------
int main()
{
    //create BST from list of nodes 
    vector<Node*> nodes;
    string file = "russian-troll-tweets-master/IRAhandle_tweets_2.csv";
    GetData(file, nodes);
	Node* root = BinaryInsert(nodes, 0, nodes.size() - 1);
    bool exit = false;
    cout << "Welcome to the Russian Troll Factory!" << endl;
    while(!exit){
        //Starting Menu
        cout << "Please make a selection: " << endl;
        cout << "1. Search by Phrase" << endl;
        cout << "2. Search by Date" << endl;
        cout << "3. Search by Wing" << endl;
        cout << "4. Exit" << endl;
        int input;
        int choice;
        string search;
        cin >> input;
        switch (input) {
        //Search by phrase
        case 1:
            cout << "How would you like to search?" << endl;
            cout << "1. Depth Search" << endl;
            cout << "2. Breadth Search" << endl;
            cin >> choice;
            if (choice == 1){
                cout << "You are doing DFS by phrase!" << endl;
                cout << "Enter the phrase you want to search for:" << endl;
                getline(cin, search);
                cout << "You are searching for ' " << search << " '"<<endl << endl;

                //perform DFS search and time it
                vector<string> tweets, names, wing;
                vector<int> likes, followers; 

                steady_clock::time_point start = steady_clock::now();
                DepthFirstPhrase(search, root, tweets, names, wing, likes, followers);
                steady_clock::time_point stop = steady_clock::now();
                auto duration = duration_cast<nanoseconds>(stop-start);

                //Print out top 5 search results
                cout << tweets.size() <<" number of tweets were found!"<< endl;
                cout << "Here are the top 5:" << endl << endl;
                printTweets(names, tweets, wing, likes, followers);
                cout << "Time taken for DFS by phrase: " << duration.count() << " nanoseconds" << endl;
            }
            else{
                cout << "You are doing BFS by phrase!" << endl;
                cout << "Enter the phrase you want to search for:" << endl;
                getline(cin, search);
                cout << "You are searching for ' " << search << " '"<<endl << endl;

                //perform BFS search and time it
                vector<string> tweets, names, wing;
                vector<int> likes, followers; 
                steady_clock::time_point start = steady_clock::now();
                BreadthFirstPhrase(search, root, tweets, names, wing, likes, followers);
                steady_clock::time_point stop = steady_clock::now();
                auto duration = duration_cast<nanoseconds>(stop-start);

                //Print out top 5 search results
                cout << tweets.size() <<" number of tweets were found!"<< endl;
                cout << "Here are the top 5:" << endl << endl;
                printTweets(names, tweets, wing, likes, followers);
                cout << "Time taken for BFS by phrase: " << duration.count() << " nanoseconds" << endl;
            }
            break;
        //Search by Date
        case 2:
            cout << "How would you like to search?" << endl;
            cout << "1. Depth Search" << endl;
            cout << "2. Breadth Search" << endl;
            cin >> choice;
            if (choice == 1){
                cout << "You are doing DFS by Date!" << endl;
                cout << "Enter the date you want to search by in mmddyyyy format:" << endl;
                getline(cin, search);
                cout << "You are searching for ' " << search << " '"<<endl << endl;

                //Perform DFS search and time it
                vector<string> tweets, names, wing;
                vector<int> likes, followers; 
                steady_clock::time_point start = steady_clock::now();
                DepthFirstDate(search, root, names, tweets, wing, likes, followers);
                steady_clock::time_point stop = steady_clock::now();
                auto duration = duration_cast<nanoseconds>(stop-start);

                //Print out top 5 search results
                cout << tweets.size() <<" number of tweets were found!"<< endl;
                cout << "Here are the top 5:" << endl << endl;
                printTweets(names, tweets, wing, likes, followers);
                cout << "Time taken for DFS by date: " << duration.count() << " nanoseconds" << endl;
            }
            else{
                cout << "You are doing BFS by Date!" << endl;
                cout << "Enter the date you want to search by in mmddyyyy format:" << endl;
                getline(cin, search);
                cout << "You are searching for ' " << search << " '"<<endl << endl;

                //Perform BFS search and time it
                vector<string> tweets, names, wing;
                vector<int> likes, followers; 
                steady_clock::time_point start = steady_clock::now();
                BreadthFirstDate(search, root, names, tweets, wing, likes, followers);
                steady_clock::time_point stop = steady_clock::now();
                auto duration = duration_cast<nanoseconds>(stop-start);

                //Print out top 5 search results
                cout << tweets.size() <<" number of tweets were found!"<< endl;
                cout << "Here are the top 5:" << endl << endl;
                printTweets(names, tweets, wing, likes, followers);
                cout << "Time taken for BFS by date: " << duration.count() << " nanoseconds" << endl;
            }
            break;
        //Search by Wing
        case 3:
            cout << "How would you like to search?" << endl;
            cout << "1. Depth Search" << endl;
            cout << "2. Breadth Search" << endl;
            cin >> choice;
            if (choice == 1){
                cout << "You are doing DFS by Wing!" << endl;
                cout << "Enter the wing you want to search by:" << endl;
                getline(cin, search);
                cout << "You are searching for ' " << search << " '"<< endl << endl;

                //Perform DFS searchand time it
                vector<Node*> specifiedWings;
                steady_clock::time_point start = steady_clock::now();
                WingDFS(specifiedWings, root, search);
                steady_clock::time_point stop = steady_clock::now();
                auto duration = duration_cast<nanoseconds>(stop-start);

                //Print out top 5 search results
                cout << specifiedWings.size() <<" number of tweets were found!"<< endl;
                cout << "Here are the top 5:" << endl << endl;
                printTweets(specifiedWings);
                cout << "Time taken for DFS by wing: " << duration.count() << " nanoseconds" << endl;
            }
            else{
                cout << "You are doing BFS by Wing!" << endl;
                cout << "Enter the wing you want to search by:" << endl;
                getline(cin, search);
                cout << "You are searching for ' " << search << " '" << endl <<endl;

                //Perform BFS search and time it
                vector<Node*> specifiedWings;
                steady_clock::time_point start = steady_clock::now();
                WingBFS(specifiedWings, root, search);
                steady_clock::time_point stop = steady_clock::now();
                auto duration = duration_cast<nanoseconds>(stop-start);

                //Print out top 5 search results
                cout << specifiedWings.size() <<" number of tweets were found!"<< endl;
                cout << "Here are the top 5:" << endl << endl;
                printTweets(specifiedWings);
                cout << "Time taken for BFS by wing: " << duration.count() << " nanoseconds" << endl;
            }
            break;
        case 4:
            cout << "Bye Bye!!!" << endl;
            exit = true;
            break;
        default:
            cout << "Please make a valid selection! \n" << endl;
            break;
        }
    }
}