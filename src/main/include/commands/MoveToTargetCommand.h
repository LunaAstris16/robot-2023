// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include <pathplanner/lib/commands/PPSwerveControllerCommand.h>
#include <pathplanner/lib/PathPlannerTrajectory.h>
#include <pathplanner/lib/PathPlanner.h>
#include <photonlib/PhotonCamera.h>

#include "subsystems/DriveSubsystem.h"
#include "subsystems/PoseEstimatorSubsystem.h"

/**
 * An example command.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class MoveToTargetCommand
    : public frc2::CommandHelper<frc2::CommandBase, MoveToTargetCommand> {
  public:
    MoveToTargetCommand(
      DriveSubsystem* pDriveSubsystem, 
      photonlib::PhotonCamera *pCamera, 
      PoseEstimatorSubsystem *pPoseEstimator, 
      std::string position);

    ~MoveToTargetCommand();

    void Initialize() override;

    void Execute() override;

    void End(bool interrupted) override;

    bool IsFinished() override;

  private:

    //subsystems
    DriveSubsystem *m_pDriveSubsystem;
    photonlib::PhotonCamera *m_pCamera;
    PoseEstimatorSubsystem *m_pPoseEstimator;

    //positioning relative to the april tag
    std::string position;
    std::unordered_map<std::string, frc::Pose2d> positionMap {
      {"Center", {1.5_m, 0_m, {180_deg}}},
      {"Right", {2_m, 16_in, {180_deg}}},
      {"Left", {2_m, -16_in, {180_deg}}},
      {"Loading", {2_m, 1_m, {180_deg}}}
    };
    pathplanner::PPSwerveControllerCommand* alignCommand = NULL;
    pathplanner::PathConstraints constraints = { 1_mps, 1_mps_sq };

};