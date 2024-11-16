#include<iostream>
#include<unistd.h>
#include<sys/wait.h>
#include<string>
#include<cstring>
using namespace std;

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        cout << "There is Error in command line argument\n";
        return 0;
    }
    else
    {
        //Step1
        int n = stoi(argv[1]);

        cout << "The number (n) is: " << n << endl;
        if (n < 0)
        {
            cout << "The conjecture is only apllicable to positive numbers :( \n";
            return 0;
        }
        bool check = false;
        int fd[2];
        int fd2[2];

        int rc = pipe(fd);
        int rc2 = pipe(fd2);
        if (rc < 0)
        {
            perror("pipe");
            exit(1);
        }
        if (rc2 < 0)
        {
            perror("pipe2");
            exit(1);
        }

        int status;


        int num = n;
        while (1)
        {


            //step4
            int pid = fork();
            if (pid < 0)
            {
                perror("Fork");
                exit(1);
            }

            //step2

            if (pid == 0)
            {
                //Child

                int no;
                //Child redaing data from parent
                read(fd[0], &no, sizeof(int));
                if ((no % 2) != 0)
                {
                    no = ((3 * no) + 1);
                }

                else
                {
                    no = (no / 2);
                }
                cout << no << " ";
                write(fd2[1], &no, sizeof(int));
                exit(0);
            }

            //step3

            if (pid > 0)
            {
                //parent

                write(fd[1], &num, sizeof(int));
                wait(&status);
                read(fd2[0], &num, sizeof(int));

                if (num == 1)
                {

                    close(fd[1]);
                    close(fd2[0]);
                    cout << endl;
                    break;
                }
                if (num < 0)
                {
                    close(fd[1]);
                    close(fd2[0]);
                    cout << "CAUTION: WORNG SIZE INPUT! \n";
                    break;
                }

            }
        }
    }


    return 0;
}