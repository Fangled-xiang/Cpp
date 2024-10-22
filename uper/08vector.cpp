#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;



class Person
{
public:
    Person()
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


void test01()
{
    vector<Person> vec;

    Person p1("fang",18);
    Person p2("liu",20);
    Person p3("hu",15);


    vec.push_back(p1);
    vec.push_back(p2);
    vec.push_back(p3);

    for(auto v:vec)
    {
        cout << v.name_ << "-"<<v.age_ <<" "<<endl;
    }
}


void test02()
{
    vector<vector<int>> vec;//类似于二维数组

    vector<int> v1;
    vector<int> v2;
    vector<int> v3;
    vector<int> v4;

    int i = 1;
    v1.push_back(i++);
    v2.push_back(i++);
    v3.push_back(i++);
    v4.push_back(i++);

    vec.push_back(v1);
    vec.push_back(v2);
    vec.push_back(v3);
    vec.push_back(v4);

    for(auto v:vec)
    {
        for(auto i:v)
        {
            cout<<i<<" ";
        }
        cout <<endl;
    }

}


void test03()
{
    vector<int> vec1;

    for(int i =0;i<9;i++)
    {
        vec1.push_back(i);
    }


    vector<int> vec2(vec1);  //拷贝构造

    vec1 = vec2;  //operator =

    vec1.empty();
    vec1.size() <= vec1.capacity()  ;

    vec1.resize(15,  0);

    for(auto i:vec1)
    {
        cout<< i <<" ";
    }
    cout<<endl;

    vec1.resize(5); //变短直接删除末尾，变成以0来填充

    for(auto i:vec1)
    {
        cout<< i <<" ";
    }
    cout <<endl;


    vec1.swap(vec2);  //互换操作

    //容量只会变大不会变小、删除/resize掉数据之后，容量不会减小
    //巧用swap进行空间的收缩，swap会自动收缩内存
    vector<int>(vec1).swap(vec1);   //匿名对象会自动回收析构

    vector<int>  v3;
    v3.reserve( 10 );  //分配了内存但是没有值、减少分配内存的次数


}


void test04()
{
    vector<int> vec1(5,5);

    //第一个参数是迭代器
    vec1.insert(vec1.begin()  +3 ,  100);
    vec1.insert(vec1.end()  -1 , 50);

    for(auto i:vec1)
    {
        cout<< i <<" ";
    }
    cout<<endl;


    cout<< vec1.front()<<endl;
    cout << vec1.back()<<endl;   //begin和end是迭代器，注意区别

    vec1[3] = 555;
    cout<<"3::   " <<vec1[3] << endl;



}



int main()
{
    test01();  //自定义类型容器
    test02();  //容器嵌套容器

    test03();  //赋值、容量大小、互换、预留空间

    test04();  //插入、删除 insert\erease（迭代器参数：例如  vec.begin()+3   、数据存取（【】或者at）


}









