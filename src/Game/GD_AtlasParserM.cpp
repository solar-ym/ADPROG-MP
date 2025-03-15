#include "GD_AtlasParserM.h"

bool comparePrefix(string word, string prefix){
    int wordLen = word.length();
    int prefixLen = prefix.length();

    if(wordLen<prefixLen) return false;

    return word.substr(0, prefixLen) == prefix;
}

bool containsChar(string word, char character){
    return find(word.begin(), word.end(), character) != word.end();
}

unordered_map<string,IntRect>* createDictionary(string atlasFile){
    ifstream file(atlasFile);
    if(!file) {
        cerr << "Error opening file!" << endl;
        return nullptr;
    }

    string imageName;
    getline(file, imageName);

    string line, imgName, bounds;

    unordered_map<string,IntRect>* dictionary = new unordered_map<string,IntRect>();

    while(getline(file, line)){
        if(comparePrefix(line,"size:")){
            continue;
        }else if(comparePrefix(line,"repeat:")){
            continue;
        }else if(comparePrefix(line,"format:")){
            continue;
        }else if(!containsChar(line,':')){
            imgName = line;
            getline(file, line);
            
            if(!comparePrefix(line,"bounds:")) return nullptr;
            bounds = line.substr(7, line.length());

            istringstream stream(bounds);
            string part;
            vector<string> segments;

            while (getline(stream, part, ','))
                segments.push_back(part);
            
            if(segments.size()!=4) return nullptr;

            int x = atoi(segments[0].c_str());
            int y = atoi(segments[1].c_str());
            int width = atoi(segments[2].c_str());
            int height = atoi(segments[3].c_str());

            (*dictionary)[imgName] = IntRect({x,y},{width,height});
        }
    }
    file.close();
    return dictionary;
}
