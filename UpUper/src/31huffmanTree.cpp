#include<iostream>
#include<unordered_map>
#include<queue>
#include<functional>
using namespace std;


/*
哈夫曼树：最佳判定树、最优二叉树、一种带权路径长短的二叉树、常用于数据的压缩
树的带权路径长度：所有叶子节点的权值乘以其到根节点的路径长度

引用场景（哈夫曼编码）：数据压缩--》给字符进行二进制编码--》统计数据的出现频率（频率高的/权值大的，期望编码要短一些）
    哈夫曼编码是一种变长编码的方式、具有立刻可解码性（任一字符的编码不会是一个更长编码的前缀，例：不会出现100 D，1000 E）
    解码也是通过哈夫曼树进行解压

构建过程： 统计字符出现频率/权值   得到一组权值 2 4 2 6 8 10
    从权值里选取两个最小的权值，构建一颗二叉树，生产的父节点的权值是两个孩子节点的权值之和，在把该二叉树的根节点值放回权值中，再重复
        这样叶子节点上就是最初始的权值，同时这样构造可以保证叶子节点到根节点的距离乘以权值之和是最小的
    同时，因为需要取最小的，没必要进行排序，采用最小堆就可以。 priority_queue  (默认是大根堆)
        左孩子指向0，右孩子指向1，路径上的数字就是哈夫曼编码
*/

class huffmanTree
{
public:
    huffmanTree()
        :minheap_([](Node* n1,Node* n2)->bool {return n1->weight_ >n2->weight_;})
        ,root_(nullptr)
    {}
    ~huffmanTree()
    {

    }

public:
    void creat(string str)
    {
        unordered_map<char, uint16_t> dataMap;
        for(char ch:str)
        {
            dataMap[ch]++;   //这个写法简略了几步
        }

        for(auto& pair:dataMap)
        {
            minheap_.push(new Node(pair.first, pair.second));
        }

        while (minheap_.size() > 1)
        {
            Node *n1 = minheap_.top();
            minheap_.pop();

            Node*n2 = minheap_.top();
            minheap_.pop();

            //生成父节点
            Node* node = new Node('\0', n1->weight_ + n2->weight_);
            node->left_ = n1;
            node->right_ = n2;

            minheap_.push(node);
        }

        root_ = minheap_.top();
        minheap_.pop();
        
    }

    void showhuffmanCode()
    {
        string code;
        showhuffmanCode(root_, code);

        for(auto& pair:codeMap_)
        {
            cout<< pair.first <<" : "<<pair.second<<endl;
        }
    }


    string encode(string str)
    {
        string encode_str;
        for(char ch:str)
        {
            encode_str.append(codeMap_[ch]);
        }
        return encode_str;
    }

    string decode(string encode)
    {
        string decode_str;
        Node*cur =root_;

        for(char ch:encode)
        {
            if(ch == '0')
            {
                cur = cur->left_;
            }
            else
            {
                cur = cur->right_;
            }

            if(cur->left_ ==nullptr&& cur->right_==nullptr)
            {
                decode_str.push_back(cur->data_);
                cur = root_;
            }
        }

        return decode_str;
        }

private:
    struct Node
    {
        Node(char data, uint16_t weight)
            :data_(data)
            ,weight_(weight)
            ,left_(nullptr)
            ,right_(nullptr)
        {}
        char data_;
        uint16_t weight_;
        Node* left_;
        Node* right_;

        bool operator>(const Node& node) const
        {
            return weight_> node.weight_;
        }
    };

    void showhuffmanCode(Node *root, string code)
    {
        //VLR
        if(root->left_ == nullptr && root->right_ == nullptr)
        {
            codeMap_[root->data_] = code;
            return;
        }

        showhuffmanCode(root->left_, code+"0");
        showhuffmanCode(root->right_, code +"1");
    }

private:
    Node* root_;
    unordered_map<char ,string> codeMap_;  //字符对应的编码

    using MinHeap = priority_queue<Node*, vector<Node*>, function<bool(Node*,Node*)>>;   
    MinHeap minheap_;
    
    

};


int main()
{
    string str = "ABACDAEHGHFHIUIYYTDSDFHGKJLJIFDEG";

    huffmanTree htree;
    htree.creat(str);
    htree.showhuffmanCode();

    string code = htree.encode(str);
    cout<< code <<endl;

    cout<< htree.decode(code) <<endl;

}