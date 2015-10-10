
#include <tile/plugin.h>
#include <stdexcept>

#ifdef _WINDOWS
  #define NOMINMAX
  #include <windows.h>
  #define handle HMODULE
  #define dlsym GetProcAddress
  #define dlclose FreeLibrary
  #define dlerror GetLastError
  #define DATAMAPS_SUPPORTS_DLOPEN
#else
  #ifdef DATAMAPS_HAS_DLCFN
    #include <dlfcn.h>
    #define DATAMAPS_SUPPORTS_DLOPEN
  #endif
  #define handle void *
#endif

// TODO - handle/report dlerror

namespace datamaps
{

struct _dl_lib_t {
    handle dl;
};

PluginInfo::PluginInfo(std::string const& filename,
                       std::string const& library_name)
    : filename_(filename),
      name_(),
      module_(new dl_lib_t)
      {
#ifdef _WINDOWS
          if (module_) module_->dl = LoadLibraryA(filename.c_str());
#else
  #ifdef DATAMAPS_HAS_DLCFN
          if (module_) module_->dl = dlopen(filename.c_str(),RTLD_LAZY);
  #else
          throw std::runtime_error("no support for loading dynamic objects (Datamaps not compiled with -DDATAMAPS_HAS_DLCFN)");
  #endif
#endif
          if (module_ && module_->dl)
          {
                dl_profile_func name = reinterpret_cast<dl_profile_func>(dlsym(module_->dl, library_name.c_str()));
                if (name) name_ = name();
          }
      }

PluginInfo::~PluginInfo()
{
    if (module_)
    {
#ifdef DATAMAPS_SUPPORTS_DLOPEN
        if (module_->dl)
        {
            dlclose(module_->dl);
            module_->dl=0;
        }
#endif
        delete module_;
    }
}


void * PluginInfo::get_symbol(std::string const& sym_name) const
{
#ifdef DATAMAPS_SUPPORTS_DLOPEN
    return static_cast<void *>(dlsym(module_->dl, sym_name.c_str()));
#else
    return NULL;
#endif
}

std::string const& PluginInfo::name() const
{
    return name_;
}

bool PluginInfo::valid() const
{
#ifdef DATAMAPS_SUPPORTS_DLOPEN
    if (module_ && module_->dl && !name_.empty()) return true;
#endif
    return false;
}

std::string PluginInfo::get_error() const
{
    return std::string("could not open: '") + name_ + "'";
}

void PluginInfo::init()
{
    // do any initialization needed
}

void PluginInfo::exit()
{
    // do any shutdown needed
}


}
