//AVL树：BST+节点平衡操作：二叉平衡搜索树：搜索O（long2（n）） --不平衡趋于O（n）
//AVL树维护平衡的四种节点旋转操作：
//1.左孩子的左子树太高（child可以有两个子节点）：right——rotate
//2.右孩子的右子树太高：left_rotate (站在node的角度看)
//3.左孩子的右子树太高（child只有一个右节点）--左右旋转，先掰到同一直线，先对孩子节点调用上面的左旋，在对node调用右旋

#include<iostream>
#include<cmath>
using namespace std;

template<typename T>

class AVLTree
{
public:
    AVLTree():root_(nullptr)  {};

    //插入
    void insert(const T &val)
    {
        root_ = insert(root_,val);
    }

    //删除
    void remove(const T &val)
    {
        root_ = remove(root_,val);
    }


private:
    struct Node
    {
        Node(T data = T())
            :data_(data)
            ,left_(nullptr)
            ,right_(nullptr)
            ,height_(1)
        {}
        T data_;
        Node* left_;
        Node* right_;
        int height_;
    };
    Node* root_;
    int height(Node *node)
    {
        return node == nullptr? 0:node->height_;
    }

    //右旋转操作  
    Node*right_rotate(Node*node) //返回节点以便于改变node的父节点的指向
    {
        Node *child = node->left_;
        node->left_ = child->right_;
        child->right_ = node;

        //高度更新
        node->height_ = max(height(node->left_),height(node->right_)) + 1;
        child->height_ = max(height(child->left_),height(child->right_)) + 1;

        return child;
    }

    //左旋转操作
    Node*left_rotate(Node*node) //返回节点以便于改变node的父节点的指向
    {
        Node *child = node->right_;
        node->right_ = child->left_;
        child->left_ = node;

        //高度更新
        node->height_ = max(height(node->left_),height(node->right_)) + 1;
        child->height_ = max(height(child->left_),height(child->right_)) + 1;

        return child;
    }

    //左平衡操作  左右旋转操作
    Node*leftbalance(Node*node)
    {
        node->left_ = left_rotate(node->left_);
        return right_rotate(node);
    }

    //右平衡操作
    Node*rightbalance(Node*node)
    {
        node->right_ = right_rotate(node->right_);
        return left_rotate(node);
    }

    Node*insert(Node*node,const T &val)
    {
        if(node == nullptr)  //递归结束
        {
            return new Node(val);
        }
        if(node->data_ > val)
        {
            //递归时执行
            node->left_ = insert(node->left_,val);
            //递归回溯执行、判断是否失衡
            if(height(node->left_) - height(node->right_) > 1)
            {
                if(height(node->left_->left_) >= height(node->left_->right_))
                {
                    node = right_rotate(node);
                }
                else
                {
                    node = leftbalance(node);
                }
            }
        }
        else if(node->data_ < val)
        {
            node->right_ = insert(node->right_,val);
            if(height(node->right_) - height(node->left_) > 1)
            {
                if(height(node->right_->right_) >= height(node->right_->left_))
                {
                    node = left_rotate(node);
                }
                else
                {
                    node = rightbalance(node);
                }
            }

        }
        else
        {
            ;
        }

        //递归回溯时：检查跟新节点高度
        node->height_ = max(height(node->left_),height(node->right_)) +1;
        return node;
    }

    Node*remove(Node*node,const T &val)
    {
        if(node == nullptr)
        {
            return nullptr;
        }

        if(node->data_ > val)
        {
            node->left_ = remove(node->left_,val);
            //删除左边导致右边过高
            if(height(node->right_) - height(node->left_) > 1)
            {
                if(height(node->right_->right_) >= height(node->right_->left_))
                {
                    node = left_rotate(node);
                }
                else
                {
                    node = rightbalance(node);
                }
            }
        }
        else if(node->data_ < val)
        {
            node->right_ = remove(node->right_,val);
            if(height(node->left_) - height(node->right_) > 1)
            {
                if(height(node->left_->left_) >= height(node->left_->right_))
                {
                    node = right_rotate(node);
                }
                else
                {
                    node = leftbalance(node);
                }
            }
        }
        else
        {
            //先处理两个孩子的节点的删除
            if(node->left_ != nullptr && node->right_ != nullptr)
            {
                //为了避免删除前驱或者后继失衡，谁高删除谁
                if(height(node->left_) >= height(node->right_))
                {
                    //删前驱
                    Node*pre = node->left_;
                    while (pre->right_ != nullptr)
                    {
                        pre = pre->right_;//指向前驱
                    }
                    node->data_ = pre->data_;
                    node->left_ = remove(node->left_,pre->data_); 
                }
                else
                {
                    //删前驱
                    Node*post = node->right_;
                    while (post->left_ != nullptr)
                    {
                        post = post->left_;//指向前驱
                    }
                    node->data_ = post->data_;
                    node->right_ = remove(node->right_,post->data_); 
                }
                
            }
            else //最多一个孩子
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
                    return right;//!!!!
                }
                else
                {
                    return nullptr;
                }

            }
        }

        node->height_ = max(height(node->left_),height(node->right_))+1;

        return node;//回溯过程中把当前节点给父节点返回
    }

    
};

// int main()
// {
//     AVLTree<int> s;
//     for(int i = 0;i<10;i++)
//     {
//         s.insert(i);
//     }

//     s.remove(5);

//     return 0;
// }