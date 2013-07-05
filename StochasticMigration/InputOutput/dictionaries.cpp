/*    
 *    Copyright (c) 2010-2013, Delft University of Technology
 *    All rights reserved.
 *    See COPYING for license details.
 *
 *    Changelog
 *      YYMMDD    Author            Comment
 *      120808    K. Kumar          File created.
 *      130217    K. Kumar          Updated "mab simulations" references to "stochastic migration".
 *      130704    K. Kumar          Updated definition of dictionary entries for database 
 *                                  generator.
 *
 *    References
 *
 *    Notes
 *
 */

#include <boost/assign/list_of.hpp>
#include <boost/make_shared.hpp>

#include "StochasticMigration/InputOutput/dictionaries.h"

namespace stochastic_migration
{
namespace input_output
{

using namespace tudat::input_output::dictionary;
using boost::assign::list_of;
using boost::make_shared;

//! Get dictionary for databaseGenerator application.
DictionaryPointer getDatabaseGeneratorDictionary( )
{
    DictionaryPointer dictionary = make_shared< Dictionary >( );

    addEntry( dictionary, "CASE",                                  1, 0 );
    addEntry( dictionary, "DATABASE",                              1, 0, list_of( "DB" ) );
    addEntry( dictionary, "NUMBEROFSIMULATIONS",                   1, 0, list_of( "POPULATION" ) );
    addEntry( dictionary, "RANDOMWALKSIMULATIONDURATION",          0, 0 );
    addEntry( dictionary, "SYNODICPERIODLIMIT",                    0, 0 );
    addEntry( dictionary, "OUTPUTINTERVAL",                        0, 0 );
    addEntry( dictionary, "STARTUPINTEGRATIONDURATION",            0, 0, list_of( "STARTUP" ) );
    addEntry( dictionary, "CONJUNCTIONEVENTDETECTIONDISTANCE",     0, 0,
                list_of( "CONJUNCTIONDISTANCE ") );
    addEntry( dictionary, "OPPOSITIONEVENTDETECTIONDISTANCE",      0, 0,
                list_of( "OPPOSITIONDISTANCE ") );
    addEntry( dictionary, "CENTRALBODYGRAVITATIONALPARAMETER",     0, 0, list_of( "GRAVPARAM" ) );
    addEntry( dictionary, "CENTRALBODYJ2GRAVITYCOEFFICIENT",       0, 0, list_of( "J2" ) );
    addEntry( dictionary, "CENTRALBODYEQUATORIALRADIUS",           0, 0, list_of( "RADIUS" ) );
    addEntry( dictionary, "SEMIMAJORAXISDISTRIBUTIONLIMIT",        1, 0, list_of( "SMALIMIT" ) );
    addEntry( dictionary, "ECCENTRICITYDISTRIBUTIONMEAN",          0, 0, list_of( "ECCMEAN" ) );
    addEntry( dictionary, "ECCENTRICITYDISTRIBUTIONANGLE",         0, 0, list_of( "ECCANGLE" ) );
    addEntry( dictionary, "ECCENTRICITYDISTRIBUTIONFULLWIDTHHALFMAXIMUM", 
                1, 0, list_of( "ECCFWHM" ) );
    addEntry( dictionary, "INCLINATIONDISTRIBUTIONMEAN",           0, 0, list_of( "INCMEAN" ) );
    addEntry( dictionary, "INCLINATIONDISTRIBUTIONANGLE",          0, 0, list_of( "INCANGLE" ) );
    addEntry( dictionary, "INCLINATIONDISTRIBUTIONFULLWIDTHHALFMAXIMUM",                       
                1, 0, list_of( "INCFWHM" ) );
    addEntry( dictionary, "PERTURBEDBODYRADIUS",                   0, 0 );
    addEntry( dictionary, "PERTURBEDBODYBULKDENSITY",              0, 0 );
    addEntry( dictionary, "PERTURBEDBODYSEMIMAJORAXISATT0",        0, 0, list_of( "SMA0" ) );
    addEntry( dictionary, "PERTURBEDBODYECCENTRICITYATT0",         0, 0, list_of( "ECC0" ) );
    addEntry( dictionary, "PERTURBEDBODYINCLINATIONATT0",          0, 0, list_of( "INC0" ) );
    addEntry( dictionary, "PERTURBEDBODYARGUMENTOFPERIAPSISATT0",  0, 0, list_of( "AOP0" ) );
    addEntry( dictionary, "PERTURBEDBODYLONGITUDEOFASCENDINGNODEATT0",
                0, 0, list_of( "RAAN0" ) );
    addEntry( dictionary, "PERTURBEDBODYTRUEANOMALYATT0",          0, 0, list_of( "TRAN0" ) );
    addEntry( dictionary, "NUMERICALINTEGRATORTYPE",               0, 0, list_of( "INTEGRATOR" ) );
    addEntry( dictionary, "INITIALSTEPSIZE",                       0, 0, list_of( "STEPSIZE0" ) );
    addEntry( dictionary, "RUNGEKUTTARELATIVEERRORTOLERANCE",      0, 0, list_of( "RELTOL" ) );
    addEntry( dictionary, "RUNGEKUTTAABSOLUTEERRORTOLERANCE",      0, 0, list_of( "ABSTOL" ) );
    addEntry( dictionary, "TESTPARTICLECASETABLENAME",             0, 0 );
    addEntry( dictionary, "TESTPARTICLEINPUTTABLENAME",            0, 0 );
    addEntry( dictionary, "TESTPARTICLEKICKTABLENAME",             0, 0 );
    addEntry( dictionary, "RANDOMWALKMONTECARLORUNTABLENAME",      0, 0 );
    addEntry( dictionary, "RANDOMWALKPERTURBERTABLENAME",          0, 0 );
    addEntry( dictionary, "RANDOMWALKOUTPUTTABLENAME",             0, 0 );

    return dictionary;
}

//! Get dictionary for testParticleSimulator application.
DictionaryPointer getTestParticleSimulatorDictionary( )
{
    // Retrieve dictionary for database generator.
    DictionaryPointer dictionary = make_shared< Dictionary >( );

    // Add additional entries for test particle simulator.
    addEntry( dictionary, "APPLICATIONMODE",                       0, 0, list_of( "MODE" ) );
    addEntry( dictionary, "DATABASE",                              1, 0, list_of( "DB" ) );
    addEntry( dictionary, "CASE",                                  1, 0 );
    addEntry( dictionary, "NUMBEROFTHREADS",                       0, 0, list_of( "THREADS" ) );
    addEntry( dictionary, "FILEOUTPUTDIRECTORY",                   0, 0, list_of( "OUTPUTDIR" ) );
    addEntry( dictionary, "SIMULATIONSTOEXECUTE",                  0, 0, 
                list_of( "SIMULATIONS" ) );
    addEntry( dictionary, "TESTPARTICLECASETABLENAME",             0, 0 );
    addEntry( dictionary, "TESTPARTICLEINPUTTABLENAME",            0, 0 );
    addEntry( dictionary, "TESTPARTICLEKICKTABLENAME",             0, 0 );  
    addEntry( dictionary, "RANDOMWALKSIMULATIONDURATION",          0, 0 ); 
    addEntry( dictionary, "SYNODICPERIODLIMIT",                    0, 0 );
    addEntry( dictionary, "OUTPUTINTERVAL",                        0, 0 );
    addEntry( dictionary, "STARTUPINTEGRATIONDURATION",            0, 0, list_of( "STARTUP" ) );
    addEntry( dictionary, "CONJUNCTIONEVENTDETECTIONDISTANCE",     0, 0,
                list_of( "CONJUNCTIONDISTANCE ") );
    addEntry( dictionary, "OPPOSITIONEVENTDETECTIONDISTANCE",      0, 0,
                list_of( "OPPOSITIONDISTANCE ") );
    addEntry( dictionary, "CENTRALBODYGRAVITATIONALPARAMETER",     0, 0, list_of( "GRAVPARAM" ) );
    addEntry( dictionary, "CENTRALBODYJ2GRAVITYCOEFFICIENT",       0, 0, list_of( "J2" ) );
    addEntry( dictionary, "CENTRALBODYEQUATORIALRADIUS",           0, 0, list_of( "RADIUS" ) );
    addEntry( dictionary, "PERTURBEDBODYRADIUS",                   0, 0 );
    addEntry( dictionary, "PERTURBEDBODYBULKDENSITY",              0, 0 );
    addEntry( dictionary, "PERTURBEDBODYSEMIMAJORAXISATT0",        0, 0, list_of( "SMA0" ) );
    addEntry( dictionary, "PERTURBEDBODYECCENTRICITYATT0",         0, 0, list_of( "ECC0" ) );
    addEntry( dictionary, "PERTURBEDBODYINCLINATIONATT0",          0, 0, list_of( "INC0" ) );
    addEntry( dictionary, "PERTURBEDBODYARGUMENTOFPERIAPSISATT0",  0, 0, list_of( "AOP0" ) );
    addEntry( dictionary, "PERTURBEDBODYLONGITUDEOFASCENDINGNODEATT0",
                0, 0, list_of( "RAAN0" ) );
    addEntry( dictionary, "PERTURBEDBODYTRUEANOMALYATT0",          0, 0, list_of( "TRAN0" ) );  
    addEntry( dictionary, "NUMERICALINTEGRATORTYPE",               0, 0, list_of( "INTEGRATOR" ) );
    addEntry( dictionary, "INITIALSTEPSIZE",                       0, 0, list_of( "STEPSIZE0" ) );
    addEntry( dictionary, "RUNGEKUTTARELATIVEERRORTOLERANCE",      0, 0, list_of( "RELTOL" ) );
    addEntry( dictionary, "RUNGEKUTTAABSOLUTEERRORTOLERANCE",      0, 0, list_of( "ABSTOL" ) );   

    return dictionary;
}

//! Get dictionary for randomWalkSimulator application.
DictionaryPointer getRandomWalkSimulatorDictionary( )
{
    DictionaryPointer dictionary = make_shared< Dictionary >( );

    addEntry( dictionary, "DATABASE",                         1, 0, list_of( "DB" ) );
    addEntry( dictionary, "NUMBEROFTHREADS",                  0, 0, list_of( "THREADS" ) );
    addEntry( dictionary, "OUTPUTDIRECTORY",                  0, 0 );
    addEntry( dictionary, "MONTECARLOPOPULATION",             1, 0, list_of( "MCPOP" ) );
    addEntry( dictionary, "PERTURBERPOPULATION",              0, 0, list_of( "PERTURBERPOP" ) );
    addEntry( dictionary, "MASSDISTRIBUTIONTYPE",             0, 0, list_of( "MASSDIST" ) );
    addEntry( dictionary, "MASSDISTRIBUTIONPARAMETERS",       0, 0, list_of( "MASSDISTPARAM" ) );
    addEntry( dictionary, "OBSERVATIONPERIOD",                0, 0, list_of( "POBS" ) );
    addEntry( dictionary, "EPOCHWINDOWSIZE",                  0, 0  );
    addEntry( dictionary, "NUMBEROFEPOCHWINDOWS",             0, 0, list_of( "NUMEPOCHS" ) );

    return dictionary;
}

} // namespace input_output
} // namespace stochastic_migration
