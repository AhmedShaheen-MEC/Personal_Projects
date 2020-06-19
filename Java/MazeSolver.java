package Lab;

import lejos.hardware.Button;
import lejos.hardware.lcd.LCD;
import lejos.hardware.motor.EV3LargeRegulatedMotor;
import lejos.hardware.port.MotorPort;
import lejos.utility.Delay;

public class Lab5 {
	private static int INTIAL_SPEED = 800;
	private static MotorsControl robotDriver;
	private static final int ROTATION_STEP = 90;

	public static void main(String[] args) {
		Menu colorSelector = new Menu();
		int desiredColor = colorSelector.chooseColor();
		robotDriver = new MotorsControl();
		robotDriver.setUpSpeed(INTIAL_SPEED);
		int target_pose;

		while (Button.ENTER.isUp()) {
			robotDriver.setUpSpeed(INTIAL_SPEED);
			robotDriver.driveForward(false);
			robotDriver.checkSurrounding();
			target_pose = robotDriver.setDirection();
			if (target_pose == 180) {
				for (int i = 0; i < 4; i++) {
					robotDriver.rotate(ROTATION_STEP);
					if (robotDriver.ultraObject.getDistance() < robotDriver.LONG_RANGE) {
						robotDriver.colorAdjustement(desiredColor);
					}
				}
			}
			robotDriver.rotate(target_pose);
		}
	}
}
