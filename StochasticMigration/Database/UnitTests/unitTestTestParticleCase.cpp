/*    
 *    Copyright (c) 2010-2013, Delft University of Technology
 *    All rights reserved.
 *    See COPYING for license details.
 *
 *    Changelog
 *      YYMMDD    Author            Comment
 *      130329    K. Kumar          File created.
 *      130704    K. Kumar          Updated tests based on revised table schema.
 *
 *    References
 *
 *    Notes
 *
 */

#define BOOST_TEST_MAIN

#include <iostream>
#include <stdexcept>

#include <boost/make_shared.hpp>
#include <boost/test/unit_test.hpp>

#include <Eigen/Core>

#include <TudatCore/Astrodynamics/BasicAstrodynamics/orbitalElementConversions.h>
#include <TudatCore/Basics/testMacros.h>
#include <TudatCore/Mathematics/BasicMathematics/mathematicalConstants.h>

#include <Tudat/Mathematics/BasicMathematics/linearAlgebraTypes.h>

#include <Assist/Basics/operatorOverloadFunctions.h>

#include "StochasticMigration/Database/testParticleCase.h"

namespace stochastic_migration
{
namespace unit_tests
{

using namespace tudat::basic_astrodynamics::orbital_element_conversions;
using namespace tudat::basic_mathematics::mathematical_constants;

//! Test fixture used to test the TestParticleCase struct.
struct TestParticleCaseFixture
{
public:

    // Set Eigen macro to correctly align class with fixed-size vectorizable types.
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW

    //! Constructor initializing valid parameters.
    TestParticleCaseFixture( )
        : caseNumber( 1 ),
          randomWalkSimulationDuration( 1.2345e6 ),
          synodicPeriodLimit( 1.23e4 ),
          outputInterval( 3600.0 ),
          startUpIntegrationDuration( 0.0 ),
          conjunctionEventDetectionDistance( 1.234e5 ),
          oppositionEventDetectionDistance( 1.234e5 ),
          centralBodyGravitationalParameter( 2.345e10 ),
          centralBodyJ2GravityCoefficient( 0.0 ),
          centralBodyEquatorialRadius( 0.0 ),
          semiMajorAxisDistributionLimit( 1000.0e3 ),
          eccentricityDistributionMean( 1.0e-3 ),
          eccentricityDistributionAngle( PI / 4.0 ),
          eccentricityDistributionFullWidthHalfMaximum( 1.0e-4 ),
          inclinationDistributionMean( 1.0e-3 ),
          inclinationDistributionAngle( PI / 4.0 ),          
          inclinationDistributionFullWidthHalfMaximum( 1.0e-4 ),          
          perturbedBodyRadius( 2.345e6 ),
          perturbedBodyBulkDensity( 3.45e7 ),
          perturbedBodyStateInKeplerianElementsAtT0(
              ( Eigen::VectorXd( 6 ) << 1234.5, 0.55, 0.975, 1.234, 4.567, 3.456 ).finished( ) ),
          numericalIntegratorType( "RKF78" ),
          initialStepSize( 60.0 ),          
          numericalIntegratorRelativeTolerance( 1.0e-12 ),
          numericalIntegratorAbsoluteTolerance( 1.0e-15 )
    { }

    //! Declare parameters of test particle case.
    //! Case number.
    int caseNumber;

    //! Random walk simulation duration [s].
    double randomWalkSimulationDuration;

    //! Synodic period limit [s].
    double synodicPeriodLimit;

    //! Output interval, determining output frequency for data files [s].
    double outputInterval;

    //! Startup integration duration [s].
    double startUpIntegrationDuration;

    //! Mutual distance used to detect start and end of conjunction events [m].
    double conjunctionEventDetectionDistance;

    //! Distance used to detect start and end of opposition events [m].
    double oppositionEventDetectionDistance;

    //! Central body gravitational parameter [m^3 s^-2].
    double centralBodyGravitationalParameter;

