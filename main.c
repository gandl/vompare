#define _GNU_SOURCE
#include <stdio.h>
#include <gmp.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>


static int disp_prec = 10;              //Precision of output
static char* printing_order = "vaow";   //Order of printing volt, amps, resistance and power
static int print_units = 1;             //Print units after the values
static mp_bitcnt_t calc_prec = 64;
static int cl_arg_present = 0;

//Two values have to be given to be able to calculate the two missing values
int calc_values(mpf_t *volt, mpf_t *amp, mpf_t *res, mpf_t *power){
    if( mpf_sgn(*volt) && mpf_sgn(*amp)){
        mpf_div(*res, *volt, *amp);
        mpf_mul(*power, *volt, *amp);
    }
    else if( mpf_sgn(*volt) && mpf_sgn(*res)){
        mpf_div(*amp, *volt, *res);
        mpf_mul(*power, *volt, *amp);
    }
    else if( mpf_sgn(*volt) && mpf_sgn(*power)){
        mpf_div(*amp, *power, *volt);
        mpf_div(*res, *volt, *amp);
    }
    else if( mpf_sgn(*amp) && mpf_sgn(*res)){
        mpf_mul(*volt, *res, *amp);
        mpf_mul(*power, *volt, *amp);
    }
    else if( mpf_sgn(*amp) && mpf_sgn(*power)){
        mpf_div(*volt, *power, *amp);
        mpf_div(*res, *volt, *amp);
    }
    else{
        return 0;
    }

    return 1;
}

//print all given values in order given by "printing_order", ending with newline
int print_values(mpf_t *volt, mpf_t *amp, mpf_t *res, mpf_t *power){

    if(print_units){
        for(int i = 0; i < strlen(printing_order); i++){
            switch(printing_order[i]){
                case 'a' : gmp_printf ("% .*FfA", disp_prec, *amp, disp_prec);
                break;
                case 'v' : gmp_printf ("% .*FfV", disp_prec, *volt, disp_prec);
                break;
                case 'w' : gmp_printf ("% .*FfW", disp_prec, *power, disp_prec);
                break;
                case 'o' : gmp_printf ("% .*FfO", disp_prec, *res, disp_prec);
                break;  
            }   
        }
    }
    else{
        for(int i = 0; i < strlen(printing_order); i++){
            switch(printing_order[i]){
                case 'a' : gmp_printf ("% .*Ff", disp_prec, *amp, disp_prec);
                break;
                case 'v' : gmp_printf ("% .*Ff", disp_prec, *volt, disp_prec);
                break;
                case 'w' : gmp_printf ("% .*Ff", disp_prec, *power, disp_prec);
                break;
                case 'o' : gmp_printf ("% .*Ff", disp_prec, *res, disp_prec);
                break;  
            }   
        }
    }
    printf("\n");
    return 1;
}



//identify the units(volt, ampere, resistance or power) of the given input.
int init_values(mpf_t *volt, mpf_t *amp, mpf_t *res, mpf_t *power, char *first, char *sec){
/*
    if(strlen(first) > 64 || strlen(sec) > 64){
        fprintf(stderr, "Input too long!\n");
        return 0;
    }
*/
    mpf_init(*volt);
    mpf_init(*amp);
    mpf_init(*res);
    mpf_init(*power);
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
        case 'W' : mpf_set_str(*power, first, 10);
        break; 
        case 'w' : mpf_set_str(*power, first, 10);
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
        case 'W' : mpf_set_str(*power, sec, 10);
        break; 
        case 'w' : mpf_set_str(*power, sec, 10);
        break; 
        default : return 0;
             
    }

    return 1;
}


int main(int argc, char **argv){

    mpf_t i_volt, i_amp, i_res, i_power;
    int options;
    ssize_t read;
    size_t len = 0;
    char *line = NULL;
    mpf_set_default_prec(calc_prec);

    //work trhough given program options
    opterr = 0;

    while ((options = getopt (argc, argv, "no:p:d:")) != -1)
    switch (options){
      case 'n':
        print_units = 0;
        break;
      case 'o':
        printing_order = optarg;
        break;
      case 'd':
        disp_prec = atoi(optarg);
        break;
      case 'p':
        calc_prec = atoi(optarg);
      case '?':
        if (optopt == 'o' || optopt == 'p' || optopt == 'd')
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


    

    //solve for two given command line arguments
    if(argc > optind + 2){
        fprintf(stderr, "Too many arguments\n");
        return 0;
    }
    
    if(argc == optind + 2){
        cl_arg_present = 1;
     
        if(init_values(&i_volt, &i_amp, &i_res, &i_power, argv[optind], argv[optind + 1])){
            if(calc_values(&i_volt, &i_amp, &i_res, &i_power))
                print_values(&i_volt, &i_amp, &i_res, &i_power);
        }

    }
    

    
    //work through stdin input. it has to be given two values in each line seperated by space
    
    if(!cl_arg_present){
    
        while((read = getline(&line, &len, stdin)) != -1){
                char *stream_input[2];
                stream_input[0] = (char*) malloc(len * sizeof(char));
                stream_input[1] = (char*) malloc(len * sizeof(char));
                sscanf(line, "%s %s", stream_input[0], stream_input[1]);
                printf("%s\n", stream_input[0]);
                printf("%s\n", stream_input[1]);
                if(strlen(stream_input[0]) <= 64 && strlen(stream_input[1]) <= 64){
                    if(init_values(&i_volt, &i_amp, &i_res, &i_power, stream_input[0], stream_input[1])){
                        if(calc_values(&i_volt, &i_amp, &i_res, &i_power))
                            print_values(&i_volt, &i_amp, &i_res, &i_power);
                    }
                }
                
                
                free(stream_input[0]);
                free(stream_input[1]);
                
            
            free(line);
            len = 0;      
                    
        }
    }
  
    return 1;

}

