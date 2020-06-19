package Lab;

import lejos.hardware.sensor.EV3UltrasonicSensor;
import lejos.hardware.port.SensorPort;
import lejos.robotics.SampleProvider;
import lejos.hardware.lcd.LCD; 

	
public class UltraSonic {
	private  EV3UltrasonicSensor distanceSensor;
	private  SampleProvider  distance;
	private  float [] sample_Distane;
	
	public UltraSonic (){
		distanceSensor = new EV3UltrasonicSensor(SensorPort.S4);
		distance  = distanceSensor.getDistanceMode();
		sample_Distane  = new float [distance.sampleSize()];
	}
	
	public  float  getDistance (){  // Get the measured distance
		float actdist; 
		distance.fetchSample (sample_Distane, 0);
		actdist = sample_Distane[0];
		LCD.drawString("Measured_dis:"+ actdist , 0,0);
		return actdist;	
	}
}