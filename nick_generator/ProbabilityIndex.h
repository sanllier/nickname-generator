#ifndef _PROBABILITY_INDEX_
#define _PROBABILITY_INDEX_
//---------------------------------------------------------------

#include <map>
#include <vector>
#include <string>

//---------------------------------------------------------------

class ProbabilityIndex
{
private:
    struct SFollowerData
    {
        long amount;
        float probability;
        char follower;

        void Inc() { ++amount; }        

        SFollowerData()
            : amount(0)
            , probability(0.0f)        
            , follower(0)
        {}
    };

public:
    ProbabilityIndex();
    ~ProbabilityIndex();

    void Build( const std::vector< std::string >& data, size_t seedLen );
    char GetNext( const char* root, bool needNormalize = false ) const;

    void GetRoots( std::vector< std::string >& roots ) const;

private:
    inline char Normalize( char ch ) const;

private:
    const int ENGLISH_ALPHABET_SIZE = 26;

    std::map< std::string, std::vector< SFollowerData > > m_index;
    size_t m_seedLen;
};

//---------------------------------------------------------------
#endif