CppVerbalExpressions
====================


## C++ Regular Expressions made easy
VerbalExpressions is a C++11 Header library that helps to construct difficult regular expressions.

This C++ lib is based off of the (original) Javascript [VerbalExpressions](https://github.com/jehna/VerbalExpressions) library by [jehna](https://github.com/jehna/).

## Other Implementations
You can see an up to date list of all ports on [VerbalExpressions.github.io](http://VerbalExpressions.github.io).
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
verex expr = verex()
            .search_one_line()
            .start_of_line()
            .then( "http" )
            .maybe( "s" )
            .then( "://" )
            .maybe( "www." )
            .anything_but( " " )
            .end_of_line();

// Use verex's test() function to find if it matches
std::cout << expr.test("https://www.google.com") << std::endl;

// Ouputs the actual expression used: ^(?:http)(?:s)?(?:://)(?:www.)?(?:[^ ]*)$
std::cout << expr << std::endl;
```

### Replacing strings

```c++
// Create a test string
std::string replaceMe = "Replace bird with a duck";
// Create an expression that seeks for word "bird"
verex expr2 = verex().find("bird");
// Execute the expression
std::cout << expr2.replace(replaceMe, "duck") << std::endl;
```

### Shorthand for string replace:

```c++
std::cout << verex().find( "red" ).replace( "We have a red house", "blue" ) << std::endl;
```




Here you can find the API documentation for Verbal Expressions

## Basic usage
Basic usage of Verbal Expressions starts from the expression `verex()`. You can chain methods afterwards. Those are described under the "terms" section.

```c++
auto expr = verex();
```

##API

### Terms
* .anything()
* .anything_but( const std::string & value )
* .something()
* .something_but(const std::string & value)
* .end_of_line()
* .find( const std::string & value )
* .maybe( const std::string & value )
* .start_of_line()
* .then( const std::string & value )

### Special characters and groups
* .any( const std::string & value )
* .any_of( const std::string & value )
* .br()
* .linebreak()
* .range( const std::initializer_list<std::string> & args )
* .tab()
* .word()

### Modifiers
* .with_any_case()
* .search_one_line()
* .search_global()

### Functions
* .replace( const std::string & source, const std::string & value )
* .test()

### Other
* .add( expression )
* .multiple( const std::string & value )
* .alt()
