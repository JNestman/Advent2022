#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>

/*****************************
* A simple struct to hold our
* commands
******************************/
struct commands {
	int numMove;
	int moveFrom;
	int moveTo;
};

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
* Put everything in their starting
* positions
******************************/
std::stack<char> initializeStacks(std::vector<char> contents)
{
	std::stack<char> myStack;
	for (int i = contents.size(); i > 0; i--)
	{
		myStack.push(contents[i - 1]);
	}

	return myStack;
}

/*****************************
* Extract the numbers and assign
* them their purpose
******************************/
commands extractCommands(std::string assignments)
{
	std::vector<std::string> split;
	commands thisLine;
	thisLine.numMove = 0;
	thisLine.moveFrom = 0;
	thisLine.moveTo = 0;

	splitByChar(split, assignments, ' ');

	for (int i = 0; i < split.size(); i++)
	{
		for (int j = 0; j < split[i].length(); j++)
		{
			if (std::isdigit(split[i][j]))
			{
				if (!thisLine.numMove)
					thisLine.numMove = std::stoi(split[i]);
				else if (!thisLine.moveFrom)
					thisLine.moveFrom = std::stoi(split[i]);
				else
					thisLine.moveTo = std::stoi(split[i]);

				break;
			}
			else
				break;
		}
	}

	return thisLine;
}

/*****************************
* We will move contents of the
* stacks according to the
* instructions we've recieved
******************************/
void executeCommands(std::vector<std::stack<char>>& stacks, std::vector<commands> myCommands, bool multiStack)
{
	for (int command = 0; command < myCommands.size(); command++)
	{
		if (multiStack)
		{
			std::stack<char> temp;
			for (int numPushes = 0; numPushes < myCommands[command].numMove; numPushes++)
			{
				temp.push(stacks[myCommands[command].moveFrom - 1].top());
				stacks[myCommands[command].moveFrom - 1].pop();
			}

			while (!temp.empty())
			{
				stacks[myCommands[command].moveTo - 1].push(temp.top());
				temp.pop();
			}
		}
		else
		{
			for (int numPushes = 0; numPushes < myCommands[command].numMove; numPushes++)
			{
				stacks[myCommands[command].moveTo - 1].push(stacks[myCommands[command].moveFrom - 1].top());
				stacks[myCommands[command].moveFrom - 1].pop();
			}
		}
	}
}

/*****************************
* Main will read in the text
* file and display the results
******************************/
int main() {

	std::ifstream assignmentsFile("instructions.txt");
	std::string line;
	std::vector<commands> myCommands;
	std::vector<std::stack<char>> stacks;
	std::vector<std::stack<char>> partTwoStacks;

	std::vector<std::vector<char>> stacksContents{  { 'P', 'G', 'R', 'N' }, 
													{ 'C', 'D', 'G', 'F', 'L', 'B', 'T', 'J' }, 
													{ 'V', 'S', 'M'}, 
													{ 'P', 'Z', 'C', 'R', 'S', 'L'},
													{ 'Q', 'D', 'W', 'C', 'V', 'L', 'S', 'P'}, 
													{ 'S', 'M', 'D', 'W', 'N', 'T', 'C'}, 
													{ 'P', 'W', 'G', 'D', 'H'},
													{ 'V', 'M', 'C', 'S', 'H', 'P', 'L', 'Z' },
													{ 'Z', 'G', 'W', 'L', 'F', 'P', 'R'} };

	for (int i = 0; i < stacksContents.size(); i++)
	{
		stacks.push_back(initializeStacks(stacksContents[i]));
	}

	partTwoStacks = stacks;

	if (assignmentsFile.is_open())
	{
		while (getline(assignmentsFile, line))
		{
			myCommands.push_back(extractCommands(line));
		}
	}
	else
	{
		std::cout << "Error opening file." << std::endl;
		return 0;
	}

	executeCommands(stacks, myCommands, false);

	//Display for both parts
	std::cout << "Part 1: ";
	for (int i = 0; i < stacks.size(); i++)
	{
		std::cout << stacks[i].top();
	}

	executeCommands(partTwoStacks, myCommands, true);

	std::cout << std::endl << "Part 2: ";
	for (int i = 0; i < partTwoStacks.size(); i++)
	{
		std::cout << partTwoStacks[i].top();
	}

}
