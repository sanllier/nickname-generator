#ifndef _DICTIONARY_LOADER_
#define _DICTIONARY_LOADER_
//---------------------------------------------------------------

#include <vector>
#include <string>

//---------------------------------------------------------------

class DictionaryLoader
{

public:
    static void LoadNLSeparetedFile( std::vector< std::string >& dictionary, const std::string& fileName );
    static void LoadFCFile( std::vector< std::string >& dictionary, const std::string& fileName );
};

//---------------------------------------------------------------
#endif