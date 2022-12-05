#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>

/*****************************
* Split a given string by a 
* given character
******************************/
void splitByChar(std::vector<std::string>& splitInto, std::string splitFrom, const char character)
{
	std::stringstream ssOne(splitFrom);

	while (ssOne.good())
	{
		std::string temp;
		std::getline(ssOne, temp, character);
		splitInto.push_back(temp);
	}
}

/*****************************
* Determines if the given string
* has assignments fully covered
* by either side
******************************/
bool hasFullOverlap(std::string assignments)
{
	std::vector<std::string> split;
	std::vector<std::string> firstAssignment;
	std::vector<std::string> secondAssignment;

	splitByChar(split, assignments, ',');

	splitByChar(firstAssignment, split[0], '-');

	splitByChar(secondAssignment, split[1], '-');

	if ((stoi(firstAssignment[0]) <= stoi(secondAssignment[0]) && stoi(firstAssignment[1]) >= stoi(secondAssignment[1])) ||
		(stoi(firstAssignment[0]) >= stoi(secondAssignment[0]) && stoi(firstAssignment[1]) <= stoi(secondAssignment[1])))
		return true;

	return false;
}

/*****************************
* Determines if the given string
* has assignments partially covered
* by either side
******************************/
bool hasPartialOverlap(std::string assignments)
{
	std::vector<std::string> split;
	std::vector<std::string> firstAssignment;
	std::vector<std::string> secondAssignment;

	splitByChar(split, assignments, ',');

	splitByChar(firstAssignment, split[0], '-');

	splitByChar(secondAssignment, split[1], '-');

	if ((stoi(firstAssignment[0]) >= stoi(secondAssignment[0]) && stoi(firstAssignment[0]) <= stoi(secondAssignment[1])) ||
		(stoi(firstAssignment[1]) >= stoi(secondAssignment[0]) && stoi(firstAssignment[1]) <= stoi(secondAssignment[1])) ||
		(stoi(secondAssignment[0]) >= stoi(firstAssignment[0]) && stoi(secondAssignment[0]) <= stoi(firstAssignment[1])) ||
		(stoi(secondAssignment[1]) >= stoi(firstAssignment[0]) && stoi(secondAssignment[1]) <= stoi(firstAssignment[1])))
		return true;

	return false;
}

/*****************************
* Main will read in the text
* file and display the results
******************************/
int main() {

	std::ifstream assignmentsFile("assignments.txt");
	std::string line;
	int fullOverlapPairs = 0;
	int partialOverlapPairs = 0;
	

	if (assignmentsFile.is_open())
	{
		while (getline(assignmentsFile, line))
		{
			fullOverlapPairs += hasFullOverlap(line);
			partialOverlapPairs += hasPartialOverlap(line);
		}
	}
	else
	{
		std::cout << "Error opening file." << std::endl;
		return 0;
	}

	std::cout << "Total Full Overlapping Assignments: " << fullOverlapPairs << std::endl;
	std::cout << "Total Partial Overlapping Assignments: " << partialOverlapPairs << std::endl;
}