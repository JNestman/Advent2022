#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <deque>

int main() {

	std::ifstream assignmentsFile("signal.txt");
	std::string line;
	std::deque<char> signal;
	int numCharacters = 0;

	if (assignmentsFile.is_open())
	{
		while (getline(assignmentsFile, line))
		{
			for (int i = 0; i < line.size(); i++)
			{
				signal.push_back(line[i]);

				if (signal.size() > 13)
				{
					for (int outer = 0; outer < signal.size(); outer++)
					{
						for (int inner = outer + 1; inner < signal.size(); inner++)
						{
							if (signal[inner] == signal[outer])
							{
								goto outOfLoop;
							}
						}
					}

					numCharacters = i + 1;
					break;

					outOfLoop:
					signal.pop_front();
				}
			}
		}
	}
	else
	{
		std::cout << "Error opening file." << std::endl;
		return 0;
	}

	std::cout << "We processed " << numCharacters << " to find the start of packet marker." << std::endl;
}