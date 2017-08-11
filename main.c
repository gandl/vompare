#include <stdio.h>
#include <gmp.h>
#include <string.h>
#include <stdlib.h>

#define DISP_PREC 5

int main(int argc, char **argv){


    //Initial Input Check
    if(argc != 3){
        fprintf(stderr, "Not enough or to many arguemnts");
        return 0;
    }
    
    //Declare Stuff
    mpf_t i_volt, i_amp, i_res, i_pow;
    char *i_first, *i_sec;
    char first_unit, second_unit;

    //Initialize Stuff
    mpf_init(i_volt);
    mpf_init(i_amp);
    mpf_init(i_res);
    mpf_init(i_pow);
    
    first_unit = argv[1][strlen(argv[1]) - 1];
    second_unit = argv[2][strlen(argv[2]) - 1];

    i_first = (char *) malloc(strlen(argv[1]));
    i_sec = (char *) malloc(strlen(argv[2]));

    strcpy(i_first, argv[1]);
    strcpy(i_sec, argv[2]);

    i_first[strlen(i_first) - 1] = '\0';
    i_sec[strlen(i_sec) - 1] = '\0';
    
    //Check the Units
    switch(first_unit){
        case 'V' : mpf_set_str(i_volt, i_first, 10);
        break;
        case 'v' : mpf_set_str(i_volt, i_first, 10);
        break; 
        case 'A' : mpf_set_str(i_amp, i_first, 10);
        break; 
        case 'a' : mpf_set_str(i_amp, i_first, 10);
        break; 
        case 'O' : mpf_set_str(i_res, i_first, 10);
        break; 
        case 'o' : mpf_set_str(i_res, i_first, 10);
        break; 
        case 'W' : mpf_set_str(i_pow, i_first, 10);
        break; 
        case 'w' : mpf_set_str(i_pow, i_first, 10);
        break; 
        default : fprintf(stderr, "Wrong Type for first Unit: %c \n",first_unit); return 0;
             
    }
    
    switch(second_unit){
        case 'V' : mpf_set_str(i_volt, i_sec, 10);
        break;
        case 'v' : mpf_set_str(i_volt, i_sec, 10);
        break; 
        case 'A' : mpf_set_str(i_amp, i_sec, 10);
        break; 
        case 'a' : mpf_set_str(i_amp, i_sec, 10);
        break; 
        case 'O' : mpf_set_str(i_res, i_sec, 10);
        break; 
        case 'o' : mpf_set_str(i_res, i_sec, 10);
        break; 
        case 'W' : mpf_set_str(i_pow, i_sec, 10);
        break; 
        case 'w' : mpf_set_str(i_pow, i_sec, 10);
        break; 
        default : fprintf(stderr, "Wrong Type for second Unit: %c \n",second_unit); return 0;
             
    }

    free(i_first);
    free(i_sec);

    //Calculate the values
    if( mpf_sgn(i_volt) && mpf_sgn(i_amp)){
        mpf_div(i_res, i_volt, i_amp);
        mpf_mul(i_pow, i_volt, i_amp);
    }
    else if( mpf_sgn(i_volt) && mpf_sgn(i_res)){
        mpf_div(i_amp, i_volt, i_res);
        mpf_mul(i_pow, i_volt, i_amp);
    }
    else if( mpf_sgn(i_volt) && mpf_sgn(i_pow)){
        mpf_div(i_amp, i_pow, i_volt);
        mpf_div(i_res, i_volt, i_amp);
    }
    else if( mpf_sgn(i_amp) && mpf_sgn(i_res)){
        mpf_mul(i_volt, i_res, i_amp);
        mpf_mul(i_pow, i_volt, i_amp);
    }
    else if( mpf_sgn(i_amp) && mpf_sgn(i_pow)){
        mpf_div(i_volt, i_pow, i_amp);
        mpf_div(i_res, i_volt, i_amp);
    }
    else{
        fprintf(stderr, "Seems like you gave the same argument twice. \n");
        return 0;
    }

    //Print the values 
    gmp_printf ("% .*Ff V\n", 5, i_volt, DISP_PREC);
    gmp_printf ("% .*Ff A\n", 5, i_amp, DISP_PREC);
    gmp_printf ("% .*Ff O\n", 5, i_res, DISP_PREC);
    gmp_printf ("% .*Ff W\n", 5, i_pow, DISP_PREC);

    return 1;

}

