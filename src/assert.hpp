#pragma once

#include <boost/exception/all.hpp>
#include <boost/exception/diagnostic_information.hpp>
#include <string>

typedef boost::error_info<struct tag_error_info, std::string> err_msg;

//! All errors we use should derive from BaseError.
//!
//! Please don't catch BaseError itself, as you'd also be catching all
//! FatalErrors.
struct BaseError : virtual boost::exception, virtual std::exception {};
struct RecoverableError : BaseError {};
struct FatalError : BaseError {};
struct AssertionError : FatalError {};

#ifndef NDEBUG
    #define ASSERT(expr) do {\
        if (expr);\
        else {\
            std::string error = "Assertion failed: '";\
            error += #expr;\
            error += "'.";\
            BOOST_THROW_EXCEPTION(AssertionError() << err_msg(error));\
        }\
    } while(false)
#else
    #define ASSERT(expr) do {} while(false)
#endif

template<typename EXCEPTION, typename CharT, typename Traits>
void print_diagnostic_info(std::basic_ostream<CharT, Traits>& o, EXCEPTION const& e) {
#ifndef NDEBUG
    o << boost::diagnostic_information(e) << std::endl;
#else
    (void)o;
    (void)e;
#endif
}
