#include<iostream>
#include<string>

using namespace std;

template<typename T>
void sort(T arr[],int size)
{
    for(int i =0;i<size ;i++)
    {
        T max = arr[i];
        int k = i;

        for(int j=i+1;j<size;j++)
        {
            if(max < arr[j])
            {
                max = arr[j];
                k = j;
            }
        }

        if(k != i)
        {
            arr[k] = arr[i];
            arr[i] = max;
        }
    }

    for(int i=0;i<size;i++)
    {
        cout<< arr[i] <<" ";
    }
    cout<<endl;
}


/*
int main()
{
    int arr1[] = {15,44,75,2,54,36,4,78,52,55,12,22};
    char arr2[] = {'x','s','a','g','b'};


    int size = sizeof(arr2) / sizeof(char);
    sort(arr2,size);

}*/