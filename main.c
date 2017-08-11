#include <stdio.h>
#include <gmp.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv){
    
    if(argc != 3){
        fprintf(stderr, "Not enough or to many arguemnts");
    }
    
    mpf_t i_volt, i_amp, i_res, i_pow;
    
    mpf_init(i_volt);
    mpf_init(i_amp);
    mpf_init(i_res);
    mpf_init(i_pow);
    
    char *i_first, *i_sec;

    i_first = (char *) malloc(strlen(argv[1]));
    i_sec = (char *) malloc(strlen(argv[2]));

    strcpy(i_first, argv[1]);
    strcpy(i_sec, argv[2]);

    i_first[strlen(i_first) - 1] = '\0';
    i_sec[strlen(i_sec) - 1] = '\0';
    
    char first_unit = argv[1][strlen(argv[1]) - 1];
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
        default : printf("Input1: %c Nix gefunden :( \n",first_unit);
             
    }
    char second_unit = argv[2][strlen(argv[2]) - 1];
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
        default : printf("Input2: %c Nix gefunden :( \n",second_unit);
             
    }

    free(i_first);
    free(i_sec);

    if( mpf_sgn(i_volt) && mpf_sgn(i_amp)){
        mpf_div(i_res, i_volt, i_amp);
        mpf_mul(i_pow, i_volt, i_amp);
    }
    else if( mpf_sgn(i_volt) && mpf_sgn(i_res)){
        mpf_div(i_amp, i_volt, i_res);
    }
    else if( mpf_sgn(i_volt) && mpf_sgn(i_pow)){
        mpf_div(i_amp, i_pow, i_volt);
    }
    else if( mpf_sgn(i_amp) && mpf_sgn(i_res)){
        mpf_mul(i_volt, i_res, i_amp);
    }
    else if( mpf_sgn(i_amp) && mpf_sgn(i_pow)){
        mpf_div(i_volt, i_pow, i_amp);
    }
    else{
        fprintf(stderr, "Something with arguments. \n");
    }

    gmp_printf ("Volt % .*Ff \n", 5, i_volt, 5);
    gmp_printf ("Ampere % .*Ff \n", 5, i_amp, 5);
    gmp_printf ("Ohm % .*Ff \n", 5, i_res, 5);
    gmp_printf ("Watt % .*Ff \n", 5, i_pow, 5);



}

/*
V Volt
A Ampere
O Ohm
W Watt

U = R · I   ->   Spannung = Widerstand · Stromstärke

R = U / I   ->   Widerstand = Spannung / Stromstärke

I = U / R   ->   Stromstärke = Spannung / Widerstand

P = U · I   ->   Leistung = Spannung · Stromstärke

U = P / I   ->   Spannung = Leistung / Stromstärke

I = P / U   ->   Stromstärke = Leistung / Spannung
*/