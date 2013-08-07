CppVerbalExpressions
====================


## C++ Regular Expressions made easy
VerbalExpressions is a C++11 Header library that helps to construct difficult regular expressions.

This C++ lib is based off of the (original) Javascript [VerbalExpressions](https://github.com/jehna/VerbalExpressions) library by [jehna](https://github.com/jehna/).

## Other Implementations
You can see an up to date list of all ports in our [organization](https://github.com/VerbalExpressions).
- [Javascript](https://github.com/jehna/VerbalExpressions)
- [Ruby](https://github.com/VerbalExpressions/RubyVerbalExpressions)
- [C#](https://github.com/VerbalExpressions/CSharpVerbalExpressions)
- [Python](https://github.com/VerbalExpressions/PythonVerbalExpressions)
- [Java](https://github.com/VerbalExpressions/JavaVerbalExpressions)
- [PHP](https://github.com/VerbalExpressions/PHPVerbalExpressions)

## How to get started

In case you do not have C++11 compliant standard library you can still use boost.regex.

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
Basic usage of Verbal Expressions starts from the expression `VerEx()`. You can chain methods afterwards. Those are described under the "terms" section.

```c++
auto expr = VerEx();
```

##API 

### Terms
* .anything()
* .anythingBut( const std::string & value )
* .something()
* .somethingBut(const std::string & value)
* .endOfLine()
* .find( const std::string & value )
* .maybe( const std::string & value )
* .startOfLine()
* .then( const std::string & value )

### Special characters and groups
* .any( const std::string & value )
* .anyOf( const std::string & value )
* .br()
* .lineBreak()
* .range( const std::initializer_list<std::string> & args )
* .tab()
* .word()

### Modifiers
* .withAnyCase()
* .searchOneLine()
* .searchGlobal()

### Functions
* .replace( const std::string & source, const std::string & value )
* .test()

### Other
* .add( expression )
* .multiple( const std::string & value )
* .alt()
