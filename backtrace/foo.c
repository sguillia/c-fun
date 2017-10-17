// foo.c

// cc foo.c -shared -fPIC -o libfoo.so -Wl,-undefined,dynamic_lookup

// show() function is declared inside the main. I'm lazy and don't want to put it inside a lib.
// Let's ignore the undefined reference warning! (yes, undefined reference is a warning, not an error)

void show();

void foo()
{
	show();
}
