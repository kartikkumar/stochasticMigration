/*    
 * Copyright (c) 2010-2014, Delft University of Technology
 * Copyright (c) 2010-2014, K. Kumar (me@kartikkumar.com)
 * All rights reserved.
 * See http://bit.ly/12SHPLR for license details.
 */


#include <string>
 
#include <boost/filesystem.hpp>
#include <boost/test/unit_test.hpp>

#include "Stomi/InputOutput/rootPath.h"

namespace stomi
{
namespace unit_tests
{

//! Check if the Stomi root-path is detected correctly.
BOOST_AUTO_TEST_CASE( test_getRootPath )
{
    // Check if the root-path is an existing folder.
    BOOST_CHECK( boost::filesystem::is_directory( input_output::getStomiRootPath( ) ) );

    // If using a STOMI_CUSTOM_ROOT_PATH define, check if it matches the macro value.
    #ifdef STOMI_CUSTOM_ROOT_PATH
        BOOST_CHECK( std::string( STOMI_CUSTOM_ROOT_PATH ).compare(
                         input_output::getStomiRootPath( ) == 0 );
    #endif
}    

} // namespace unit_tests
} // namespace stomi
