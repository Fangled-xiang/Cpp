//基本概念：根节点、左节点、右节点、祖先节点、兄弟节点、叔叔节点、叶子节点、左子树、右子树
//左孩子<父节点<右孩子--BST树  层数long2（N）--二分搜索时间复杂度

#include<iostream>
#include<functional>
#include<stack>
#include<queue>
#include<vector>
using namespace std;



template<typename T, typename Compare=less<T>>

class BSTtree
{

public:
    BSTtree():root_(nullptr){}
    //析构函数
    ~BSTtree()
    {
        if(root_ != nullptr)
        {
            queue <Node*> s;
            s.push(root_);
            while (!s.empty())
            {
                Node* front = s.front();
                s.pop();

                if(front->left_ != nullptr)
                {
                    s.push(front->left_);
                }
                if(front->right_ != nullptr)
                {
                    s.push(front->right_);
                }
                delete front;
            }
            
        }
    }

    void non_insert(const T &val)//非递归插入
    {
        if(root_ == nullptr)
        {
            root_ = new Node(val);
            return;
        }
        Node* parent = nullptr;
        Node * cur = root_;
        while (cur!=nullptr)
        {
            if(cur->data_ > val)
            {
                parent = cur;
                cur = cur->left_;
            }
            else if (cur->data_ < val)
            {
                parent = cur;
                cur = cur->right_;
            }
            else
            {
                //不插入
                return;
            }
        }

        if(val < parent->data_)
        {
            parent->left_ = new Node(val);
        }
        else
        {
            parent->right_ = new Node(val);
        }

    }

    void insert(const T &val)
    {
        root_ = insert(root_ , val);
    }

    //删除：找前驱或者后继节点的值，把待删除的值覆盖掉，再删除前驱或者后继节点
    //前驱节点：当前节点左子树值中最大的节点，后继节点：当前节点右子树值中最小的节点（前驱/后继节点没有或者最多有一个孩子）--这样不影响BST树的性质
    void non_remove(const T &val)
    {
        if(root_ == nullptr)
        {
            return;
        }

        Node * parent = nullptr;
        Node *cur = root_;
        while (cur != nullptr)
        {
            if(!Compare(cur->data_ , val))
            {
                parent = cur;
                cur = cur->left_;
            }
            else if(Compare(cur->data_ , val))
            {
                parent = cur;
                cur = cur->right_;
            }
            else
            {
                break;
            }
        }

        if(cur == nullptr)
        {
            return;
        }

        if(cur->left_ != nullptr && cur->right_ != nullptr)  //情况三：有两个孩子
        {
            parent = cur;
            Node *pre = cur->left_;
            while (pre->left_ != nullptr)
            {
                parent = pre;
                pre = pre->right_;
            }

            cur->data_ = pre->data_;
            cur = pre; //转化成情况1/2：有或者没有孩子（前驱节点可能有左孩子），后面删除cur
        }

        Node *child = cur->left_;
        if(child == nullptr)
        {
            child = cur->right_; //有孩子总会指向唯一的孩子，没有还是空
        }

        if(parent == nullptr) // 删除根节点
        {
            root_ = child;
        }
        else
        {
            if(parent->left_ == cur)
            {
                parent->left_ = child;
            }
            else
            {
                parent->right_ = child;
            }
        }

        delete cur;        
    }

    void remove(const T &val)
    {
        root_ = remove(root_, val);
    }


    //查询
    bool non_query(const T &val)
    {
        Node *cur = root_;
        while (cur != nullptr)
        {
            if(cur->data_ == val)
            {
                return true;
            }
            else if (cur->data_<val)
            {
                cur = cur->right_;
            }
            else
            {
                cur = cur->left_;
            }
            
        }

        return false;
        
    }

    bool quary(const T &val)
    {
        return !(quary(root_,val) == nullptr);
    }

    //二叉树遍历：层序遍历（一层一层从上到下从左到右）
    //前序遍历，中序、后序遍历（V当前，LR左右，L需要出现在V之前；VLR前序、LVR中序、LRV后序）、每一个节点都是一样的顺序
    void preOrder()
    {
        preOrder(root_);
        cout<<endl;
    }
    void inOrder()
    {
        inOrder(root_);
        cout<<endl;
    }
    void postOrder()
    {
        postOrder(root_);
        cout<<endl;
    }

    void levelOrder()//层序遍历
    {
        int h = level();
        for(int i=0;i<h;i++)
        {
            levelOrder(root_ , i);
        }
        cout<<endl;
    }

    int level()  //层数
    {
        return level(root_);
    }
    int number()
    {
        return number(root_);
    }

