#include <stdio.h>
#include <gmp.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

#define DISP_PREC 10

char* printing_order = "vaow";
int print_units = 1;

//Two values have to be given to be able to calculate the rest
int calc_values(mpf_t *volt, mpf_t *amp, mpf_t *res, mpf_t *powe){
    if( mpf_sgn(*volt) && mpf_sgn(*amp)){
        mpf_div(*res, *volt, *amp);
        mpf_mul(*powe, *volt, *amp);
    }
    else if( mpf_sgn(*volt) && mpf_sgn(*res)){
        mpf_div(*amp, *volt, *res);
        mpf_mul(*powe, *volt, *amp);
    }
    else if( mpf_sgn(*volt) && mpf_sgn(*powe)){
        mpf_div(*amp, *powe, *volt);
        mpf_div(*res, *volt, *amp);
    }
    else if( mpf_sgn(*amp) && mpf_sgn(*res)){
        mpf_mul(*volt, *res, *amp);
        mpf_mul(*powe, *volt, *amp);
    }
    else if( mpf_sgn(*amp) && mpf_sgn(*powe)){
        mpf_div(*volt, *powe, *amp);
        mpf_div(*res, *volt, *amp);
    }
    else{
        return 0;
    }

    return 1;
}

//print all given values in a list, ending with newline
int print_values(mpf_t *volt, mpf_t *amp, mpf_t *res, mpf_t *powe){

    if(print_units){
        for(int i = 0; i < strlen(printing_order); i++){
            switch(printing_order[i]){
                case 'a' : gmp_printf ("% .*FfA", DISP_PREC, *amp, DISP_PREC);
                break;
                case 'v' : gmp_printf ("% .*FfV", DISP_PREC, *volt, DISP_PREC);
                break;
                case 'w' : gmp_printf ("% .*FfW", DISP_PREC, *powe, DISP_PREC);
                break;
                case 'o' : gmp_printf ("% .*FfO", DISP_PREC, *res, DISP_PREC);
                break;  
            }   
        }
    }
    else{
        for(int i = 0; i < strlen(printing_order); i++){
            switch(printing_order[i]){
                case 'a' : gmp_printf ("% .*Ff", DISP_PREC, *amp, DISP_PREC);
                break;
                case 'v' : gmp_printf ("% .*Ff", DISP_PREC, *volt, DISP_PREC);
                break;
                case 'w' : gmp_printf ("% .*Ff", DISP_PREC, *powe, DISP_PREC);
                break;
                case 'o' : gmp_printf ("% .*Ff", DISP_PREC, *res, DISP_PREC);
                break;  
            }   
        }
    }
    return 1;
}



//assign input values to the correct units
int init_values(mpf_t *volt, mpf_t *amp, mpf_t *res, mpf_t *powe, char *first, char *sec){

    mpf_init(*volt);
    mpf_init(*amp);
    mpf_init(*res);
    mpf_init(*powe);

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
        case 'W' : mpf_set_str(*powe, first, 10);
        break; 
        case 'w' : mpf_set_str(*powe, first, 10);
        break; 
        default : return 0;
             
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
        case 'W' : mpf_set_str(*powe, sec, 10);
        break; 
        case 'w' : mpf_set_str(*powe, sec, 10);
        break; 
        default : return 0;
             
    }

    return 1;
}


int main(int argc, char **argv){

    mpf_t i_volt, i_amp, i_res, i_powe;
    int c;

    opterr = 0;

    while ((c = getopt (argc, argv, "no:")) != -1)
    switch (c){
      case 'n':
        print_units = 0;
        break;
      case 'o':
        printing_order = optarg;
        break;
      case '?':
        if (optopt == 'o')
          fprintf (stderr, "Option -%c requires an argument.\n", optopt);
        else if (isprint (optopt))
          fprintf (stderr, "Unknown option `-%c'.\n", optopt);
        else
          fprintf (stderr,
                   "Unknown option character `\\x%x'.\n",
                   optopt);
        return 1;
      default:
        abort ();
      }


    if(init_values(&i_volt, &i_amp, &i_res, &i_powe, argv[optind], argv[optind + 1]))
        if(calc_values(&i_volt, &i_amp, &i_res, &i_powe))
            print_values(&i_volt, &i_amp, &i_res, &i_powe);

    
    return 1;

}

