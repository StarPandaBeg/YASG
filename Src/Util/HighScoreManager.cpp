#include "HighScoreManager.h"

#include "../GameConfig.h"

util::ScoreRow util::HighScoreManager::loadRow(std::fstream& f)
{
	std::string userName;
	int score;
	int time;
	char c;

	std::getline(f, userName, ';');
	userName.erase(std::remove(userName.begin(), userName.end(), '\n'), userName.end());
	f >> score >> c >> time;
	
	return ScoreRow{ userName, score, time };;
}

void util::HighScoreManager::writeRow(std::fstream& f, ScoreRow row)
{
	f << row.playerName << ";" << row.score << ";" << row.time << "\n";
}

void util::HighScoreManager::truncate()
{
	if (_scoreTable.size() <= RECORDS) return;
	int toRemove = _scoreTable.size() - RECORDS;
	for (int i = 0; i < toRemove; i++) _scoreTable.erase(std::prev(_scoreTable.end()));
}

util::HighScoreManager* util::HighScoreManager::instance()
{
	static HighScoreManager instance(CFG_HIGHSCORE_FILENAME);
	return &instance;
}

bool util::HighScoreManager::load()
{
	std::fstream f(_filePath, std::fstream::in);
	if (!f.is_open()) return false;

	int i = 0;
	while (!f.eof() && i++ < RECORDS) {
		ScoreRow row = loadRow(f);
		if (!f.eof())
			_scoreTable.emplace(row.score, row);
	}

	return true;
}

bool util::HighScoreManager::save()
{
	std::fstream f(_filePath, std::fstream::out);
	if (!f.is_open()) return false;

	for (auto scoreRow : _scoreTable) {
		writeRow(f, scoreRow.second);
	}
	return true;
}

void util::HighScoreManager::add(ScoreRow row)
{
	auto hash = row.score;
	auto min = 0;
	if (_scoreTable.size() > 0) min = std::prev(_scoreTable.end())->first;

	if (hash >= min || _scoreTable.size() < RECORDS) {
		_scoreTable.emplace(hash, row);
		truncate();
		save();
	}
}

std::vector<util::ScoreRow> util::HighScoreManager::get()
{
	std::vector<ScoreRow> vec;
	for (auto scoreRow : _scoreTable) {
		vec.push_back(scoreRow.second);
	}
	return vec;
}