    //非递归实现：
    void non_preOrder()
    {
        if(root_ == nullptr)
        {
            return;
        }
        stack<Node*> s;
        s.push(root_);
        while (!s.empty())
        {
            Node *top = s.top();
            s.pop();
            cout<< top->data_ <<" "; //V

            if(top->right_ != nullptr)
            {
                s.push(top->right_);
            }
            if(top->left_ != nullptr)
            {
                s.push(top->left_);
            }
        }
        cout<<endl;
    }

    void non_inOrder()
    {
        if(root_ == nullptr)
        {
            return;
        }
        stack<Node*> s;
        Node *cur = root_;
        while(cur != nullptr)
        {
            s.push(cur);
            cur = cur->left_;
        }

        while (!s.empty())
        { 
            Node *top = s.top();
            s.pop();
            cout<< top->data_ <<" "; //V

            cur = top->right_;
            while(cur != nullptr)
            {
               s.push(cur); 
               cur = cur->left_;
            }
        }

        cout<<endl;
    }

    void non_postOrder()  //用两个栈，LRV，先按VRL和前序一样，再逆序，最后打印
    {
        if(root_ == nullptr)
        {
            return;
        }
        stack<Node*> s,s2;
        s.push(root_);
        while (!s.empty())
        {
            Node *top = s.top();
            s.pop();
            // cout<< top->data_ <<" "; //V
            s2.push(top);

            if(top->left_ != nullptr)
            {
                s.push(top->left_);
            }
            if(top->right_ != nullptr)
            {
                s.push(top->right_);
            }
        }

        while (!s2.empty())
        {
            Node *top2 = s2.top();
            s2.pop();
            cout<< top2->data_<<" ";
        }

        cout<<endl;
        
        
    }

    void non_levelOrder()//靠一个队列来实现
    {
        if(root_ == nullptr)
        {
            return;
        }

        queue<Node*> que;
        que.push(root_);
        while (!que.empty())
        {
            Node *front = que.front();
            que.pop();

            cout<<front->data_<<" ";
            if(front->left_ != nullptr)
            {
                que.push(front->left_);
            }
            if(front->right_ != nullptr)
            {
                que.push(front->right_);
            }
        }
        cout<<endl;
    }

    //查找一个区间内的值：利用中序遍历升序的特点
    void findVals(vector<T> &vec,int i,int j)  //[i,j]
    {
        findVals(root_,vec,i,j);
    }

    bool isBSTtree()
    {
        return false;
    }

    //找最近公共祖先节点
    int getLCA(int val1,int val2)
    {
        Node*p = getLCA(root_,val1,val2);
        if(p == nullptr)
        {
            throw"no LCA";
        }
        else
        {
            return p->data_;
        }
    }

    //镜像翻转
    void mirror01()//左右孩子节点互换
    {
        return mirror01(root_);
    }

    bool mirr02()//镜像对称-以根节点为对称轴
    {
        return mirr02(root_->left_,root_->right_) ;
    }
    
    //平衡树：任意节点左右子树！！高度差不超过1
    bool isBalance()
    {
        return false;
    }

    //求中序倒数第k个节点值；LVR
    int getval(int k)
    {
        Node *p = getval(root_, k);
        return p->data_;
    }

private://****************************************************************************************** */
    struct Node
    {
        Node(T data=T())
            : data_(data)
            , left_(nullptr)
            , right_(nullptr)
        {}
        T data_;
        Node *left_;
        Node *right_;
    };
    Node *root_;

    void preOrder(Node *node)
    {
        if(node!= nullptr)
        {
            cout<< node->data_ <<" ";//V
            preOrder(node->left_); // L
            preOrder(node->right_);  //R
        }
    }

    void inOrder(Node *node)
    {
        if(node!= nullptr)
        {
            inOrder(node->left_); // L
            cout<< node->data_ <<" ";//V 
            inOrder(node->right_);  //R
        }
    }

    void postOrder(Node *node)
    {
        if(node!= nullptr)
        {
            postOrder(node->left_); // L
            postOrder(node->right_);  //R
            cout<< node->data_ <<" ";//V 
        }
    }

    int level(Node *node) //递归实现以node为节点的子树高度
    {
        if(node == nullptr)
        {
            return 0;
        }
        int left = level(node->left_);
        int right = level(node->right_);
        return left>right? left+1:right+1;
    }
    
    int number(Node *node) //递归实现以node为节点的中数
    {
        if(node == nullptr)
        {
            return 0;
        }
        int left = number(node->left_);
        int right = number(node->right_);
        return left+right+1;
    }

