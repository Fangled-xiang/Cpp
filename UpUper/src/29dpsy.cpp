/*
    倒排索引：常用于搜索引擎、百度、微软、
        淘宝、天猫、拼多多（不可能直接在MYSQL里面进行数据搜索）、solr、elasticsearch开源的全文搜索引擎
        由单词的集合“词典”，  倒排列表的集合“倒排文件”组成
        存储方式：内存索引和 B+树

    全文搜索的两种方法：
        匹配搜索：KMP、BF
        利用索引进行全文搜索

    正排索引：统计一页P1里面，每个词的个数
    倒排索引结构：行列相反，即一个词出现在那些page里面，显示排的顺序可以根据频率、优先级等进行打分然后排序

        如：keywords1（单词）：  P1、P2（倒排列表）   
            Keywords2：             P2               P1（倒排项）可以包含频率、位置等信息，Keywords的集合就是词典
              词典                倒排文件

    搜索单个word：在词典里查找word
    搜索一个句子： 分词再搜索、求结果的交集、给搜索结果打分并排序展示
*/


#include<iostream>
#include<string>
#include<unordered_map>  //哈希无规则的索引、map是有序索引
#include<list>
#include<vector>
#include<queue>
using namespace std;

#include<DataStruct.h>

struct InverTerm //倒排项
{
    InverTerm(string docid,int freqs,int location)
        :docid_(docid)
        ,freqs_(freqs)
    {
        locations_.emplace_back(location);
    }
    string docid_;  //文档P1
    int freqs_;
    list<int> locations_;
};


class InvertList//倒排列表
{
private:
    list<InverTerm> termlist_;  

public:
    //添加倒排项
    void addTerm(string docid, int location)
    {
        for(auto &term :termlist_)
        {
            if(term.docid_ == docid)  //倒排项已经已经创建了
            {
                term.freqs_ ++;
                term.locations_.emplace_back(location);
                return;
            }
        }

        termlist_.emplace_back(docid , 1,location);  //emplace_back可以调用构造函数，而pushback只是拷贝
    }
    
    //获取倒排列表内存
    const list<InverTerm>& getInvertList() const
    {
        return termlist_;
    }


};


class InvertIndex  //倒排索引(全部文件：词典+列表文件)
{
private:
    string suffix_; //过滤文档后缀 .cpp .cc .ccxx .c
    unordered_map<string,InvertList> invertMap_; 
    list<string> fileList_; //所有需要建立倒排的文件


public:
    void setSearchPath(const char* path)
    {
        cout<< "getallfiles..." << endl;
        fileList_ = getallfiles(path);
        // for(auto& filepah:fileList_)
        // {
        //     cout << filepah <<endl;
        // }
        cout << "finish..." <<endl;

        cout << "createInvertIndex..." <<endl;
        createInvertIndex();
        cout << "finish..." <<endl;
    }

    void query(string phrase)
    {
        //先分词
        vector<string> wordList;
        char *word = strtok(const_cast<char*>(phrase.c_str()), " ");
        while (word != nullptr)
        {
            word = trim(word);
            if(strlen(word) > 0)
            {
                wordList.emplace_back(word);
            }
            word = strtok(nullptr, " ");
        }

        if(wordList.empty())
        {
            return;
        }
        
        if(wordList.size()==1)
        {
            auto it = invertMap_.find(wordList[0]);
            if(it == invertMap_.end())
            {
                cout<< " no find "<<endl;
                return;
            }

            for(auto& term :it->second.getInvertList())
            {
                cout << term.docid_ << "  freques: " << term.freqs_<<endl;
            }
        }
        else
        {
                cout<<".....pass!"<<endl;
        }
    }

private:
    //创建倒排索引结构
    void createInvertIndex()
    {
        for(string & filepah:fileList_)
        {
            cout << " . ";
            FILE* pf = fopen(filepah.c_str(),"r");
            if(pf == nullptr)
            {
                cout << "err!!" <<endl;
                continue;
            }


            //按行读取内容，按空格进行分词
            vector<string> wordlist;
            int location = 0;
            const int LINE_SIZE = 2048;
            char line[LINE_SIZE] = {0};

            while(!feof(pf))
            {
                fgets(line,LINE_SIZE,pf);

                //按行按“空格分词”
                char * word = strtok(line , " ");
                while (word != nullptr)
                {
                    word = trim(word);//过滤\t \n等
                    if(strlen(word) > 0)
                    {
                       wordlist.emplace_back(word);
                    }
                    
                    word = strtok(nullptr," ");
                }

                //给wordList里面单词创建倒排列表
                for(string &w:wordlist)
                {
                    location ++;
                    auto it = invertMap_.find(w);
                    if(it == invertMap_.end())
                    {
                        InvertList list;
                        list.addTerm(filepah,location);
                        invertMap_.emplace(w,list);
                    }
                    else
                    {
                        it->second.addTerm(filepah,location);
                    }
                 }
                
            }
            
            fclose(pf);
        }
        cout <<endl;
    }

    list<string> getallfiles(const char *dir) 
    { 
        _chdir(dir); 
        
        //首先查找dir中符合要求的文件 
        long hFile; 
        _finddata_t fileinfo; 
        list<string> filelist_;
        if ((hFile=_findfirst("*.*",&fileinfo)) != -1) 
        { 
            do 
            { 
            if (!(fileinfo.attrib & _A_SUBDIR)) 
            { 
                char filename[_MAX_PATH]; 
                strcpy(filename, "E:\\VScode\\Code\\UPUPUP\\src\\");
                strcat(filename,fileinfo.name); 

                string str;
                str = filename;

                filelist_.emplace_back(str);


            } 
            } while (_findnext(hFile,&fileinfo) == 0); 
            _findclose(hFile); 
        } 
        return filelist_;
    }

    char* trim(char* word)
    {
        int i =0;
        while (word[i] != '\0')
        {
            if(word[i] == ' ' || word[i] == '\t' || word[i] =='\n')
            {
                i++;
            }
            else
            {
                break;
            }

            int j = i;
            while (word[j] != '\0')
            {
                if(word[j] == ' ' || word[j] == '\t' || word[j] =='\n')
                {
                    break;
                }
                j++;
            }
            word[j] = '\0';
        }
        return word+i;
    }
    
};


int main()
{
    InvertIndex index;
    index.setSearchPath("E:\\VScode\\Code\\UPUPUP\\src");

    while (1)
    {
        char buf[128];
        cout <<"search:  ";
        cin.getline(buf,128);
        index.query(buf);
    }
}
