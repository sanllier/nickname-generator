#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <string>
#include <fstream>

#include "DictionaryLoader.h"
#include "ProbabilityIndex.h"
#include "Builder.h"
#include "Styler.h"
#include "Styles.h"

//--------------------------------------------------------------------------

int main( int argc, char** argv )
{
    srand( (unsigned int)(time(0)) );

    std::vector< std::string > dictionary;
    //DictionaryLoader::LoadNLSeparetedFile( dictionary, "test.txt" );
    DictionaryLoader::LoadFCFile( dictionary, "names.fc" );

    //ProbabilityIndex index_aa;
    //index_aa.Build( dictionary, 2 );

    ProbabilityIndex index_aaa;
    index_aaa.Build( dictionary, 3 );

    //ProbabilityIndex index_aaaa;
    //index_aaaa.Build( dictionary, 4 );

    Builder builder( 0, &index_aaa, 0 );

    Styler styler;
    styler += new CapitalLetter();
    styler += new EvenCapital();
    styler += new OddCapital();
    styler += new XModifier();
    styler += new OModifier();
    styler += new AModifier();
    styler += new LIModifier();
    styler += new SurroundUnderline();
    styler += new TwoLetterYearModifier();
    styler += new FourLetterYearModifier();

    const int TARGET_AMOUNT = 10000;
    const int MAX_LEN = 10;
    const int DISPERSIA = 5;

    std::vector< std::string > generated;
    generated.resize(TARGET_AMOUNT);

    for ( int i = 0; i < TARGET_AMOUNT; ++i )
    {
        if ( i % 50 == 0 )
            std::cout << "  > " << i << "/" << TARGET_AMOUNT << "\n";

        generated[i] = builder.Build( MAX_LEN - rand() % DISPERSIA );
        styler.Style( generated[i] );
    }
    
    std::cout << "  > " << TARGET_AMOUNT << "/" << TARGET_AMOUNT << "\n--> Saving in file...\n";

    std::fstream outFile;
    outFile.open( "generated.txt", std::fstream::out );
    for ( int i = 0; i < TARGET_AMOUNT; ++i )
        outFile << generated[i] << '\n';
    outFile.close();

    return 0;
}

//--------------------------------------------------------------------------