    //! Central body J2 gravity field coefficient.
    double centralBodyJ2GravityCoefficient;

    //! Central body equatorial radius [m].
    double centralBodyEquatorialRadius;

    //! Limits on maximum semi-major axis values wrt perturbed body [m].
    double semiMajorAxisDistributionLimit;

    //! Mean eccentricity value for distribution.
    double eccentricityDistributionMean;

    //! Angle between vector components of eccentricity distribution [rad].
    double eccentricityDistributionAngle;

    //! FWHM eccentricity value for distribution.
    double eccentricityDistributionFullWidthHalfMaximum;

    //! Mean inclination value for distribution [rad].
    double inclinationDistributionMean;

    //! Angle between vector components of inclination distribution [rad].
    double inclinationDistributionAngle;

    //! FWHM inclination value for distribution [rad].
    double inclinationDistributionFullWidthHalfMaximum;

    //! Perturbed body radius [m].
    double perturbedBodyRadius;

    //! Perturbed body bulk density [kg m^-3].
    double perturbedBodyBulkDensity;

    //! Perturbed body state in Keplerian elements at T0.
    tudat::basic_mathematics::Vector6d perturbedBodyStateInKeplerianElementsAtT0;

    //! Numerical integrator type.
    std::string numericalIntegratorType;

    //! Initial step size for numerical integrator.
    double initialStepSize;

    //! Relative tolerance for numerical integrator.
    double numericalIntegratorRelativeTolerance;

    //! Absolute tolerance for numerical integrator.
    double numericalIntegratorAbsoluteTolerance;

