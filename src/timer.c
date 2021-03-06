#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>

//Replaced with notify-send
//#include "config.h"

mode_t umask();

int timerDaemon();
void printHelp();
void printTime();
int timer(int minutes);
void chronometer();
void printFinish();

int newTimer = 0;
int newChro = 0;
int printMode = 0;

int main(int argc, char *argv[]){
	int opt;
	int timeToSet = 0;
	pid_t pid, sid;


	while((opt = getopt(argc, argv, "bct:")) != -1){
		switch(opt){
		case 't':
			newTimer = 1;
			timeToSet = atoi(optarg);
			break;
		case 'c':
			newChro = 1;
			break;
		case 'b':
			printMode = 1;
			break;
		}
	}

	if(newTimer == 1 && printMode == 1){
		printf("Timer set to %i\n", timeToSet);
		timer(timeToSet);
	} else if(newChro == 1 && printMode == 1){
		chronometer();
	} else if(newTimer == 1) {
		//https://www.go4expert.com/articles/writing-linux-daemon-process-c-t27616/
		pid = fork();

		if(pid < 0){
			exit(EXIT_FAILURE);
		}

		if(pid > 0){
			exit(EXIT_SUCCESS);
		}

		umask(0);

		sid = setsid();
		if(sid < 0){
			exit(EXIT_FAILURE);
		}

		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		close(STDERR_FILENO);

		timerDaemon(timeToSet);

		return(0);

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

//under construction
//timer works as a deamon
int timerDaemon(int minutes){
	int hours;
	int seconds = minutes * 60;

    char secLeft[20] = " seconds left!";
    char command[100], msg[100] = {};
    strcpy(command, "notify-send ");

	while(seconds != 0){
		if(seconds == 30 || seconds == 60 || seconds == 300){
			sprintf(msg, "\"Time left: %d seconds!\"", seconds);
            strcpy(command, "notify-send ");
            strcat(command, msg);
			system(command);
		}

		seconds--;

		sleep(1);
	}

	system("notify-send \"Time done!\"");

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
	printf("-h		Print help\n-t [minutes]	Set timer\n-c 		Start a chronometer\n-b 		Print mode\n");
}

void printFinish(){
	//clean the terminal
	printf("\e[1;1H\e[2J");

	printf("Time is up!\n");
}

void reader(char* read){
		
}
