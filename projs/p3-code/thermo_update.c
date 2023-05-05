#include "thermo.h"

/*
Uses the two global variables (ports) THERMO_SENSOR_PORT and
THERMO_STATUS_PORT to set the temp structure. If THERMO_SENSOR_PORT
is above its maximum trusted value, associated with +50.0 deg C,
does not alter temp and returns 1.  Otherwise, sets fields of temp
based on converting sensor value to degrees and checking whether
Celsius or Fahrenheit display is in effect. Returns 0 on successful
set. This function DOES NOT modify any global variables but may
access global variables.

CONSTRAINT: Uses only integer operations. No floating point
operations are used as the target machine does not have a FPU.
*/
int set_temp_from_ports(temp_t *temp){
    
    if(THERMO_SENSOR_PORT<=64000){ // check if value is valid
        
        int tem=THERMO_SENSOR_PORT/64; // floor quotient
        int rem=THERMO_SENSOR_PORT%64; // remainder
        
        if(rem<32){ // rounds down
            tem=tem-500; // measures difference, adds no tenth
        }
        else{ // rounds up
            tem=tem-500+1; // measures difference, adds one tenth
        }
        
        temp->tenths_degrees=tem; // sets temperature field, default to celcius
        temp->is_fahrenheit=0b0; // 0b0000, sets degree type field, default to celcius
        int mask=0b1; // 0b0001
        
        if(THERMO_STATUS_PORT&mask){ // changes both fields to fahrenheit if needed
            tem=(tem*9)/5+320; // conversion
            temp->tenths_degrees=tem;
            temp->is_fahrenheit=0b1; // 0b0001
        }
        
        return 0; // successful

    }
    
    return 1; // unsuccessful

}

/*
Alters the bits of integer pointed to by display to reflect the
temperature in struct arg temp.  If temp has a temperature value
that is below minimum or above maximum temperature allowable or if
an improper indication of celsius/fahrenheit is given, does nothing
and returns 1. Otherwise, calculates each digit of the temperature
and changes bits at display to show the temperature according to
the pattern for each digit.  This function DOES NOT modify any
global variables but may access global variables.
*/
int set_display_from_temp(temp_t temp, int *display){
    
    // the blocks below determine if the temp is not allowable or degree type is not allowable
    if(temp.is_fahrenheit){
        if(temp.tenths_degrees<-580||temp.tenths_degrees>1220){ // min/max fahrenheit
            return 1; // unsuccessful
        }
    }
    else{
        if(temp.tenths_degrees<-500||temp.tenths_degrees>500){ // min/max celsius
            return 1; // unsuccessful
        }
    }
    if(temp.is_fahrenheit!=0&&temp.is_fahrenheit!=1){ // unacceptable degree type
        return 1; // unsuccessful
    }

    int bit_masks[10]={ // display bits array
        0b1111110, // 0
        0b0001100, // 1
        0b0110111, // 2
        0b0011111, // 3
        0b1001101, // 4
        0b1011011, // 5
        0b1111011, // 6
        0b0001110, // 7
        0b1111111, // 8
        0b1011111  // 9
    };
    
    // these variables relate in terms of tenths of degrees but they are actually the
    int temp_thou=temp.tenths_degrees/1000;if(temp_thou<0){temp_thou=-temp_thou;} // hundreds,
    int temp_hund=(temp.tenths_degrees%1000)/100;if(temp_hund<0){temp_hund=-temp_hund;} // tens,
    int temp_tens=(temp.tenths_degrees%100)/10;if(temp_tens<0){temp_tens=-temp_tens;} // ones,
    int temp_ones=temp.tenths_degrees%10;if(temp_ones<0){temp_ones=-temp_ones;} // and tenths spots on the display

    int bits=0;
    int sign=0b1<<21; // keeps track of spot to put negative sign if needed
    
    if(temp_thou==0){
        bits=bits<<7; // no hundreds, shift for tens
    }
    else{
        bits=bit_masks[temp_thou]<<7; // set hundreds, shift for tens
    }

    if(temp_thou==0&&temp_hund==0){
        bits=bits<<7; // no tens, shift for ones
        sign=sign>>7; // sign moves to be by ones
    }
    else{
        bits=(bits|bit_masks[temp_hund])<<7; // set tens, shift for ones
    }

    bits=(bits|bit_masks[temp_tens])<<7; // set ones (always) and shift for tenths
    
    bits=bits|bit_masks[temp_ones]; // set tenths (always)
    
    if(temp.tenths_degrees<0){ // turn on negative bit (if negative)
        bits=bits|sign;
    }
    if(temp.is_fahrenheit){ // turn on fahrenheit bit
        int far=0b1<<29;
        bits=bits|far;
    }
    else{ // turn on celcius bit
        int cel=0b1<<28;
        bits=bits|cel;
    }
    
    *display=bits; // dereference set the display

    return 0; // success

}

/*
Called to update the thermometer display.  Makes use of
set_temp_from_ports() and set_display_from_temp() to access
temperature sensor then set the display. Checks these functions and
if they indicate an error, makes no changes to the display.
Otherwise modifies THERMO_DISPLAY_PORT to set the display.

CONSTRAINT: Does not allocate any heap memory as malloc() is NOT
available on the target microcontroller.  Uses stack and global
memory only.
*/
int thermo_update(){
   
    temp_t temp; // stack initialzation
    int ret;
    
    ret=set_temp_from_ports(&temp);
    if(ret){
        return ret; // unsuccessful (bad sensor val)
    }
    
    ret=set_display_from_temp(temp,&THERMO_DISPLAY_PORT);
    if(ret){
        return ret; // unsuccessful (error indicated)
    }
    
    return ret; // successful

}