extern "C" void __stack_chk_fail(void) { }

namespace __cxxabiv1
{
/* guard variables */

/* WTF, G++ is forcing me to define this, but i have no clue what it does,
    * but it stopped a bug I had for a few days in here*/
    __extension__ typedef int __guard __attribute__((mode(__DI__)));

    extern "C" int __cxa_guard_acquire (__guard *);
    extern "C" void __cxa_guard_release (__guard *);
    extern "C" void __cxa_guard_abort (__guard *);

    extern "C" int __cxa_guard_acquire (__guard *g)
    {
        return !*(char *)(g);
    }

    extern "C" void __cxa_guard_release (__guard *g)
    {
        *(char *)g = 1;
    }

    extern "C" void __cxa_guard_abort (__guard *)
    {

    }

    extern "C" void __cxa_begin_catch(__guard*);
    extern "C" void __cxa_end_catch(__guard*);
    extern "C" void __gxx_personality_v0(__guard*);
}