
#ifndef DATAMAPS_PLUGIN_HPP
#define DATAMAPS_PLUGIN_HPP

// stl
#include <string>

namespace datamaps
{

typedef struct _dl_lib_t dl_lib_t;
typedef const char* (*dl_profile_func) ();

class PluginInfo
{
public:
    PluginInfo (std::string const& filename, std::string const& library_name);
    ~PluginInfo();
    std::string const& name() const;
    bool valid() const;
    std::string get_error() const;
    void * get_symbol(std::string const& sym_name) const;

    static void init();
    static void exit();

private:
    std::string filename_;
    std::string name_;
    dl_lib_t * module_;
};
}

#endif // DATAMAPS_PLUGIN_HPP
