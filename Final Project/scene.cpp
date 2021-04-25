#include "scene.h"

Scene::Scene()
{
}

Scene::Scene(std::string worldfile)
{
    //camera = Camera(glm::vec3(0,0,0), glm::vec3(0,0,0));
    loadWorldFile(worldfile);
    filename = worldfile;
}

void Scene::drawScene()
{
    //camera.updateView();
    for (Object *object : objects)
    {
        object->draw();
    }
    ShaderHandler::updateScreenTex(); //may need to change this depending on how effects need to interact
    for (Object *effect : effects)
    {
        effect->draw();
    }
}

//takes: 0,0,0
glm::vec3 Scene::GetVectorFromString(std::string str)
{
    std::string numbers[3] = {"", "", ""};
    std::string delim = ",";
    auto start = 0U;
    auto end = str.find(delim);

    int index = 0;

    while (end != std::string::npos && index < 2)
    {
        numbers[index] = str.substr(start, end - start);

        start = end + delim.length();
        end = str.find(delim, start);
        index++;
    }
    numbers[index] = str.substr(start, end);
    glm::vec3 vec;
    if (index == 1)
    {
        vec = glm::vec3(stof(numbers[0]), stof(numbers[0]), stof(numbers[0]));
    }
    else
    {
        vec = glm::vec3(stof(numbers[0]), stof(numbers[1]), stof(numbers[2]));
    }

    return vec;
}

void Scene::LoadObject(std::string objLine)
{
    //check if it is a comment line
    if (objLine[0] == '#')
    {
        return;
    }

    std::string settings[7] = {"", "", "", "", "", "", ""};
    std::string delim = " ";
    auto start = 0U;
    auto end = objLine.find(delim);

    int index = 0;

    while (end != std::string::npos && index < 6)
    {
        settings[index] = objLine.substr(start, end - start);

        start = end + delim.length();
        end = objLine.find(delim, start);
        index++;
    }
    settings[index] = objLine.substr(start, end);

    std::string objName = settings[0];
    if (objName == "")
    {
        return;
    }

    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale(1, 1, 1);
    std::string texturePath = "Textures/" + settings[4];
    bool hasAlpha = false;
    std::string normalMapPath = settings[6];

    //position
    if (index >= 1)
    {
        position = GetVectorFromString(settings[1]);
    }
    //rotation
    if (index >= 2)
    {
        rotation = GetVectorFromString(settings[2]);
    }
    //scale
    if (index >= 3)
    {
        scale = GetVectorFromString(settings[3]);
    }
    //texture alpha
    if (index >= 5)
    {
        if (settings[5] == "true")
        {
            hasAlpha = true;
        }
        else if (settings[5] == "false")
        {
            hasAlpha = false;
        }
        else
        {
            std::cout << "ERROR: true or false does not exist setting alpha value to false" << std::endl;
            hasAlpha = false;
        }
    }

    if (objName == "Surface")
    {
        objects.push_back(new Surface(position, scale, rotation, texturePath, hasAlpha));
    }
    else if (objName == "Floor")
    {
        objects.push_back(new Floor(position, scale, rotation, texturePath, hasAlpha));
    }
    else if (objName == "Ring")
    {
        objects.push_back(new Ring(position, scale, rotation));
    }
    else if (objName == "Pillar")
    {
        objects.push_back(new Pillar(position, scale, rotation));
    }
    else if (objName == "Lava")
    {
        objects.push_back(new Lava(position, scale, rotation));
    }
    else if (objName == "Shimmer")
    {
        effects.push_back(new Shimmer(position, scale, rotation));
    }
}

void Scene::loadWorldFile(std::string worldfile)
{
    objects.clear();
    effects.clear();
    std::ifstream file(worldfile);
    // open files
    if (file.is_open())
    {
        std::string line;
        while (getline(file, line))
        {
            LoadObject(line);
        }
        file.close();
    }
}

void Scene::reload()
{
    loadWorldFile(filename);
}

void Scene::rotateCam(glm::vec3 rot)
{
    //camera.rotate(rot);
}

void Scene::moveCam(glm::vec3 mov)
{
    //camera.move(mov);
}