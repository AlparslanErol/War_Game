#include "Background.h"

Background::Background() {
	levelSprites = std::vector<std::shared_ptr<olc::Sprite>>();
	for (int i = 0; i < 7; ++i)
		levelSprites.push_back(make_shared<olc::Sprite>("Sprites/Level" + to_string(i + 1) + ".png"));
}

Background::~Background() {

}