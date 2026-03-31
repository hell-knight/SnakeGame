#include "Leaderboard.h"
#include "Game.h"
#include <iostream>
#include <fstream>

namespace SnakeGame
{
	void InitLeaderboard(std::map<std::string, int>& list)
	{
		if (!DeserializeGame(list))
		{
			UpdateScore(list, "Alice", 100);
			UpdateScore(list, "Bob", 80);
			UpdateScore(list, "Carol", 64);
			UpdateScore(list, "Dave", 55);
			UpdateScore(list, "Egor", 41);
			UpdateScore(list, "Filip", 35);
			UpdateScore(list, "George", 23);
			UpdateScore(list, "Hanna", 19);
			UpdateScore(list, "Ivan", 12);
			UpdateScore(list, "Jion", 5);
		}
	}

	void UpdateScore(std::map<std::string, int>& list, const std::string& name, int score)
	{
		if (!VerifNameScore(name, score))
		{
			return;
		}

		auto it = list.find(name);
		if (it != list.end())
		{
			if (score > it->second)
			{
				it->second = score;
			}
		}
		else
		{
			list[name] = score;
		}
	}

	bool VerifNameScore(const std::string& name, int score)
	{
		if (name.empty() || name.find_first_not_of(" \t") == std::string::npos)
		{
			std::cerr << "Error: Player name cannot be empty or consist only of spaces\n";
			return false;
		}

		if (score < 0)
		{
			std::cerr << "Error: points cannot be negative ( " << score << " )\n";
			return false;
		}
		return true;
	}

	std::vector<Record> BuildSortedRecords(std::map<std::string, int>& list)
	{
		std::vector<Record> result;
		result.reserve(list.size());

		for (const auto& [name, score] : list)
		{
			result.push_back({name, score});
		}

		MyInsertionSort(result);

		return result;
	}

	bool DeserializeGame(std::map<std::string, int>& list)
	{
		list.clear();
		std::ifstream file(RECORDS_TABLE_FILE);
		if (file.is_open())
		{
			std::string name;
			int score;
			while (file >> name >> score)
			{
				list[name] = score;
			}
			file.close();
			return true;
		}

		return false;
	}

	bool SerializeGame(const std::map<std::string, int>& list)
	{
		std::ofstream file(RECORDS_TABLE_FILE);
		if (file.is_open())
		{
			for (const auto& record : list)
			{
				file << record.first << " " << record.second << std::endl;
			}
			file.close();
			return true;
		}

		return false;
	}
	
}