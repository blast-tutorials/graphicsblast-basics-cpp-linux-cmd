#pragma once

#include "texture.h"
#include "model.h"
#include "entity.h"

#include <map>
#include <string>

using namespace std;

class Scene
{
    public:
        void setFilename(string newSceneFilename);
        bool loadScene();
        void deleteScene();

        void draw();

        string getFilename();
        string getErrorMessage();

    private:
        map<string, Texture> textures;
        map<string, Model> models;
        map<string, Entity> entities;

        string filename;
        string errorMessage;
};
