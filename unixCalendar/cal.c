#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <time.h>

#define TRUE 1
#define FALSE 0

char *months[] = 
{
	" ",
	"January",
	"February",
	"March",
	"April",
	"May",
	"June",
	"July",
	"August",
	"September",
	"October",
	"November",
	"December"
};

char *days[] = {" ", "Su", "Mo", "Tu", "We", "Th", "Fr", "Sa"};

int numDays[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};

int thirdMonthLastDay;

void GetMonthYear(int *month, int *year) {
	time_t timenow;
	struct tm *current;
	time(&timenow);
	current = gmtime(&timenow);
	*month = current->tm_mon+1;
	*year = current->tm_year+1900;
}


int CheckLeapYear (int year)
{
	if (year % 4 == 0 && year % 100 != 0 || year % 400 == 0)
	{
		numDays[2] = 29;
		return TRUE;
	}
	else
	{
		numDays[2] = 28;
		return FALSE;
	}
}

int FindDayOfWeek(int month, int year)
{
	int totalDays, numLeapYears, numStandardYears, leapYearDays, standardYearDays;
	numLeapYears = ((year - 1) / 4) - ((year - 1) / 100) + ((year - 1) / 400);
	numStandardYears = year - numLeapYears;
	leapYearDays = 366 * numLeapYears;
	standardYearDays = 365 * numStandardYears;
	totalDays = leapYearDays + standardYearDays;

	if (month == 1)
	{
		return (totalDays % 7) + 1;
	}
	else
	{
		for (int currentMonth = 1; currentMonth < month; currentMonth++)
		{
			totalDays += numDays[currentMonth];
		}
		return (totalDays % 7) + 1;
	}
}

int GetYearStrLen (int year)
{
	int yearLength;

	if (year >= 1000)
	{
		yearLength = 4;
	}
	else if (year > 99)
	{
		yearLength = 3;
	}
	else if (year > 9)
	{
		yearLength = 2;
	}
	else
	{
		yearLength = 1;
	}

	return yearLength;
}

void PrintWeekDays()
{
	for (int day = 1; day <= 7; day++)
	{
		if (day == 7)
		{
			printf("%s", days[day]);
		}
		else
		{
			printf("%s ", days[day]);
		}
	}
}

void PrintMonthName (char *month, int year, int wantYear)
{
	int nameLen = strlen(month);
	int spaces = 20;
	if (wantYear)
	{
		int yearLength = GetYearStrLen(year);
		spaces = (spaces-(nameLen+yearLength));
	}
	else
	{
		spaces -= nameLen;
	}
	spaces /= 2;

	for (int i = 0; i < spaces; i++)
	{
		printf(" ");
	}

	if (wantYear)
	{
		printf("%s %d", month, year);
	}
	
	else
	{
		printf("%s", month);
	}

	for (int i = 0; i < spaces; i++)
	{
		printf(" ");
	}
}

int PrintWeek (int firstDay, int firstDate, int monthDays)
{
	int day;
	for (day = 1; day < firstDay; day++)
	{
		printf("   ");
	}
	for (day = firstDay; day <= 7; day++)
	{
		if (firstDate > monthDays)
		{
			if (firstDate == monthDays + 1)
			{
				thirdMonthLastDay = day;
			}
			if (day != 7)
			{
				printf("   ");
			}
			else
			{
				printf("  ");
			}			
		}
		else
		{
			if (day != 7)
			{
				printf("%2d ", firstDate);
			}
			else
			{
				printf("%2d", firstDate);
			}
		}
		firstDate++;
	}
	return firstDate;
}

void PrintFormattedYear (int year)
{
	int firstDay, secondDay, thirdDay, yearLength, spaces;
	int i, j, day;
	int firstMonth, secondMonth, thirdMonth;
	int lastDateOne, lastDateTwo, lastDateThree;
	int firstMonthDays, secondMonthDays, thirdMonthDays, isLeapYear;
	CheckLeapYear(year);
	firstDay = FindDayOfWeek(1, year);
	yearLength = GetYearStrLen(year);
	spaces = 62;
	spaces-=yearLength;
	spaces/=2;
	for (i = 0; i < spaces; i++)
	{
		printf(" ");
	}
	printf("%d", year);
	for (i = 0; i < spaces; i++)
	{
		printf(" ");
	}
	printf("\n");
	for (i = 1; i <= 12; i += 3)
	{
		lastDateOne = 1, lastDateTwo = 1, lastDateThree = 1;
		firstMonth = i, secondMonth = i+1, thirdMonth = i+2;
		firstMonthDays = numDays[firstMonth];
		secondMonthDays = numDays[secondMonth];
		thirdMonthDays = numDays[thirdMonth];
		PrintMonthName(months[firstMonth], year, 0);
		printf("  ");
		PrintMonthName(months[secondMonth], year, 0);
		printf("  ");
		PrintMonthName(months[thirdMonth], year, 0);
		printf("\n");
		for (j = 1; j <= 3; j++)
		{
			PrintWeekDays();
			if (j < 3)
			{
				printf("  ");
			}
		}
		printf("\n");

		secondDay = FindDayOfWeek(secondMonth, year);
		thirdDay = FindDayOfWeek(thirdMonth, year);

		for (j = 1; j <= 6; j++)
		{
			lastDateOne = PrintWeek(firstDay, lastDateOne, firstMonthDays);
			printf("  ");
			lastDateTwo = PrintWeek(secondDay, lastDateTwo, secondMonthDays);
			printf("  ");
			lastDateThree = PrintWeek(thirdDay, lastDateThree, thirdMonthDays);
			printf("\n");
			if (j != 6)
			{
				firstDay = 1, secondDay = 1, thirdDay = 1;
			}
			else
			{
				firstDay = FindDayOfWeek(thirdMonth+1, year);
			}
		}
		if (i < 10)
		{
			printf("\n");
		}
	}
}

