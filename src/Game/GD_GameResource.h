#pragma once

#include "GD_AtlasParserM.h"
#include "../Utility/configurations.h"

class GD_GameResource{
	public:
		static GD_GameResource* createInstance();
		unordered_map<string,IntRect>* getAtlas();
		Texture* getTexture();
		Font* getFont();
	private:
		static GD_GameResource* myInstance;
		unordered_map<string,IntRect>* atlas;
		Texture texture;
		Font font;
		GD_GameResource();
};
