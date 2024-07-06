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
atomic -> atom | number
addition -> atomic addition_p
addition_p -> "+" atomic addition_p | atomic
multiplication -> atomic multiplication_p
multiplication_p -> "+" atomic multiplication_p | atomic
exponentiation -> atomic exponentiation_p
exponentiation_p -> "+" atomic exponentiation_p | atomic
```