void PrintMonthOfYear (int month, int year)
{
	int i, j, k, day;
	CheckLeapYear(year);
	int currentDay = FindDayOfWeek(month, year);

	PrintMonthName(months[month], year, 1);
	printf("\n");

	for (day = 1; day <= 7; day++)
	{
		if (day == 7){
			printf("%s", days[day]);
		}
		else
		{
			printf("%s ", days[day]);
		}			
	}

	printf("\n");

	for (k = 1; k < currentDay; k++)
	{
		printf("   ");
	}

	for (j = 1; j <= numDays[month]; j++)
	{
		printf("%2d ", j);
		currentDay++;
		if (currentDay > 7)
		{
			currentDay = 1;
			printf("\n");
		}
	}
	
	printf("\n");
}

int MatchSubstring (char *input)
{
	int length = strlen(input);
	int isMatch = FALSE;
	for (int month = 1; month <= 12; month++)
	{
		char *monthName = months[month];
		int monthNameLen = strlen(monthName);
		for (int i = 0; i < length; i++)
		{
			if (tolower(input[i]) != tolower(monthName[i]))
			{
				break;
			}
			if (i == monthNameLen - 1)
			{
				isMatch = TRUE;
				break;
			}
			if (i == length - 1)
			{
				isMatch = TRUE;
			}
		}
		if (isMatch == TRUE)
		{
			return month;
		}
	}
	return 0;
}

int CheckForNumber (char *input)
{
	int i = 0;

	while (input[i] != '\0')
	{
		if (!isdigit(input[i]))
		{
			return FALSE;
		}
		i++;
	}
	return TRUE;
}

int CheckMonth (char *input)
{
	int month;
	int isNumber = CheckForNumber(input);
	if (isNumber)
	{
		month = atoi(input);
	}
	else
	{
		char *monthTemp = input;
		int monthMatch = MatchSubstring(monthTemp);
		if (monthMatch == 0)
		{
			printf("Month must be valid name or substring.\n");
			return 0;	
		}
		else
		{
			month = monthMatch;
		}
	}
	return month;
}

int main(int argc, char **argv)
{
	if (argc == 1)
	{
		int year, month;
		GetMonthYear(&month, &year);
		PrintMonthOfYear(month, year);
		return 0;
	}
	if (argc == 2)
	{
		if (argv[1][0] == '-' && argv[1][1] == 'm')
		{
			printf("If you wish to print a specific month, please input '-m monthNameOrInteger [yearInt]'\nor 'monthNameOrInteger [yearInt]'.");
			return 0;
		}
		int year = atoi(argv[1]);

		if (year > 9999 || year < 1)
		{
			printf("Year input must be between 1 and 9999.\n");
			return 0;
		}
		PrintFormattedYear(year);
		return 0;
	}
	else
	{
		if (argc >= 3)
		{
			int month = 0, year = 0;
			int m, y;
			GetMonthYear(&m, &y);
			
			if (argc == 3)
			{
				if (argv[1][0] == '-' && argv[1][1] == 'm')
				{
					month = CheckMonth(argv[2]);
					if (month == 0)
					{
						printf("Month must be a valid substring or a number from 1 to 12.\n");
						return 0;
					}
					else
					{						
						PrintMonthOfYear(month, y);
						return 0;
					}
				}
				else
				{
					month = CheckMonth(argv[1]);
					if (month == 0)
					{
						printf("Month must be a valid substring or a number from 1 to 12.\n");
						return 0;
					}
					int isNumber = CheckForNumber(argv[2]);
					if (!isNumber)
					{
						printf("Year must be an integer between 1 and 9999.\n");
						return 0;
					}
					year = atoi(argv[2]);
					if (year > 9999 || year < 1)
					{
						printf("Year input must be between 1 and 9999.\n");
						return 0;
					}
					PrintMonthOfYear(month, year);
					return 0;
				}
			}			
			if (argc > 3)
			{
				if (argv[1][0] == '-' && argv[1][1] == 'm')
				{
					month = CheckMonth(argv[2]);
					if (month == 0)
					{
						printf("Month must be a valid substring or a number from 1 to 12.\n");
						return 0;
					}
					int isNumber = CheckForNumber(argv[3]);
					if (!isNumber)
					{
						printf("Year must be an integer between 1 and 9999.\n");
						return 0;
					}
					year = atoi(argv[3]);
					if (year > 9999 || year < 1)
					{
						printf("Year input must be between 1 and 9999.\n");
						return 0;
					}
					PrintMonthOfYear(month, year);
					return 0;
				}
				else
				{
					printf("Invalid input. Verify that your second argument is '-m'.\n");
					return 0;
				}
			}
		}
	}
}

