#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// OZGE ONEYMAN 24906

int main()
{
	ifstream inFile;
	char ch;
	int count=0;
	inFile.open("loremipsum.txt");

	while (!inFile.eof())
	{
		inFile.get(ch);
		if (ch== 'a')
		{
			count ++;
		}

	}
	cout << "Number of occurrence of character 'a' in the file: " << count << endl;
	inFile.close();

	return 0;
}