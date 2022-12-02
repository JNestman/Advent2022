#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int calcMatchResult(char opponentChoice, char myChoice) {
	int result = 0;

	switch (opponentChoice) {
		case 'A':
			switch (myChoice) {
				case 'X':
					result += 1 + 3;
					break;
				case 'Y':
					result += 2 + 6;
					break;
				case 'Z':
					result += 3 + 0;
					break;
				default:
					std::cout << "Unknown character in choice: " << myChoice << std::endl;
			}
			break;
		case 'B':
			switch (myChoice) {
				case 'X':
					result += 1 + 0;
					break;
				case 'Y':
					result += 2 + 3;
					break;
				case 'Z':
					result += 3 + 6;
					break;
				default:
					std::cout << "Unknown character in choice: " << myChoice << std::endl;
			}
			break;
		case 'C':
			switch (myChoice) {
				case 'X':
					result += 1 + 6;
					break;
				case 'Y':
					result += 2 + 0;
					break;
				case 'Z':
					result += 3 + 3;
					break;
				default:
					std::cout << "Unknown character in choice: " << myChoice << std::endl;
			}
			break;
		default:
			std::cout << "Unknown opponent character: " << opponentChoice << std::endl;
	}

	return result;
}

int calcEndResult(char opponentChoice, char myChoice) {
	int result = 0;

	switch (opponentChoice) {
	case 'A':
		switch (myChoice) {
			case 'X':
				result += 3 + 0;
				break;
			case 'Y':
				result += 1 + 3;
				break;
			case 'Z':
				result += 2 + 6;
				break;
			default:
				std::cout << "Unknown character in choice: " << myChoice << std::endl;
		}
		break;
	case 'B':
		switch (myChoice) {
			case 'X':
				result += 1 + 0;
				break;
			case 'Y':
				result += 2 + 3;
				break;
			case 'Z':
				result += 3 + 6;
				break;
			default:
				std::cout << "Unknown character in choice: " << myChoice << std::endl;
		}
		break;
	case 'C':
		switch (myChoice) {
			case 'X':
				result += 2 + 0;
				break;
			case 'Y':
				result += 3 + 3;
				break;
			case 'Z':
				result += 1 + 6;
				break;
			default:
				std::cout << "Unknown character in choice: " << myChoice << std::endl;
		}
		break;
	default:
		std::cout << "Unknown opponent character: " << opponentChoice << std::endl;
	}

	return result;
}


int main() {

	std::fstream outcomeFile("outcome.txt", std::fstream::in);
	char line;
	std::vector<char> opponentChoice;
	std::vector<char> myChoice;
	int finalResult = 0;

	while (outcomeFile >> std::noskipws >> line)
	{
		if (line == 'A' || line == 'B' || line == 'C')
		{
			opponentChoice.push_back(line);
		}
		else if (line == 'X' || line == 'Y' || line == 'Z')
		{
			myChoice.push_back(line);
		}
	}

	for (int i = 0; i < opponentChoice.size(); i++)
	{
		finalResult += calcMatchResult(opponentChoice[i], myChoice[i]);
	}

	std::cout << "My total when my choice is a move: " << finalResult << std::endl;

	finalResult = 0;

	for (int i = 0; i < opponentChoice.size(); i++)
	{
		finalResult += calcEndResult(opponentChoice[i], myChoice[i]);
	}

	std::cout << "My total when my choice is an outcome: " << finalResult << std::endl;

	return 0;
}
