/*    
 *    Copyright (c) 2010-2014, Delft University of Technology
 *    Copyright (c) 2010-2014, K. Kumar (me@kartikkumar.com)
 *    All rights reserved.
 *    See http://bit.ly/12SHPLR for license details.
 */

#ifndef STOMI_DICTIONARIES_H
#define STOMI_DICTIONARIES_H

#include <Tudat/InputOutput/dictionaryTools.h>

namespace stomi
{
namespace input_output
{

//! Get dictionary for test particle database generator application.
/*!
 * Returns standard dictionary for test particle database generator application.
 * \return Shared-pointer to new dictionary for test particle database generator application.
 */
tudat::input_output::dictionary::DictionaryPointer getTestParticleDatabaseGeneratorDictionary( );

//! Get dictionary for random walk database generator application.
/*!
 * Returns standard dictionary for random walk database generator application.
 * \return Shared-pointer to new dictionary for random walk database generator application.
 */
tudat::input_output::dictionary::DictionaryPointer getRandomWalkDatabaseGeneratorDictionary( );

//! Get dictionary for testParticleSimulator application.
/*!
 * Returns standard dictionary for TestParticleSimulator application.
 * \return Shared-pointer to new dictionary for TestParticleSimulator application.
 */
tudat::input_output::dictionary::DictionaryPointer getTestParticleSimulatorDictionary( );

//! Get dictionary for randomWalkSimulator application.
/*!
 * Returns standard dictionary for RandomWalkSimulator application.
 * \return Shared-pointer to new dictionary for RandomWalkSimulator application.
 */
tudat::input_output::dictionary::DictionaryPointer getRandomWalkSimulatorDictionary( );

} // namespace input_output
} // namespace stomi

#endif // STOMI_DICTIONARIES_H

/*
 *    Unit tests need to be added to test the lexical dictionaries defined.
 */
