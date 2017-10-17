backtrace() shows list of functions call stack
Example:
0   a.out                               0x000000010769ddfa show + 42
1   libfoo.so                           0x00000001076d3f8b foo + 11
2   a.out                               0x000000010769deef main + 143

This is awesome

What does it does when foo is in an external lib,
	and the external lib is dynamically loaded with dlopen,
	and that we close the lib handle before calling backtrace?

0   a.out                               0x000000010cd23dbe show + 46
1   ???                                 0x000000010cd59f8b 0x0 + 4510293899
2   a.out                               0x000000010cd23ebd main + 173

kek

But once show() returns, it returns into the closed lib...
[1]    56944 segmentation fault  ./a.out

So we must goto back into main, but goto works only inside a function, so ket's use setjmp and longjmp

0   a.out                               0x000000010cd23dbe show + 46
1   ???                                 0x000000010cd59f8b 0x0 + 4510293899
2   a.out                               0x000000010cd23ebd main + 173
Done!

This program workflow is wonderful.
