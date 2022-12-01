#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main() {

	std::ifstream caloriesFile("calories.txt");
	std::string line;
	std::vector<std::vector<std::string>> elvesCalories;

	if (caloriesFile.is_open())
	{
		std::vector<std::string> elfLoad;

		while (getline(caloriesFile, line))
		{
			if (line.empty())
			{
				elvesCalories.push_back(elfLoad);
				elfLoad.clear();
			}
			else
			{
				elfLoad.push_back(line);
			}
		}

		caloriesFile.close();
	}

	int mostCalories = 0;
	int elfChad = 0;
	std::vector<int> topThree;
	

	for (int elf = 0; elf < elvesCalories.size(); elf++)
	{
		int elfTotal = 0;

		for (int load = 0; load < elvesCalories[elf].size(); load++)
		{
			elfTotal += std::stoi(elvesCalories[elf][load]);
		}

		if (topThree.empty())
		{
			topThree.push_back(elfTotal);
		}
		else
		{
			for (std::vector<int>::iterator it = topThree.begin(); it != topThree.end(); it++)
			{
				if ((*it) < elfTotal)
				{
					topThree.insert(it, elfTotal);

					if (topThree.size() > 3)
						topThree.pop_back();

					break;
				}
			}
		}

		if (elfTotal > mostCalories)
		{
			mostCalories = elfTotal;
			elfChad = elf;
		}
	}


	std::cout << "Elf #" << elfChad << " with " << mostCalories << " calories" << std::endl;
	std::cout << "Top three elves total: " << topThree[0] + topThree[1] + topThree[2] << std::endl;
	return 0;
}