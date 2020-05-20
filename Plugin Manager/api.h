//API for plugin and plugin loader side

// A symbol starting with T is a type


// This is the interface that the plugin will expose to the host application. The interface
// is simply a struct of method pointers

// These two structs much be declared in both the Host application and any plugin

typedef struct
{
    int (*getVersion)();
    const char* (*getID)();
    const char* (*getDisplayName)();
    const char* (*getAuthor)();
    const char* (*getDescription)();
    int (*add)(int a, int b);
} TPluginInterface;


// This is the interface that the host application expses to the plugin
// The interface is simply a struct of method pointers
typedef struct {
    int (*getHostVersion)();
    int (*multPtr)(int a, int b);
    void (*printPtr) (int x);
} THostInterface;
