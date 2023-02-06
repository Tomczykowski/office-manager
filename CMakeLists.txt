cmake_minimum_required(VERSION 3.21)
project(projektproi2022_sekula_tomczykowski_pawlak)

set(CMAKE_CXX_STANDARD 14)

include_directories(Company)
include_directories(Currency)
include_directories(Invoice)
include_directories(Office)
include_directories(Person)
include_directories(Tax)
include_directories(TaxFunctions)
include_directories(UnitTests)
include_directories(UnitTests/CurrencyUnitTest)
include_directories(UnitTests/CompanyUnitTest)
include_directories(UnitTests/OfficeUnitTest)
include_directories(UnitTests/InvoiceUnitTest)
include_directories(UnitTests/PersonUnitTest)
include_directories(UnitTests/TaxUnitTest)
include_directories(UnitTests/TaxFunctionUnitTest)


add_library(TaxesUltimateLib
        Company/Company.cpp
        Company/Company.h
        Currency/Currency.cpp
        Currency/Currency.h
        Invoice/Invoice.cpp
        Invoice/Invoice.h
        Office/Office.cpp
        Office/Office.h
        Person/Person.cpp
        Person/Person.h
        Tax/Tax.cpp
        Tax/Tax.h
        TaxFunctions/TaxFunctions.cpp
        TaxFunctions/TaxFunctions.h)

set_target_properties(TaxesUltimateLib PROPERTIES LINKER_LANGUAGE CXX)

add_executable(TaxesApp TaxesApp/TaxesApp.cpp)
target_link_libraries(TaxesApp TaxesUltimateLib)


#testy
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
if(WIN32)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
endif(WIN32)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(PersonUnitTest UnitTests/PersonUnitTest/PersonUnitTest.cpp)
target_link_libraries(PersonUnitTest PUBLIC gtest_main TaxesUltimateLib)

add_executable(CompanyUnitTest UnitTests/CompanyUnitTest/CompanyUnitTest.cpp)
target_link_libraries(CompanyUnitTest PUBLIC gtest_main TaxesUltimateLib)

add_executable(CurrencyUnitTest UnitTests/CurrencyUnitTest/CurrencyUnitTest.cpp)
target_link_libraries(CurrencyUnitTest PUBLIC gtest_main TaxesUltimateLib)

add_executable(OfficeUnitTest UnitTests/OfficeUnitTest/OfficeUnitTest.cpp)
target_link_libraries(OfficeUnitTest PUBLIC gtest_main TaxesUltimateLib)

add_executable(InvoiceUnitTest UnitTests/InvoiceUnitTest/InvoiceUnitTest.cpp)
target_link_libraries(InvoiceUnitTest PUBLIC gtest_main TaxesUltimateLib)

add_executable(TaxUnitTest UnitTests/TaxUnitTest/TaxUnitTest.cpp)
target_link_libraries(TaxUnitTest PUBLIC gtest_main TaxesUltimateLib)

add_executable(TaxFunctionUnitTest UnitTests/TaxFunctionUnitTest/TaxFunctionUnitTest.cpp)
target_link_libraries(TaxFunctionUnitTest PUBLIC gtest_main TaxesUltimateLib)

include(GoogleTest)
gtest_discover_tests(PersonUnitTest)
gtest_discover_tests(CompanyUnitTest)
gtest_discover_tests(CurrencyUnitTest)
gtest_discover_tests(OfficeUnitTest)
gtest_discover_tests(InvoiceUnitTest)
gtest_discover_tests(TaxUnitTest)
gtest_discover_tests(TaxFunctionUnitTest)
