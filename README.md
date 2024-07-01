# function-parser
Library to parsing mathematical expressions.

We define grammar in the way given below.

```regexp
sin -> "sin"
cos -> "cos"
tan -> "tan"
cot -> "cot"
sqrt -> "sqrt"
cbrt -> "cbrt"

function_kw -> sin | cos | tan | cot | sqrt | cbrt

number -> (([1-9][0-9]*)|0)(\.[0-9]*)?
atom -> "x"
addition -> addition+addition | atom | number
```