    //! Get test particle case created from specified parameters.
    database::TestParticleCasePointer getTestParticleCase( )
    {
        return boost::make_shared< database::TestParticleCase >(
            database::TestParticleCase( 
                caseNumber, randomWalkSimulationDuration, synodicPeriodLimit,
                outputInterval, startUpIntegrationDuration, conjunctionEventDetectionDistance,
                oppositionEventDetectionDistance, centralBodyGravitationalParameter,
                centralBodyJ2GravityCoefficient, centralBodyEquatorialRadius, 
                semiMajorAxisDistributionLimit, eccentricityDistributionMean, 
                eccentricityDistributionAngle, eccentricityDistributionFullWidthHalfMaximum, 
                inclinationDistributionMean, inclinationDistributionAngle,
                inclinationDistributionFullWidthHalfMaximum, perturbedBodyRadius, 
                perturbedBodyBulkDensity, perturbedBodyStateInKeplerianElementsAtT0, 
                numericalIntegratorType, initialStepSize, numericalIntegratorRelativeTolerance,
                numericalIntegratorAbsoluteTolerance ) );
    }

protected:

private:
};    

BOOST_FIXTURE_TEST_SUITE( test_test_particle_case, TestParticleCaseFixture )

//! Test correct construction of test particle case.
BOOST_AUTO_TEST_CASE( testTestParticleCaseStructContruction )
{
    // Create test particle case.
    database::TestParticleCasePointer testParticleCase = getTestParticleCase( );

    // Check that the test particle case created contains all the data as required.
    BOOST_CHECK_EQUAL( testParticleCase->caseNumber, caseNumber );     
    BOOST_CHECK_EQUAL( testParticleCase->randomWalkSimulationDuration, 
                       randomWalkSimulationDuration );
    BOOST_CHECK_EQUAL( testParticleCase->synodicPeriodLimit, synodicPeriodLimit );
    BOOST_CHECK_EQUAL( testParticleCase->outputInterval, outputInterval );
    BOOST_CHECK_EQUAL( testParticleCase->startUpIntegrationDuration, startUpIntegrationDuration );
    BOOST_CHECK_EQUAL( testParticleCase->conjunctionEventDetectionDistance, 
                       conjunctionEventDetectionDistance );
    BOOST_CHECK_EQUAL( testParticleCase->oppositionEventDetectionDistance, 
                       oppositionEventDetectionDistance );
    BOOST_CHECK_EQUAL( testParticleCase->centralBodyGravitationalParameter, 
                       centralBodyGravitationalParameter );
    BOOST_CHECK_EQUAL( testParticleCase->centralBodyJ2GravityCoefficient, 
                       centralBodyJ2GravityCoefficient );
    BOOST_CHECK_EQUAL( testParticleCase->centralBodyEquatorialRadius, 
                       centralBodyEquatorialRadius );
    BOOST_CHECK_EQUAL( testParticleCase->semiMajorAxisDistributionLimit, 
                       semiMajorAxisDistributionLimit );
    BOOST_CHECK_EQUAL( testParticleCase->eccentricityDistributionMean, 
                       eccentricityDistributionMean );
    BOOST_CHECK_EQUAL( testParticleCase->eccentricityDistributionAngle, 
                       eccentricityDistributionAngle );
    BOOST_CHECK_EQUAL( testParticleCase->eccentricityDistributionFullWidthHalfMaximum,
                       eccentricityDistributionFullWidthHalfMaximum );
    BOOST_CHECK_EQUAL( testParticleCase->inclinationDistributionMean, 
                       inclinationDistributionMean );
    BOOST_CHECK_EQUAL( testParticleCase->inclinationDistributionAngle, 
                       inclinationDistributionAngle );
    BOOST_CHECK_EQUAL( testParticleCase->inclinationDistributionFullWidthHalfMaximum,
                       inclinationDistributionFullWidthHalfMaximum );
    BOOST_CHECK_EQUAL( testParticleCase->perturbedBodyRadius, perturbedBodyRadius );
    BOOST_CHECK_EQUAL( testParticleCase->perturbedBodyBulkDensity, perturbedBodyBulkDensity );    

    {
        TUDAT_CHECK_MATRIX_BASE( testParticleCase->perturbedBodyStateInKeplerianElementsAtT0,
                                 perturbedBodyStateInKeplerianElementsAtT0 )
                BOOST_CHECK_EQUAL(
                    testParticleCase->perturbedBodyStateInKeplerianElementsAtT0.coeff( row, col ),
                    perturbedBodyStateInKeplerianElementsAtT0.coeff( row, col ) );
    }

    BOOST_CHECK_EQUAL( testParticleCase->numericalIntegratorType, numericalIntegratorType );
    BOOST_CHECK_EQUAL( testParticleCase->initialStepSize, initialStepSize );    
    BOOST_CHECK_EQUAL( testParticleCase->numericalIntegratorRelativeTolerance, 
                       numericalIntegratorRelativeTolerance );
    BOOST_CHECK_EQUAL( testParticleCase->numericalIntegratorAbsoluteTolerance, 
                       numericalIntegratorAbsoluteTolerance );
}

//! Test initialization of test particle case with non-positive case number.
BOOST_AUTO_TEST_CASE( testTestParticleCaseNonPositiveCaseNumberError )
{
    // Set flag to indicate if error is thrown to false.
    bool isError = false;

    // Set case number to invalid (non-positive) number.
    caseNumber = -1;

    // Try to create test particle case.
    try { database::TestParticleCasePointer testParticleCase = getTestParticleCase( ); }

    // Catch expected run-time error.
    catch ( std::runtime_error& error ) { isError = true; }

    // Check that construction of test particle case failed.
    BOOST_CHECK( isError );
}

//! Test initialization of test particle case with non-positive random walk simulation duration.
BOOST_AUTO_TEST_CASE( testTestParticleCaseNonPositiveRandomWalkSimulationDurationError )
{
    // Set flag to indicate if error is thrown to false.
    bool isError = false;

    // Set random walk duration to invalid (non-positive) value.
    randomWalkSimulationDuration = -1.0;

    // Try to create test particle case.
    try { database::TestParticleCasePointer testParticleCase = getTestParticleCase( ); }

    // Catch expected run-time error.
    catch ( std::runtime_error& error ) { isError = true; }

    // Check that construction of test particle case failed.
    BOOST_CHECK( isError );
}

//! Test initialization of test particle case with non-positive synodic period limit.
BOOST_AUTO_TEST_CASE( testTestParticleCaseNonPositiveSynodicPeriodLimitError )
{
    // Set flag to indicate if error is thrown to false.
    bool isError = false;

    // Set synodic period limit to invalid (non-positive) value.
    synodicPeriodLimit = -1.0;

    // Try to create test particle case.
    try { database::TestParticleCasePointer testParticleCase = getTestParticleCase( ); }

    // Catch expected run-time error.
    catch ( std::runtime_error& error ) { isError = true; }

    // Check that construction of test particle case failed.
    BOOST_CHECK( isError );
}

//! Test initialization of test particle case with non-positive output interval.
BOOST_AUTO_TEST_CASE( testTestParticleCaseNonPositiveOutputIntervalError )
{
    // Set flag to indicate if error is thrown to false.
    bool isError = false;

    // Set output interval to invalid (non-positive) value.
    outputInterval = -1.0;

    // Try to create test particle case.
    try { database::TestParticleCasePointer testParticleCase = getTestParticleCase( ); }

    // Catch expected run-time error.
    catch ( std::runtime_error& error ) { isError = true; }

    // Check that construction of test particle case failed.
    BOOST_CHECK( isError );
}

//! Test initialization of test particle case with non-positive start-up integration duration.
BOOST_AUTO_TEST_CASE( testTestParticleCaseNonPositiveStartUpIntegrationDurationError )
{
    // Set flag to indicate if error is thrown to false.
    bool isError = false;

    // Set start-up integration duration to invalid (non-positive) value.
    startUpIntegrationDuration = -1.0;

    // Try to create test particle case.
    try { database::TestParticleCasePointer testParticleCase = getTestParticleCase( ); }

    // Catch expected run-time error.
    catch ( std::runtime_error& error ) { isError = true; }

    // Check that construction of test particle case failed.
    BOOST_CHECK( isError );
}

//! Test initialization of test particle case with non-positive conjunction event detection. 
//! distance.
BOOST_AUTO_TEST_CASE( testTestParticleCaseNonPositiveConjunctionEventDetectionDistanceError )
{
    // Set flag to indicate if error is thrown to false.
    bool isError = false;

    // Set conjunction event detection distance to invalid (non-positive) value.
    conjunctionEventDetectionDistance = -1.0;

    // Try to create test particle case.
    try { database::TestParticleCasePointer testParticleCase = getTestParticleCase( ); }

    // Catch expected run-time error.
    catch ( std::runtime_error& error ) { isError = true; }

    // Check that construction of test particle case failed.
    BOOST_CHECK( isError );
}

//! Test initialization of test particle case with non-positive opposition event detection.
//! distance.
BOOST_AUTO_TEST_CASE( testTestParticleCaseNonPositiveOppositionEventDetectionDistanceError )
{
    // Set flag to indicate if error is thrown to false.
    bool isError = false;

    // Set opposition event detection distance to invalid (non-positive) value.
    oppositionEventDetectionDistance = -1.0;

    // Try to create test particle case.
    try { database::TestParticleCasePointer testParticleCase = getTestParticleCase( ); }

    // Catch expected run-time error.
    catch ( std::runtime_error& error ) { isError = true; }

    // Check that construction of test particle case failed.
    BOOST_CHECK( isError );
}

//! Test initialization of test particle case with non-positive central body gravitational 
//! parameter.
BOOST_AUTO_TEST_CASE( testTestParticleCaseNonPositiveCentralBodyGravitationalParameterError )
{
    // Set flag to indicate if error is thrown to false.
    bool isError = false;

    // Set central body gravitational parameter to invalid (non-positive) value.
    centralBodyGravitationalParameter = -1.0;

    // Try to create test particle case.
    try { database::TestParticleCasePointer testParticleCase = getTestParticleCase( ); }

    // Catch expected run-time error.
    catch ( std::runtime_error& error ) { isError = true; }

    // Check that construction of test particle case failed.
    BOOST_CHECK( isError );
}

//! Test initialization of test particle case with non-positive central body J2 gravity 
//! coefficient. 
BOOST_AUTO_TEST_CASE( testTestParticleCaseNonPositiveCentralBodyJ2GravityCoefficientError )
{
    // Set flag to indicate if error is thrown to false.
    bool isError = false;

    // Set central body J2 gravity coefficient to invalid (non-positive) value.
    centralBodyJ2GravityCoefficient = -1.0;

    // Try to create test particle case.
    try { database::TestParticleCasePointer testParticleCase = getTestParticleCase( ); }

    // Catch expected run-time error.
    catch ( std::runtime_error& error ) { isError = true; }

    // Check that construction of test particle case failed.
    BOOST_CHECK( isError );
}

//! Test initialization of test particle case with non-positive central body equatorial radius.
BOOST_AUTO_TEST_CASE( testTestParticleCaseNonPositiveCentralBodyEquatorialRadiusError )
{
    // Set flag to indicate if error is thrown to false.
    bool isError = false;

    // Set central body equatorial radius to invalid (non-positive) value.
    centralBodyEquatorialRadius = -1.0;

    // Try to create test particle case.
    try { database::TestParticleCasePointer testParticleCase = getTestParticleCase( ); }

    // Catch expected run-time error.
    catch ( std::runtime_error& error ) { isError = true; }

    // Check that construction of test particle case failed.
    BOOST_CHECK( isError );
}

//! Test initialization of test particle case with non-positive semi-major axis distribution limit.
BOOST_AUTO_TEST_CASE( testTestParticleCaseNonPositiveSemiMajorAxisDistributionLimitError )
{
    // Set flag to indicate if error is thrown to false.
    bool isError = false;

    // Set semi-major axis distribution limit to invalid (non-positive) value.
    semiMajorAxisDistributionLimit = -1.0;

    // Try to create test particle case.
    try { database::TestParticleCasePointer testParticleCase = getTestParticleCase( ); }

    // Catch expected run-time error.
    catch ( std::runtime_error& error ) { isError = true; }

    // Check that construction of test particle case failed.
    BOOST_CHECK( isError );
}

//! Test initialization of test particle case with non-positive eccentricity distribution mean.
BOOST_AUTO_TEST_CASE( testTestParticleCaseNonPositiveEccentricityDistributionMeanError )
{
    // Set flag to indicate if error is thrown to false.
    bool isError = false;

    // Set eccentricity distribution mean to invalid (non-positive) value.
    eccentricityDistributionMean = -1.0;

    // Try to create test particle case.
    try { database::TestParticleCasePointer testParticleCase = getTestParticleCase( ); }

    // Catch expected run-time error.
    catch ( std::runtime_error& error ) { isError = true; }

    // Check that construction of test particle case failed.
    BOOST_CHECK( isError );
}

//! Test initialization of test particle case with non-positive eccentricity distribution angle.
BOOST_AUTO_TEST_CASE( testTestParticleCaseNonPositiveEccentricityDistributionAngleError )
{
    // Set flag to indicate if error is thrown to false.
    bool isError = false;

    // Set eccentricity distribution angle to invalid (non-positive) value.
    eccentricityDistributionAngle = -1.0;

    // Try to create test particle case.
    try { database::TestParticleCasePointer testParticleCase = getTestParticleCase( ); }

    // Catch expected run-time error.
    catch ( std::runtime_error& error ) { isError = true; }

    // Check that construction of test particle case failed.
    BOOST_CHECK( isError );
}

//! Test initialization of test particle case with non-positive eccentricity distribution FWHM .
BOOST_AUTO_TEST_CASE( testTestParticleCaseNonPositiveEccentricityDistributionFWHMError )
{
    // Set flag to indicate if error is thrown to false.
    bool isError = false;

    // Set eccentricity distribution FWHM to invalid (non-positive) value.
    eccentricityDistributionFullWidthHalfMaximum = -1.0;

    // Try to create test particle case.
    try { database::TestParticleCasePointer testParticleCase = getTestParticleCase( ); }

    // Catch expected run-time error.
    catch ( std::runtime_error& error ) { isError = true; }

    // Check that construction of test particle case failed.
    BOOST_CHECK( isError );
}

//! Test initialization of test particle case with non-positive inclination distribution mean.
BOOST_AUTO_TEST_CASE( testTestParticleCaseNonPositiveInclinationDistributionMeanError )
{
    // Set flag to indicate if error is thrown to false.
    bool isError = false;

    // Set inclination distribution mean to invalid (non-positive) value.
    inclinationDistributionMean = -1.0;

    // Try to create test particle case.
    try { database::TestParticleCasePointer testParticleCase = getTestParticleCase( ); }

    // Catch expected run-time error.
    catch ( std::runtime_error& error ) { isError = true; }

    // Check that construction of test particle case failed.
    BOOST_CHECK( isError );
}

//! Test initialization of test particle case with non-positive inclination distribution angle.
BOOST_AUTO_TEST_CASE( testTestParticleCaseNonPositiveInclinationDistributionAngleError )
{
    // Set flag to indicate if error is thrown to false.
    bool isError = false;

    // Set inclination distribution angle to invalid (non-positive) value.
    inclinationDistributionAngle = -1.0;

    // Try to create test particle case.
    try { database::TestParticleCasePointer testParticleCase = getTestParticleCase( ); }

    // Catch expected run-time error.
    catch ( std::runtime_error& error ) { isError = true; }

    // Check that construction of test particle case failed.
    BOOST_CHECK( isError );
}

//! Test initialization of test particle case with non-positive inclination distribution FWHM.
BOOST_AUTO_TEST_CASE( testTestParticleCaseNonPositiveInclinationDistributionFWHMError )
{
    // Set flag to indicate if error is thrown to false.
    bool isError = false;

    // Set inclination distribution FWHM to invalid (non-positive) value.
    inclinationDistributionFullWidthHalfMaximum = -1.0;

    // Try to create test particle case.
    try { database::TestParticleCasePointer testParticleCase = getTestParticleCase( ); }

    // Catch expected run-time error.
    catch ( std::runtime_error& error ) { isError = true; }

    // Check that construction of test particle case failed.
    BOOST_CHECK( isError );
}

//! Test initialization of test particle case with non-positive perturbed body radius.
BOOST_AUTO_TEST_CASE( testTestParticleCaseNonPositivePerturbedBodyRadiusError )
{
    // Set flag to indicate if error is thrown to false.
    bool isError = false;

    // Set perturbed body radius to invalid (non-positive) value.
    perturbedBodyRadius = -1.0;

    // Try to create test particle case.
    try { database::TestParticleCasePointer testParticleCase = getTestParticleCase( ); }

    // Catch expected run-time error.
    catch ( std::runtime_error& error ) { isError = true; }

    // Check that construction of test particle case failed.
    BOOST_CHECK( isError );
}

//! Test initialization of test particle case with non-positive perturbed body bulk density.
BOOST_AUTO_TEST_CASE( testTestParticleCaseNonPositivePerturbedBodyBulkDensityError )
{
    // Set flag to indicate if error is thrown to false.
    bool isError = false;

    // Set perturbed body bulk density to invalid (non-positive) value.
    perturbedBodyBulkDensity = -1.0;

    // Try to create test particle case.
    try { database::TestParticleCasePointer testParticleCase = getTestParticleCase( ); }

    // Catch expected run-time error.
    catch ( std::runtime_error& error ) { isError = true; }

    // Check that construction of test particle case failed.
    BOOST_CHECK( isError );
}

//! Test initialization of test particle case with non-positive perturbed body initial semi-major 
//! axis.
BOOST_AUTO_TEST_CASE( testTestParticleCaseNonPositivePerturbedBodyInitialSemiMajorAxisError )
{
    // Set flag to indicate if error is thrown to false.
    bool isError = false;

    // Set perturbed body initial semi-major axis to invalid (non-positive) value.
    perturbedBodyStateInKeplerianElementsAtT0( semiMajorAxisIndex ) = -1.0;

    // Try to create test particle case.
    try { database::TestParticleCasePointer testParticleCase = getTestParticleCase( ); }

    // Catch expected run-time error.
    catch ( std::runtime_error& error ) { isError = true; }

    // Check that construction of test particle case failed.
    BOOST_CHECK( isError );
}

//! Test initialization of test particle case with non-elliptical perturbed body initial
//! eccentricity axis.
BOOST_AUTO_TEST_CASE( testTestParticleCaseNonPositivePerturbedBodyInitialEccentricityError )
{
    // Set flag to indicate if error is thrown to false.
    bool isError = false;

    // Set perturbed body initial eccentricity to invalid (non-elliptical) value.
    perturbedBodyStateInKeplerianElementsAtT0( eccentricityIndex ) = -1.0;

    // Try to create test particle case.
    try { database::TestParticleCasePointer testParticleCase = getTestParticleCase( ); }

    // Catch expected run-time error.
    catch ( std::runtime_error& error ) { isError = true; }

    // Check that construction of test particle case failed.
    BOOST_CHECK( isError );
}

//! Test initialization of test particle case with non-positive perturbed body initial inclination
//! axis.
BOOST_AUTO_TEST_CASE( testTestParticleCaseNonPositivePerturbedBodyInitialInclinationError )
{
    // Set flag to indicate if error is thrown to false.
    bool isError = false;

    // Set perturbed body initial inclination to invalid (non-positive) value.
    perturbedBodyStateInKeplerianElementsAtT0( inclinationIndex ) = -1.0;

    // Try to create test particle case.
    try { database::TestParticleCasePointer testParticleCase = getTestParticleCase( ); }

    // Catch expected run-time error.
    catch ( std::runtime_error& error ) { isError = true; }

    // Check that construction of test particle case failed.
    BOOST_CHECK( isError );
}

//! Test initialization of test particle case with empty numerical integrator type.
BOOST_AUTO_TEST_CASE( testTestParticleCaseEmptyNumericalIntegratorTypeError )
{
    // Set flag to indicate if error is thrown to false.
    bool isError = false;

    // Set numerical integrator type to invalid (non-positive) value.
    numericalIntegratorType = "";

    // Try to create test particle case.
    try { database::TestParticleCasePointer testParticleCase = getTestParticleCase( ); }

    // Catch expected run-time error.
    catch ( std::runtime_error& error ) { isError = true; }

    // Check that construction of test particle case failed.
    BOOST_CHECK( isError );
}

//! Test initialization of test particle case with non-positive numerical integrator relative 
//! tolerance.
BOOST_AUTO_TEST_CASE( testTestParticleCaseNonPositiveNumericalIntegratorRelativeToleranceError )
{
    // Set flag to indicate if error is thrown to false.
    bool isError = false;

    // Set numerical integrator relative tolerance to invalid (non-positive) value.
    numericalIntegratorRelativeTolerance = -1.0;

    // Try to create test particle case.
    try { database::TestParticleCasePointer testParticleCase = getTestParticleCase( ); }

    // Catch expected run-time error.
    catch ( std::runtime_error& error ) { isError = true; }

    // Check that construction of test particle case failed.
    BOOST_CHECK( isError );
}

//! Test initialization of test particle case with non-positive numerical integrator absolute 
//! tolerance.
BOOST_AUTO_TEST_CASE( testTestParticleCaseNonPositiveNumericalIntegratorAbsoluteToleranceError )
{
    // Set flag to indicate if error is thrown to false.
    bool isError = false;

    // Set numerical integrator absolute tolerance to invalid (non-positive) value.
    numericalIntegratorAbsoluteTolerance = -1.0;

    // Try to create test particle case.
    try { database::TestParticleCasePointer testParticleCase = getTestParticleCase( ); }

    // Catch expected run-time error.
    catch ( std::runtime_error& error ) { isError = true; }

    // Check that construction of test particle case failed.
    BOOST_CHECK( isError );
}

//! Test comparison of TestParticleCase pointers using overloaded == operator.
BOOST_AUTO_TEST_CASE( testTestParticleCaseEqualComparison )
{
    // Create TestParticleCase pointers.
    database::TestParticleCasePointer testParticleCase = getTestParticleCase( );
    database::TestParticleCasePointer testParticleCase2 = getTestParticleCase( );

    // Check that operator is overloaded correctly.
    BOOST_CHECK( *testParticleCase == *testParticleCase2 );
}

//! Test comparison of TestParticleCase pointers using overloaded != operator.
BOOST_AUTO_TEST_CASE( testTestParticleCaseNonEqualComparison )
{
    using namespace assist::basics::operator_overload_functions;

    // Create TestParticleCase pointers.
    database::TestParticleCasePointer testParticleCase = getTestParticleCase( );

    caseNumber = 2;
    database::TestParticleCasePointer testParticleCase2 = getTestParticleCase( );

    // Check that operator is overloaded correctly.
    BOOST_CHECK( *testParticleCase != *testParticleCase2 );
}

//! Test comparison of TestParticleCase pointers using overloaded < operator.
BOOST_AUTO_TEST_CASE( testTestParticleCaseLessThanComparison )
{
    // Create TestParticleCase pointers.
    database::TestParticleCasePointer testParticleCase = getTestParticleCase( );

    caseNumber = 2;
    database::TestParticleCasePointer testParticleCase2 = getTestParticleCase( );

    // Check that operator is overloaded correctly.
    BOOST_CHECK( *testParticleCase < *testParticleCase2 );
}

//! Test comparison of TestParticleCase pointers using overloaded > operator.
BOOST_AUTO_TEST_CASE( testTestParticleCaseGreaterThanComparison )
{
    using namespace assist::basics::operator_overload_functions;

    // Create TestParticleCase pointers.
    database::TestParticleCasePointer testParticleCase = getTestParticleCase( );

    caseNumber = 2;
    database::TestParticleCasePointer testParticleCase2 = getTestParticleCase( );

    // Check that operator is overloaded correctly.
    BOOST_CHECK( *testParticleCase2 > *testParticleCase );
}

//! Test comparison of TestParticleCase pointers using overloaded <= operator.
BOOST_AUTO_TEST_CASE( testTestParticleCaseLessThanOrEqualComparison )
{
    using namespace assist::basics::operator_overload_functions;

    // Create TestParticleCase pointers.
    database::TestParticleCasePointer testParticleCase = getTestParticleCase( );

    caseNumber = 2;
    database::TestParticleCasePointer testParticleCase2 = getTestParticleCase( );

    // Check that operator is overloaded correctly.
    BOOST_CHECK( *testParticleCase <= *testParticleCase2 );
}

//! Test comparison of TestParticleCase pointers using overloaded >= operator.
BOOST_AUTO_TEST_CASE( testTestParticleCaseGreaterThanOrEqualComparison )
{
    using namespace assist::basics::operator_overload_functions;

    // Create TestParticleCase pointers.
    database::TestParticleCasePointer testParticleCase = getTestParticleCase( );

    caseNumber = 2;
    database::TestParticleCasePointer testParticleCase2 = getTestParticleCase( );

    // Check that operator is overloaded correctly.
    BOOST_CHECK( *testParticleCase2 >= *testParticleCase );
}

BOOST_AUTO_TEST_SUITE_END( )

} // namespace unit_tests
} // namespace stochastic_migration    
