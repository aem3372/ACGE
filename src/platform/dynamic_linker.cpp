#include <map>
#include <string>
#include <stdio.h>
#include "dynamic_linker.h"

#ifdef _ACGE_PLATFORM_WIN32

DynamicLinker* DynamicLinker::instance = NULL;

class DynamicLinker::DynamicLinkerPrivate
{
public:
    std::map<std::string, HMODULE> table;
};

DynamicLinker* DynamicLinker::getInstance()
{
    if(instance == NULL)
    {
        instance = new DynamicLinker();
    }
    return instance;
}

void DynamicLinker::loadLibrary(const char* name, const char* path)
{
    if(impl->table.count(std::string(name)))
    {
        printf("error: name defined or library loaded!\n");
    }

    HMODULE hModule = NULL;
    hModule = ::LoadLibrary(path);
    if(hModule == NULL)
    {
        printf("error: load fail!\n");
    }
    impl->table[std::string(name)] = hModule;
}

void DynamicLinker::freeLibrary(const char* name)
{
    if(!impl->table.count(std::string(name)))
    {
        printf("error: library not load!\n");
    }
    ::FreeLibrary(impl->table[std::string(name)]);
}

void* DynamicLinker::getProcAddress(const char* name, const char* procName)
{
    return (void*)::GetProcAddress(impl->table[std::string(name)], procName);
}

DynamicLinker::DynamicLinker()
:impl(new DynamicLinkerPrivate)
{

}

DynamicLinker::~DynamicLinker()
{
    delete impl;
}

#endif
