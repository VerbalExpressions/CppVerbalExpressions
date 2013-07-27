CppVerbalExpressions
====================


VerbalExpressions v0.1
=====================

## C++ Regular Expressions made easy
VerbalExpressions is a C++11 Header library that helps to construct difficult regular expressions.

This C++ lib is based off of the (original) Javascript [VerbalExpressions](https://github.com/jehna/VerbalExpressions) library by [jenha](https://github.com/jehna/).

## Other Implementations
You can see an up to date list of all ports in our [organization](https://github.com/VerbalExpressions).
- [Ruby](https://github.com/VerbalExpressions/RubyVerbalExpressions)
- [C#](https://github.com/VerbalExpressions/CSharpVerbalExpressions)
- [Python](https://github.com/VerbalExpressions/PythonVerbalExpressions)
- [Java](https://github.com/VerbalExpressions/JavaVerbalExpressions)
- [PHP](https://github.com/VerbalExpressions/PHPVerbalExpressions)

## How to get started

C++11 support for regex is still poor in the standard library, you will likely need boost_regex.
Download / set that up, then try the example file. Once C++ standard supports <regex> decently it will be painless to switch. 

## Examples

Here's a couple of simple examples to give an idea of how VerbalExpressions works:

### Testing if we have a valid URL

```c++
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
```

### Replacing strings

```c++
// Create a test string
std::string replaceMe = "Replace bird with a duck";
// Create an expression that seeks for word "bird"
VerEx expr2 = VerEx().find("bird");
// Execute the expression
std::cout << expr2.replace(replaceMe, "duck") << std::endl;
```

### Shorthand for string replace:

```c++
std::cout << VerEx().find( "red" ).replace( "We have a red house", "blue" ) << std::endl;
```




Here you can find the API documentation for Verbal Expressions

## Basic usage
Basic usage of Verbal Expressions is through a singleton, called `VerEx()`, that creates a new expression for you:
```c++
auto expr = VerEx();
```

##API 

### Terms
* .anything()
* .anythingBut( value )
* .something()
* .somethingBut(value)
* .endOfLine()
* .find( value )
* .maybe( value )
* .startOfLine()
* .then( value )

### Special characters and groups
* .any( value )
* .anyOf( value )
* .br()
* .lineBreak()
* .range( from, to )
* .tab()
* .word()

### Modifiers
* .withAnyCase()
* .searchOneLine()
* .searchGlobal()

### Functions
* .replace( source, value )
* .test()

### Other
* .add( expression )
* .multiple( value )
* .alt()