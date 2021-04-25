#include "ShaderHandler.h"
//TODO: add time as uniform
namespace ShaderHandler
{
    namespace
    {
        unsigned int screenTex = 0;
        int W = 0, H = 0;
        unsigned int active = 0;
        std::map<std::string, unsigned int> shaders; //holds all loaded textures so that they only need to be loaded once
    }

    unsigned int LoadShader(std::string name, std::string vert, std::string frag)
    {
        if (shaders.find(name) != shaders.end()) //if shader already exists in map
        {
            return shaders.at(name);
        }
        //  Create program
        unsigned int prog = glCreateProgram();
        //  Create and compile vertex shader
        if (vert != "")
            CreateShader(prog, GL_VERTEX_SHADER, vert.c_str());
        //  Create and compile fragment shader
        if (frag != "")
            CreateShader(prog, GL_FRAGMENT_SHADER, frag.c_str());
        //  Link program
        glLinkProgram(prog);
        //  Check for errors
        PrintProgramLog(prog);
        //add to the map
        shaders.emplace(name, prog);
        //  Return name
        ErrCheck("LoadShader");
        return prog;
    }

    unsigned int LoadGeomShader(std::string name, std::string vert, std::string geom, std::string frag)
    {
        if (shaders.find(name) != shaders.end()) //if shader already exists in map
        {
            return shaders.at(name);
        }
        //  Create program
        unsigned int prog = glCreateProgram();
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
        ErrCheck("LoadGeomShader");
        return prog;
    }

    unsigned int LoadTesShader(std::string name, std::string vert, std::string tesc, std::string tese, std::string geom, std::string frag)
    {
        if (shaders.find(name) != shaders.end()) //if shader already exists in map
        {
            return shaders.at(name);
        }
        //  Create program
        unsigned int prog = glCreateProgram();
        CreateShader(prog, GL_VERTEX_SHADER, vert.c_str());
        CreateShader(prog, GL_TESS_CONTROL_SHADER, tesc.c_str());
        CreateShader(prog, GL_TESS_EVALUATION_SHADER, tese.c_str());
        CreateShader(prog, GL_GEOMETRY_SHADER, geom.c_str());
        CreateShader(prog, GL_FRAGMENT_SHADER, frag.c_str());

        //  Link program
        glLinkProgram(prog);
        //  Check for errors
        PrintProgramLog(prog);
        //add to the map
        shaders.emplace(name, prog);
        //  Return name
        ErrCheck("LoadTesShader");
        return prog;
    }

    unsigned int LoadAttrShader(std::string name, std::string vert, std::string frag, std::string attr[])
    {
        if (shaders.find(name) != shaders.end()) //if shader already exists in map
        {
            return shaders.at(name);
        }

        int k;
        //  Create program
        int prog = glCreateProgram();
        //  Create and compile vertex shader
        if (vert != "")
            CreateShader(prog, GL_VERTEX_SHADER, vert.c_str());
        //  Create and compile fragment shader
        if (frag != "")
            CreateShader(prog, GL_FRAGMENT_SHADER, frag.c_str());

        //  Set names
        for (k = 0; attr[k].c_str(); k++)
            if (attr[k][0])
                glBindAttribLocation(prog, k, attr[k].c_str());

        ErrCheck("CreateAttrShaderProg");
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
        std::cout << "shader not found - get: " << name << std::endl;
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
        std::cout << "shader not found - use: " << name << std::endl;
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

    void updateTime(float time)
    {
        for (auto const &x : shaders)
        {
            unsigned int val = x.second;
            glUseProgram(val);
            int id = glGetUniformLocation(val, "time");
            glUniform1f(id, time);
        }
        glUseProgram(active);
    }

    void updatePixMan(int width, int height, float dX, float dY)
    {
        W = width;
        H = height;
        for (auto const &x : shaders)
        {
            unsigned int val = x.second;
            glUseProgram(val);
            int id = glGetUniformLocation(val, "dX");
            glUniform1f(id, dX);
            id = glGetUniformLocation(val, "dY");
            glUniform1f(id, dY);

            glm::vec2 res = glm::vec2(width, height);
            id = glGetUniformLocation(val, "resolution");
            glUniform2fv(id, 1, &res[0]);
        }
        glUseProgram(active);
    }

    void updateScreenTex()
    {
        if (screenTex == 0)
        {
            glGenTextures(1, &screenTex);
            //  Image texture
            glBindTexture(GL_TEXTURE_2D, screenTex);
            //  Nearest returns exact cell values
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            //  do not allow texture wrapping so that you dont see the other side of the screen
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        }
        glBindTexture(GL_TEXTURE_2D, screenTex);
        glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 0, 0, W, H, 0);
        for (auto const &x : shaders)
        {
            unsigned int val = x.second;
            glUseProgram(val);
            int id = glGetUniformLocation(val, "screenTex");
            glUniform1i(id, 0);
        }
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    unsigned int getScreenTex()
    {
        return screenTex;
    }

    void updateParticle(std::string name, glm::vec3 vel, glm::vec3 acc, float starttime)
    {
        unsigned int val = getShader(name);
        glUseProgram(val);
        ErrCheck("shadboi");
        int id = glGetUniformLocation(val, "velocity");
        glUniform3fv(id, 1, &vel[0]);
        ErrCheck("shadboi2");
        id = glGetUniformLocation(val, "acceleration");
        glUniform3fv(id, 1, &acc[0]);
        ErrCheck("shadboi3");
        id = glGetUniformLocation(val, "starttime");
        glUniform1f(id, starttime);
        ErrCheck("shadboi4");
        glUseProgram(active);
    }

} //end ShaderHandler namespace