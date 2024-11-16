#include<iostream>
#include<unistd.h>
#include<pthread.h>
#include<climits>
using namespace std;




void* fibonacci(void* param)
{

    int n = *(int*)param;

    int* fib = new int[n];
    fib[0] = 0, fib[1] = 1;
    int n1 = 0, n2 = 1;
    for (int i = 2; i < n; ++i)
    {

        fib[i] = n1 + n2;

        n1 = n2;
        n2 = fib[i];
    }
    return (void*)fib;
}


int main(int  argc, char* argv[])
{

    if (argc < 1)
    {
        cout << "Invalid argument list\n";
        return 0;
    }

    else
    {
        int  n = stoi(argv[1]);
        pthread_t pid1;
        pthread_create(&pid1, NULL, &fibonacci, &n);

        int* arr;
        pthread_join(pid1, (void**)&arr);

        for (int i = 0; i < n; i++)
        {
            cout << arr[i] << " ";
        }


        cout << endl;








        return 0;
    }


}























