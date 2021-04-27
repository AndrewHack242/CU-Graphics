#include "Object.h"


glm::vec3 RotateY(glm::vec3 dis, float deg)
{
    glm::vec3 pivot = glm::vec3(0,1,0);
    return dis * (float)Cos(deg) + (glm::cross(pivot,dis)) * (float)Sin(deg) + pivot * (glm::dot(pivot,dis) * (1 - (float)Cos(deg)));
}

Object::Object()
{
}

Object::Object(glm::vec3 position, glm::vec3 scale, glm::vec3 rotation)
{
    pos = position;
    s = scale;
    rot = rotation;
}

void Object::draw()
{
    //TODO: update all shaders model matrices for use in this object
    //  Create Model matrix //TODO: calculate model matrix in obj
    glm::mat4 model(1.0f);
    model = glm::translate(model, glm::vec3(pos.x, pos.y, pos.z));
    model = glm::rotate(model, glm::radians(rot.x), glm::vec3(1.0, 0.0, 0.0));
    model = glm::rotate(model, glm::radians(rot.y), glm::vec3(0.0, 1.0, 0.0));
    model = glm::rotate(model, glm::radians(rot.z), glm::vec3(0.0, 0.0, 1.0));
    model = glm::scale(model, glm::vec3(s.x, s.y, s.z));

    ShaderHandler::updateModelMatrix(model);
    drawObject();
    glBindVertexArray(0);
}

void Object::drawObject()
{
    std::cout << "an object does not have a drawObject() function." << std::endl;
}

void Object::VAOInit()
{
    std::cout << "an object does not have a VBOInit() function." << std::endl;
}

void Object::updatePos(glm::vec3 newpos)
{
    pos = newpos;
}