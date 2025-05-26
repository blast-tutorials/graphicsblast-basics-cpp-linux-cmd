#pragma once

#include "model.h"
#include "texture.h"

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext/matrix_transform.hpp>

class Entity
{
    public:
        Entity();

        void setModel(Model* newModel);
        void setTexture(Texture* newTexture);

        void setPosition(float newX, float newY, float newZ);
        void updatePosition(float deltaX, float deltaY, float deltaZ);
        glm::vec3 getPosition();

        void setOrientation(float newRX, float newRY, float newRZ);
        void updateOrientation(float deltaRX, float deltaRY, float deltaRZ);
        glm::vec3 getOrientation();

        bool isDrawable();
        void draw();

    private:
        Model* model;
        Texture* texture;

        float x, y, z;
        float rx, ry, rz;

        glm::mat4 modelMatrix;
        void updateModelMatrix();
};
