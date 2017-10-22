#pragma once
#include "Coordinate.hpp"
#include "MoveDirection.hpp"
#include "KgDxGraphic.hpp"
#include <vector>
#include <utility>

class MapData {
private:
	int ChipWidth, ChipHeight;
	int GraphWidth, GraphHeight;
	std::vector<std::vector<KgDxGraphic::NoExcept::Picture>> Stage;
	std::vector<std::vector<bool>> Passable;
	std::vector<std::vector<int>> ItemMap;
	MapData(const std::string MapCSVFilePath, const std::string MapChipSheetFilePath, const std::string HitJudgeInfoCSVFilePath,
		const std::string ItemMapCSVFilePath, const std::string MapChipWidth, const std::string MapChipHeight, const std::string MapChipTotal);
	MapData(const std::string MapCSVFilePath, const std::string MapChipSheetFilePath, const std::string HitJudgementInfoCSVFilePath,
		const std::string ItemMapCSVFilePath, const int MapChipWidth, const int MapChipHeight, const int MapChipTotal);
public:
	MapData() = default;
	MapData(const std::string MapConfigFilePath);
	void GraphStage() const;
	std::pair<int, int> GetGraphSize() const;
	bool AbleToMove(const MoveDirection Direction, const Coordinate CurrentPoint) const;
};
