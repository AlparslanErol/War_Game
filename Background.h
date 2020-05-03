#pragma once
#include "Manager.h"

class Background {

public:
	Background();
	~Background();
	std::vector<std::shared_ptr<olc::Sprite>> levelSprites;
};
