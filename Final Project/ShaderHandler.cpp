#include "ShaderHandler.h"

namespace ShaderHandler
{
    namespace
    {
        unsigned int active = 0;
        std::map<std::string, unsigned int> shaders; //holds all loaded textures so that they only need to be loaded once
    }

    unsigned int LoadShader(std::string name, std::string vert, std::string frag)
    {
        if (shaders.find(name) != shaders.end()) //if texture already exists in map
        {
            return shaders.at(name);
        }
        //  Create program
        int prog = glCreateProgram();
        //  Create and compile vertex shader
        CreateShader(prog, GL_VERTEX_SHADER, vert.c_str());
        //  Create and compile fragment shader
        CreateShader(prog, GL_FRAGMENT_SHADER, frag.c_str());
        //  Link program
        glLinkProgram(prog);
        //  Check for errors
        PrintProgramLog(prog);
        //add to the map
        shaders.emplace(name, prog);
        //  Return name
        return prog;
    }

    unsigned int LoadGeomShader(std::string name, std::string vert, std::string geom, std::string frag)
    {
        if (shaders.find(name) != shaders.end()) //if texture already exists in map
        {
            return shaders.at(name);
        }
        //  Create program
        int prog = glCreateProgram();
        //  Create and compile vertex shader
        CreateShader(prog, GL_VERTEX_SHADER, vert.c_str());
#ifdef GL_GEOMETRY_SHADER
        //  Create and compile geometry shader
        CreateShader(prog, GL_GEOMETRY_SHADER, geom.c_str());
#else
        if (geom)
            Fatal("Geometry Shader not supported\n");
#endif
        //  Create and compile fragment shader
        CreateShader(prog, GL_FRAGMENT_SHADER, frag.c_str());
        //  Link program
        glLinkProgram(prog);
        //  Check for errors
        PrintProgramLog(prog);
        //add to the map
        shaders.emplace(name, prog);
        //  Return name
        return prog;
    }

    unsigned int getShader(std::string name)
    {
        if (shaders.find(name) != shaders.end()) //if texture already exists in map
        {
            return shaders.at(name);
        }
        std::cout << "shader not found" << std::endl;
        return 0;
    }

    unsigned int useShader(std::string name)
    {
        if (shaders.find(name) != shaders.end()) //if texture already exists in map
        {
            glUseProgram(shaders.at(name));
            active = shaders.at(name);
            return shaders.at(name);
        }
        std::cout << "shader not found" << std::endl;
        return (0);
    }

    void disableShaders()
    {
        active = 0;
        glUseProgram(0);
    }

    void updateProjMatrix(glm::mat4 proj)
    {
        for (auto const &x : shaders)
        {
            unsigned int val = x.second;
            glUseProgram(val);
            int id = glGetUniformLocation(val, "ProjectionMatrix");
            glUniformMatrix4fv(id, 1, 0, &proj[0][0]);
        }
        glUseProgram(active);
    }

    void updateViewMatrix(glm::mat4 view)
    {
        for (auto const &x : shaders)
        {
            unsigned int val = x.second;
            glUseProgram(val);
            int id = glGetUniformLocation(val, "ViewMatrix");
            glUniformMatrix4fv(id, 1, 0, &view[0][0]);
        }
        glUseProgram(active);
    }

    void updateModelMatrix(glm::mat4 model)
    {
        for (auto const &x : shaders)
        {
            unsigned int val = x.second;
            glUseProgram(val);
            int id = glGetUniformLocation(val, "ModelMatrix");
            glUniformMatrix4fv(id, 1, 0, &model[0][0]);
        }
        glUseProgram(active);
    }

    void updateLightInfo(glm::vec4 global, glm::vec4 ambient, glm::vec4 diffuse, glm::vec4 specular, glm::vec4 position, glm::vec4 lightcolor)
    {
        for (auto const &x : shaders)
        {
            unsigned int val = x.second;
            glUseProgram(val);
            int id = glGetUniformLocation(val, "Global");
            glUniform4fv(id, 1, &global[0]);
            id = glGetUniformLocation(val, "Ambient");
            glUniform4fv(id, 1, &ambient[0]);
            id = glGetUniformLocation(val, "Diffuse");
            glUniform4fv(id, 1, &diffuse[0]);
            id = glGetUniformLocation(val, "Specular");
            glUniform4fv(id, 1, &specular[0]);
            id = glGetUniformLocation(val, "Position");
            glUniform4fv(id, 1, &position[0]);
            id = glGetUniformLocation(val, "LightColor");
            glUniform4fv(id, 1, &lightcolor[0]);
        }
        glUseProgram(active);
    }

    void updateFOV(float fov)
    {
        for (auto const &x : shaders)
        {
            unsigned int val = x.second;
            glUseProgram(val);
            int id = glGetUniformLocation(val, "fov");
            glUniform1f(id, fov);
        }
        glUseProgram(active);
    }

} //end ShaderHandler namespace