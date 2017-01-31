#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <getopt.h>
#include "info.h"
#include "struct.h"
#include "names.h"

#include "const.h"

void getname(char **array_names,int count_names,char *ln,short int *i,char nstyle,char *sep,flag *FLAG);
void error(char *str);


int main(int argc,char *argv[]){

    static struct option long_opt[] = {
        {"women",   0,0,'w'},
        {"male",    0,0,'m'},
        {"eng",     0,0,'e'},
        {"rare",    0,0,'r'},
        {"all-names",0,0,'a'},
        {"line",    0,0,'l'},
        {"version", 0,0,'v'},
        {"count",   1,0,'c'},
        {"separator",1,0,'s'},
        {"num-style",1,0,'i'},
        {"help",0,0,'h'},
        {0,0,0,0}
    };
    
	sex man = {0,0};
	flag FLAGS = {FALSE,FALSE,FALSE,FALSE,TRUE}; 

	int ch;
	char digit_style;
	char separator[128] = "";
	char ln[4] = "";

	int numeric = 0;
	int count = 1;
        int optidx;

        while(TRUE){
            
            if( (ch = getopt_long(argc,argv,"wmeralvc:s:i:h",long_opt,&optidx)) == -1 )
                break;

            switch(ch){
                case 'w':
                    man.woman = TRUE;
                    break;
                case 'm':
                    man.male = TRUE;
                    break;
                case 'e':
                    FLAGS.EN = TRUE;
                    break;
                case 'r':
                    FLAGS.RARE = TRUE;
                    break;
                case 'a':
                    FLAGS.ALLNAMES = TRUE;
                    break;
                case 'l':
                    FLAGS.ENDL = FALSE;
                    break;
                case 'v':
                    version();
                    break;
                case 'c':
                    count = atoi(optarg);
                    break;
                case 's':
                    sprintf(separator,"%s",optarg);
                    // separator = optarg;
                    break;
                case 'i':
                    numeric = atoi(optarg);
                    FLAGS.NUMSTR = TRUE;
                    break;
                case 'h':
                    help();
                    break;
                default:
                    printf("randname: unknow option '%c'\n",ch);
                    help();
            }
        }

	if(!FLAGS.ENDL) sprintf(ln,"%s","\n");

        /* 
         *Filters errors   
         */
        
    // if male and woman is true except error
	if( !man.woman && !man.male )
            error("Required option '-m' or '-w'");
        
    // if count is negative number except error
	if( count < 0 )		 	
            error("Option value should not be less 0");
        
    // except warning if selected english rare names
	if(FLAGS.EN && FLAGS.RARE) 	
            printf("[%sWarning%s]: in the database name aren't rare english names\n",YELLOW,DEFAULT);


	if(FLAGS.ALLNAMES && man.woman){
		if(FLAGS.EN){
			count = MAX_EN_NAME_WOMEN;
		}
		else if(FLAGS.RARE){
			count = MAX_RNAME_WOMEN;
		}
		else{
			count = MAX_NAME_WOMEN;
		}
	}
	else if(FLAGS.ALLNAMES && man.male){
		if(FLAGS.EN){
			count = MAX_EN_NAME_MALE;
		}
		else if(FLAGS.RARE){
			count = MAX_RNAME_MALE;
		}
		else{
			count = MAX_NAME_MALE;
		}
	}

	/* Определение стиля нумерованного вывода */
	digit_style = (numeric == 1) ? ')' : (numeric == 2) ? '.' : (numeric == 3) ? '-' : ')' ;
	
	srand(time(NULL));
        
	short int i = 0;
	short int rand_rate = 0;
	count++;

	while(i < count-1){

		if(i == count - 1) sprintf(separator,"%s","");

		rand_rate = (FLAGS.ALLNAMES == 0) ? (rand() % 2) + 1 : (FLAGS.ALLNAMES == 1 && FLAGS.RARE == 1) ? 1 : 0 ;

					/*	Если был определён флаг english (англ.имена)	*/
		if(FLAGS.EN){
			if(man.woman)	getname(eng_name_women,MAX_EN_NAME_WOMEN,ln,&i,digit_style,separator,&FLAGS);
			if(man.male)	getname(eng_name_male,MAX_EN_NAME_MALE,ln,&i,digit_style,separator,&FLAGS);
		}
		else{		/*	По умолч. Русские имена							*/
			if(rand_rate == 1){	/*	Если был определён флаг rare (редкие имена)	*/
				if(man.woman)	getname(rare_name_women,MAX_RNAME_WOMEN,ln,&i,digit_style,separator,&FLAGS);
				if(man.male)	getname(rare_name_male,MAX_RNAME_MALE,ln,&i,digit_style,separator,&FLAGS);
			}
			else{	/*	Обычные имена имена	*/
				if(man.woman)	getname(name_women,MAX_NAME_WOMEN,ln,&i,digit_style,separator,&FLAGS);
				if(man.male)	getname(name_male,MAX_NAME_MALE,ln,&i,digit_style,separator,&FLAGS);
			}
		}
	}

	if(FLAGS.ENDL) 
            putchar('\n');
        
	return 0;
}

/*
getname: печатает имя из указ массива [array_names] макс знач [count_names]
[ln]: '\n' - отступ строки
[ns]: (numer string) нумерование строк
[i]: счотчик для вывода строк (если (True) FLAGS.NUMSTR)
[nstyle]: стиль нумерования строк
[sep]: разделитель
//Переименовать в getname
*/
void getname(char **array_names,int count_names,char *ln,short int *i,char nstyle,char *sep,flag *FLAG){
	
	int crand;
	if(!FLAG->ALLNAMES)
    	crand = rand() % count_names;
	else 
    	crand = *i;

	if(FLAG->NUMSTR) 
    	printf("%i%c ",*i+1,nstyle);

	printf("%s",array_names[crand]);
	printf("%s%s",sep,ln);

	*i = *i + 1;
}

// error: print message of error and exit program
void error(char *str){
	printf("[%serror%s]: %s\n",RED,DEFAULT,str);
	exit(1);
}
