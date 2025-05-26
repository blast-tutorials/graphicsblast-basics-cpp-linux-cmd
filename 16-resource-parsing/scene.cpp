#include "scene.h"

#include <SDL3/SDL.h>

#include <fstream>
#include <sstream>

void Scene::setFilename(string newSceneFilename)
{
    filename = SDL_GetBasePath() + newSceneFilename;
}

bool Scene::loadScene()
{
    errorMessage = "";
    deleteScene();

    if(filename.empty())
    {
        errorMessage = "Scene filename not set";
        return false;
    }

    ifstream fileStream(filename);
    if(!fileStream.is_open())
    {
        errorMessage = "Unable to open file";
        return false;
    }

    string line;
    while(getline(fileStream, line))
    {
        istringstream iss(line);

        string objectType, objectName, filename;
        iss >> objectType >> objectName >> filename;

        if(objectType == "Texture")
        {
            textures[objectName].setFilename(filename);

            if(!textures[objectName].loadTexture())
            {
                errorMessage = "Failed to load texture ";
                errorMessage += objectName;
                errorMessage += " - ";
                errorMessage += textures[objectName].getError();

                deleteScene();
                fileStream.close();

                return false;
            }
        }
        else if(objectType == "Model")
        {
            models[objectName].setFilename(filename);

            if(!models[objectName].loadOBJModel())
            {
                errorMessage = "Failed to load model ";
                errorMessage += objectName;
                errorMessage += " - ";
                errorMessage += models[objectName].getError();

                deleteScene();
                fileStream.close();

                return false;
            }
        }
    }

    fileStream.clear();
    fileStream.seekg(0);

    while(getline(fileStream, line))
    {
        istringstream iss(line);

        string objectType, objectName;
        iss >> objectType >> objectName;

        if(objectType == "Entity")
        {
            string key, value;
            iss >> key >> value;

            while(value.length())
            {
                if(key == "texture")
                {
                    if(!textures.count(value))
                    {
                        errorMessage = "Entity referenced texture which was not found: ";
                        errorMessage += objectName;

                        deleteScene();
                        fileStream.close();
                        return false;
                    }

                    entities[objectName].setTexture(&textures[value]);
                }
                else if(key == "model")
                {
                    if(!models.count(value))
                    {
                        errorMessage = "Entity referenced model which was not found: ";
                        errorMessage += objectName;

                        deleteScene();
                        fileStream.close();
                        return false;
                    }

                    entities[objectName].setModel(&models[value]);
                }
                else if(key == "x")
                {
                    entities[objectName].updatePosition(stof(value), 0, 0);
                }
                else if(key == "y")
                {
                    entities[objectName].updatePosition(0, stof(value), 0);
                }
                else if(key == "z")
                {
                    entities[objectName].updatePosition(0, 0, stof(value));
                }
                else if(key == "rx")
                {
                    entities[objectName].updateOrientation(stof(value), 0, 0);
                }
                else if(key == "ry")
                {
                    entities[objectName].updateOrientation(0, stof(value), 0);
                }
                else if(key == "rz")
                {
                    entities[objectName].updateOrientation(0, 0, stof(value));
                }

                key = "";
                value = "";
                iss >> key >> value;
            }
        }
    }

    fileStream.close();

    return true;
}

void Scene::deleteScene()
{
    for(auto& element : textures)
    {
        element.second.deleteTexture();
    }

    for(auto& element : models)
    {
        element.second.deleteModel();
    }

    models.clear();
    textures.clear();
    entities.clear();
}

void Scene::draw()
{
    for(auto& element : entities)
    {
        element.second.draw();
    }
}

string Scene::getFilename()
{
    return filename;
}

string Scene::getErrorMessage()
{
    return errorMessage;
}
