
#ifndef Macros_h
#define Macros_h

//#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")

//macro to pick the right glGenVertexArray function
#ifndef GENVERTEXARRAYS
#define GENVERTEXARRAYS(n,id) \
if(GLEW_APPLE_vertex_array_object) glGenVertexArraysAPPLE(1,id);\
else if (GLEW_ARB_vertex_array_object) glGenVertexArrays(n,id)
#endif

//macro to pick the right glBindVertexArray function
#ifndef BINDVERTEXARRAY
#define BINDVERTEXARRAY(id) \
if(GLEW_APPLE_vertex_array_object) glBindVertexArrayAPPLE(id);\
else if (GLEW_ARB_vertex_array_object) glBindVertexArray(id)
#endif


#endif /* Macros_h */
