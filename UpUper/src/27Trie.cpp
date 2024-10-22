/*
    Trie树：字典树：前缀树、单词查找树
    应用场景：单词检索：1w个词，实现单词的排序、快速检索、前缀搜索、效率非常高，时间复杂度O（m）
    算法核心：利用字符串的公共前缀来减少查询时间、最大限度减小无畏的比较
    1.根节点不包含字符，每一个节点包含一个字符，从根节点到某一节点连接起来就是字符串
    2.每个节点的所有字符串包含的字符都不相同

*/
#include<iostream>
#include<string>
#include<map>
#include<vector>
#include<queue>
using namespace std;


class TrieTree
{
public:
    TrieTree()
    {
        root_ = new TrieNode('\0' ,0);
    }

    ~TrieTree()
    {
        queue<TrieNode*> que;
        que.push(root_);

        while (!que.empty())
        {
            TrieNode*front = que.front();
            que.pop();
            for(auto &pair:front->nodeMap_)
            {
                que.push(pair.second);
            }
            delete front;
            
        }
    }

    void add(const string &word)
    {
        TrieNode* cur = root_;
        for(int i =0;i<word.size();i++)
        {
            auto childIt = cur->nodeMap_.find(word[i]);
            if(childIt == cur->nodeMap_.end())
            {
                TrieNode*child = new TrieNode(word[i],0);
                cur->nodeMap_.emplace(word[i],child);
                cur = child;
            }
            else
            {
                cur = childIt->second;
            }
        }

        cur->freqs_++;
    }

    int query(const string &word)  //O（m）
    {
        TrieNode*cur = root_;
        for(int i =0;i<word.size();i++)
        {
            auto childIt = cur->nodeMap_.find(word[i]);
            if(childIt == cur->nodeMap_.end())
            {
                return 0;
            }
            else
            {
                cur = childIt->second;
            }
        }
        return cur->freqs_;
    }

    //前序遍历字典树
    void preOrder()
    {
        string word;
        vector<string> wordlist;
        preOrder(root_,word,wordlist);
        for(auto word :wordlist)
        {
            cout << word <<endl;
        }
        cout <<endl; 
    }

    vector<string> queryPrefix(const string &prefix)
    {
        TrieNode*cur = root_;
        for(int i =0;i<prefix.size();i++)
        {
            auto childIt = cur->nodeMap_.find(prefix[i]);
            if(childIt == cur->nodeMap_.end())
            {
                return {};
            }
            else
            {
                cur = childIt->second;
            }
        }

        vector<string> wordlist;
        preOrder(cur,prefix.substr(0,prefix.size()-1),wordlist);

        return wordlist;
    }

    void remove(const string &word)
    {
        TrieNode *cur = root_;
        TrieNode *del = root_;
        char delch = word[0];

        for(int i=0;i<word.size();i++)
        {
            auto childTt = cur->nodeMap_.find(word[i]);
            if(childTt == cur->nodeMap_.end())
            {
                return;
            }

            if(cur->freqs_ > 0 || cur->nodeMap_.size()>1)
            {
                del = cur;
                delch = word[i];
            }

            cur = childTt->second;
        }

        if(cur->nodeMap_.empty())
        {   TrieNode*child = del->nodeMap_[delch];
            del->nodeMap_.erase(delch); 

            queue<TrieNode*> que;
            que.push(child);

            while (!que.empty())
            {
                TrieNode*front = que.front();
                que.pop();
                for(auto &pair:front->nodeMap_)
                {
                    que.push(pair.second);
                }
                delete front;
            }

        }
        else
        {
            cur->freqs_ = 0;
        }
    }

private:
    struct TrieNode
    {
        TrieNode(char ch ,int freqs)
            :ch_(ch)
            ,freqs_(freqs)
        {}
        char ch_;
        int freqs_;
        map<char,TrieNode*> nodeMap_;
    };
    

private:
    void preOrder(TrieNode*cur,string word,vector<string> &wordlist)
    {
        //VLR
        if(cur != root_)
        {
            word.push_back(cur->ch_);
            if(cur->freqs_ >0)
            {
                wordlist.emplace_back(word);
            }
        }

        for(auto pair:cur->nodeMap_)
        {
            preOrder(pair.second,word,wordlist);
        }

    }

private:
    TrieNode* root_;
    

};


/*
int main()
{
    TrieTree s;
    s.add("hello");
    cout<< s.query("hello") <<endl;

    s.add("he");
    s.add("she");
    s.add("hey");
    s.add("hero");
    s.add("subway");

    // s.preOrder();

    vector<string> wordlist;
    wordlist = s.queryPrefix("he");
    for( auto val:wordlist)
    {
        cout << val << " ";
    }
    cout <<endl;

    s.remove("hey");
    s.remove("hello");
    s.preOrder();
}
*/