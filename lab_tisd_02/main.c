#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>

#include "country_t.h"

#define ARG_ERROR -2
#define FILE_ERROR -1
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
#define INPUT_ERROR 2

int main(int argc, char **argv)
{
	FILE *fsrc;
	
	if (argc != 2)
	{
		printf("Program is processing file with countries, to proceed start program with directory to database.\n");
		fflush(stdout);
		return ARG_ERROR;
	}
	
	country_t countries_arr[M_COUNTRIES];
	country_sort keys_arr[M_COUNTRIES];
	int volume = 0;	
	char menu[10];
	char check;
	int main_sorted = 0;
	printf("\nInput one of commands names:\n0) menu - to show menu\n1) read - to read file\n2) print - to print file\n3) add - to add country to file\n4) delete - to delete country from file\n5) sort - to sort main or keys table\n6) search - to search country by continent and sport type)\n7) exit - to exit programm.\n");
	fflush(stdout);
	while (1)
	{
		printf("\n");
		fflush(stdout);
		scanf("%s", menu);
		if (! strcmp(menu, "menu"))
		{
			printf("\nInput one of commands names:\n0) menu - to show menu\n1) read - to read file\n2) print - to print file\n3) add - to add country to file\n4) delete - to delete country from file\n5) sort - to sort main or keys table\n6) search - to search country by continent and sport type)\n7) exit - to exit programm.\n");
			fflush(stdout);
		}
		
		else if (! strcmp(menu, "read"))
		{
			if (read_file(fsrc, &volume, countries_arr, keys_arr, argv[1]) != EXIT_SUCCESS)
				return FILE_ERROR;
			printf("File was successfully readed.\n");
		}
		
		else if ((! strcmp(menu, "print")) && volume != 0)
		{
			print_countries(volume, countries_arr);
			printf("\nFile was successfully printed.\n");
		}
	 
		else if ((! strcmp(menu, "add")) && volume != 0)
		{
			fsrc = fopen(argv[1], "a");
			if (fsrc == NULL)
			{
				printf("Could not open %s because of %s\n", menu, strerror(errno));
				fflush(stdout);
				return FILE_ERROR;
			}

			if (add_country(fsrc) != EXIT_SUCCESS)
			{
				printf("Input record is not as it intended to be!\n");
				fflush(stdout);
				fclose(fsrc);
				continue;
			}
			fclose(fsrc);
			
			if (read_file(fsrc, &volume, countries_arr, keys_arr, argv[1]) != EXIT_SUCCESS)
				return FILE_ERROR;
			
			printf("Country was successfully added.\n");
		}

		else if ((! strcmp(menu, "delete")) && volume != 0)
		{
			

			char continent_search[M_CONTINENT];
			char sport_search[M_TOURISM];
			printf("You can delete countries by continent and sports type, to proceed type one of continents names \n'Africa', 'Asia', 'Australia', 'Europe', 'North_America' or 'South_America' : ");
			fflush(stdout);
			if (scanf("%s", continent_search) != 1)
			{
				printf("Empty input or wrong name!\n");
				fflush(stdout);
				continue;
			}

			printf("Input one of sports types 'skiing', 'climbing' or 'surfing' : ");
			fflush(stdout);
			if (scanf("%s", sport_search) != 1)
			{
				printf("Empty input or wrong type!\n");
				fflush(stdout);
				continue;
			}

			if (! strcmp(continent_search, "Africa") || ! strcmp(continent_search, "Asia") || ! strcmp(continent_search, "Australia") || ! strcmp(continent_search, "Europe") || ! strcmp(continent_search, "North_America") || ! strcmp(continent_search, "South_America"))
			{
				if (! strcmp(sport_search, "skiing") || ! strcmp(sport_search, "climbing") || ! strcmp(sport_search, "surfing"))
				{
					fsrc = fopen(argv[1], "w");
					delete_country(fsrc, volume, countries_arr, continent_search, sport_search);
					printf("Countries was successfully deleted.\n");
					fflush(stdout);
					fclose(fsrc);
				}
				else
				{
					printf("Wrong sport type!\n");
					fflush(stdout);
				}
			}
			else
			{
				printf("Wrong continent name!\n");
				fflush(stdout);
			}
			
			if (read_file(fsrc, &volume, countries_arr, keys_arr, argv[1]) != EXIT_SUCCESS)
				return FILE_ERROR;
		}

		else if ((! strcmp(menu, "sort")) && volume != 0)
		{
			
			char sort_type[10];
			printf("Choose what to sort main table or keys table (input main or key): ");
			fflush(stdout);
			if (scanf("%s", sort_type) != 1)
			{
				printf("Wrong sort type!\n");
				fflush(stdout);
				continue;
			}

			if (! strcmp(sort_type, "main"))
			{
				printf("What sort algorithm do you want? Input s for standart and q for quick: ");
				fflush(stdout);
				char choice;
				scanf("\n%c", &choice);
				if (choice == 's')
				{
					scanf("%c", &check);
					if (check != '\n')
					{
						printf("Wrong sort type!\n");
						fflush(stdout);
						continue;
					}
					sort_main_table(volume, countries_arr);
					main_sorted = 1;
				}
					
				else if (choice == 'q')
				{
					scanf("%c", &check);
					if (check != '\n')
					{
						printf("Wrong sort type!\n");
						fflush(stdout);
						continue;
					}
					qsort(countries_arr, volume, COUNTRY_T_SIZE, country_cmp);
					main_sorted = 1;
				}
					
				else
				{
					printf("Wrong sort type!\n");
					fflush(stdout);
					continue;
				}

				printf("Main table was sorted!\n");
				printf("Do you want to print the main table? Input y or n: ");
				fflush(stdout);
				scanf("\n%c", &choice);
				if (choice == 'y')
				{
					scanf("%c", &check);
					if (check != '\n')
					{
						printf("Wrong input!\n");
						fflush(stdout);
						continue;
					}
					print_countries(volume, countries_arr);
				}
					
				else if (choice != 'n')
				{
					scanf("%c", &check);
					if (check != '\n')
					{
						printf("Wrong input!\n");
						fflush(stdout);
						continue;
					}
					printf("Wrong input!\n");
					fflush(stdout);
					continue;
				}
			}

			else if (! strcmp(sort_type, "key"))
			{
				printf("What sort algorithm do you want? Input s for standart and q for quick: ");
				fflush(stdout);
				char choice;
				scanf("\n%c", &choice);
				if (choice == 's')
				{
					scanf("%c", &check);
					if (check != '\n')
					{
						printf("Wrong sort type!\n");
						fflush(stdout);
						continue;
						
					}
					sort_keys_table(volume, keys_arr);
					if (main_sorted)
						update_index(volume, keys_arr);
				}
					
				else if (choice == 'q')
				{
					scanf("%c", &check);
					if (check != '\n')
					{
						printf("Wrong sort type!\n");
						fflush(stdout);
						continue;
					}
					qsort(keys_arr, volume, COUNTRY_SORT_SIZE, country_key_cmp);
					if (main_sorted)
						update_index(volume, keys_arr);
				}
					
				else
				{
					printf("Wrong sort type!\n");
					fflush(stdout);
					continue;
				}

				
				printf("Keys table was sorted!\n");
				printf("Do you want to print the keys table? Input y or n: ");
				fflush(stdout);
				scanf("\n%c", &choice);
				if (choice == 'y')
				{
					scanf("%c", &check);
					if (check != '\n')
					{
						printf("Wrong input!\n");
						fflush(stdout);
						continue;
					}
					print_key_table(volume, keys_arr);
				}
					
				else if (choice != 'n')
				{
					scanf("%c", &check);
					if (check != '\n')
					{
						printf("Wrong input!\n");
						fflush(stdout);
						continue;
					}
					printf("Wrong input!\n");
					fflush(stdout);
					continue;
				}

				printf("Do you want to print sorted main table? Input y or n: ");
				fflush(stdout);
				scanf("\n%c", &choice);
				if (choice == 'y')
				{
					scanf("%c", &check);
					if (check != '\n')
					{
						printf("Wrong input!\n");
						fflush(stdout);
						continue;
					}
					print_main_table_by_keys(volume, countries_arr, keys_arr);
				}
					
				else if (choice != 'n')
				{
					scanf("%c", &check);
					if (check != '\n')
					{
						printf("Wrong input!\n");
						fflush(stdout);
						continue;
					}
					printf("Wrong input!\n");
					fflush(stdout);
					continue;
				}
			}

			else
			{
				printf("Wrong table type!\n");
				fflush(stdout);
				continue;
			}
		}

		else if ((! strcmp(menu, "search")) && volume != 0)
		{

			char continent_search[M_CONTINENT];
			char sport_search[M_TOURISM];
			printf("You can search countries by continent and sports type, to proceed type one of continents names \n'Africa', 'Asia', 'Australia', 'Europe', 'North_America' or 'South_America' : ");
			fflush(stdout);
			if (scanf("%s", continent_search) != 1)
			{
				printf("Empty input or wrong name!\n");
				fflush(stdout);
				continue;
			}

			printf("Input one of sports types 'skiing', 'climbing' or 'surfing' : ");
			fflush(stdout);
			if (scanf("%s", sport_search) != 1)
			{
				printf("Empty input or wrong type!\n");
				fflush(stdout);
				continue;
			}

			if (! strcmp(continent_search, "Africa") || ! strcmp(continent_search, "Asia") || ! strcmp(continent_search, "Australia") || ! strcmp(continent_search, "Europe") || ! strcmp(continent_search, "North_America") || ! strcmp(continent_search, "South_America"))
			{
				if (! strcmp(sport_search, "skiing") || ! strcmp(sport_search, "climbing") || ! strcmp(sport_search, "surfing"))
					print_match_countries(volume, countries_arr, continent_search, sport_search);
				else
				{
					printf("Wrong sport type!\n");
					fflush(stdout);
				}
			}
			else
			{
				printf("Wrong continent name!\n");
				fflush(stdout);
				continue;
			}

		}

		else if (! strcmp(menu, "exit"))
		{
			printf("Shutting down...\n");
			return EXIT_SUCCESS;
		}

		else
		{
			printf("Wrong function name or file not readed.\n");
			fflush(stdout);
		}
	}
	
	return EXIT_SUCCESS;
}
