#include<iostream>
#include<string>

using namespace std;

class Person
{
public:
    Person()  //一定要有才行，不能只有有参构造
        :name_("name")
        ,age_(18)
    {}

    Person(string name  ,int age)
        :name_(name)
        ,age_(age)
    {}


public:
    string name_;
    int age_;

};


template<typename T>
class myarray
{

public:
    myarray(int size = 10)
        :size_(size)
        ,cur_(0)
    {
        myarr = new T[size];
    }

    ~myarray()
    {
        delete[] myarr;
        myarr = nullptr;
    }

    myarray(const myarray &arr)   //深拷贝
    {
        this->size_ = arr.size_;
        this->cur_ = arr.cur_;

        this->myarr = new T[arr.size_];

        for(int i =0;i<this->size_;i++)
        {
            this->myarr[i] = arr.myarr[i];
        }

    }


    myarray& operator=(const myarray &arr)
    {
        this->size_ = arr.size_;
        this->cur_ = arr.cur_;

        this->myarr = new T[arr.size_];

        for(int i =0;i<this->size_;i++)
        {
            this->myarr[i] = arr.myarr[i];
        }
    }


public:
    void push_back(const T &val)
    {
        if(size_ == cur_)
        {
            return;
        }
        myarr[cur_] = val;
        cur_ ++;
    }

    void pop_back()
    {
        if(cur_ == 0)
        {
            return;
        }

        cur_--;
    }

    T& operator[] (int index)
    {
        return myarr[index];
    }

    int get_count()
    {
        return cur_;
    }

    int get_cap()
    {
        return size_;
    }

private:
    int size_;
    T* myarr;
    int cur_;

};









template<class T>
void printMyarr(myarray<T> arr)
{
    for(int i =0;i<arr.get_count();i++)
    {
        cout << arr[i].name_ << "-"<<arr[i].age_ <<" ";
    }
    cout<<endl;
}


/*
int main()
{
    // myarray<int> arr1;
    // arr1.push_back(12);
    // arr1.push_back(8);

    // myarray<int> arr2 = arr1;
    // myarray<int> arr3(arr2);

    // myarray<int> arr4(20);
    // arr4 = arr3;


    // printMyarr(arr4);


    myarray<Person> arr;

    Person p1("lll",18);
    Person p2("kkk",20);

    arr.push_back(p1);
    arr.push_back(p2);

    myarray<Person> arr2 = arr;
    printMyarr(arr2);

}*/