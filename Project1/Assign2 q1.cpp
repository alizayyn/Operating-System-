#include<iostream>
#include<unistd.h>
#include<pthread.h>
#include<climits>
using namespace std;

float avg = 0;
int  Min = INT_MAX;
int Max = INT_MIN;


struct Arr {
    int* Array;
    int size;

};



void* average(void* param)
{

    Arr temp = *(Arr*)param;

    for (int i = 0; i < temp.size; i++)
    {
        avg = avg + temp.Array[i];

    }
    avg = avg / temp.size;

    return (void*)NULL;


}

void* minimum(void* param)
{
    Arr temp = *(Arr*)param;
    for (int i = 0; i < temp.size; i++)
    {
        if (Min > temp.Array[i])
        {
            Min = temp.Array[i];
        }
    }
    return (void*)NULL;

}

void* maximum(void* param)
{
    Arr temp = *(Arr*)param;

    for (int i = 0; i < temp.size; i++)
    {
        if (Max < temp.Array[i])
        {
            Max = temp.Array[i];
        }
    }
    return (void*)NULL;

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
        //int * arr = new int [argc-1];

        Arr arr;
        arr.Array = new int[argc - 1];
        arr.size = argc - 1;
        for (int i = 0; i < argc - 1; i++)
        {
            arr.Array[i] = stoi(argv[i + 1]);
        }

        cout << "Int arr: ";

        for (int i = 0; i < argc - 1; i++)
        {
            cout << arr.Array[i] << " ";
        }
        cout << endl;

        pthread_t pid1, pid2, pid3;

        pthread_create(&pid1, NULL, &average, &arr);
        pthread_join(pid1, NULL);
        cout << "The average of the arr is : " << avg << endl;

        pthread_create(&pid2, NULL, &minimum, &arr);
        pthread_join(pid2, NULL);
        cout << "The minimum of the arr is : " << Min << endl;

        pthread_create(&pid3, NULL, &maximum, &arr);
        pthread_join(pid3, NULL);
        cout << "The maximum of the arr is : " << Max << endl;


    }








    return 0;
}

























