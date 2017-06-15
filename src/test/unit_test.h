////
//// Created by artef on 15.06.2017.
////
//
//#ifndef PLAYIN_UNIT_TEST_H
//#define PLAYIN_UNIT_TEST_H
//
//#include <iostream>
//#include "VBOTest/VBOTest.h"
//#include <vector>
//#include <tuple>
//
//#include <boost/log/utility/unique_identifier_name.hpp>
//#include <boost/exception/diagnostic_information.hpp>
//
//using namespace std;
//
//std::vector<std::tuple<void (*)(void), std::string, std::string, int> > tests;
//
//int main(int argc, char **argv) {
//
//    cout << "Running tests..." << endl;
//    cout << "____________________________________________" << endl;
//
//    int success = 0;
//    int fail = 0;
//
//    vector<std::tuple<std::string, std::string, int> > failed_tests;
//
//    for (auto &v : tests) {
//
//        cout << "Running test: \"" << std::get<1>(v) << "\":" << endl;
//        cout << std::get<2>(v) << ":" << std::get<3>(v) << endl;
//        try {
//            (*(std::get<0>(v)))();
//            success += 1;
//            cout << endl << "Success." << endl;
//        } catch (...) {
//            auto msg = boost::current_exception_diagnostic_information();
//            failed_tests.push_back(std::tuple<std::string, std::string, int>(
//                    msg,
//                    std::get<2>(v),
//                    std::get<3>(v)
//            ));
//
//            fail += 1;
//            cout << endl << "Failed." << endl;
//        }
//        cout << endl;
//
//    }
//
//    cout << "____________________________________________" << endl;
//    cout << "Failed tests:" << endl;
//
//    cout << "____________________________________________" << endl;
//    cout << "Success: " << success << endl;
//    cout << "Fail: " << fail << endl;
//}
//
//#define PPCAT_NX(A, B) A ## B
//#define PPCAT(A, B) PPCAT_NX(A, B)
//
//#define TEST_CASE_NAMED(name, unique_name)\
//void PPCAT(foo_,unique_name)(void);\
//namespace PPCAT(generic_namespace_,unique_name) {\
//    int o = ( tests.push_back( \
//        tuple<void (*)(void), std::string, std::string, int>( \
//            &PPCAT(foo_,unique_name),name,__FILE__,__LINE__)\
//        )\
//    ,0);\
//}\
//void PPCAT(foo_,unique_name)(void)
//
//#define TEST_CASE(name)\
//    TEST_CASE_NAMED(name, BOOST_LOG_UNIQUE_IDENTIFIER_NAME(test_scope_) )
//
//#endif // PLAYIN_UNIT_TEST_H