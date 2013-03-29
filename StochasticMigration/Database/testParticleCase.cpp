/*    Copyright (c) 2010-2013, Delft University of Technology
 *    All rights reserved.
 *
 *    Redistribution and use in source and binary forms, with or without modification, are
 *    permitted provided that the following conditions are met:
 *      - Redistributions of source code must retain the above copyright notice, this list of
 *        conditions and the following disclaimer.
 *      - Redistributions in binary form must reproduce the above copyright notice, this list of
 *        conditions and the following disclaimer in the documentation and/or other materials
 *        provided with the distribution.
 *      - Neither the name of the Delft University of Technology nor the names of its contributors
 *        may be used to endorse or promote products derived from this software without specific
 *        prior written permission.
 *
 *    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS
 *    OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 *    MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *    COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 *    EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 *    GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 *    AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 *    NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 *    OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *    Changelog
 *      YYMMDD    Author            Comment
 *      130218    K. Kumar          File created.
 *
 *    References
 *
 *    Notes
 *
 */

#include <limits>
#include <sstream>
#include <stdexcept>

#include <TudatCore/Astrodynamics/BasicAstrodynamics/orbitalElementConversions.h>
#include <TudatCore/Astrodynamics/BasicAstrodynamics/unitConversions.h>

#include <Assist/Astrodynamics/unitConversions.h>
#include <Assist/Basics/comparisonFunctions.h>

#include "StochasticMigration/Database/testParticleCase.h"

