#include "Styler.h"

#include <cstdlib>

//---------------------------------------------------------------

Styler::~Styler()
{
    for ( int i = 0; i < m_styles.size(); ++i )
        delete m_styles[i];
}

//---------------------------------------------------------------

Styler& Styler::operator+=( IStyle* style )
{
    m_styles.push_back( style );
    return *this;
}

void Styler::Style( std::string& line )
{
    if ( m_styles.empty() )
        return;

    int styleIndex = 0;
    do 
    {
        const auto r = rand();
        if ( float(r) / float( RAND_MAX ) < 0.33f )
            return;

        styleIndex = r % m_styles.size();
    } while ( !(*m_styles[ styleIndex ])( line ) );
}

//---------------------------------------------------------------
