#include "ecl.hpp"

#include <iostream>

#include <chrono>
#include <thread>

#include <dlfcn.h>

#define SLEEP(x) std::this_thread::sleep_for(std::chrono::seconds(x))

void runTest(int (*fun)(int)) {
    auto start = std::chrono::high_resolution_clock::now();
    printf("40th fibonacci from dynamic library: %d\n", (*fun)(40));
    auto end = std::chrono::high_resolution_clock::now();

    auto elapsed =  std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    std::cout << "RUNTIME IN NANOSECONDS " << elapsed.count() << "ns \n" << std::endl;
}

void runDynamic() {
    void *handle;
    int (*fibonacci)(int);
    char *error;

   handle = dlopen("./src/fibonacci.so", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "%s\n", dlerror());
        exit(EXIT_FAILURE);
    }

   dlerror();    /* Clear any existing error */

   /* Writing: fibonacci = (double (*)(double)) dlsym(handle, "fib");
       would seem more natural, but the C99 standard leaves
       casting from "void *" to a function pointer undefined.
       The assignment used below is the POSIX.1-2003 (Technical
       Corrigendum 1) workaround; see the Rationale for the
       POSIX specification of dlsym(). */

   *(void **) (&fibonacci) = dlsym(handle, "fib");

   if ((error = dlerror()) != NULL)  {
        fprintf(stderr, "%s\n", error);
        exit(EXIT_FAILURE);
    }

    //RUN TEST!!!
    runTest(fibonacci);

    dlclose(handle);
}

void runLoaded() {
    ECL::eval("(load \"src/scripts/fibonacci.fas\")");

    runTest([](int v) -> int {
        return ecl_to_int(ECL::eval("(fib "+std::to_string(v)+')'));
    });
    

}

int main(int argc, char* argv[]) {
    // Bootstrap Lisp
    ECL::initialize(argc, argv);

    runDynamic();
    runLoaded();

    ECL::shutdown();
    return EXIT_SUCCESS;
}