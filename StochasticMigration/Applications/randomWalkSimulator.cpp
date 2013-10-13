/*    
 *    Copyright (c) 2010-2013, Delft University of Technology
 *    Copyright (c) 2010-2013, K. Kumar (me@kartikkumar.com)
 *    All rights reserved.
 *    See http://bit.ly/12SHPLR for license details.
 */

// #include <algorithm>
// #include <cmath>
// #include <iomanip>
#include <iostream>
// #include <iterator>
// #include <limits>
// #include <stdexcept>
#include <string>
// #include <sstream>
// #include <vector>

// #include <omp.h>

// #include <boost/algorithm/string/predicate.hpp>
// #include <boost/filesystem.hpp>
// #include <boost/random/uniform_real_distribution.hpp>
// #include <boost/random/uniform_int_distribution.hpp>
// #include <boost/random/variate_generator.hpp>

// // #include <sqlite3.h>

// #include <Assist/Astrodynamics/astrodynamicsBasics.h>
// #include <Assist/Astrodynamics/unitConversions.h>
// #include <Assist/Basics/commonTypedefs.h>
// #include <Assist/Basics/comparisonFunctions.h>
#include <Assist/InputOutput/basicInputOutput.h>
// #include <Assist/Mathematics/statistics.h>

// #include <Tudat/InputOutput/basicInputOutput.h>
#include <Tudat/InputOutput/dictionaryTools.h>
#include <Tudat/InputOutput/fieldType.h>
#include <Tudat/InputOutput/separatedParser.h>
#include <Tudat/InputOutput/parsedDataVectorUtilities.h>
// // #include <Tudat/Mathematics/Statistics/simpleLinearRegression.h>

// // #include <TudatCore/Astrodynamics/BasicAstrodynamics/physicalConstants.h>
// #include <TudatCore/Astrodynamics/BasicAstrodynamics/orbitalElementConversions.h>
// #include <TudatCore/Mathematics/BasicMathematics/basicMathematicsFunctions.h>

// #include "StochasticMigration/Astrodynamics/hillSphere.h"
// #include "StochasticMigration/Astrodynamics/randomWalkFunctions.h"
// #include "StochasticMigration/Database/databaseReadFunctions.h" 
// #include "StochasticMigration/Database/testParticleCase.h"
// #include "StochasticMigration/Database/testParticleInput.h"
// #include "StochasticMigration/Database/testParticleKick.h"
#include "StochasticMigration/InputOutput/dictionaries.h"

