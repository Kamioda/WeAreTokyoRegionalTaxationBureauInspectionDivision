#include "D:/Users/AinoMegumi/BitBucket/Kamioda Games/CommonSourceCode/Split.hpp"
#include "MapData.hpp"
#include "PropertiesRead.hpp"
#include <fstream>

// 後ろ２つの引数をstd::stringからintへ変換するためだけのコンストラクタ
MapData::MapData(const std::string MapCSVFilePath, const std::string MapChipSheetFilePath, const std::string HitJudgeInfoCSVFilePath,
	const std::string ItemMapCSVFilePath, const std::string MapChipWidth, const std::string MapChipHeight, const std::string MapChipTotal)
	: MapData(MapCSVFilePath, MapChipSheetFilePath, HitJudgeInfoCSVFilePath, ItemMapCSVFilePath, std::stoi(MapChipWidth),
		std::stoi(MapChipHeight), std::stoi(MapChipHeight)) {}

// 実際にマップ情報を読み取るコンストラクタ
MapData::MapData(const std::string MapCSVFilePath, const std::string MapChipSheetFilePath, const std::string HitJudgementInfoCSVFilePath,
	const std::string ItemMapCSVFilePath, const int MapChipWidth, const int MapChipHeight, const int MapChipTotal) {
	this->ChipWidth = MapChipWidth;
	this->ChipHeight = MapChipHeight;
	const std::vector<KgDxGraphic::NoExcept::Picture> Data = KgDxGraphic::NoExcept::Picture::DivLoad(
		MapChipSheetFilePath,
		[](const std::string MapChipSheetFilePath, const int MapChipTotal, const int MapChipWidth, const int MapChipHeight) {
			const KgDxGraphic::NoExcept::Picture p(MapChipSheetFilePath);
			KgDxGraphic::DivLoadSettings d;
			d.AllNum = MapChipTotal;
			d.XNum = p.Width / MapChipWidth;
			d.YNum = p.Height / MapChipHeight;
			d.XSize = MapChipWidth;
			d.YSize = MapChipHeight;
			return d;
		}(MapChipSheetFilePath, MapChipTotal, MapChipWidth, MapChipHeight)
	);
	{
		std::ifstream ifs(MapCSVFilePath);
		for (std::string s; std::getline(ifs, s);) {
			std::vector<KgDxGraphic::NoExcept::Picture> Temp;
			for (const std::string i : SplitA(s, ',')) {
				Temp.emplace_back(Data[std::stoi(i)]);
			}
			this->Stage.emplace_back(Temp);
			if (this->Stage.size() >= 2 && this->Stage[0].size() != this->Stage.back().size())
				throw std::runtime_error(MapCSVFilePath + " : データが不正です。");
		}
		ifs.close();
	}
	{
		std::ifstream ifs(HitJudgementInfoCSVFilePath);
		for (std::string s; std::getline(ifs, s);) {
			std::vector<bool> Temp;
			for (const std::string i : SplitA(s, ',')) Temp.emplace_back(std::stoi(i) == 1);
			this->Passable.emplace_back(Temp);
			if (this->Passable.back().size() != this->Stage[this->Passable.back().size() - 1].size())
				throw std::runtime_error(HitJudgementInfoCSVFilePath + " : データが不正です。");
		}
		ifs.close();
	}
	this->GraphWidth = this->ChipWidth * this->Stage[0].size();
	this->GraphHeight = this->ChipHeight * this->Stage.size();
}

// コンフィグファイルを読み込むためのコンストラクタ
MapData::MapData(const std::string MapConfigFilePath) {
	const PropertiesRead Prop(MapConfigFilePath);
	MapData(Prop.GetData("Map"), Prop.GetData("Chip"), Prop.GetData("Hit"), Prop.GetData("Item"),
		Prop.GetData("ChipW"), Prop.GetData("ChipH"), Prop.GetData("ChipT"));
}

void MapData::GraphStage() const {
	for (int i = 0; i < this->Stage.size(); i++) {
		for (int j = 0; j < this->Stage[i].size(); j++) this->Stage[i][j].Print(j * this->ChipWidth, i + this->ChipHeight, false);
	}
}

std::pair<int, int> MapData::GetGraphSize() const {
	return std::make_pair(this->GraphWidth, this->GraphHeight);
}

bool MapData::AbleToMove(const MoveDirection Direction, const Coordinate CurrentPoint) const {
	switch (Direction) {
		case MoveDirection::Up:
			if (CurrentPoint.Y == 0) return false;
			this->Passable[CurrentPoint.Y - 1][CurrentPoint.X];
		case MoveDirection::Down:
			if (CurrentPoint.Y == this->Passable.size() - 1) return false;
			return this->Passable[CurrentPoint.Y + 1][CurrentPoint.X];
		case MoveDirection::Left:
			if (CurrentPoint.X == 0) return false;
			return this->Passable[CurrentPoint.Y][CurrentPoint.X - 1];
		case MoveDirection::Right:
			if (CurrentPoint.X == this->Passable.size() - 1) return false;
			return this->Passable[CurrentPoint.Y][CurrentPoint.X + 1];
		default:
			return false;
	}
}
