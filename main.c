#include <stdio.h>
#include <gmp.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define DISP_PREC 10

//Two values have to be given to be able to calculate the rest
int calc_values(mpf_t *volt, mpf_t *amp, mpf_t *res, mpf_t *pow){
    if( mpf_sgn(*volt) && mpf_sgn(*amp)){
        mpf_div(*res, *volt, *amp);
        mpf_mul(*pow, *volt, *amp);
    }
    else if( mpf_sgn(*volt) && mpf_sgn(*res)){
        mpf_div(*amp, *volt, *res);
        mpf_mul(*pow, *volt, *amp);
    }
    else if( mpf_sgn(*volt) && mpf_sgn(*pow)){
        mpf_div(*amp, *pow, *volt);
        mpf_div(*res, *volt, *amp);
    }
    else if( mpf_sgn(*amp) && mpf_sgn(*res)){
        mpf_mul(*volt, *res, *amp);
        mpf_mul(*pow, *volt, *amp);
    }
    else if( mpf_sgn(*amp) && mpf_sgn(*pow)){
        mpf_div(*volt, *pow, *amp);
        mpf_div(*res, *volt, *amp);
    }
    else{
        return 0;
    }

    return 1;
}

//print all given values in a list, ending with newline
int print_values(mpf_t *volt, mpf_t *amp, mpf_t *res, mpf_t *pow){
    gmp_printf ("% .*FfV", DISP_PREC, *volt, DISP_PREC);
    gmp_printf ("% .*FfA", DISP_PREC, *amp, DISP_PREC);
    gmp_printf ("% .*FfO", DISP_PREC, *res, DISP_PREC);
    gmp_printf ("% .*FfW", DISP_PREC, *pow, DISP_PREC);
    printf("\n");

    return 1;
}

//assign input values to the correct units
int init_values(mpf_t *volt, mpf_t *amp, mpf_t *res, mpf_t *pow, char *first, char *sec){

    mpf_init(*volt);
    mpf_init(*amp);
    mpf_init(*res);
    mpf_init(*pow);

    char first_unit = first[strlen(first) - 1];
    char second_unit = sec[strlen(sec) - 1];

    first[strlen(first) - 1] = '\0';
    sec[strlen(sec) - 1] = '\0';

    switch(first_unit){
        case 'V' : mpf_set_str(*volt, first, 10);
        break;
        case 'v' : mpf_set_str(*volt, first, 10);
        break; 
        case 'A' : mpf_set_str(*amp, first, 10);
        break; 
        case 'a' : mpf_set_str(*amp, first, 10);
        break; 
        case 'O' : mpf_set_str(*res, first, 10);
        break; 
        case 'o' : mpf_set_str(*res, first, 10);
        break; 
        case 'W' : mpf_set_str(*pow, first, 10);
        break; 
        case 'w' : mpf_set_str(*pow, first, 10);
        break; 
        default : fprintf(stderr, "ERROR: Wrong Type for first Unit: %c \n",first_unit); return 0;
             
    }
    
    switch(second_unit){
        case 'V' : mpf_set_str(*volt, sec, 10);
        break;
        case 'v' : mpf_set_str(*volt, sec, 10);
        break; 
        case 'A' : mpf_set_str(*amp, sec, 10);
        break; 
        case 'a' : mpf_set_str(*amp, sec, 10);
        break; 
        case 'O' : mpf_set_str(*res, sec, 10);
        break; 
        case 'o' : mpf_set_str(*res, sec, 10);
        break; 
        case 'W' : mpf_set_str(*pow, sec, 10);
        break; 
        case 'w' : mpf_set_str(*pow, sec, 10);
        break; 
        default : fprintf(stderr, "ERROR: Wrong Type for second Unit: %c \n",second_unit); return 0;
             
    }
}


int main(int argc, char **argv){


    //Initial Input Check
    if(argc != 3){
        fprintf(stderr, "ERROR: Not enough or to many arguemnts");
        return 0;
    }
    
    //Declare Stuff
    mpf_t i_volt, i_amp, i_res, i_pow;


    //init Values
    init_values(&i_volt, &i_amp, &i_res, &i_pow, argv[1], argv[2]);

    //Calculate Values
    if(!calc_values(&i_volt, &i_amp, &i_res, &i_pow))
        fprintf(stderr, "ERROR: Could not calculate Values. \n");

    
    //Print the values 
    print_values(&i_volt, &i_amp, &i_res, &i_pow);

    return 1;

}

