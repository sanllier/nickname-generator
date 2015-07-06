#ifndef _STYLER_
#define _STYLER_
//---------------------------------------------------------------

#include <string>
#include <vector>

//---------------------------------------------------------------

class IStyle
{
public:
    virtual bool operator()( std::string& line ) = 0;
};

//---------------------------------------------------------------

class Styler
{
public:
    ~Styler();

    Styler& operator+=( IStyle* style );
    void Style( std::string& line );

private:
    std::vector< IStyle* > m_styles;
};

//---------------------------------------------------------------
#endif