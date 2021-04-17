#include <string>
#include <vector>
#include <queue>
using namespace std;

//Node struct
struct Node
{
	string name;
	vector<string> tweets; 
	vector<int> likes; 
	vector<int> followers;
	vector<int> dates; //mmddyy
	string wing;
    Node* left, *right;

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
		//finish
	}
};

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

int main(){
    vector<string> content, name, wing;  //each index in these five vectors correspond to a twitter post
    vector<int> updates, followers;
    DepthFirstPhrase(phrase, head, content, name, wing, updates, followers);  //passes in references
    BreadthFirstPhrase(phrase, head, content, name, wing, updates, followers);
    return 0;
}
