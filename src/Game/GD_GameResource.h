#pragma once

#include "GD_AtlasParserM.h"
#include "../Utility/configurations.h"

class GD_GameResource{
	public:
		static GD_GameResource* createInstance();
		unordered_map<string,IntRect>* getAtlas();
		unordered_map<string,IntRect>* getUIAtlas();
		Texture* getTexture();
		Texture* getUITexture();
		Font* getFont();
	private:
		static GD_GameResource* myInstance;
		unordered_map<string,IntRect>* atlas;
		unordered_map<string,IntRect>* UIAtlas;
		Texture texture;
		Texture UITexture;
		Font font;
		GD_GameResource();
};