//! Execute random walk simulations.
int main( const int numberOfInputs, const char* inputArguments[ ] )
{
//     using std::advance;
    using std::cout;
    using std::endl;
//     using std::generate;
    using std::string;
//     using std::runtime_error;

//     using namespace boost::filesystem;
//     using boost::iequals;
//     using namespace boost::random;

//     using namespace assist::astrodynamics;
//     using namespace assist::basics;
    using namespace assist::input_output;
//     using namespace assist::mathematics;

//     using namespace tudat::basic_astrodynamics::orbital_element_conversions;
//     using namespace tudat::basic_mathematics;
    using namespace tudat::input_output;
    using namespace tudat::input_output::dictionary;
    using namespace tudat::input_output::field_types::general;
    using namespace tudat::input_output::parsed_data_vector_utilities;
// //     using namespace tudat::statistics;

//     using namespace stochastic_migration::astrodynamics;
//     using namespace stochastic_migration::database;
    using namespace stochastic_migration::input_output;

    ///////////////////////////////////////////////////////////////////////////

    // Input deck.

    // Check input arguments.
    checkNumberOfInputArguments( numberOfInputs - 1 );

    // Get input parameter dictionary.
    const DictionaryPointer dictionary = getRandomWalkSimulatorDictionary( );

    // Read and filter input stream.
    string filteredInput = readAndFilterInputFile( inputArguments[ 1 ] );

    // Declare a separated parser.
    SeparatedParser parser( string( ": " ), 2, parameterName, parameterValue );

    // Parse filtered data.
    const ParsedDataVectorPtr parsedData = parser.parse( filteredInput );

    cout << endl;
    cout << "****************************************************************************" << endl;
    cout << "Input parameters" << endl;
    cout << "****************************************************************************" << endl;
    cout << endl;

    // Extract input parameters.

    // Extract required parameters. 
    const string databasePath = extractParameterValue< string >(
                parsedData->begin( ), parsedData->end( ), findEntry( dictionary, "DATABASE" ) );
    cout << "Database                                                     " 
         << databasePath << endl;

    const string caseName = extractParameterValue< string >(
                parsedData->begin( ), parsedData->end( ), findEntry( dictionary, "CASE" ) );
    cout << "Random walk case                                             "  << caseName << endl;  

//     const double perturberDensity = extractParameterValue< double >(
//                 parsedData->begin( ), parsedData->end( ),
//                 findEntry( dictionary, "PERTURBERDENSITY" ) );    
//     cout << "Perturber density                                         "
//          << perturberDensity << " perturbers per R_Hill" << endl;                         

//     const double perturberRingMass = extractParameterValue< double >(
//                 parsedData->begin( ), parsedData->end( ),
//                 findEntry( dictionary, "PERTURBERRINGMASS" ) );    
//     cout << "Perturber ring mass                                       "
//          << perturberRingMass << " M_PerturbedBody" << endl;              

//     const double observationPeriod = extractParameterValue< double >(
//                 parsedData->begin( ), parsedData->end( ),
//                 findEntry( dictionary, "OBSERVATIONPERIOD" ),
//                 TUDAT_NAN, &convertJulianYearsToSeconds );
//     cout << "Observation period                                        "
//          << convertSecondsToJulianYears( observationPeriod ) << " yrs" << endl; 

//     const unsigned int numberOfEpochWindows = extractParameterValue< unsigned int >(
//                 parsedData->begin( ), parsedData->end( ),
//                 findEntry( dictionary, "NUMBEROFEPOCHWINDOWS" ) );    
//     cout << "Number of epoch windows                                   "
//          << numberOfEpochWindows << endl;                                                 

//     const double epochWindowSize = extractParameterValue< double >(
//                 parsedData->begin( ), parsedData->end( ),
//                 findEntry( dictionary, "EPOCHWINDOWSIZE" ),
//                 TUDAT_NAN, &convertJulianDaysToSeconds  );
//     cout << "Epoch window size                                         "
//          << convertSecondsToJulianDays( epochWindowSize ) << " days" << endl;     

//     // Extract optional parameters. 
//     const int numberOfThreads = extractParameterValue< int >(
//                 parsedData->begin( ), parsedData->end( ),
//                 findEntry( dictionary, "NUMBEROFTHREADS" ), 1 );
//     cout << "Number of threads                                         "
//          << numberOfThreads << endl;  

//     const string outputMode = extractParameterValue< string >(
//                 parsedData->begin( ), parsedData->end( ),
//                 findEntry( dictionary, "OUTPUTMODE" ), "DATABASE" );
//     cout << "Output mode                                               "
//          << outputMode << endl;          

//     const string fileOutputDirectory = extractParameterValue< string >(
//                 parsedData->begin( ), parsedData->end( ),
//                 findEntry( dictionary, "FILEOUTPUTDIRECTORY" ), "" ) + "/";
//     cout << "File output directory                                     "
//          << fileOutputDirectory << endl;

//     const string testParticleCaseTableName = extractParameterValue< string >(
//                 parsedData->begin( ), parsedData->end( ),
//                 findEntry( dictionary, "TESTPARTICLECASETABLENAME" ), "test_particle_case" );
//     cout << "Test particle case table                                  "
//          << testParticleCaseTableName << endl;

//     const string testParticleInputTableName = extractParameterValue< string >(
//                 parsedData->begin( ), parsedData->end( ),
//                 findEntry( dictionary, "TESTPARTICLEINPUTTABLENAME" ), "test_particle_input" );
//     cout << "Test particle input table                                 "
//          << testParticleInputTableName << endl;

//     const string testParticleKickTableName = extractParameterValue< string >(
//                 parsedData->begin( ), parsedData->end( ),
//                 findEntry( dictionary, "TESTPARTICLEKICKTABLENAME" ), "test_particle_kicks" );
//     cout << "Test particle kick table                                  "
//          << testParticleKickTableName << endl; 

//     const string randomWalkMonteCarloRunTableName = extractParameterValue< string >(
//                 parsedData->begin( ), parsedData->end( ),
//                 findEntry( dictionary, "RANDOMWALKMONTECARLORUNTABLENAME" ),
//                 "random_walk_monte_carlo_runs" );
//     cout << "Random walk Monte Carlo run table                         "
//               << randomWalkMonteCarloRunTableName << endl;

//     const string randomWalkPerturberTableName = extractParameterValue< string >(
//                 parsedData->begin( ), parsedData->end( ),
//                 findEntry( dictionary, "RANDOMWALKPERTURBERTABLENAME" ),
//                 "random_walk_perturbers" );
//     cout << "Random walk perturber table                               "
//               << randomWalkPerturberTableName << endl;

//     const string randomWalkOutputTableName = extractParameterValue< string >(
//                 parsedData->begin( ), parsedData->end( ),
//                 findEntry( dictionary, "RANDOMWALKOUTPUTTABLENAME" ), "random_walk_output" );
//     cout << "Random walk output table                                  "
//               << randomWalkOutputTableName << endl;                 

    // Check that all required parameters have been set.
    checkRequiredParameters( dictionary );

    ///////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////

    // Fetch case and input data from database.

    cout << endl;
    cout << "****************************************************************************" << endl;
    cout << "Database operations" << endl;
    cout << "****************************************************************************" << endl;
    cout << endl;

//     // Generate output message.
//     cout << "Fetching test particle case data from database ..." << endl;   

//     // Retrieve and store case data.
//     const TestParticleCasePointer caseData = getTestParticleCase( 
//         databasePath, caseName, testParticleCaseTableName ); 

//     // Generate output message to indicate that case data was fetched successfully.
//     cout << "Test particle case data fetched successfully from database!" << endl;   

//     // Generate output message.
//     cout << "Fetching test particle input data from database ..." << endl;   

//     // Get entire test particle input table from database. Only test particle simulations that 
//     // are complete are fetched for the given case ID.
//     const TestParticleInputTable inputTable = getCompleteTestParticleInputTable(
//                 databasePath, caseData->caseId, testParticleInputTableName, true );    

//     // Generate output message to indicate that input table was fetched successfully.
//     cout << "Test particle input data (" << inputTable.size( )
//          << " rows) fetched successfully from database!" << endl;    

    ///////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////

    // Compute derived parameters.

    cout << endl;
    cout << "****************************************************************************" << endl;
    cout << "Derived parameters" << endl;
    cout << "****************************************************************************" << endl;
    cout << endl;

//     // Compute epoch window spacing [s].
//     const double epochWindowSpacing = observationPeriod / ( numberOfEpochWindows - 1 );
//     cout << "Epoch window spacing                                      " 
//          << convertSecondsToJulianDays( epochWindowSpacing ) << " days" << endl;

//     // Compute mass of perturbed body [kg].
//     const double perturbedBodyMass = computeMassOfSphere(
//                 caseData->perturbedBodyRadius, caseData->perturbedBodyBulkDensity );
//     cout << "Perturbed body mass                                       " 
//          << perturbedBodyMass << " kg" << endl;

//     // Compute perturbed body's gravitational parameter [m^3 s^-2].
//     const double perturbedBodyGravitationalParameter
//             = computeGravitationalParameter( perturbedBodyMass );
//     cout << "Perturbed body gravitational parameter                    " 
//          << perturbedBodyGravitationalParameter << " m^3 s^-2" << endl;
         
//     // Compute perturber population using density and semi-major axis distribution limits.
//     // Note, in the floor() function, adding 0.5 is a workaround for the fact that there is no
//     // round() function in C++03 (it is available in C++11).
//     ConvertHillRadiiToMeters convertHillRadiiToMeters( 
//         caseData->centralBodyGravitationalParameter, perturbedBodyGravitationalParameter, 
//         caseData->perturbedBodyStateInKeplerianElementsAtT0( semiMajorAxisIndex ) );
//     const double perturberDensityInMeters = perturberDensity / convertHillRadiiToMeters( 1.0 );
//     const unsigned int perturberPopulation = std::floor( 
//         2.0 * caseData->semiMajorAxisDistributionLimit * perturberDensityInMeters + 0.5 );
//     cout << "Perturber population                                      " 
//          << perturberPopulation << endl;

//     // Compute perturber mass ratio.
//     // Note, for the random walk simulations, the mass ratio is equal for all perturbers.
//     const double perturberMassRatio = perturberRingMass / perturberPopulation;
//     cout << "Perturber mass ratio                                      "
//          << perturberMassRatio << std::endl;

    ///////////////////////////////////////////////////////////////////////////

//     ///////////////////////////////////////////////////////////////////////////

//     // Create required random number generators.

//     // Define a random number generator and initialize it with a reproducible seed (current cpu
//     // time).
//     GlobalRandomNumberGeneratorType randomNumberGenerator = getGlobalRandomNumberGenerator( );

//     // Define an uniform random number distribution for test particle simulation ID indices in 
//     // input table.
//     uniform_int_distribution< > simulationIdIndexDistribution( 1, inputTable.size( ) );

//     // Define variate generator for simulation ID indices using the random number
//     // generator and uniform distribution of simulation ID indices in input table.
//     variate_generator< GlobalRandomNumberGeneratorType&, uniform_int_distribution< > > 
//     generateSimulationId( randomNumberGenerator, simulationIdIndexDistribution );

//     // Define an uniform random number distribution to select a random observation period during
//     // random walk simulation period.
//     uniform_real_distribution< > observationPeriodDistribution(
//                 epochWindowSize / 2.0, 
//                 caseData->randomWalkSimulationPeriod - observationPeriod - epochWindowSize / 2.0 );

//     // Define variate generator for the first epoch in the observation period.
//     variate_generator< GlobalRandomNumberGeneratorType&, uniform_real_distribution< > > 
//     generateObservationPeriodStartEpoch( randomNumberGenerator, observationPeriodDistribution );

//     ///////////////////////////////////////////////////////////////////////////

//     ///////////////////////////////////////////////////////////////////////////

//     // Execute Monte Carlo simulation.

//     cout << endl;
//     cout << "****************************************************************************" << endl;
//     cout << "Simulation loop" << endl;
//     cout << "****************************************************************************" << endl;
//     cout << endl;

//     // Execute simulation loop.
//     cout << "Starting simulation loop ... " << endl;
//     cout << monteCarloPopulation << " Monte Carlo simulations queued for execution ..." << endl;
//     cout << endl;    

//     // Loop over Monte Carlo population size.
// #pragma omp parallel for num_threads( numberOfThreads )
//     for ( unsigned int monteCarloIndividual = 0; monteCarloIndividual < monteCarloPopulation;
//           monteCarloIndividual++ )
//     {
//         ///////////////////////////////////////////////////////////////////////////

//         // Emit output message.
// #pragma omp critical( outputToConsole )
//         {
//             cout << "Simulation " << monteCarloIndividual + 1 << " / " << monteCarloPopulation
//                  << " on thread " << omp_get_thread_num( ) + 1 << " / " <<  omp_get_num_threads( )
//                  << endl;
//         }

//         ///////////////////////////////////////////////////////////////////////////

//         ///////////////////////////////////////////////////////////////////////////

//         // Select simulation ID indices (test particle simulation indices in input 
//         // table retrieved from database) to generate list of perturbers.

//         // Declare vector containing simulation IDs and associated mass ratios used to define
//         // perturbers.
//         std::vector< int > selectedSimulationIdIndices( perturberPopulation );

//         // If desired perturber population is greater than number of completed simulations fetched,
//         // from the database input table, throw a run-time error.
//         if ( perturberPopulation > inputTable.size( ) )
//         {
//             throw runtime_error( "ERROR: Perturber population > # completed simulations" );
//         }

//         // Else, populate the vector of selected simulation IDs, ensuring that all IDs are unique.
//         else
//         {
//             // Generate vector of randomly selected simulation IDs.
//             generate( selectedSimulationIdIndices.begin( ), selectedSimulationIdIndices.end( ),
//                       generateSimulationId );

//             // Check if the simulation IDs are unique, and if not, generate new random number.
//             for ( unsigned int i = 0; i < selectedSimulationIdIndices.size( ); i++ )
//             {
//                 for ( unsigned int j = 0; j < selectedSimulationIdIndices.size( ); j++ )
//                 {
//                     // If inner and outer loop point to the same element, skip.
//                     if ( i == j )
//                     {
//                         continue;
//                     }

//                     // Else, check if the elements are equal, and if they are generate a new 
//                     // simulation ID index and restart looping.
//                     else if ( selectedSimulationIdIndices.at( j ) 
//                               == selectedSimulationIdIndices.at( i ) )
//                     {
//                         selectedSimulationIdIndices.at( j ) = generateSimulationId( );
//                         i = 0;
//                         break;
//                     }
//                 }
//             }
//         }

//         ///////////////////////////////////////////////////////////////////////////

//         ///////////////////////////////////////////////////////////////////////////

//         // Retrieve aggregate kick table from database based on selected simulation IDs for
//         // perturbers. 
//         // To avoid locking of the database, this section is thread-critical, so will be
//         // executed one-by-one by multiple threads.

//         TestParticleKickTable kickTable;

// #pragma omp critical( retrievekickTable )
//         {
//             kickTable = getTestParticleKickTable(
//                         databasePath, caseData->randomWalkSimulationPeriod,
//                         selectedSimulationIdIndices, testParticleKickTableName );
//         }

//         ///////////////////////////////////////////////////////////////////////////

//         ///////////////////////////////////////////////////////////////////////////

//         // Execute random walk simulation.

//         // Declare perturbed body propagation history. This stores the propagation history of the
//         // action variables only (semi-major axis, eccentricity, inclination).
//         DoubleKeyVector3dValueMap keplerianActionElementsHistory;

//         // Set perturbed body initial state (actions) in Keplerian elements.
//         keplerianActionElementsHistory[ 0.0 ]
//                 = caseData->perturbedBodyStateInKeplerianElementsAtT0.segment( 0, 3 );

//         // Declare iterator to previous state in Keplerian elements.
//         DoubleKeyVector3dValueMap::iterator iteratorPreviousKeplerianElements
//                 = keplerianActionElementsHistory.begin( );

//         // Loop through aggregate kick table and execute kicks on perturbed body. 
//         for ( TestParticleKickTable::iterator iteratorKickTable = kickTable.begin( );
//               iteratorKickTable != kickTable.end( ); iteratorKickTable++ )
//         {
//             // Execute kick and store results in propagation history.
//             keplerianActionElementsHistory[ iteratorKickTable->conjunctionEpoch ]
//                     = executeKick( iteratorPreviousKeplerianElements->second,
//                                    iteratorKickTable, perturberMassRatio );

//             advance( iteratorPreviousKeplerianElements, 1 );
//         }

//         // Check if output mode is set to "FILE".
//         // If so, open output file and write header content.
//         // Check if the output directory exists: if not, create it.
//         if ( iequals( outputMode, "FILE" ) )
//         {
//             std::ostringstream keplerianActionElementsFilename;
//             keplerianActionElementsFilename << "monteCarloRun" << monteCarloIndividual + 1
//                                             << "_keplerianActionElements.csv"; 
            
//             std::ostringstream keplerianActionElementsFileHeader;
//             keplerianActionElementsFileHeader << "epoch,semiMajorAxis,eccentricity,inclination" 
//                                               << endl;
//             keplerianActionElementsFileHeader << "# [s],[m],[-],[rad]" << endl;                                            

//             writeDataMapToTextFile( keplerianActionElementsHistory,
//                                     keplerianActionElementsFilename.str( ),
//                                     fileOutputDirectory, keplerianActionElementsFileHeader.str( ),
//                                     std::numeric_limits< double >::digits10, 
//                                     std::numeric_limits< double >::digits10,
//                                     "," );
//         }

//         // Select a random observation period start epoch.
//         const double observationPeriodStartEpoch = generateObservationPeriodStartEpoch( );

//         ///////////////////////////////////////////////////////////////////////////

//         ///////////////////////////////////////////////////////////////////////////

//         // Compute maximum longitude residual change in propagation history.

// //         // Compute longitude history.
// //         DoubleKeyDoubleValueMap longitudeHistory
// //                 = computeLongitudeHistory( keplerianActionElementsHistory,
// //                                            caseData.uranusGravitationalParameter );

// //         // Compute reduced longitude history.
// //         DoubleKeyDoubleValueMap reducedLongitudeHistory
// //                 = reduceLongitudeHistory( longitudeHistory, observationPeriodEpoch,
// //                                           epochWindowSpacing, epochWindowSize,
// //                                           numberOfEpochWindows );

// //         // Set input data for simple linear regression.
// //         SimpleLinearRegression longitudeHistoryRegression( reducedLongitudeHistory );

// //         // Compute linear fit.
// //         longitudeHistoryRegression.computeFit( );

// //         // Clear longitude residuals history.
// //         DoubleKeyDoubleValueMap longitudeResidualsHistory;

// //         // Generate longitude history residuals by subtracting linear fit from data.
// //         for ( DoubleKeyDoubleValueMap::iterator iteratorReducedLongitudeHistory
// //               = reducedLongitudeHistory.begin( );
// //               iteratorReducedLongitudeHistory != reducedLongitudeHistory.end( );
// //               iteratorReducedLongitudeHistory++ )
// //         {
// //             longitudeResidualsHistory[ iteratorReducedLongitudeHistory->first ]
// //                     = iteratorReducedLongitudeHistory->second
// //                     - longitudeHistoryRegression.getCoefficientOfConstantTerm( )
// //                     - longitudeHistoryRegression.getCoefficientOfLinearTerm( )
// //                     * iteratorReducedLongitudeHistory->first;
// //         }

// //         // Declare map of epoch-window average longitude residuals.
// //         DoubleKeyDoubleValueMap epochWindowAverageLongitudeResiduals;

// //         for ( unsigned int windowNumber = 0; windowNumber < numberOfEpochWindows; windowNumber++ )
// //         {
// //             const double epochWindowCenter = epochWindowSize / 2.0
// //                     + windowNumber * epochWindowSpacing;

// //             epochWindowAverageLongitudeResiduals[ epochWindowCenter ]
// //                     = computeAverageLongitudeResidualForEpochWindow(
// //                         longitudeResidualsHistory,
// //                         epochWindowCenter - epochWindowSize / 2.0,
// //                         epochWindowCenter + epochWindowSize / 2.0 );
// //         }

// //         // Compute map of maximum longitude residual change during propagation history.
// //         double maximumLongitudeResidualChange = ( std::max_element(
// //                     epochWindowAverageLongitudeResiduals.begin( ),
// //                     epochWindowAverageLongitudeResiduals.end( ),
// //                     compareDoubleKeyDoubleValueElements ) )->second
// //                 - ( std::min_element(
// //                         epochWindowAverageLongitudeResiduals.begin( ),
// //                         epochWindowAverageLongitudeResiduals.end( ),
// //                         compareDoubleKeyDoubleValueElements ) )->second;

//         ///////////////////////////////////////////////////////////////////////////        

//         ///////////////////////////////////////////////////////////////////////////

//         // Compute maximum eccentricity change in propagation history.

//         // Declare maximum eccentricity change in window.
//         double maximumEccentricityChange = 0.0;

//         {
//             // Populate temporary map with epochs and eccentricities.
//             DoubleKeyDoubleValueMap eccentricityHistory;

//             for ( DoubleKeyVector3dValueMap::iterator iteratorKeplerianActionElements 
//                   = keplerianActionElementsHistory.begin( );
//                   iteratorKeplerianActionElements != keplerianActionElementsHistory.end( );
//                   iteratorKeplerianActionElements++ )
//             {
//                 eccentricityHistory[ iteratorKeplerianActionElements->first ]
//                     = iteratorKeplerianActionElements->second( eccentricityIndex );
//             }            

//             // Declare map of average eccentricities per window.
//             DoubleKeyDoubleValueMap averageEccentricities;

//             // Loop over observation period and compute average eccentricities per epoch window.
//             for ( unsigned int windowNumber = 0; 
//                   windowNumber < numberOfEpochWindows; 
//                   windowNumber++ )
//             {
//                 const double epochWindowCenter = observationPeriodStartEpoch
//                         + windowNumber * epochWindowSpacing;

//                 averageEccentricities[ epochWindowCenter ] 
//                     = computeStepFunctionWindowAverage( 
//                         eccentricityHistory, 
//                         epochWindowCenter - epochWindowSize / 2.0, 
//                         epochWindowCenter + epochWindowSize / 2.0 );
//             }

//             // Compute maximum eccentricity change during propagation history.
//             maximumEccentricityChange 
//                 = ( std::max_element( averageEccentricities.begin( ), 
//                                       averageEccentricities.end( ),
//                                       CompareDoubleKeyDoubleValueMapValues( ) ) )->second
//                   - ( std::min_element( averageEccentricities.begin( ), 
//                                         averageEccentricities.end( ),
//                                         CompareDoubleKeyDoubleValueMapValues( ) ) )->second;        
//         }

//         ///////////////////////////////////////////////////////////////////////////

//         ///////////////////////////////////////////////////////////////////////////

//         // Compute maximum inclination change in propagation history.

//         // Declare maximum inclination change in window.
//         double maximumInclinationChange = 0.0;

//         {
//             // Populate temporary map with epochs and inclinations.
//             DoubleKeyDoubleValueMap inclinationHistory;

//             for ( DoubleKeyVector3dValueMap::iterator iteratorKeplerianActionElements 
//                   = keplerianActionElementsHistory.begin( );
//                   iteratorKeplerianActionElements != keplerianActionElementsHistory.end( );
//                   iteratorKeplerianActionElements++ )
//             {
//                 inclinationHistory[ iteratorKeplerianActionElements->first ]
//                     = iteratorKeplerianActionElements->second( inclinationIndex );
//             }            

//             // Declare map of average inclinations per window.
//             DoubleKeyDoubleValueMap averageInclinations;

//             // Loop over observation period and compute average inclinations per epoch window.
//             for ( unsigned int windowNumber = 0; 
//                   windowNumber < numberOfEpochWindows; 
//                   windowNumber++ )
//             {
//                 const double epochWindowCenter = observationPeriodStartEpoch
//                         + windowNumber * epochWindowSpacing;

//                 averageInclinations[ epochWindowCenter ] 
//                     = computeStepFunctionWindowAverage( 
//                         inclinationHistory, 
//                         epochWindowCenter - epochWindowSize / 2.0, 
//                         epochWindowCenter + epochWindowSize / 2.0 );
//             }

//             // Compute maximum inclination change during propagation history.
//             maximumInclinationChange 
//                 = ( std::max_element( averageInclinations.begin( ), 
//                                       averageInclinations.end( ),
//                                       CompareDoubleKeyDoubleValueMapValues( ) ) )->second
//                   - ( std::min_element( averageInclinations.begin( ), 
//                                         averageInclinations.end( ),
//                                         CompareDoubleKeyDoubleValueMapValues( ) ) )->second;        

//             cout << "Max i: " << maximumInclinationChange << endl;
//         }

//         ///////////////////////////////////////////////////////////////////////////

// //         ///////////////////////////////////////////////////////////////////////////

// //         // Write random walk table to database. To avoid locking of the database, this section is
// //         // thread-critical, so will be executed one-by-one by multiple threads.
// // #pragma omp critical( accessDatabase )
// //         {
// //             // Populate kick table in database.
// //             populateRandomWalkTable( databasePath, selectedSimulationIdIndices, massFactors,
// //                                      massDistributionType, massDistributionParameters,
// //                                      observationPeriod, epochWindowSize, numberOfEpochWindows,
// //                                      maximumEccentricityChange, maximumLongitudeResidualChange,
// //                                      maximumInclinationChange );
// //         }

//         ///////////////////////////////////////////////////////////////////
//     }

//     ///////////////////////////////////////////////////////////////////////////

//     return EXIT_SUCCESS;
}
