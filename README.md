KickStart-V1
============

This Git provides some starting material to kickstart your projects on La BlueFrog :

- Documentation : <br>
  . Structure of the example projects (see readme.txt)<br>
  . Development environment and toolchain options (see /documentation)<br>
  . Board hardware (datasheets etc., see /documentation) <br>

- Sample C projects  -- exercizing various functionalities of La BlueFrog-V1.<br>
  . Usable as starting point to write your own applications.<br>
  . Also illustrating usage of the libraries provided (see below).<br>

- Libraries:<br>
  . « BlueFrogV1-Lib »: for easy set-up of the board and usage of its functionalities (Flash, OLEDs, LEDs, switches…) — abstracting the hardware details.<br>
  . Plus, STM32 and ARM-core specific libraries: just use them as illustrated in the examples.<br>


To give you a quick idea of what C code could look like using the libraries provided: <br>
with the following main.c, you initialize the STM32 and most peripherals on La BlueFrog V1 (even though we're not using them all in this example) and turn on/off 2 LEDs under control of the slider switch:
```
int main(void)
{
    // Board Initializations and Configurations
    Set_System();
    PWR_Init();
    Led_Config();
    Slide_Config();  
    FLASH_Init();
    OLED_Init();

    // Infinite Loop -  Control LEDs from slider switch
    while(1)
    {
            if (!GPIO_ReadInputDataBit(SLIDE_1_GPIO_PORT, SLIDE_1_PIN))
            {
               Led_Verte_ON();
               Led_Rouge_OFF(); 
            }
            if (!GPIO_ReadInputDataBit(SLIDE_2_GPIO_PORT, SLIDE_2_PIN))
            {
               Led_Verte_OFF();
               Led_Rouge_ON();
            }   
    }
    return 0;
}
```
The libraries are fairly easy to modify or enhance to suit your own needs.

-
Note:<br>
I am providing this package as a means to help using La BlueFrog V1 as easily as possible. <br>
As I am by no means a hardcore software guy, many improvements are for sure possible in the way these sample projects are structured and coded. This will come with time and as more experienced software developpers bring their contribution. <br>
In the future, it is planned to add a number of convenient libraries — such as a file system for embedded, a lightweight graphic library for the OLED, etc. <br>
You are welcome to contribute. Contact me if you would like information on what is already in progress.<br>

PS: Most of the software dev work before setting up this Git was done by Roman (thanks!).
