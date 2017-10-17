// bt.c

// cc bt.c

// Tested on OS X Sierra 10.12.6

#include <stdio.h>
#include <execinfo.h>
#include <dlfcn.h>
#include <setjmp.h>

void *h = NULL;
jmp_buf env;

void show()
{
	void *data[50];
	
	// Close libfoo.so so that
	// (1) dladdr() called by backtrace() doesn't know about libfoo.so
	// (2) Returning from show() will segfault as libfoo.so calls show()
	dlclose(h);
	
	// Get call stack
	int ret = backtrace(data, 3);
	//printf("Backtrace ret %d\n", ret);

	// Print symbols
	backtrace_symbols_fd(data, ret, 1);

	// Jump back to main, setjmp() in main will return 42
	longjmp(env, 42);

	// Will segfault if return here
}

int main(int ac, char **av)
{
	int ret;
	
	// Will return 0 on first call
	// Will return 42 if called from longjmp()
	ret = setjmp(env);
	if (ret != 0)
		goto out; // Wonderful - works very well
	
	printf("Ret of setjmp is %d\n", ret);
	
	// Should check dlopen return val
	h = dlopen("libfoo.so", RTLD_LAZY);
	
	void *foo = dlsym(h, "foo"); // Get function pointer

	if (!foo)
	{
		printf("No foo\n");
		return 1;
	}
	
	void (*cb)(void) = foo;

	cb();

out:
	printf("Done!\n");
	
	return 0;
}
