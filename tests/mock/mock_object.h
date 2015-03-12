#ifndef __MOCK_OBJECT_H__
#define __MOCK_OBJECT_H__

#ifdef __cplusplus
extern "C" {
#endif 

class MockObject
{
public:
    char* name;
    void mock() {
    
    }
};


__declspec(dllexport) void* createInstance();

#ifdef __cplusplus
}
#endif 

#endif