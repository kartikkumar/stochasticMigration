/*    
 *    Copyright (c) 2010-2013, Delft University of Technology
 *    Copyright (c) 2010-2013, K. Kumar (me@kartikkumar.com)
 *    All rights reserved.
 *    See http://bit.ly/12SHPLR for license details.
 *
 *    Changelog
 *      YYMMDD    Author            Comment
 *      120520    K. Kumar          File created from old TestParticleKick.h.
 *      130212    K. Kumar          Added Doxygen comments and a note. Added planetary_rings
 *                                  namespace. Added ()-operator overloading to allow for sorting
 *                                  using STL containers.
 *      130217    K. Kumar          Updated "mab simulations" references to "stochastic migration";
 *                                  renamed file.
 *      130218    K. Kumar          Updated "encounter" to "conjunction" to reduce confusion in
 *                                  code.
 *      130308    K. Kumar          Moved constructor implementation to source file and added
 *                                  sanity checks to ensure that test particle kick is valid.
 *      130309    K. Kumar          Moved all existing operator overloads to non-member functions
 *                                  and added new ones, including for pointer comparisons.
 *      130328    K. Kumar          Moved standard operator overload functions to Assist.
 *      130329    K. Kumar          Updated typedef for test particle kick table to boost ptr_set.
 *      130708    K. Kumar          Added kick ID, Tisserance parameter, and energy & angular 
 *                                  momentum relative errors; removed mass ratio.
 *
 *    References
 *      sbi. C++ Operator Overloading, Stack Overflow,
 *          http://stackoverflow.com/questions/4421706/operator-overloading, 2010, last accessed:
 *          9th March, 2013.
 *
 *    Notes
 *
 */

#ifndef STOCHASTIC_MIGRATION_TEST_PARTICLE_KICK_H
#define STOCHASTIC_MIGRATION_TEST_PARTICLE_KICK_H

#include <iostream>
#include <map>

#include <boost/ptr_container/ptr_set.hpp>
#include <boost/shared_ptr.hpp>

namespace stochastic_migration
{
namespace database
{

//! Data struct that contains kick data, generated by test particle simulations.
/*!
 * This data struct contains data for one kick, stored in an SQLite3 database. The data stored
 * is generated by a test particle simulation.
 */
struct TestParticleKick
{
public:

    //! Default constructor, taking input values for all elements of kick.
    TestParticleKick( const int aKickId,
                      const int aSimulationNumber,
                      const double aConjunctionEpoch,
                      const double aConjunctionDistance,
                      const double aPreConjunctionEpoch,
                      const double aPreConjunctionDistance,
                      const double aPreConjunctionSemiMajorAxis,
                      const double aPreConjunctionEccentricity,
                      const double aPreConjunctionInclination,
                      const double aPostConjunctionEpoch,
                      const double aPostConjunctionDistance,
                      const double aPostConjunctionSemiMajorAxis,
                      const double aPostConjunctionEccentricity,
                      const double aPostConjunctionInclination );

    //! Unique id for kick in database.
    const int kickId;

    //! Simulation number.
    const int simulationNumber;

    //! Conjunction epoch [s].
    const double conjunctionEpoch;

    //! Conjunction distance [m].
    const double conjunctionDistance;

    //! Pre-Conjunction (opposition) epoch [s].
    const double preConjunctionEpoch;

    //! Pre-Conjunction (opposition) distance [m].
    const double preConjunctionDistance;

    //! Pre-Conjunction semi-major axis of test particle [m].
    const double preConjunctionSemiMajorAxis;

    //! Pre-Conjunction eccentricity of test particle [-].
    const double preConjunctionEccentricity;

    //! Pre-Conjunction inclination of test particle [rad].
    const double preConjunctionInclination;

    //! Post-Conjunction (opposition) epoch [s].
    const double postConjunctionEpoch;

    //! Post-Conjunction (opposition) distance [m].
    const double postConjunctionDistance;

    //! Post-Conjunction semi-major axis of test particle [m].
    const double postConjunctionSemiMajorAxis;

    //! Post-Conjunction eccentricity of test particle [-].
    const double postConjunctionEccentricity;

    //! Post-Conjunction inclination of test particle [rad].
    const double postConjunctionInclination;

protected:
private:
};

//! Typedef for shared-pointer to TestParticleKick object.
typedef boost::shared_ptr< TestParticleKick > TestParticleKickPointer;

//! Typedef for table of kicks (pointers) generated by test particle simulations.
typedef boost::ptr_set< TestParticleKick > TestParticleKickTable;

//! Typedef for map of test particle simulation numbers & mass ratios.
typedef std::map< unsigned int, double > TestParticleSimulationNumbersAndMassRatios;

// // Define all of the operator overloads as non-member functions (sbi, 2010).

//! Overload == operator.
bool operator==( const TestParticleKick& testParticleKick1,
                 const TestParticleKick& testParticleKick2 );

//! Overload < operator.
bool operator<( const TestParticleKick& testParticleKick1,
                const TestParticleKick& testParticleKick2 );

//! Overload << operator.
std::ostream& operator<<( std::ostream& outputStream, const TestParticleKick& testParticleKick );

} // namespace database
} // namespace stochastic_migration

#endif // STOCHASTIC_MIGRATION_TEST_PARTICLE_KICK_H
