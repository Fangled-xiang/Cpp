//红黑树：前提还是BST树，不是平衡树，左右高度差不超过两倍（一边一直黑，，一边红黑交替）
//只有插入和查询，选AVL树，如果删除插入查询都很多，上千万（20几层，查询很快O（long2（n））），选红黑树
//每个节点都有颜色，3.root是黑色、null空节点是黑色，4.每个叶子节点到根节点路上不能有连续的红色节点，
//5.从根节点到其每个叶子的所有简单路径都包含相同数目的黑色节点

//插入：非空必须插入红色节点（性质5），父节点为黑直接插，否则开始调整
//情况1：父亲和叔叔变成黑色，爷爷改成红色，再指向爷爷节点，继续向上调整
//情况2：叔叔是黑色，爷爷和父亲换颜色，再进行左旋(维护性质4),就可以break了
//情况3：情况2但是插在右节点，和父亲换位置，然后父亲变成左孩子，就是情况2


//删除：
//两个孩子，找前驱节点覆盖，颜色不覆盖，在删除前驱节点
//一个孩子：删的是红色，不影响，直接bst删除，黑色如下
//情况1：补上来红色，直接set黑就行（性质5），补上来黑色：从兄弟节点借
//从兄弟借：四种情况：
//情况1：兄弟黑色，兄弟右孩子红色
//情况2：兄弟黑色，兄弟左孩子红色
//情况3：兄弟以及两个孩子都是黑色，想爷爷的兄弟借，一直向上借
//情况4：兄弟红色，进行左旋，兄弟就是黑色了，然后再考虑1-3情况

#include<iostream>
using namespace std;

template<typename T>  
class RBtree
{
private:
    enum Color
    {
        BLACK,
        RED
    };
    struct Node
    {
        Node( T data=T(), Node*parent = nullptr,Node*left = nullptr, Node*right = nullptr, Color color = BLACK)
            :data_(data)
            ,parent_(parent)
            ,left_(left)
            ,right_(right)
            ,color_(color)
        {}
        T data_;
        Node* left_;
        Node* right_;
        Node* parent_;
        Color color_;
    };
    Node *root_;

    Color color(Node*node)
    {
        return node == nullptr? BLACK:node->color_;
    }
    void setcolor(Node*node,Color color)
    {
        node->color_ = color;
    }

    Node*left(Node*node)
    {
        return node->left_;
    }
    Node*right(Node*node)
    {
        return node->right_;
    }
    Node*parent(Node*node)
    {
        return node->parent_;
    }

    void leftRotate(Node*node)
    {
        Node *child = node->right_;
        child->parent_ = node->parent_;
        
        if(node->parent_ == nullptr)
        {
            root_ = child;
        }
        else 
        {
            if(node == node->parent_->left_)
            {
                node->parent_->left_ = child;
            }
            else
            {
                node->parent_->right_ = child;
            }
        }
        
        node->right_ = child->left_;
        if(child->left_ != nullptr)
        {
            child->left_->parent_ = node;
        }
        child->left_ = node;
        node->parent_ = child;
    }
    void rightRotate(Node*node)
    {
        Node *child = node->left_;
        child->parent_ = node->parent_;
        
        if(node->parent_ == nullptr)
        {
            root_ = child;
        }
        else 
        {
            if(node == node->parent_->left_)
            {
                node->parent_->left_ = child;
            }
            else
            {
                node->parent_->right_ = child;
            }
        }
        
        node->left_ = child->right_;
        if(child->right_ != nullptr)
        {
            child->right_->parent_ = node;
        }
        child->right_ = node;
        node->parent_ = child;
    }

public:
    void insert(const T &val)
    {
        if(root_ == nullptr)
        {
            root_ = new Node(val);
            return;
        }

        Node*parent = nullptr;
        Node*cur = root_;
        while (cur != nullptr)
        {
            if(cur->data_ > val)
            {
                parent = cur;
                cur = cur->left_;
            }
            else if(cur->data_ < val)
            {
                parent = cur;
                cur = cur->right_;
            }
            else
            {
                return;
            }
        }

        Node*node = new Node(val,parent,nullptr,nullptr,RED);
        if(parent->data_ > val)
        {
            parent->left_ = node;
        }
        else
        {
            parent->right_ = node;
        }

        if(RED == color(parent))
        {
            fixAfterInsert(node);
        }
    }