    void levelOrder(Node *node,int i)
    {
        if(node == nullptr)
        {
            return;
        }
        if(i == 0)
        {
            cout<< node->data_<<" ";
            return;
        }
        levelOrder(node->left_, i-1);
        levelOrder(node->right_, i-1);
    }

    Node* insert(Node*node , const T &val)
    {
        if(node == nullptr)
        {
            return new Node(val);
        }

        if(node->data_ == val)
        {    
        }
        else if(node->data_ < val)
        {
            node->right_ = insert(node->right_ ,val);
        }
        else
        {
            node->left_ = insert(node->left_,val);
        }
        return node;
    }

    Node* quary(Node*node, const T &val)
    {
        if(node == nullptr)
        {
            return nullptr;
        }

        if(node->data_ == val)
        {
            return node;
        }
        else if(node->data_ < val)
        {
            node = quary(node->right_ ,val);
        }
        else
        {
            node = quary(node->left_,val);
        }
        return node;
    }

    Node* remove(Node*node, const T &val)
    {
        if(node == nullptr)
         {
            return nullptr;
         }

         if(node->data_ = val)
         {
            if(node->left_ != nullptr && node->right_ != nullptr)
            {
                Node *pre = node->left_;
                while (pre->right_ != nullptr)
                {
                    pre = pre->right_;
                }
                node->data_ = pre->data_;
                node->left_ = remove(node->left_ , pre->data_);
            }
            else
            {
                if(node->left_ != nullptr)
                {
                    Node *left = node->left_;
                    delete node;
                    return left;
                }
                else if(node->right_ != nullptr)
                {
                    Node *right = node->right_;
                    delete node;
                    return right;
                }
                else
                {
                    delete node;
                    return nullptr;
                }
            }
         }
         else if (node->data_ < val)
         {
            node->right_ = remove(node->right_ , val);
         }
         else
         {
            node->left_ = remove(node->left_ , val);
         }
         return node;
         
    }


    void findVals(Node*node , vector<T> &vec,int i,int j)  //[i,j]
    {
        if(node != nullptr)
        {
            if(node->data_ >i )
            {
               findVals(node->left_,vec,i,j); 
            }  

            if(node->data_ >=i && node->data_<= j)
            {
                vec.push_back(node->data_);
            }

            if(node->data_ < j)
            {
                findVals(node->right_,vec,i,j);
            }
        }
    }

    Node* getLCA(Node*node,int val1,int val2)
    {
        if(node == nullptr)
        {
            return nullptr;
        }
        else if(node->data_ > val1 && node->data_ >val2)
        {
            return getLCA(node->left_ , val1, val2);
        }
        else if (node->data_ < val1 && node->data_ < val2)
        {
            return getLCA(node->right_,val1,val2);
        }
        else
        {
            return node;
        }
        
    }

    void mirror01(Node*node)
    {
        if(node == nullptr)
        {
            return;
        }

        Node*temp = node->left_;
        node->left_ = node->right_;
        node->right_ = temp;

        mirror01(node->left_);
        mirror01(node->right_);
    }

    bool mirr02(Node*node1,Node*node2)
    {
        if(node1 == nullptr && node2 == nullptr)
        {
            return true;
        }
        if(node1 == nullptr || node2 == nullptr)
        {
            return false;
        }
        if(node1->data_ != node2->data_)
        {
            return false;
        }

        return mirr02(node1->left_,node2->right_) && mirr02(node1->right_,node2->left_);
    }

    int i = 1;
    Node* getval(Node*node,int k)
    {
        if(node == nullptr)
        {
            return nullptr;
        }
        Node *left = getval(node->right_ , k );
        if(left != nullptr)
        {
            return left;
        }

        if(i++ == k)
        {
            return node;
        }

        return getval(node->left_,k);
    }
};




void BST_test()
{
    int ar[] = {58,24,67,0,34,62,69,5,41,64,78};
    BSTtree<int> bst;
    for(int v:ar)
    {
        bst.insert(v);
    }

    cout<< bst.getval(4) <<endl;

    // cout<< bst.non_query(67) <<endl;
    bst.preOrder();
    bst.inOrder();
    bst.postOrder();
    bst.levelOrder();

    // cout<<bst.quary(67)<<endl;

    bst.non_preOrder();
    bst.non_inOrder();
    bst.non_postOrder();
    bst.non_levelOrder();

    vector<int> vec;
    bst.findVals(vec,10,60);
    for(int v:vec)
    {
        cout<<v<<" ";
    }
    cout<<endl;

    cout << bst.getLCA(67,34)<<endl;

    bst.mirror01();
    bst.inOrder();

    cout<<bst.mirr02()<<endl;
    


}

// int main()
// {
//     BST_test();
// }