#include "declareStuff.hpp"
Motor FrontRightM(1, true, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);
Motor FrontLeftM(2,  false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);
Motor BackRightM(3,  true, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);
Motor BackLeftM(4,  false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);
Motor IntakeM(5,  true, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees);
Motor LiftM(6,  false, AbstractMotor::gearset::red, AbstractMotor::encoderUnits::degrees);
Motor Flywheel1M(9,  false, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees);
Motor Flywheel2M(10,  true, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees);

Controller MasterC;

ControllerButton intakeInButton(ControllerDigital::L1);
ControllerButton intakeOutButton(ControllerDigital::L2);
ControllerButton runFlywheelFastButton(ControllerDigital::X);
ControllerButton runFlywheelMediumButton(ControllerDigital::A);
ControllerButton runFlywheelSlowButton(ControllerDigital::B);

ChassisControllerIntegrated drive = ChassisControllerFactory::create(
  {FrontLeftM, BackLeftM}, {FrontRightM, BackRightM},
  AbstractMotor::gearset::green,
  {4.15_in, 14.5_in}
);

ChassisControllerPID drivePID = ChassisControllerFactory::create(
  {FrontLeftM, BackLeftM}, {FrontRightM, BackRightM},
  IterativePosPIDController::Gains{0.004, 0.00001, 0.000008},
  IterativePosPIDController::Gains{0.004, 0, 0.0001},
  IterativePosPIDController::Gains{0.006, 0.00001, 0.0001},
  AbstractMotor::gearset::green,
  {4.15_in, 14.5_in}
);

AsyncPosIntegratedController lift = AsyncControllerFactory::posIntegrated(LiftM);

MotorGroup flywheel({Flywheel1M,Flywheel2M});

AsyncMotionProfileController driveController = AsyncControllerFactory::motionProfile(0.75, 1.0, 5.0, drive);

bool autonRunning = false;

void initialize() {
	Flywheel1M.set_brake_mode(MOTOR_BRAKE_COAST);
	Flywheel2M.set_brake_mode(MOTOR_BRAKE_COAST);
	IntakeM.set_brake_mode(MOTOR_BRAKE_BRAKE);
	LiftM.set_brake_mode(MOTOR_BRAKE_HOLD);
	FrontLeftM.set_brake_mode(MOTOR_BRAKE_HOLD);
	FrontRightM.set_brake_mode(MOTOR_BRAKE_HOLD);
	BackRightM.set_brake_mode(MOTOR_BRAKE_HOLD);
	BackLeftM.set_brake_mode(MOTOR_BRAKE_HOLD);
}

void disabled() {

}

void competition_initialize() {

}
