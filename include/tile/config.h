
#ifndef DATAMAPS_CONFIG_HPP
#define DATAMAPS_CONFIG_HPP

// Windows DLL support

#ifdef _WINDOWS
#  define DATAMAPS_EXP __declspec (dllexport)
#  define DATAMAPS_IMP __declspec (dllimport)
#  ifdef DATAMAPS_EXPORTS
#    define DATAMAPS_DECL __declspec (dllexport)
#  else
#    define DATAMAPS_DECL __declspec (dllimport)
#  endif
#  pragma warning( disable: 4251 )
#  pragma warning( disable: 4275 )
#  if (_MSC_VER >= 1400) // vc8
#    pragma warning(disable : 4996) //_CRT_SECURE_NO_DEPRECATE
#  endif
#else
#  if __GNUC__ >= 4
#  define DATAMAPS_EXP __attribute__ ((visibility ("default")))
#  define DATAMAPS_DECL __attribute__ ((visibility ("default")))
#  define DATAMAPS_IMP __attribute__ ((visibility ("default")))
#  else
#  define DATAMAPS_EXP
#  define DATAMAPS_DECL
#  define DATAMAPS_IMP
#  endif
#endif

#endif // DATAMAPS_CONFIG_HPP