namespace stochastic_migration
{
namespace database
{

using namespace assist::basics;
using namespace tudat::basic_astrodynamics::orbital_element_conversions;

//! Constructor taking all case data as input.
TestParticleCase::TestParticleCase(
        const int aCaseNumber,
        const double aRandomWalkSimulationDuration,
        const double aSynodicPeriodLimit,
        const double anOutputInterval,
        const double aStartUpIntegrationDuration,
        const double aConjunctionEventDetectionDistance,
        const double anOppositionEventDetectionDistance,
        const double aCentralBodyGravitationalParameter,
        const double aCentralBodyJ2GravityCoefficient,
        const double aCentralBodyEquatorialRadius,
        const double aSemiMajorAxisLimit,
        const double aMeanEccentricity,
        const double aFullWidthHalfMaxmimumEccentricityDistribution,
        const double aMeanInclination,
        const double aFullWidthHalfMaxmimumInclinationDistribution,
        const double aPerturbedBodyGravitationalParameter,
        const tudat::basic_mathematics::Vector6d& aPerturbedBodyStateInKeplerianElementsAtT0,
        const std::string& aNumericalIntegratorType,
        const double aNumericalIntegratorRelativeTolerance,
        const double aNumericalIntegratorAbsoluteTolerance,
        const double anInitialStepSize )
    : caseNumber( checkPositive( aCaseNumber, "Case number" ) ),
      randomWalkSimulationDuration( 
        checkPositive( aRandomWalkSimulationDuration, "Random walk duration [s]" ) ),
      synodicPeriodLimit( 
        checkPositive( aSynodicPeriodLimit, "Synodic period limit [s]" ) ),
      outputInterval( checkPositive( anOutputInterval, "Output interval [s]" ) ),
      startUpIntegrationDuration( 
        checkPositive( aStartUpIntegrationDuration, "Startup integration duration [s]" ) ),
      conjunctionEventDetectionDistance( 
        checkPositive( aConjunctionEventDetectionDistance, 
                       "Conjunction event detection distance [m]" ) ),
      oppositionEventDetectionDistance( 
        checkPositive( anOppositionEventDetectionDistance,
                       "Opposition event detection distance [m]" ) ),
      centralBodyGravitationalParameter( 
        checkPositive( aCentralBodyGravitationalParameter, 
                       "Central body gravitational parameter [m^3 s^-2]" ) ),
      centralBodyJ2GravityCoefficient( 
        checkGreaterThan( aCentralBodyJ2GravityCoefficient, 
                          "Central body J2 gravity coefficient [-]",
                          -std::numeric_limits< double >::min( ) ) ),
      centralBodyEquatorialRadius( 
        checkGreaterThan( aCentralBodyEquatorialRadius, "Central body equatorial radius [m]",
                          -std::numeric_limits< double >::min( ) ) ),
      semiMajorAxisLimit( checkPositive( aSemiMajorAxisLimit, "Semi-major axis limit [m]" ) ),
      meanEccentricity( checkPositive( aMeanEccentricity, "Mean eccentricity [-]" ) ),
      fullWidthHalfMaxmimumEccentricityDistribution( 
        checkPositive( aFullWidthHalfMaxmimumEccentricityDistribution, 
                       "Full-Width Half-Maximum eccentricity [-]" ) ),
      meanInclination( checkPositive( aMeanInclination, "Mean inclination [rad]" ) ),
      fullWidthHalfMaxmimumInclinationDistribution( 
        checkPositive( aFullWidthHalfMaxmimumInclinationDistribution, 
                       "Full-Width Half-Maximum inclination [rad]" ) ),
      perturbedBodyGravitationalParameter( 
        checkPositive( aPerturbedBodyGravitationalParameter, 
                       "Perturbed body gravitational parameter [m^3 s^-2]" ) ),
      perturbedBodyStateInKeplerianElementsAtT0( 
        ( Eigen::VectorXd( 6 ) 
            << checkPositive( aPerturbedBodyStateInKeplerianElementsAtT0( semiMajorAxisIndex ),
                              "Perturbed body initial semi-major axis [m]" ),
               checkPositive( aPerturbedBodyStateInKeplerianElementsAtT0( eccentricityIndex ),
                              "Perturbed body initial eccentricity [-]" ),
               checkPositive( aPerturbedBodyStateInKeplerianElementsAtT0( inclinationIndex ),
                              "Perturbed body initial inclination [rad]" ),
               aPerturbedBodyStateInKeplerianElementsAtT0.segment( 3, 3 ) ).finished( ) ),
      numericalIntegratorType( aNumericalIntegratorType ),
      numericalIntegratorRelativeTolerance( 
        checkPositive( aNumericalIntegratorRelativeTolerance, 
                       "Numerical integrator relative tolerance [-]" ) ),
      numericalIntegratorAbsoluteTolerance( 
        checkPositive( aNumericalIntegratorAbsoluteTolerance, 
                       "Numerical integrator absolute tolerance [-]" ) ),
      initialStepSize( anInitialStepSize )
{
    if ( aNumericalIntegratorType.empty( ) )
    {
        std::stringstream errorMessage;
        errorMessage << "Numerical integrator type string is empty";
        throw std::runtime_error( errorMessage.str( ) );
    }
}

//! Overload == operator.
bool operator==( const TestParticleCase& testParticleCase1,
                 const TestParticleCase& testParticleCase2 )
{
    return ( testParticleCase1.caseNumber == testParticleCase2.caseNumber
             && testParticleCase1.randomWalkSimulationDuration
             == testParticleCase2.randomWalkSimulationDuration
             && testParticleCase1.synodicPeriodLimit == testParticleCase2.synodicPeriodLimit
             && testParticleCase1.outputInterval == testParticleCase2.outputInterval
             && testParticleCase1.startUpIntegrationDuration
             == testParticleCase2.startUpIntegrationDuration
             && testParticleCase1.conjunctionEventDetectionDistance
             == testParticleCase2.conjunctionEventDetectionDistance
             && testParticleCase1.oppositionEventDetectionDistance
             == testParticleCase2.oppositionEventDetectionDistance
             && testParticleCase1.centralBodyGravitationalParameter
             == testParticleCase2.centralBodyGravitationalParameter
             && testParticleCase1.centralBodyJ2GravityCoefficient
             == testParticleCase2.centralBodyJ2GravityCoefficient
             && testParticleCase1.centralBodyEquatorialRadius
             == testParticleCase2.centralBodyEquatorialRadius
             && testParticleCase1.semiMajorAxisLimit == testParticleCase2.semiMajorAxisLimit
             && testParticleCase1.meanEccentricity == testParticleCase2.meanEccentricity
             && testParticleCase1.fullWidthHalfMaxmimumEccentricityDistribution
             == testParticleCase2.fullWidthHalfMaxmimumEccentricityDistribution
             && testParticleCase1.meanInclination == testParticleCase2.meanInclination
             && testParticleCase1.fullWidthHalfMaxmimumInclinationDistribution
             == testParticleCase2.fullWidthHalfMaxmimumInclinationDistribution
             && testParticleCase1.perturbedBodyGravitationalParameter
             == testParticleCase2.perturbedBodyGravitationalParameter
             && testParticleCase1.perturbedBodyStateInKeplerianElementsAtT0
             == testParticleCase2.perturbedBodyStateInKeplerianElementsAtT0
             && !testParticleCase1.numericalIntegratorType.compare(
                 testParticleCase2.numericalIntegratorType )
             && testParticleCase1.numericalIntegratorRelativeTolerance
             == testParticleCase2.numericalIntegratorRelativeTolerance
             && testParticleCase1.numericalIntegratorAbsoluteTolerance
             == testParticleCase2.numericalIntegratorAbsoluteTolerance
             && testParticleCase1.initialStepSize == testParticleCase2.initialStepSize );
}

//! Overload < operator.
bool operator<( const TestParticleCase& testParticleCase1,
                const TestParticleCase& testParticleCase2 )
{
    return testParticleCase1.caseNumber < testParticleCase2.caseNumber;
}

//! Overload << operator.
std::ostream& operator<<( std::ostream& outputStream, const TestParticleCase& testParticleCase )
{
    using namespace tudat::basic_astrodynamics::orbital_element_conversions;
    using namespace tudat::basic_astrodynamics::unit_conversions;
    using namespace assist::astrodynamics;
    
    // Write contents of TestParticleCase object to output stream.
    outputStream << "Case: " << testParticleCase.caseNumber << std::endl;
    outputStream << "Random walk simulation duration [Jyr]: "
                 << convertSecondsToJulianYears(
                        testParticleCase.randomWalkSimulationDuration ) << std::endl;
    outputStream << "Synodic period limit [Jyr]: "
                 << convertSecondsToJulianYears( testParticleCase.synodicPeriodLimit )
                 << std::endl;
    outputStream << "Output interval [hr]: "
                 << convertSecondsToHours( testParticleCase.outputInterval ) << std::endl;
    outputStream << "Startup integration duration [Jyr]: "
                 << convertSecondsToJulianYears( testParticleCase.startUpIntegrationDuration )
                 << std::endl;
    outputStream << "Conjunction event detection distance [m]: "
                 << testParticleCase.conjunctionEventDetectionDistance << std::endl;
    outputStream << "Opposition event detection distance [m]: "
                 << testParticleCase.oppositionEventDetectionDistance << std::endl;
    outputStream << "Central body gravitational parameter [m^3 s^-2]: "
                 << testParticleCase.centralBodyGravitationalParameter << std::endl;
    outputStream << "Central body J2 gravity coefficient: "
                 << testParticleCase.centralBodyJ2GravityCoefficient << std::endl;
    outputStream << "Central body equatorial radius [m]: "
                 << testParticleCase.centralBodyEquatorialRadius << std::endl;
    outputStream << "Semi-major axis limit [m]: "
                 << testParticleCase.semiMajorAxisLimit << std::endl;
    outputStream << "Mean eccentricity [-]: "
                 << testParticleCase.meanEccentricity << std::endl;
    outputStream << "FWHM eccentricity [-]: "
                 << testParticleCase.fullWidthHalfMaxmimumEccentricityDistribution << std::endl;
    outputStream << "Mean inclination [deg]: "
                 << convertRadiansToDegrees( testParticleCase.meanInclination ) << std::endl;
    outputStream << "FWHM inclination [deg]: "
                 << convertRadiansToDegrees(
                        testParticleCase.fullWidthHalfMaxmimumInclinationDistribution )
                 << std::endl;
    outputStream << "Perturbed body's gravitational parameter [m^3 s^-2]: "
                 << testParticleCase.perturbedBodyGravitationalParameter << std::endl;
    outputStream << "Perturbed body's semi-major axis at T0 [m]: "
                 << testParticleCase.perturbedBodyStateInKeplerianElementsAtT0(
                        semiMajorAxisIndex ) << std::endl;
    outputStream << "Perturbed body's eccentricity at T0 [-]: "
                 << testParticleCase.perturbedBodyStateInKeplerianElementsAtT0( eccentricityIndex )
                 << std::endl;
    outputStream << "Perturbed body's inclination at T0 [deg]: "
                 << convertRadiansToDegrees(
                        testParticleCase.perturbedBodyStateInKeplerianElementsAtT0(
                            inclinationIndex ) ) << std::endl;
    outputStream << "Perturbed body's argument of periapsis at T0 [deg]: "
                 << convertRadiansToDegrees(
                        testParticleCase.perturbedBodyStateInKeplerianElementsAtT0(
                            argumentOfPeriapsisIndex ) ) << std::endl;
    outputStream << "Perturbed body's longitude of ascending node at T0 [deg]: "
                 << convertRadiansToDegrees(
                        testParticleCase.perturbedBodyStateInKeplerianElementsAtT0(
                            longitudeOfAscendingNodeIndex ) ) << std::endl;
    outputStream << "Perturbed body's true anomaly at T0 [deg]: "
                 << convertRadiansToDegrees(
                        testParticleCase.perturbedBodyStateInKeplerianElementsAtT0(
                            trueAnomalyIndex ) ) << std::endl;
    outputStream << "Numerical integration type: "
                 << testParticleCase.numericalIntegratorType << std::endl;
    outputStream << "Numerical integrator relative tolerance: "
                 << testParticleCase.numericalIntegratorRelativeTolerance << std::endl;
    outputStream << "Numerical integrator absolute tolerance: "
                 << testParticleCase.numericalIntegratorAbsoluteTolerance << std::endl;
    outputStream << "Numerical integrator initial step size [s]: "
                 << testParticleCase.initialStepSize << std::endl;

    // Return output stream.
    return outputStream;
}

} // namespace database
} // namespace stochastic_migration
