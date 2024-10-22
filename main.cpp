#include<main.h>

/*--------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
//vector容器
#include<vector>
void test_vector()
{
    vector<Person> vec;
    vec.emplace_back("guo", 35,175);   //默认构造插入

    vec.push_back(p1);
    vec.push_back(p2);
    vec.push_back(p3);

    sort(vec.begin(),vec.end(), [](auto &a, auto &b) ->bool{return a.age_ <b.age_;});  //sort算法对自定义类型数据的自定义排序

    for(auto v:vec)
    {
        cout << v.name_ << "  "<<v.age_<< "  "<< v.height_<<endl;
    }
}



/*--------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
//priority_que容器
#include<queue>
void test_que()
{
    priority_queue<int> que1;
    priority_queue<int, vector<int>,  greater<> >   que2;   //默认大根堆改成小根堆、自建类型直接传入grater<>就行

    priority_queue< Person,  vector<Person>, mycompare >  q;   //对于自定义类型数据需要传入一个自定义的比较器对象、自定义排序方式的最后一个会成为堆顶
    q.emplace("guo",35,175);  
   
    q.push(p1);
    q.push(p2);
    
    while(!q.empty())
    {
        auto v = q.top();
        cout << v.name_ << "  "<<v.age_<< "  "<< v.height_<<endl;
        q.pop();
    }
}


/*--------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
//unorder_map/map容器 = set容器+pair键值对 (具体应用可参考31哈夫曼编码)
#include<unordered_map>
#include<map>
void test_map()
{
    map< int, Person, greater<int> > m;  //自定义类型根据pair的key进行构造二叉树

    m.insert(  pair<int, Person>(11, p1)  );
    m.insert( make_pair(15, p2) );
    m.emplace(9, Person("guo",35,175) );  //带参构造以及临时对象

    m[22] = p3;     //!!注意，一定要在Person类中加上Person（）{}的默认构造！！！

    cout << m[15].name_ <<endl <<endl;    //获取值

    for(auto s : m)
    {
    cout<<"key: "<<s.first<<"   "<< s.second.name_ << "--" << s.second.age_ << "--" << s.second.height_<<endl;
    }
}


/*--------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
//最常用文件操作
#include<fstream>
#include <sstream>
string path = "E:\\VScode\\Code\\UPUPUP\\src\\36bian.txt";  //必须是绝对路径
void test_file(const string path)  //记得要加const
{
    ifstream ifs;
    ifs.open(path.c_str(),ios::in);

    string line;
    while (getline(ifs, line)) 
    {
        char c1 = line[0];
        int s=static_cast<int>(c1); //按行读取，提取行字符串的某一个，强制转换


        stringstream ss(line);
        string val;
        vector<string> data;
        while (getline(ss, val, ','))    //分隔符拆分
        {
            data.push_back(val);
        }

        cout<< data[0] <<" "<<data[1] <<  stoi(data[2]) <<endl;  //字符串sto..的数据类型转换

    }
    ifs.close();
}


/*--------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
int main()
{
    test_map();
    // test_file(path);
}