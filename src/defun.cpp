#include "ecl.hpp"

#include <iostream>

cl_object example() {
    return ecl_make_integer(3);
}

int main(int argc, char* argv[]) {
    // Bootstrap Lisp
    ecl::initialize(argc, argv);

    // ecl::defun("example", example);
    
    ecl::defun("example", [](){
        return ecl_make_integer(3);
    });

    cl_env_ptr env = ecl_process_env();
    ECL_CATCH_ALL_BEGIN(env) {
    /*
    * Code that is protected. Uncaught lisp conditions, THROW,
    * signals such as SIGSEGV and SIGBUS may cause jump to
    * this region.
    */
        std::cout << ecl_to_int(ecl::eval("(example)")) << std::endl;
    } ECL_CATCH_ALL_IF_CAUGHT {
    /*
    * If the exception, lisp condition or other control transfer
    * is caught, this code is executed.
    */
        std::cout << "ERROR!!!";
    } ECL_CATCH_ALL_END;
    /*
    * In all cases we exit here.
    */
    

    return EXIT_SUCCESS;
}