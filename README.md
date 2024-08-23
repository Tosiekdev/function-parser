# Function parser

## Brief
This header only library provides interface for parsing mathematical
functions of one variable.

## Installation
Library itself is (one) header only, so the easiest way is just putting
it into your project. However, it depends on 
[lexy](https://github.com/foonathan/lexy) parsing library. Author of 
lexy suggests adding following lines to cmake to make everything work.
```cmake
include(FetchContent)
FetchContent_Declare(lexy URL https://lexy.foonathan.net/download/lexy-src.zip)

FetchContent_MakeAvailable(lexy)
target_link_libraries(project_name foonathan::lexy)
```

## Usage
To use this library you only have to include `function_parser.hpp` in 
your project.
```c++
#include <az_math/function_parser.hpp>
```
Having library include, expression parsing can be done by using 
function `parse_expression` which takes int as an argument and returns
`std::shared_ptr` to abstract class `az::Production`. If parsing 
doesn't generate value, `nullptr` is returned.
```c++
std::string expr = /*string expression*/;
std::shared_ptr<az::Production> function = az::parse_expression(expr);
if (!function) {
    // rise error...
} else {
// do something...
}
```
`Production` interface provides function `evaluate` to calculating 
obtained function value for given x.
```c++
double x = 3.14;
double value = function->evaluate(x);
```

## Syntax
Library parses expressions based on positive decimal numbers and 
*x* variable. This atoms can be merged using following operators:
`+ - * / ^`.

Negative value is possible to obtain by using `-` operator, e.g.
`-3.14`.

There is also possibility to use some of the basic math functions using
expression `function_kw(x)`. Library supports this function keywords:
* `sin` - calculates sine,
* `cos` - calculates cosine,
* `tan` - calculates tangent,
* `cot` - calculates cotangent,
* `sqrt` - calculates square root,
* `cbrt` - calculates cube root.
* `ln` - calculates natural logarithm.
* `log` - calculates base 10 logarithm.
* `lg` - calculates base 2 logarithm.
* `arcsin` - calculates arcsine.
* `arccos` - calculates arccosine.
* `arctan` - calculates arctangent.

Operation order is preserved and brackets are supported to force 
operation order. Example:
```c++
std::string expr = "6/3*(x+1)";
std::shared_ptr<az::Production> function = az::parse_expression(expr);
function->evaluate(2); // will be evaluated as ((6/3)*(2+1))->(2*3)->(6)
```
