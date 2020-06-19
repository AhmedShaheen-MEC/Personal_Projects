	package Lab;

import lejos.hardware.sensor.EV3ColorSensor;
import lejos.hardware.sensor.SensorMode;
import lejos.hardware.port.SensorPort;
import lejos.hardware.lcd.LCD; 



public class ColorSensor {
	private final  int[]  Array = {0 ,0,0};
	private  String color_name= ""; 
	private  int color_id;
	private  EV3ColorSensor colorsensor;
	private float [] id;
	private SensorMode colorid;
	
	
	public ColorSensor() {
			colorsensor = new EV3ColorSensor(SensorPort.S1); 
	}
	public void getColor() {
			
		//Get samples 
		colorid = colorsensor.getColorIDMode(); 	// obtain the color ID( 0-7)
		id = new float  [colorid.sampleSize()];
		colorid.fetchSample(id,0);
		color_id=(int) id[0];
		color_name= getcolorName();
		//print the result
		print();
		
	}
	public int getColor_id() {
		return color_id;
	}
	
	private void print() {
		LCD.drawString("Det_Color:" + color_name, 3, 5);
    }
	private String getcolorName () {
		
	   switch (color_id) {
	    case (0) : color_name = "None"; break; 
	    case (1) : color_name = "Black"; break; 
	    case (2) : color_name = "Blue"; break; 
	    case (3) : color_name = "Green"; break; 
	    case (4) : color_name = "Yellow"; break; 
	    case (5) : color_name = "Red"; break; 
	    case (6) : color_name = "White"; break; 
	    case (7) : color_name = "Brown"; break; 
	   }
	  return color_name;
    }
}
