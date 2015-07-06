#include "DictionaryLoader.h"

#include <iostream>
#include <fstream>

//---------------------------------------------------------------

void DictionaryLoader::LoadNLSeparetedFile( std::vector< std::string >& dictionary, const std::string& fileName )
{
    std::cout << "--> Loading dictionary from NL separated file...\n";

    dictionary.clear();

    std::fstream dictionaryFile;
    dictionaryFile.open( fileName.c_str(), std::fstream::in );
    if ( !dictionaryFile.good() )
        return;

    std::string temp;
    while ( !dictionaryFile.eof() )
    {
        dictionaryFile >> temp;
        dictionary.push_back( temp );
    }

    dictionaryFile.close();

    std::cout << "  > DONE\n";
}

//---------------------------------------------------------------

void DictionaryLoader::LoadFCFile( std::vector< std::string >& dictionary, const std::string& fileName )
{
    std::cout << "--> Loading dictionary from FC file...\n";

    dictionary.clear();

    std::fstream dictionaryFile;
    dictionaryFile.open( fileName.c_str(), std::fstream::in );
    if ( !dictionaryFile.good() )
        return;

    std::string temp;
    std::string a, b, c;
    while ( !dictionaryFile.eof() )
    {
        dictionaryFile >> temp >> a >> b >> c;
        dictionary.push_back( temp );
    }

    dictionaryFile.close();

    std::cout << "  > DONE\n";
}

//---------------------------------------------------------------
