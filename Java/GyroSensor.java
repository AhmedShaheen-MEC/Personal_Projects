package Lab;


import lejos.hardware.lcd.LCD;
import lejos.hardware.port.SensorPort;
import lejos.hardware.sensor.EV3GyroSensor;
import lejos.robotics.SampleProvider;

	

public class GyroSensor {
	
	private  EV3GyroSensor pose_sensor ;	
	private  SampleProvider currentPose ;	
	private  float [] sample_Angle;
	
	public GyroSensor() {
		pose_sensor = new EV3GyroSensor(SensorPort.S3);
		currentPose = pose_sensor.getAngleMode();	
		sample_Angle= new float  [currentPose.sampleSize()];
	}
	 
	public void reset() {
			pose_sensor.reset(); // Initialize the starting angle to 0 whenever pose_sensor object is created..!
	}
	
	public float getAngulerdisp() {
	float rotation;
	currentPose.fetchSample(sample_Angle, 0);
	rotation= sample_Angle[0]; 
	LCD.drawString("ActAngl:"+ Math.abs(rotation) , 0,6);
	return rotation;
	} 
}
