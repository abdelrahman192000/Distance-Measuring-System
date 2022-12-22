
#include "lcd.h"
#include "ultrasonic.h"
#include "std_types.h"
#include<avr/interrupt.h> // to enable I-bit
#include<util/delay.h>

int main(void)
{
	uint16 new_distance=0;
	uint16 first_new_distance=0;
	LCD_init();
	Ultrasonic_init();   /* initialize ultrasonic/lcd driver */

	/* Enable Global Interrupt I-Bit */
	SREG |= (1<<7);

	/* Display this string only once on LCD */
	LCD_displayStringRowColumn(0, 1, "Ultrasonic_read");
	LCD_displayStringRowColumn(1, 0, "distance=    cm");

	while (1)
	{
		/* display the new_distance on LCD screen */
		new_distance= Ultrasonic_readDistance();
		LCD_moveCursor(1, 11);
		/* Display the new_distance according to the number of its Digits */
		if (new_distance != first_new_distance)//entering this condition only if the current new_distance different from the previous new_distance
		{
			if(new_distance < 10)
			{
				LCD_intgerToString(new_distance);
				LCD_displayCharacter(' ');
				LCD_displayCharacter(' ');
			}
			else if(new_distance < 100)
			{
				LCD_intgerToString(new_distance);
				LCD_displayCharacter(' ');
			}
			else
			{
				LCD_intgerToString(new_distance);
			}
		}
		first_new_distance= new_distance; // set the previous new_distance to be equal to the current position
		_delay_ms(100);

	}
}
