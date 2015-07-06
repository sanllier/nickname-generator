#ifndef _STYLES_
#define _STYLES_
//---------------------------------------------------------------

#include "Styler.h"

//---------------------------------------------------------------

class CapitalLetter: public IStyle
{
public:
    bool operator()( std::string& line ) override
    {
        if ( !line.empty() )
            line[0] = 'A' + line[0] - 'a';
        return true;
    }
};

//---------------------------------------------------------------

class EvenCapital: public IStyle
{
public:
    bool operator()( std::string& line ) override
    {        
        if ( !line.empty() )
            for ( int i = 1; i < int( line.length() ); i += 2 )
                line[i] = 'A' + line[i] - 'a';
        return true;
    }
};

//---------------------------------------------------------------

class OddCapital: public IStyle
{
public:
    bool operator()( std::string& line ) override
    {        
        if ( !line.empty() )
            for ( int i = 0; i < int( line.length() ); i += 2 )
                line[i] = 'A' + line[i] - 'a';
        return true;
    }
};

//---------------------------------------------------------------

class XModifier: public IStyle
{
public:
    bool operator()( std::string& line ) override
    {        
        if ( line.empty() )
            return true;

        std::string buf = line;

        bool applicable = false;
        for ( int i = 0; i < int( buf.length() ); ++i )
        {
            if ( buf[i] == 'x' )
            {
                buf[i] = '}';
                buf.insert( buf.begin() + i, '{' );
                applicable = true;
            }
        }

        if ( applicable && buf.length() <= 10 )
        {
            line = buf;
            return true;
        }

        return false;
    }
};

//---------------------------------------------------------------

class OModifier: public IStyle
{
public:
    bool operator()( std::string& line ) override
    {        
        if ( line.empty() )
            return true;

        bool applicable = false;
        for ( int i = 0; i < int( line.length() ); ++i )
        {
            if ( line[i] == 'o' )
            {
                line[i] = '0';
                applicable = true;
            }
        }

        return applicable;
    }
};

//---------------------------------------------------------------

class LIModifier: public IStyle
{
public:
    bool operator()( std::string& line ) override
    {        
        if ( line.empty() )
            return true;

        bool applicable = false;
        for ( int i = 0; i < int( line.length() ); ++i )
        {
            if ( line[i] == 'l' || line[i] == 'i' )
            {
                line[i] = '1';
                applicable = true;
            }
        }

        return applicable;
    }
};

//---------------------------------------------------------------

class SurroundUnderline: public IStyle
{
public:
    bool operator()( std::string& line ) override
    {        
        if ( line.length() > 8 )
            return false;

        line.insert( line.begin(), '_' );
        line += '_';

        return true;
    }
};

//---------------------------------------------------------------

class AModifier: public IStyle
{
public:
    bool operator()( std::string& line ) override
    {        
        if ( line.empty() )
            return true;

        bool applicable = false;
        for ( int i = 0; i < int( line.length() ); ++i )
        {
            if ( line[i] == 'a' )
            {
                line[i] = '@';
                applicable = true;
            }
        }

        return applicable;
    }
};

//---------------------------------------------------------------

class TwoLetterYearModifier: public IStyle
{
public:
    bool operator()( std::string& line ) override
    {        
        if ( line.empty() )
            return true;

        if ( line.length() > 7 )
            return false;

        const int BRIDGES_NUM = 2;
        char bridges[ BRIDGES_NUM ] = { '_', '@' };
        int r = rand() % (BRIDGES_NUM + 1);
       
        if ( r < BRIDGES_NUM )
            line += bridges[r];

        const int DISPERSIA = 15;
        int year = 99 - rand() % DISPERSIA;
        line += std::to_string( year );

        return true;
    }
};

//---------------------------------------------------------------

class FourLetterYearModifier: public IStyle
{
public:
    bool operator()( std::string& line ) override
    {        
        if ( line.empty() )
            return true;

        if ( line.length() > 4 )
            return false;

        const int DISPERSIA = 26;
        int year = 2002 - rand() % DISPERSIA;
        line += std::to_string( year );

        return true;
    }
};

//---------------------------------------------------------------
#endif