# Function parser

## Brief
This header only library provides interface for parsing mathematical
functions of one variable.

## Usage
To use this library you only have to include `function_parser.hpp` in 
your project.
```c++
#include <az_math/function_parser.hpp>
```
Having library include, expression parsing can be done by using 
function `parse_expression` which takes int as an argument and returns
`std::shared_ptr` to abstract class `az::Production`. If parsing 
doesn't generate value, nullptr is returned.
```c++
std::string expr = /*string expression*/;
std::shared_ptr<az::Production> function = az::parse_expression(expr);
if (!function) {
    // rise error...
}
// do something...
```
`Production` interface provides function `evaluate` to calculating 
obtained function value for given x.
```c++
double x = 3.14;
double value = function->evaluate(x);
```