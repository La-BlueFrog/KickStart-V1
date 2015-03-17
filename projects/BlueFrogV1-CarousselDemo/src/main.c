/*******************************************************************************
 * main.c
 * 
 * Author: La BlueFrog, 2015
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 *************************************************************************/

#include "LBF_Global.h"

#include "string.h"



/* --  Private Functions ----------------------------------------  */

static void ReadConfigFile( FIL* pMyFile, uint16_t* pfconfig);
static boolean_t  DecodeBMPFile(char* FileName);

static uint32_t  little_endian_32b (uint8_t data1, uint8_t data2, uint8_t data3, uint8_t data4);
static uint16_t  little_endian_16b (uint8_t data1, uint8_t data2);
static uint16_t AsciiToDec(uint8_t *data);

static void   StopAndRedBlink_On_Fail(boolean_t OkStatus);


/*******************************************************************************
* Function Name  : main.
* Description    : Main routine.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
int main(void)
{


/* ================================================================ */
/* Board Initializations and Configurations except OLED             */
/* (clocks, I/Os, on-chip peripherals, on-board ICs)                */
/* ================================================================ */

    LBF_Board_Init();

    Red_Led_ON();

/* ================================================================ */
/* Optional initialization of Middleware libraries :                */
/* USBD drivers, FatFS File System, STemWin GUI                     */
/* ================================================================ */

    // UNCOMMENT IF YOU WELL BE USING ...:
  
    /* ... La BlueFrog as USB Mass Storage (Full Speed)             */
    /*     (based on ST-provided stack part of STM32 Cube offering  */
    Delay_ms(1000);
    LBF_LaunchUSB_MassStorage();
 
    /* ... the FAT File System (FatFS)                              */
    /*     (based on ChanN's FatFS included in STM32 Cube offering) */
    LBF_FatFS_Init();

    /* ... the STemWin Graphical Library                            */
    /*     (based on Segger's emWin included in STM32 Cube offering)*/
    // LBF_emWin_Init();


    Red_Led_OFF();


/* ===================================================== */
/* Application Code Below */
/* ===================================================== */

/* ==  User Declarations =============================== */

uint16_t fconfig[11];  // configuration file to control some OLED parameters

boolean_t FatFS_Ok = TRUE;
FIL MyFile;
DIR  dir;
FILINFO  FileInfoStruct;

char listBMPfiles[50][13]; //to store up to 50 file names of 13 char each
uint8_t fnameLength;
uint8_t ImgNumber = 0;
uint8_t TotalBMPImg = 0;


/* ==  Body              =============================== */


/* -- Read Configuration File if present ---------------- */

    if ( f_open(&MyFile, "CONFIG.TXT", FA_OPEN_EXISTING|FA_READ) == FR_OK)
    {
	// status ok therefore file exists
        // Create custom configuration fconfig from this file
        ReadConfigFile( &MyFile, fconfig);
    }
    else
    {
        fconfig[0]=0xFFFF;     
            //so OLED_Config() will use default init value
    }
    f_close( &MyFile);


/*---- Initialize and Enable OLED:    -------------------*/


    LBF_OLED_Init(fconfig);  
        //sets up OLED register and powers on OLED VDDH(13V) 
    OLED_Fill(0, 0, 160, 128, BLACK);
    OLED_Fill(0, 5, 160,1, 0x0100);  //dark green line at top of screen
        //low-consumption splash screen


/* -- Open root directory  ------------------------------ */

    FatFS_Ok &= (f_opendir( &dir, "/") == FR_OK);  

    StopAndRedBlink_On_Fail(FatFS_Ok);    //in case of FatFS error


/* -- Search all BMP file  ------------------------------ */

    FatFS_Ok &= ( f_readdir( &dir, &FileInfoStruct) == FR_OK);   // 


    while (FileInfoStruct.fname[0]!=0)   //as long as item is found
    {
	fnameLength = strlen(FileInfoStruct.fname);

        if ( FileInfoStruct.fname[fnameLength-3]=='B' 
          && FileInfoStruct.fname[fnameLength-2]=='M' 
          && FileInfoStruct.fname[fnameLength-1]=='P' )
	{	
            // copy found file name to current entry of table of BMP file names
	    strcpy( &listBMPfiles[ImgNumber][0] , FileInfoStruct.fname);  
	    ImgNumber++;
	}

        //next item  (break on error) :
        if (f_readdir( &dir, &FileInfoStruct) != FR_OK) break;

    }
    TotalBMPImg = ImgNumber;

    f_closedir(&dir) ;   



