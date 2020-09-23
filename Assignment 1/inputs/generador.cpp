#include <iostream>
#include <random>

using namespace std; 

void print(int *arr,int size)
{
    for( int i=0;i<size;i++)
        std::cout << arr[i] << " ";
}

void generator(int length)
{
    cout << length << endl;
    for ( int i = 0 ; i < length ; i++)
        cout <<  rand()%length+1 << " ";
}


int main(){
    int len;
    cin >>  len;
    generator(len);
    return 0;
}