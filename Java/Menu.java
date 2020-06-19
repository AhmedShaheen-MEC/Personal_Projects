package Lab;

import lejos.hardware.Button;
import lejos.hardware.lcd.LCD;
import lejos.utility.Delay;

public class Menu {
	int colorId = 1;

	// Sitting the initial Menu
	// Sitting the initial Values of the Robot:

	public int chooseColor() {
		while (!Button.ENTER.isDown()) { // if the Enter button pressed will break the loop
		LCD.drawString("Select color:", 0, 0);
		LCD.drawString("Black", 3, 1);
		LCD.drawString("Blue", 3, 2);
		LCD.drawString("Green", 3, 3);
		LCD.drawString("Yellow", 3, 4);
		LCD.drawString("Red", 3, 5);
		LCD.drawString("White", 3, 6);
		LCD.drawString("Brown", 3, 7);
		Delay.msDelay(200);

			if (Button.UP.isDown()) {
				colorId--;
				if (colorId< 1)
					colorId= 1;
				LCD.clear(colorId + 1, 1, 0);
				LCD.drawString("> ",0 , colorId);
				Delay.msDelay(100);

			}
			// if the down bottom is pressed the highlighted row will step down:
			else if (Button.DOWN.isDown()) {
				colorId++;
				if (colorId > 7)
					colorId = 7;
				LCD.clear(colorId + 1, 0, 1);
				LCD.drawString("> ",0 , colorId);
				Delay.msDelay(100);
			}
		}
		LCD.clear();
		LCD.drawString("colorselected", 4, 4);
		Delay.msDelay(500);
		LCD.clear();
		return colorId;
	}

}