    void remove(const T &val)
    {
        if(root_ == nullptr)
        {
            return;
        }

        Node*cur = root_;  
        while (cur != nullptr)  //先查找
        {
            if(cur->data_ > val)
            {
                cur = cur->left_;
            }
            else if(cur->data_ < val)
            {
                cur = cur->right_;
            }
            else 
            {
                break;//找到了
            }
        }
        if(cur == nullptr) //没找到
        {
            cout<<"no find"<<endl;
            return;
        }

        //删除：
        if(cur->left_ != nullptr && cur->right_ != nullptr)
        {
            Node*pre = cur->left_;//找前驱
            while (pre->right_ != nullptr)
            {
                pre = pre->right_;
            }
            cur->data_ = pre->data_; 
            cur = pre;
        }

        //删除cur
        Node *child = cur->left_;
        if(cur->left_ == nullptr)
        {
            child = cur->right_;
        }

        if(child != nullptr)
        {
            child->parent_ = cur->parent_;
            if(cur->parent_ == nullptr)
            {
                root_ = child;
            }
            else
            {
                if(cur->parent_->left_ == cur)
                {
                    cur->parent_->left_ = child;
                }
                else
                {
                    cur->parent_->right_ = child;
                }
            }
            Color c = color(cur);
            delete cur;
            if(c == BLACK)
            {
                fixAfterRemove(child);
            }
        }
        else
        {
            if(cur->parent_ == nullptr)
            {
                delete cur;
                root_ = nullptr;
                return;
            }
            else //叶子节点、都为空
            {
                if(color(cur) == BLACK)
                {
                    fixAfterRemove(cur);
                }

                if(cur->parent_->left_ == cur)
                {
                    cur->parent_->left_ = nullptr;
                }
                else
                {
                    cur->parent_->right_ = nullptr;
                }

                delete cur;
            }
        }
        

    }


private:
    void fixAfterInsert(Node*node)
    {
        while (color(parent(node)) == RED)
        {
            if(left(parent(node)) == parent(node))
            {
                //爷爷节点的左孩子是父亲,叔叔在右边
                Node*uncle = right(parent(parent(node)));
                if(color(uncle) == RED)//情况1
                {
                    setcolor(parent(node),BLACK);
                    setcolor(uncle,BLACK);
                    setcolor(parent(parent(node)), RED);
                    node = parent(parent(node));//继续向上调整
                }
                else 
                {
                    //先处理情况3
                    if(right(parent(node)) == node)
                    {
                        node = parent(node);
                        leftRotate(parent(node));
                    }
                    //情况2
                    setcolor(parent(node),BLACK);
                    setcolor(parent(parent(node)),RED);
                    rightRotate(parent(parent(node)));
                    break;

                }

            }
            else
            {
                Node*uncle = left(parent(parent(node)));
                if(color(uncle) == RED)//情况1
                {
                    setcolor(parent(node),BLACK);
                    setcolor(uncle,BLACK);
                    setcolor(parent(parent(node)), RED);
                    node = parent(parent(node));//继续向上调整
                }
                else 
                {
                    //先处理情况3
                    if(left(parent(node)) == node)
                    {
                        node = parent(node);
                        rightRotate(parent(node));
                    }
                    //情况2
                    setcolor(parent(node),BLACK);
                    setcolor(parent(parent(node)),RED);
                    leftRotate(parent(parent(node)));
                    break;

                }

            }
        }
        //强制root为black
        setcolor(root_,BLACK);
    }

    void fixAfterRemove(Node*node)
    {
        while (color(node) == BLACK)
        {
            if(left(parent(node)) == node)
            {
                Node*brother = right(node);
                if(color(brother) == RED)  //情况4
                {
                    setcolor(parent(node),RED);
                    setcolor(brother,BLACK);
                    leftRotate(parent(node));
                    brother = right(parent(node));
                }

                if(color(left(brother)) == BLACK  &&  color(right(brother))== BLACK)
                {
                    setcolor(brother,RED);
                    node = parent(node);
                }
                else
                {
                    if(color(right(brother) ) != RED)
                    {
                        setcolor(brother,RED);
                        setcolor(left(brother),BLACK);
                        rightRotate(brother);
                        brother = right(parent(node));
                    }
                    else//全部归结情况1
                    {
                        setcolor(brother,color(parent(node)));
                        setcolor(parent(node),BLACK);
                        setcolor(right(brother),BLACK);
                        leftRotate(parent(node));
                        break;
                    }
                }
            }
            else
            {
                Node*brother = left(node);
                if(color(brother) == RED)  //情况4
                {
                    setcolor(parent(node),RED);
                    setcolor(brother,BLACK);
                    rightRotate(parent(node));
                    brother = left(parent(node));
                }

                if(color(right(brother)) == BLACK  &&  color(left(brother))== BLACK)
                {
                    setcolor(brother,RED);
                    node = parent(node);
                }
                else
                {
                    if(color(left(brother) ) != RED)
                    {
                        setcolor(brother,RED);
                        setcolor(right(brother),BLACK);
                        leftRotate(brother);
                        brother = left(parent(node));
                    }
                    else//全部归结情况1
                    {
                        setcolor(brother,color(parent(node)));
                        setcolor(parent(node),BLACK);
                        setcolor(left(brother),BLACK);
                        rightRotate(parent(node));
                        break;
                    }
                }
            }
        }

        setcolor(node,BLACK);
        
    }


public:
    RBtree():root_(nullptr){}

};



// int main()
// {
//     int ar[] = {58,24,67,0,34,62,69,5,41,64,78};
//     RBtree<int> rbt;
//     for(int v:ar)
//     {
//         rbt.insert(v);
//     }

//     rbt.remove(34);
//     rbt.remove(34);


// }
