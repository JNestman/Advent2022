#include <iostream>
#include <fstream>
#include <string>
#include <vector>

/*****************************************************
* Find the common character between the split entries
* and add the priorities up
******************************************************/
int splitTotal(std::vector<std::string> firstCompartment, std::vector<std::string> secondCompartment, std::vector<char> priorityMap)
{
	int prioritySum = 0;

	for (int count = 0; count < firstCompartment.size(); count++)
	{
		bool found = false;

		for (int firstLoop = 0; firstLoop < firstCompartment[count].length(); firstLoop++)
		{
			for (int secondLoop = 0; secondLoop < secondCompartment[count].length(); secondLoop++)
			{
				if (firstCompartment[count][firstLoop] == secondCompartment[count][secondLoop])
				{
					prioritySum += std::find(priorityMap.begin(), priorityMap.end(), firstCompartment[count][firstLoop]) - priorityMap.begin() + 1;

					found = true;
					break;
				}
			}

			if (found)
				break;
		}
	}

	return prioritySum;
}

/*****************************************************
* Find the common character between the three entries
* and add the priorities up
******************************************************/
int trioTotal(std::vector<std::string> trios, std::vector<char> priorityMap)
{
	if (trios.size() != 3)
	{
		std::cout << "trios is size " << trios.size() << " and not 3." << std::endl;
		return 0;
	}

	int trioSum = 0;

	for (int firstLoop = 0; firstLoop < trios[0].size(); firstLoop++)
	{
		for (int secondLoop = 0; secondLoop < trios[1].size(); secondLoop++)
		{
			if (trios[0][firstLoop] == trios[1][secondLoop])
			{
				for (int thirdLoop = 0; thirdLoop < trios[2].size(); thirdLoop++)
				{
					if (trios[0][firstLoop] == trios[2][thirdLoop])
					{
						trioSum += std::find(priorityMap.begin(), priorityMap.end(), trios[0][firstLoop]) - priorityMap.begin() + 1;
						return trioSum;
					}
				}
			}
		}
	}

	std::cout << "trios not found" << std::endl;

	return trioSum;
}

/*****************************************************
* Main will read in the text file and split it
* accordingly
******************************************************/
int main() {

	std::ifstream outcomeFile("rucksack.txt", std::fstream::in);
	std::string line;
	std::vector<std::string> firstCompartment;
	std::vector<std::string> secondCompartment;
	std::vector<std::string> trios;
	std::vector<char> priorityMap = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
									'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };
	int trioSum = 0;

	if (outcomeFile.is_open())
	{
		while (getline(outcomeFile, line))
		{
			firstCompartment.push_back(line.substr(0, line.length() / 2));
			secondCompartment.push_back(line.substr(line.length() / 2));

			trios.push_back(line);

			if (trios.size() == 3)
			{
				trioSum += trioTotal(trios, priorityMap);
				trios.clear();
			}
		}
	}
	else
	{
		std::cout << "Error opening file." << std::endl;
		return 0;
	}

	std::cout << "Sum of split rucksack priorities: " << splitTotal(firstCompartment, secondCompartment, priorityMap) << std::endl;
	std::cout << "Sum of trio rucksack priorities: " << trioSum << std::endl;


	return 0;
}