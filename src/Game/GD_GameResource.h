#pragma once

#include "GD_AtlasParserM.h"
#include "../Utility/configurations.h"

// from class

/*
	We added a couple more atlases to organize the UI from the other game assets/
*/
class GD_GameResource{
	public:
		static GD_GameResource* createInstance();
		unordered_map<string,IntRect>* getAtlas();
		unordered_map<string,IntRect>* getUIAtlas1();
		unordered_map<string,IntRect>* getUIAtlas2();
		Texture* getTexture();
		Texture* getUITexture1();
		Texture* getUITexture2();
		Font* getFont();
	private:
		static GD_GameResource* myInstance;
		unordered_map<string,IntRect>* atlas;
		unordered_map<string,IntRect>* UIAtlas1;
		unordered_map<string,IntRect>* UIAtlas2;
		Texture texture;
		Texture UITexture1;
		Texture UITexture2;
		Font font;
		GD_GameResource();
};
