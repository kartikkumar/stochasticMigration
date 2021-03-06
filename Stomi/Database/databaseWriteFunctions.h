/*    
 * Copyright (c) 2010-2014, Delft University of Technology
 * Copyright (c) 2010-2014, K. Kumar (me@kartikkumar.com)
 * All rights reserved.
 * See http://bit.ly/12SHPLR for license details.
 */

#include <string>

#include "Stomi/Database/testParticleKick.h"

#ifndef STOMI_DATABASE_WRITE_FUNCTIONS_H
#define STOMI_DATABASE_WRITE_FUNCTIONS_H

namespace stomi
{
namespace database
{

//! Populate test particle kick table.
/*!
 * Populates table of test particle kicks in SQLite database.
 * \param databaseAbsolutePath Absolute path to simulation database.
 * \param testParticleSimulationId Test particle simulation ID associated with kick table.
 * \param testParticleKickTable Table containing kick data as set of pointers to TestParticleKick 
 *          objects.
 * \param testParticleKickTableName String name of test particle kick table in database.
 * \param testParticleInputTableName String name of test particle input table in database.
 */
void populateTestParticleKickTable( const std::string& databaseAbsolutePath,
                                    const int testParticleSimulationId,
                                    const TestParticleKickTable& testParticleKickTable,
                                    const std::string& testParticleKickTableName, 
                                    const std::string& testParticleInputTableName );

//! Populate random walk output table.
/*!
 * Populates table of random walk output data in SQLite database.
 * \param databaseAbsolutePath Absolute path to simulation database.
 * \param randomWalkSimulationId Random walk simulation ID associated with output table.
 * \param averageLongitudeResidual Average longitude residual of perturbed body during random
 *           walk simulation. 
 * \param maximumLongitudeResidualChange Maximum longitude residual change that perturbed body 
 *          underwent during random walk simulation.
 * \param averageEccentricity Average eccentricity of perturbed body during random walk Monte 
 *          Carlo simulation. 
 * \param maximumEccentricityChange Maximum eccentricity change that perturbed body underwent
 *          during random walk simulation.
 * \param averageInclination Average inclination of perturbed body during random walk simulation. 
 * \param maximumInclinationChange Maximum inclination change that perturbed body underwent
 *          during random walk simulation.
 * \param randomWalkOutputTableName String name of random walk output table in database.
 * \param randomWalkInputTableName String name of random walk input table in database.
 */
void populateRandomWalkOutputTable(
        const std::string& databaseAbsolutePath, const int randomWalkSimulationId,
        const double averageLongitudeResidual, const double maximumLongitudeResidualChange,
        const double averageEccentricity, const double maximumEccentricityChange,
        const double averageInclination, const double maximumInclinationChange,
        const std::string& randomWalkOutputTableName, 
        const std::string& randomWalkInputTableName );

} // namespace database
} // namespace stomi

#endif // STOMI_DATABASE_WRITE_FUNCTIONS_H
