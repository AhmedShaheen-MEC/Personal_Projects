package Lab;

import lejos.hardware.lcd.LCD;
import lejos.hardware.motor.EV3LargeRegulatedMotor;
import lejos.hardware.port.MotorPort;
import lejos.utility.Delay;
import lejos.hardware.Button;
import lejos.hardware.Sound;

public class MotorsControl {
	public static final float LONG_RANGE = 0.3f;
	private static final float MID_RANGE = 0.15f;
	private static final float CLOSE_RANGE = 0.04f;
	private static final float WHEEL_RADIUS = 2.75f;
	private static final float RAD_DEGREES = (float) (180 / 3.14);
	private static final int VOLUME = 50, DURATION = 500, FREQUENCY = 400;
	private static final float DESIRED_DISTANCE = -100f;
	private static final int WALL_INDICATOR = 12;

	private int directionIndicator;
	private int flagArray[] = new int[4];
	private EV3LargeRegulatedMotor right;
	private EV3LargeRegulatedMotor left;
	public GyroSensor gyroObject;
	public UltraSonic ultraObject;
	private ColorSensor colorObject;

	public MotorsControl() {

		right = new EV3LargeRegulatedMotor(MotorPort.C);
		left = new EV3LargeRegulatedMotor(MotorPort.B);
		gyroObject = new GyroSensor();
		ultraObject = new UltraSonic();
		colorObject = new ColorSensor();
	}

	public void setUpSpeed(int speed) {
		right.setSpeed(speed);
		left.setSpeed(speed);

	}

	public void driveForward(boolean status) {
		float desired_angle;
		if (status) {
			right.backward();
			left.backward();
		} else {
			if (this.ultraObject.getDistance() > LONG_RANGE) {
				desired_angle = (DESIRED_DISTANCE / WHEEL_RADIUS) * RAD_DEGREES;
				right.rotate((int) desired_angle, true);
				left.rotate((int) desired_angle);
				;
			}

		}

	}

	public void driveBackward() {
		right.rotate(360,true);
		left.rotate(360);
	}

	public void stopDriving() {
		right.stop();
		left.stop();
	}

	public void closeMotorPorts() {
		right.close();
		left.close();
	}

	public int wallIndex() {
		if (ultraObject.getDistance() < MID_RANGE) {
			return WALL_INDICATOR;
		} else {

			return this.directionIndicator;
		}

	}

	public void rotate(int theta) {
		this.setUpSpeed(250);
		this.gyroObject.reset();
		right.forward();
		left.backward();
		while (true) {
			if (Math.abs(this.gyroObject.getAngulerdisp()) >= theta) {
				this.stopDriving();
				break;
			}
		}
	}

	public void rotateAnti(int error) {
		this.gyroObject.reset();
		this.setUpSpeed(120);
		right.backward();
		left.forward();
		while (true) {
			if (Math.abs(this.gyroObject.getAngulerdisp()) >= (error-1)) {
				this.stopDriving();
				break;
			}
		}
	}

	public void resetGyro() {
		gyroObject.reset();
	}

	public void checkSurrounding() {

		int directionStep = 90;
		int flagArray[] = { 0, 0, 0, 0 };
		int error;
		this.directionIndicator = 90;
		for (int i = 0; i < 4; i++) {
			this.rotate(directionStep);
			error =(int) (Math.abs(this.gyroObject.getAngulerdisp()) - directionStep);
			Delay.msDelay(200);
			flagArray[i] = this.wallIndex();
			LCD.clear(6, 7, 3);
			LCD.drawString("Surr:" + flagArray[i], 0, 7);
			this.directionIndicator += 90;
			LCD.drawString("Error:" + error, 7, 4);
			this.rotateAnti(error);
		}
		this.flagArray = flagArray;

	}

	public int setDirection() {
		int desiredPose = 0;
		if (flagArray[0] == 90) {
			desiredPose = flagArray[0];
		} else if (flagArray[2] == 270) {
			if (flagArray[3] == 360) {
				desiredPose = 0;
			}
			desiredPose = 270;
		} else if (flagArray[3] == 360) {

			desiredPose = 0;
		} else {
			desiredPose = 180;
		}
		LCD.drawString("Pose:" + desiredPose, 0, 4);

		return desiredPose;

	}

	public void colorAdjustement(int colorId) {
		while (true) {
			if (this.ultraObject.getDistance() > CLOSE_RANGE) {
				this.setUpSpeed(200);
				this.driveForward(true);
			} else  {
				this.stopDriving();
				colorObject.getColor();
				if (colorObject.getColor_id() == colorId) {
					Sound.setVolume(VOLUME);
					Sound.playTone(FREQUENCY, DURATION);
					System.exit(1);
				} else {
					this.driveBackward();
						break;
					}

				}
			}

		}

}
