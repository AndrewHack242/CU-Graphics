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
    else if (objName == "Ring")
    {
        objects.push_back(new Ring(position, scale, rotation));
    }
    //TODO: add in objects to spawn later
    //spawn objects
    /*
    if (objName == "SimpleObject")
    {
        objects.push_back(new SimpleObject(pos, scale, rot));
    }
    else if (objName == "ComplexObject")
    {
        objects.push_back(new ComplexObject(pos, scale, rot));
    }
    else if (objName == "Companion")
    {
        objects.push_back(new Companion(pos, scale, rot));
    }
    else if (objName == "Dropper")
    {
        objects.push_back(new Dropper(pos, scale, rot));
    }
    else if (objName == "Observe")
    {
        objects.push_back(new Observe(pos, scale, rot));
    }
    else if (objName == "Floor")
    {
        objects.push_back(new Floor(pos, scale, rot, {texturePath}, {hasAlpha}, normalMapPath));
    }
    else if (objName == "Wall")
    {
        objects.push_back(new Wall(pos, scale, rot, {texturePath}, {hasAlpha}, normalMapPath));
    }
    else
    {
        std::cout << "ERROR:[" << objName << "] does not exist" << std::endl;
    }
    */
}

void Scene::loadWorldFile(std::string worldfile)
{
    objects.clear();
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