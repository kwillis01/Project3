#include <string>
#include <vector>
#include <queue>
#include <map>
using namespace std;

//Node struct
struct Node
{
    string name;
    vector<string> tweets;
    vector<int> likes;
    vector<int> followers;
    vector<string> dates; //mmddyy
    string wing;
    Node *left, *right;

    Node()
    {
        name = "";
        wing = "";
        left = nullptr;
        right = nullptr;
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

void DepthFirstDate(string date, Node *root, vector<string> &names, vector<string> &tweets, vector<string> &wing, vector<int> &likes, vector<int> &followers)
{
    if (root == nullptr){
        return;
    }
    int count = 0;
    for (int i = 0; i < root->dates.size(); i++){
        if (root->dates[i] == date){
            names.push_back(root->name);
            tweets.push_back(root->tweets[i]);
            wing.push_back(root->wing[i]);
            likes.push_back(root->likes[i]);
            followers.push_back(root->followers[i]);
        }
    }
    DepthFirstDate(root->left, names, tweets, wing, likes, followers);
    DepthFirstDate(root->right, names, tweets, wing, likes, followers);
}

void BreadthFirstDate(string date, Node *root, vector<string> &names, vector<string> &tweets, vector<string> &wing, vector<int> &likes, vector<int> &followers)
{
    queue<Node *> q;
    Node *node;
    if (root == nullptr){
        return;
    }
    q.push(root);
    while (!q.empty()){
        int len = q.size();
        for (int i = 0; i < len; i++){
            node = q.front();
            if (node->left != nullptr){
                q.push(node->left);
            }
            if (node->right != nullptr){
                q.push(node->right);
            }
            q.pop();
            for (int i = 0; i < root->dates.size(); i++){
                if (root->dates[i] == date){
                    names.push_back(root->name);
                    tweets.push_back(root->tweets[i]);
                    wing.push_back(root->wing[i]);
                    likes.push_back(root->likes[i]);
                    followers.push_back(root->followers[i]);
                }
            }
        }
    }
}

//prints the data contained in the top 20 nodes
void printTweets(vector<string> &names, vector<string> &tweets, vector<string> &wing, vector<int> &likes, vector<int> &followers)
{
    if(names.size() > 20){
        int i = 0;
        while(i < 20){
            cout << "Author: @" << names[i] << endl;
            cout << "Tweet: ' " << tweets[i] << " '"<< endl;
            cout << "Number of Likes: " << likes[i] << endl;
            cout << "Followers: " << followers[i] << endl;
            cout << "Wing: " << wing[i] << endl;
            i++;
        }
    }
    else{
        cout << "Author: @" << names[i] << endl;
        cout << "Tweet: ' " << tweets[i] << " '"<< endl;
        cout << "Number of Likes: " << likes[i] << endl;
        cout << "Followers: " << followers[i] << endl;
        cout << "Wing: " << wing[i] << endl;
    }
}

int main()
{
    vector<string> tweets, names, wing; //each index in these five vectors correspond to a twitter post
    vector<int> likes, followers;       //stores the first 20 tweets on the date that it was searched
    Node *root;
    string date;

    //test DPS
    DepthFirstDate(date, root, names, tweets, wing, likes, followers);
    printTweets(names, tweets, wing, likes, followers);
    
    BreadthFirstDate(date, root, names, tweets, wing, likes, followers);
    printTweets(names, tweets, wing, likes, followers);
}