/* --  Decode BMP files with slider switch control  ------------- */
 
    ImgNumber = 0;
    while(1)
    {

        if ( Get_Slider_Select1() )
        {
	    Red_Led_ON();
            ImgNumber++;
            if (ImgNumber == TotalBMPImg) 
            {
                 ImgNumber = 0;   // roll-over
            }
	    DecodeBMPFile(&listBMPfiles[ImgNumber][0]);

	    // Wait for switch release before continuing
	    while( Get_Slider_Select1() );  

	    Red_Led_OFF();
        }

        if ( Get_Slider_Select2() )
        {
	    Green_Led_ON();
            if (ImgNumber-- == 0) 
            {
                 ImgNumber = TotalBMPImg - 1;   // roll-over
            }
	    DecodeBMPFile(&listBMPfiles[ImgNumber][0]);

	    // Wait for switch release before continuing
	    while( Get_Slider_Select2() );  

	    Green_Led_OFF();
        }

    }
    
    
}



/**************************************************************************/
/**  Private functions  **/
/**************************************************************************/

boolean_t  DecodeBMPFile(char* FileName)
{

FIL MyFile;

boolean_t  FatFS_Ok = TRUE;
boolean_t  ValidBMP = TRUE;
boolean_t TopToBottomBMP;

BYTE BMPFileHeader[14];
BYTE BMPImageHeader[40];
BYTE BMPLineBuffer[3*160];

UINT rbytes_count; /* File read counts */

uint32_t  OffsetHead;
uint32_t  ImgWidth, ImgHeight;
int32_t  ImgHeight_signed;

uint8_t   R, G, B;
uint16_t  PixelLine565[160];

uint16_t  i,j;


    /* --- Open File and Read File Hedader + Image Header  ------------------- */

    FatFS_Ok &= ( f_open(&MyFile, FileName, FA_OPEN_EXISTING|FA_READ) == FR_OK );
   
    FatFS_Ok &= ( f_read( &MyFile, BMPFileHeader, sizeof(BMPFileHeader), &rbytes_count ) == FR_OK);

    FatFS_Ok &= ( f_read( &MyFile, BMPImageHeader, sizeof(BMPImageHeader), &rbytes_count) == FR_OK);
 
    // DEBUG- Stop here and blink LED if FatFS failure
    StopAndRedBlink_On_Fail(FatFS_Ok);


    /* --- Extract and Check Information from Header Contents  ---------------- */

    // Check first 2 bytes are B,M - Bytes 0,1 in File Header
    ValidBMP &= ( (BMPFileHeader[0] == 0x42) && (BMPFileHeader[1] == 0x4D) );

    // Get Offset to Start of Pixel Data - Bytes 10-13 of File Header
    OffsetHead = little_endian_32b( BMPFileHeader[10], 
				    BMPFileHeader[11],
				    BMPFileHeader[12],
				    BMPFileHeader[13] );

    // Check picture is 24bpp - Bytes 14-15 of Image Header
    ValidBMP &= ( little_endian_16b( BMPImageHeader[14], BMPImageHeader[15] ) == 24 );

    // Get picture width in pix - Bytes 4-7 of Image Header
    ImgWidth = little_endian_32b(   BMPImageHeader[4], 
				    BMPImageHeader[5],
				    BMPImageHeader[6],
				    BMPImageHeader[7] );

    // Get picture height in pix - Bytes 8-11 of Image Header
    ImgHeight_signed = little_endian_32b(  BMPImageHeader[8], 
				    	   BMPImageHeader[9],
			   	   	   BMPImageHeader[10],
				   	   BMPImageHeader[11] );
   //Negative Height in BMP indicated Top to Bottom image coding
   if (ImgHeight_signed<0)
   {     TopToBottomBMP = TRUE;
	 ImgHeight = (uint32_t)(-ImgHeight_signed);
   }
   else
   {     TopToBottomBMP = FALSE;
	 ImgHeight = (uint32_t)(ImgHeight_signed);
   }

    // Check picture not greater than 160x128
    ValidBMP &= (  (ImgWidth <= 160) && (ImgHeight <= 128) );



    /* --- Now Read and Display Picture line by line  ------------------------ */
    /* --  unless BMP had issues                      ------------------------ */

    if (!ValidBMP)
    {
        OLED_Fill(0,0,160,128, BLUE);
    }
    else
    {

    // THIS EXECUTES SLOWLY AND WOULD NEED TO BE OPTIMIZED
    // Need to investigate what is the bottleneck

    // Move Read Pointer to start of pixel data 
    FatFS_Ok  &=  ( f_lseek( &MyFile, (DWORD)(OffsetHead)) == FR_OK );


    for(i=0; i<ImgHeight; i++)
    {
         FatFS_Ok  &=  ( f_read( &MyFile, BMPLineBuffer, 3*ImgWidth,&rbytes_count) == FR_OK);

	 // Create RGB565 buffer for OLED
	 for (j=0; j<ImgWidth;j++)
	 {
	     B = BMPLineBuffer[j*3] >> 3;      // truncate 3 LSBs
	     G = BMPLineBuffer[j*3 + 1] >> 2;  // truncate 2 LSBs
	     R = BMPLineBuffer[j*3 + 2] >> 3;  // truncate 3 LSBs
	     PixelLine565[j] =  (uint16_t)((R << 11) | (G << 5) | B);
	 }
	 if (TopToBottomBMP)
	 {
             OLED_DisplayBuffer( 0, i, (uint8_t)(ImgWidth), 1, PixelLine565 );
         }   
	 else
	 {
             OLED_DisplayBuffer( 0, (uint8_t)(ImgHeight-1-i),(uint8_t)(ImgWidth), 1, PixelLine565 );
         }   
     }
     }

     FatFS_Ok  &=  (f_close(&MyFile) == FR_OK);

     return (FatFS_Ok & ValidBMP);
}



