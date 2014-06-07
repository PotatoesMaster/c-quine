Here is the code of a [quine](http://en.wikipedia.org/wiki/Quine_(computing)), a program that outputs its own source code:

[quine.c](quine.c):
```c
#define B(x)void main(){puts("#define B(x)"x"\n#define X(s)S(s)\n#define S(s)#s\nB(X(B(x)))");}
#define X(s)S(s)
#define S(s)#s
B(X(B(x)))
```

## How it works
_Disclaimer: C processor macros are a pain to explain, I am not going into details._

### Macro stringization
```c
#define X(s) S(s)
#define S(s) #s
```

`X` is a preprocessor macro that takes an argument, expands the macros in it and transform the result to a string literal, thanks to the "stringize" operator (`#`).
We need two two macro function because one alone cannot expand macro in its argument.

*Example*
Supposing `var` is a defined by this line : `#define var 42`.
`S(var)` → `#var` → `"var"`: `S(var)` is replaced by the string literal `"var"`.
`X(var)` → `S(42)` → `#42` → `"42"`:  `X(var)` is replaced by the expansion of `var`, also as a string literal.

### Building the main function
```c
#define B(x) void main(){puts("#define B(x) "x"\n#define X(s)S(s)\n#define S(s)#s\nB(X(B(x)))");}
B(X(B(x)))
```

The body of the main function is defined by `B`.
The main function just calls `puts` to print its code, passed as a string literal.
The tricky part is the `x` argument of `B`. We pass to `B` its own definition.

This is achieved by the line `B(X(B(x)))`.

In the inner `B` call is passed the value `x` as argument. The `x` definition got replaced by the `x` passed as argument. `B(x)` is replaced by the exact definition of `B`:
```c
B(x) → void main(){puts("#define B(x) "x"\n#define X(s)S(s)\n#define S(s)#s\nB(X(B(x)))");}
```

This gets transformed in a string literal by the `X` macro:
```c
X(B(x)) → "void main(){puts(\"#define B(x) \"x\"\\n#define X(s)S(s)\\n#define S(s)#s\\nB(X(B(x)))\");}"
```

We pass this string literal to `B` again to give the program's main function:
```c
B(X(B(x))) → void main(){puts("#define B(x) ""void main(){puts(\"#define B(x) \"x\"\\n#define X(s)S(s)\\n#define S(s)#s\\nB(X(B(x)))\");}""\n#define X(s)S(s)\n#define S(s)#s\nB(X(B(x)))");}
```

Remember that two adjacent string literals are concatenated in C. `"abc" "def"`, or `"abc""def"` ends up being the same as `"abcdef"`. So ignore the double double-quotes.

So now we have our main function, and the complete code passed to `puts`.

## Links
This program is pretty simple. Peoples have done stuff a lot crazier, like [a spiraling quine in perl](https://github.com/mame/quine-relay), or [a quine relay of 50 languages](https://github.com/mame/quine-relay) (hard to see 50 languages in [that code](https://github.com/mame/quine-relay/blob/master/QR.rb), don't you think?).
