#include "Builder.h"

#include <cstdlib>

//---------------------------------------------------------------

Builder::Builder( const ProbabilityIndex* aa, const ProbabilityIndex* aaa/* = 0*/, const ProbabilityIndex* aaaa/* = 0*/ )
{
    m_index[AA] = aa;
    m_index[AAA] = aaa;
    m_index[AAAA] = aaaa;
}

//---------------------------------------------------------------

std::string Builder::Build( int len )
{
    const ProbabilityIndex* index = 0;

    if ( len > 5 && m_index[AAAA] != 0 )
        index = m_index[AAAA];
    else if ( len > 4 && m_index[AAA] != 0 )
        index = m_index[AAA];
    else if ( len > 3 && m_index[AA] != 0 )
        index = m_index[AA];

    if ( index == 0 )
        return "";

    std::vector< std::string > roots;
    index->GetRoots( roots );

    const int rootIndex = rand() % roots.size();
    std::string gen = roots[ rootIndex ];

    int pos = 0;
    while ( int( gen.length() ) < len )
    {
       const char nextSymb = index->GetNext( &gen[pos++] );
       if ( nextSymb != 0 )
           gen += nextSymb;
       else           
          break;
    }

    return gen;
}

//---------------------------------------------------------------