/* ===================================================================== */


void ReadConfigFile( FIL* pMyFile, uint16_t* pfconfig)
{

uint8_t	i;
uint8_t	CharIndex;
uint8_t	var[4];
char ConfigLine[80];
uint8_t ConfigLineNumber = 0;

	do
	{
	    // read a new line up to 80 characters
	    f_gets( ConfigLine, 80, pMyFile);   //read up to 80 chars from My‎Fil and store in ConfigLine

            CharIndex = 0; //to track char position after '=' sign
            var[0]=0; var[1]=0; var[2]=0; var[3]=0;  //to store 4 values following '=' sign
            
	    if(ConfigLine[0] != '#')  // if not a comment
	    {

              for(i=0; i<80; i++)   //examine all chars of line in turn
              {
                if(ConfigLine[i] != '\0')  // eol not reached
                { 
                    if(CharIndex != 0 && ConfigLine[i] != ' ')   // if equal sign already found and not a blank space
                    {
                        var[CharIndex-1] = ConfigLine[i];  //capture value of current char
                        CharIndex++;
                    }
                    if(ConfigLine[i] == '=')                // '=' found
                        CharIndex = 1;
                }    
                else   // break on eol
                    break;
              }            
              if(var[0] != 0) // if valid parameter found
              {
                  *(pfconfig++) = AsciiToDec(var); //update config file based on read data: var[0:3]
                  ConfigLineNumber++;
 	      }
	    }

        }while(f_eof(pMyFile) ==0);  
  
}


/* ===================================================================== */

void   StopAndRedBlink_On_Fail(boolean_t OkStatus)
{
    if (OkStatus==FALSE)   
    {
        while(1)
        {
            Red_Led_ON();
            Delay_ms(100);
            Red_Led_OFF();
            Delay_ms(250);
        }
    }
}

/* ===================================================================== */

/* ---------------------------------------------------------------
 * @brief  : 32-bit little-endian to big-endian conversion
 * @param  : little endian data
 * @return : Permuted data on 4 bytes
   --------------------------------------------------------------- */
uint32_t little_endian_32b (uint8_t data1, uint8_t data2, uint8_t data3, uint8_t data4)
{
    return (uint32_t)(data1 | (data2 << 8) | (data3 << 16) | (data4 << 24));
}



/* ---------------------------------------------------------------
 * @brief  : 16-bit little-endian to big-endian conversion
 * @param  : little endian data
 * @return : Permuted data on 2 bytes
   --------------------------------------------------------------- */
uint16_t little_endian_16b (uint8_t data1, uint8_t data2)
{
    return (uint16_t)(data1 | (data2 << 8));
}


/* ===================================================================== */

/* ---------------------------------------------------------------
 * @brief  : Convert ASCII data representing a 4-digit number into
 *           that very number in hex 
 * @param  : data: buffer of ASCII data (0x30:0 ... 0x39:9) [0.1.2.3]
 * @return : hex value represented by the ASCII code.
 --------------------------------------------------------------- */

uint16_t AsciiToDec(uint8_t *data)
{
    int8_t pos, unit = 0;
    uint16_t temp = 0, result = 0;
    
    for(pos=3; pos>=0; pos--)
    {
        if(data[pos] != 0x00)
        {

            temp = data[pos] - 0x30;
            
            if(unit == 1)
                temp *= 10;
            else if(unit == 2)
                temp *= 100;
            else if(unit == 3)
                temp *= 1000;
            
            result += temp;
            unit++;
        }
    }
    
    return result;
}


/***************************************************************END OF FILE****/
