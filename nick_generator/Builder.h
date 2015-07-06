#ifndef _BUILDER_
#define _BUILDER_
//---------------------------------------------------------------

#include <string>
#include "ProbabilityIndex.h"

//---------------------------------------------------------------

class Builder
{
private:
    enum 
    {
        AA   = 0,
        AAA  = 1,
        AAAA = 2
    };

public:
    Builder( const ProbabilityIndex* aa, const ProbabilityIndex* aaa = 0, const ProbabilityIndex* aaaa = 0 );

    std::string Build( int len );

private:
    const ProbabilityIndex* m_index[3];
};

//---------------------------------------------------------------
#endif