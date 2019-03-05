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
ControllerButton runFlywheelFastButton(ControllerDigital::A);
ControllerButton runFlywheelSlowButton(ControllerDigital::Y);
ControllerButton shootBarageButton(ControllerDigital::X);

ChassisControllerIntegrated drive = ChassisControllerFactory::create(
  {FrontLeftM, BackLeftM}, {FrontRightM, BackRightM},
  AbstractMotor::gearset::green,
  {4_in, 17_in}
);

MotorGroup flywheel({Flywheel1M,Flywheel2M});

AsyncMotionProfileController driveController = AsyncControllerFactory::motionProfile(1.0, 2.0, 10.0, drive);

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
