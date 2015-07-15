/*!
 * VerbalExpressions C++ Library v0.1
 * https://github.com/whackashoe/C++VerbalExpressions
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2013 whackashoe
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef VERBAL_EXPRESSIONS_H_
#define VERBAL_EXPRESSIONS_H_

#define USE_BOOST

#ifdef USE_BOOST
#include <boost/regex.hpp>
namespace veregex = boost;
#else
#include <regex>
namespace veregex = std;
#endif

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class verex
{
private:
    std::string prefixes;
    std::string source;
    std::string suffixes;
    std::string pattern;
    enum Flags { GLOBAL = 1,
                 MULTILINE = 2,
                 CASEINSENSITIVE = 4 };

    friend std::ostream& operator<<(std::ostream &strm, verex &v)
    {
        return strm << v.pattern;
    }

    unsigned int check_flags()
    {
        unsigned int result = 0;
        if(modifiers & CASEINSENSITIVE) result |= veregex::regex::icase;
        return result;
    }

    const std::string reduce_lines(const std::string & value)
    {
        std::string ret = value;
        std::size_t pos = ret.find("\n");
        if(pos == std::string::npos) return ret;
        return ret.substr(0, pos);
    }

public:
    unsigned int modifiers;

    verex() : prefixes(""),
              source(""),
              suffixes(""),
              pattern(""),
              modifiers(0){};

    verex& operator=(const verex& ve) = default;
    ~verex() = default;

    verex & add(const std::string & value)
    {
        source = source + value;
        pattern = prefixes + source + suffixes;
        return (*this);
    }

    verex & start_of_line(bool enable)
    {
        prefixes = enable ? "^" : "";
        return add("");
    }

    inline verex & start_of_line()
    {
        return start_of_line(true);
    }

    verex & end_of_line(bool enable)
    {
        suffixes = enable ? "$" : "";
        return add("");
    }

    inline verex & end_of_line()
    {
        return end_of_line(true);
    }

    verex & then(const std::string & value)
    {
        return add("(?:" + value + ")");
    }

    verex & find(const std::string & value)
    {
        return then(value);
    }

    verex & maybe(const std::string & value)
    {
        return add("(?:" + value + ")?");
    }

    verex & anything()
    {
        return add("(?:.*)");
    }

    verex & anything_but(const std::string & value)
    {
        return add("(?:[^" + value + "]*)");
    }

    verex & something()
    {
        return add("(?:.+)");
    }

    verex & something_but(const std::string & value)
    {
        return add("(?:[^" + value + "]+)");
    }

    const std::string replace(const std::string & source, const std::string & value)
    {
        return veregex::regex_replace(  source,
                                        veregex::regex(pattern, check_flags()), 
                                        value);
    }

    verex & linebreak()
    {
        return add("(?:(?:\\n)|(?:\\r\\n))");
    }

    inline verex & br()
    {
        return linebreak();
    }

    verex & tab()
    {
        return add("\\t");
    }

    verex & word()
    {
        return add("\\w+");
    }

    verex & any_of(const std::string & value)
    {
        return add( "[" + value + "]" );
    }

    verex & any(const std::string & value)
    {
        return any_of(value);
    }

    verex & range(std::vector<std::string> args)
    {
        std::stringstream value;
        value << "[";

        for(unsigned int _from = 0; _from < args.size(); _from += 2) {
            unsigned int _to = _from+1;
            if (args.size() <= _to) break;

            int from = atoi(args[_from].c_str());
            int to = atoi(args[_to].c_str());

            value << from << "-" << to;
        }

        value << "]";

        return add(value.str());
    }

    verex & add_modifier(char modifier)
    {
        switch (modifier) {
            case 'i':
                modifiers |= CASEINSENSITIVE;
                break;
            case 'm':
                modifiers |= MULTILINE;
                break;
            case 'g':
                modifiers |= GLOBAL;
                break;
            default:
                break;
        }

        return (*this);
    }

    verex & remove_modifier(char modifier)
    {
        switch (modifier) {
            case 'i':
                modifiers ^= CASEINSENSITIVE;
                break;
            case 'm':
                modifiers ^= MULTILINE;
                break;
            case 'g':
                modifiers ^= GLOBAL;
                break;
            default:
                break;
        }

        return (*this);
    }


    verex & with_any_case(bool enable)
    {
        if (enable) add_modifier( 'i' );
        else remove_modifier( 'i' );
        return (*this);
    }

    inline verex & with_any_case()
    {
        return with_any_case(true);
    }

    verex & search_one_line(bool enable)
    {
        if (enable) remove_modifier( 'm' );
        else add_modifier( 'm' );
        return (*this);
    }

    inline verex & search_one_line()
    {
        return search_one_line(true);
    }

    verex & search_global(bool enable)
    {
        if (enable) add_modifier( 'g' );
        else remove_modifier( 'g' );
        return (*this);
    }

    inline verex & search_global()
    {
        return search_global(true);
    }

    verex & multiple(const std::string & value)
    {
        if(value.at(0) != '*' && value.at(0) != '+')
            add("+");

        return add(value);
    }

    verex & alt(const std::string & value)
    {
        if (prefixes.find("(") == std::string::npos) prefixes += "(";
        if (suffixes.find(")") == std::string::npos) suffixes = ")" + suffixes;

        add( ")|(" );
        return then(value);
    }

    bool test(const std::string & value)
    {
        std::string toTest;
        if(modifiers & MULTILINE) toTest = value;
        else                      toTest = reduce_lines(value);

        if(modifiers & GLOBAL)
            return veregex::regex_search(toTest, veregex::regex(pattern, check_flags()));
        else
            return veregex::regex_match(toTest, veregex::regex(pattern, check_flags()));
    }
};

#endif
