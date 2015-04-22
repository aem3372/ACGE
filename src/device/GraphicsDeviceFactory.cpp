#include <stdlib.h>
#include <string.h>
#include <string>
#include "GraphicsDeviceFactory.h"
#include "tools/DynamicLinker.h"
#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/filestream.h"
#include "rapidjson/stringbuffer.h"

class GraphicsDeviceModel
{
public:
    const char* name;
    const char* path;
};

std::map<std::string,GraphicsDeviceModel> deviceMap;

GraphicsDeviceFactory* GraphicsDeviceFactory::instance = NULL;

GraphicsDeviceFactory* GraphicsDeviceFactory::getInstance()
{
    if(instance == NULL)
    {
        instance = new GraphicsDeviceFactory();
    }
    return instance;
}

IGraphicsDevice* GraphicsDeviceFactory::createByName(const char* name)
{
    typedef IGraphicsDevice* (*CallFun)();
    DynamicLinker* linker = DynamicLinker::getInstance();
    linker->loadLibrary(name,deviceMap[std::string(name)].path);
    CallFun callFun = (CallFun)linker->getProcAddress(name,"createInstance");
    IGraphicsDevice* gd = callFun();
    
    if(gd)
    {
        return gd;
    }

    return NULL;
}

void GraphicsDeviceFactory::loadList()
{
    const char* fileName = "GraphicsDevice.json";
    std::ifstream fin(fileName);
    std::stringstream buffer;
    buffer << fin.rdbuf();
    std::string contents(buffer.str());
    const char* json = contents.c_str();

    rapidjson::Document doc;
    doc.Parse<0>(json);
    if(doc.IsArray())
    {
        for(int i=0; i != doc.Size(); ++i)
        {
            if(doc[i].IsObject())
            {
                GraphicsDeviceModel model;
                if(doc[i].HasMember("name") && doc[i]["name"].IsString())
                {
                    model.name = doc[i]["name"].GetString();
                }
                if(doc[i].HasMember("path") && doc[i]["path"].IsString())
                {
                    model.path = doc[i]["path"].GetString();
                }
                deviceMap[std::string(model.name)] = model;
            }
        }
    }
}


GraphicsDeviceFactory::GraphicsDeviceFactory()
{
    loadList();
}


GraphicsDeviceFactory::~GraphicsDeviceFactory()
{

}
