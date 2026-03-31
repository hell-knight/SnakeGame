#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>


namespace SnakeGame
{
	struct Game;
	struct Record;

	void InitLeaderboard(std::map<std::string, int>& list);
	void UpdateScore(std::map<std::string, int>& list, const std::string& name, int score);
	bool VerifNameScore(const std::string& name, int score);
	std::vector<Record> BuildSortedRecords(std::map<std::string, int>& list);
	bool DeserializeGame(std::map<std::string, int>& list);
	bool SerializeGame(const std::map<std::string, int>& list);
}