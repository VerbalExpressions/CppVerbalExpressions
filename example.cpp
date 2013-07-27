#include "verbalexpressions.hpp"
#include <iostream>
#include <string>

int main() {

    // Create an example of how to test for correctly formed URLs
    VerEx expr = VerEx()
                .searchOneLine()
                .startOfLine()
                .then( "http" )
                .maybe( "s" )
                .then( "://" )
                .maybe( "www." )
                .anythingBut( " " )
                .endOfLine();

    // Use VerEx's test() function to find if it matches
    std::cout << expr.test("https://www.google.com") << std::endl;

    // Ouputs the actual expression used: ^(?:http)(?:s)?(?:://)(?:www.)?(?:[^ ]*)$
    std::cout << expr << std::endl;


    // Create a test string
    std::string replaceMe = "Replace bird with a duck";
    // Create an expression that seeks for word "bird"
    VerEx expr2 = VerEx().find("bird");
    // Execute the expression
    std::cout << expr2.replace(replaceMe, "duck") << std::endl;

    // Shorthand string replace
    std::cout << VerEx().find( "red" ).replace( "We have a red house", "blue" ) << std::endl;
    return 0;
}