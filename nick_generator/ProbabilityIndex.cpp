#include "ProbabilityIndex.h"

#include <iostream>
#include <algorithm>
#include <cstdlib>

//---------------------------------------------------------------

ProbabilityIndex::ProbabilityIndex()
{

}

ProbabilityIndex::~ProbabilityIndex()
{
    
}

//---------------------------------------------------------------

void ProbabilityIndex::Build( const std::vector< std::string >& data, size_t seedLen )
{
    std::cout << "--> Building probability index for size: " << seedLen << "...\n";

    m_index.clear();
    m_seedLen = seedLen;

    long total = 0;

    for ( const auto& item : data )
    {
        for ( int i = m_seedLen; i < int( item.length() ); ++i )
        {
            std::string root( &item[i - m_seedLen], &item[i] );
            for ( int q = 0; q < int( m_seedLen ); ++q )
                root[q] = Normalize( root[q] );

            auto found = m_index.find( root );

            if ( found == m_index.end() )
            {
                auto& node = m_index[ root ];
                node.resize( ENGLISH_ALPHABET_SIZE + 1 );
                for ( int q = 0; q < ENGLISH_ALPHABET_SIZE; ++q )
                    node[q].follower = 'a' + q;

                node[ Normalize(item[i]) - 'a' ].Inc();
            }
            else
            {
                found->second[ Normalize(item[i]) - 'a' ].Inc();
            }

            ++total;
        }
    }

    std::cout << "  > Sorting...\n";

    for ( auto& item : m_index )
    {
        int total = 0;
        for ( auto ii = item.second.begin(); ii != item.second.end() - 1; ++ii )
            total += ii->amount;

        for ( auto ii = item.second.begin(); ii != item.second.end() - 1; ++ii )
            ii->probability = total > 0.0f ? float( ii->amount ) / float( total ) : 0.0f;

        std::sort( item.second.begin(), item.second.end() - 1, 
            []( const SFollowerData& a, const SFollowerData& b ){ return a.probability < b.probability; } );
    }

    std::cout << "  > DONE\n";
}

//---------------------------------------------------------------

char ProbabilityIndex::GetNext( const char* root, bool needNomalize/* = false*/ ) const
{    
    if ( root == 0 )
        return 0;

    static std::string buf;
    if ( buf.length() != m_seedLen )
        buf.resize( m_seedLen );

    memcpy( &buf[0], root, m_seedLen );
    if ( needNomalize )
        for ( int i = 0; i < int( m_seedLen ); ++i )
            buf[i] = Normalize(buf[i]);

    const auto& found = m_index.find( root );
    if ( found == m_index.end() )
        return 0;

    const auto& node = found->second;
    const float probability = float( rand() ) / float( RAND_MAX );
    float sum = 0.0f;
    for ( int i = 0; i < ENGLISH_ALPHABET_SIZE; ++i )
    {
        sum += node[i].probability;
        if ( sum > probability )
            return node[i].follower;
    }

    return 0;
}

//---------------------------------------------------------------

void ProbabilityIndex::GetRoots( std::vector< std::string >& roots ) const
{
    roots.resize( m_index.size() );
    int pos = 0;

    for ( const auto& item : m_index )
        roots[pos++] = item.first;
}

//---------------------------------------------------------------

inline char ProbabilityIndex::Normalize( char ch ) const
{
    if ( ( ch < 'a' || ch > 'z' ) && ( ch < 'A' || ch > 'Z' ) )
        return 'z' + 1;

    return ch < 'a' ? 'a' + ch - 'A' : ch;
}

//---------------------------------------------------------------
