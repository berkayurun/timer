#include<stdio.h>
#include<unistd.h>

void printHelp();
void printTime();
int timer(int minutes);
void chronometer();
void printFinish();

int newTimer = 0;
int newChro = 0;

int main(int argc, char *argv[]){
	int opt;
	int timeToSet = 0;

	while((opt = getopt(argc, argv, "hct:")) != -1){
		switch(opt){
		case 'h':
			printHelp();
			break;
		case 't':
			newTimer = 1;
			timeToSet = atoi(optarg);
			break;
		case 'c':
			newChro = 1;
			break;
		}
	}

	if(newTimer == 1){
		printf("Timer set to %i\n", timeToSet);
		timer(timeToSet);
	} else if(newChro == 1){
		chronometer();
	} else {
		printHelp();
	}

	return 0;
}

void chronometer(){
	int counter = 0;

	while(newChro == 1){
		printTime(counter);
		counter++;
		sleep(1);
	}

}

int timer(int minutes){
	int hours;
	int seconds = minutes * 60;

	while(seconds != 0){
		printTime(seconds);

		seconds--;

		sleep(1);
	}

	printFinish();
}

void printTime(int seconds){
	//clean the terminal
	printf("\e[1;1H\e[2J");

	int hours, minutes;

	hours = seconds / 60 / 60;
	minutes = seconds / 60;

	printf("---------------\n");
	printf("| Hours:   %2i |\n", hours);
	printf("| Minutes: %2i |\n", minutes);
	printf("| Seconds: %2i |\n", seconds % 60);
	printf("---------------\n");
}

void printHelp(){
	printf("Welcome to Help!\n");
	printf("-h		Print help\n-t [minutes]	Set timer\n-c 		Start a chronometer\n");
}

void printFinish(){
	//clean the terminal
	printf("\e[1;1H\e[2J");

	printf("Time is up!\n");
}

void reader(char* read){
		
}
