#include<iostream>
#include<string>
#include<unistd.h>
#include<cstring>
#include<sys/wait.h>
#include<fcntl.h>
using namespace std;



//Custom Shell

void Display(char** str, int size)
{
	for (int i = 0; i < size; i++)
	{
		cout << str[i];
		cout << endl;
	}
}


int WordCount(char* str)
{
	int count = 0;
	for (int i = 0; str[i] != '\0'; i++)
	{
		if (str[i] == ' ' || str[i + 1] == '\0')
		{
			count++;
		}
	}
	return count;
}

int strlength(char arr[])
{
	int count = 0;
	for (int i = 0; arr[i] != '\0'; i++)
	{
		count++;
	}
	return count;

}
void strcopy(char destination[], char source[])
{
	//Deep copy.
	int i = 0;
	for (; source[i] != '\0'; i++)
	{
		destination[i] = source[i];
	}
	destination[i] = '\0';
}



char** StringTokens(char* str)
{
	int l = strlength(str);
	int w = WordCount(str);
	char** Toks = new char* [w];
	char temp[20];
	int k = 0;
	int i = 0;
	for (; i < w; i++)
	{
		for (int j = 0; str[k] != '\0'; j++)
		{
			if (str[k] != ' ' && str[k] != '<' && str[k] != '>' && str[k] != '\0')
			{
				temp[j] = str[k];
				k++;
			}

			if (str[k] == '&')
			{
				temp[j + 1] = '\0';
				break;
			}

			else if (str[k] == '<')
			{
				temp[j + 1] = '\0';
				k++;

				while (str[k] != ' ' && str[k] != '>' && str[k] != '\0')
				{
					temp[j++] = str[k];
					k++;
				}
				temp[j] = '\0';
				int fd = open(temp, O_RDONLY, 0666);
				dup2(fd, 0);// stdin (0) is replaced by fd 

			}

			else if (str[k] == '>')
			{

				temp[j + 1] = '\0';
				k++;

				while (str[k] != ' ' && str[k] != '<' && str[k] != '\0')
				{
					temp[j++] = str[k];
					k++;
				}
				temp[j] = '\0';
				int fd = open(temp, O_WRONLY | O_CREAT | O_TRUNC, 0666);
				dup2(fd, 1);// stdin (0) is replaced by fd 

			}
			else if (str[k] == ' ' || str[k] == '\0')
			{

				temp[j + 1] = '\0';
				k++;
				break;
			}


		}
		int s = strlength(temp) + 1;
		Toks[i] = new char[s];
		strcopy(Toks[i], temp);
	}
	Toks[i] = NULL;
	return Toks;
}




bool checkflag(char arr[], int l)
{
	if (arr[l] == '&')
	{
		cout << "Done[" << getpid() << "]\n";
		return true;
	}
	else
	{
		return 0;
	}


}





int main()
{
	//input of the command in the char arr

	char input[100];
	// char *buf;
	//buf=(char *)malloc(10*sizeof(char));
	//buf=getlogin();

	while (1)
	{

		cout << "\nEnter the command $ ";

		cin.getline(input, 100);
		if (input[0] == 'e' && input[1] == 'x' && input[2] == 'i' && input[3] == 't')
		{
			break;
		}

		int l1 = strlen(input);

		// checking if there is any & in the string
		bool status_ = checkflag(input, l1 - 1);





		int retid = fork();
		int status;



		if (retid < 0)
		{
			//Error

			perror("Child not forked");
			exit(1);
		}

		else if (retid == 0)
		{

			//child

			//cout<<"\n\nTokkens: "; 
			// Tokkenization of command

			char** arguments = StringTokens(input);
			//int wc=WordCount(input);
			//Display(arguments,wc);
			int err = execvp(arguments[0], arguments);
			if (err < 0)
			{
				perror("Command/args: ");
				exit(1);
			}
			exit(0);
		}


		else if (retid > 0)
		{
			//parent

			if (status_ == false)
			{
				wait(&status);
			}



		}

	}
	return 0;
}