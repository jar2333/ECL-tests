#ifndef ECL_HPP
#define ECL_HPP

#include <ecl/ecl.h>

#include <string>
#include <concepts>

// CREDIT: Autolykos, Chris Kohlhepp

#define DEFUN(name, fun) ECL::defun(#name, fun)

namespace ECL {

    template <typename T> 
    void defun(const std::string &name, T fun) { //add constraints to check if lambda
        defun(name, +fun);
    }

    template <std::same_as<cl_object>... Args>
    void defun(const std::string &name, cl_object(*fun)(Args... args)) {
        ecl_def_c_function(c_string_to_object(name.c_str()), (cl_objectfn_fixed)fun, sizeof...(Args));
    }

    // Run arbitrary Lisp expressions
    inline cl_object eval(const std::string &call) {
        return cl_safe_eval(c_string_to_object(call.c_str()), Cnil, Cnil);
    }

    // Some conversions
    inline std::string to_str(cl_object str) {
        if (cl_stringp(str)) {
            return std::string((char*)str->string.self);
        }
        else { 
            return std::string();
        }
    }

    // Initialisation does the following
    // 1) "Bootstrap" the lisp runtime
    // 2) Load an initrc to provide initial
    //    configuration for our Lisp runtime
    // 3) Make our accessors available to Lisp
    // 4) Any In-line Lisp functions for later reference
    void initialize(int argc, char **argv) {
        // Bootstrap
        cl_boot(argc, argv);
        atexit(cl_shutdown);

        // Run initrc script
        eval("(load \"initrc.lisp\")");
    }

    void shutdown() {
        cl_shutdown();
    }
}

#endif // ECL_HPP