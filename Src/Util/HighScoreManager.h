#pragma once

#include <string>
#include <map>
#include <vector>
#include <fstream>

namespace util {
	struct ScoreRow {
		std::string playerName;
		int score;
		int time;
	};

	class HighScoreManager
	{
	private:
		const int RECORDS = 12;
		std::multimap<long, ScoreRow, std::greater<long>> _scoreTable;
		std::string _filePath;

		ScoreRow loadRow(std::fstream& f);
		void writeRow(std::fstream& f, ScoreRow row);
		void truncate();

		HighScoreManager(std::string filePath) : _filePath(filePath) {}
	public:
		static HighScoreManager* instance();
		bool load();
		bool save();
		void add(ScoreRow row);
		std::vector<ScoreRow> get();
	};
}

