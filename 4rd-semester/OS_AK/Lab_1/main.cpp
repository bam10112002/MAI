#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/kd.h>
#include <stdio.h>
#include <iostream>

void Task_2(int *fd_copy, int val)
{
	int code = 0;
	for (;val > 0; val--)
	{
		code = val;
		if (val == 2)
			code = 4;
		else if (val == 3)
			code = 5;
		else if (val == 4)
			code = 2;
		else if (val == 5)
			code = 3;
			
		ioctl(*fd_copy, KDSETLED, code);
		sleep(2);		
	}

	ioctl(*fd_copy, KDSETLED, 0);
	usleep(500000);
	for (int i = 0; i < 3; i++){
		ioctl(*fd_copy, KDSETLED, 7);
		sleep(1);
		ioctl(*fd_copy, KDSETLED, 0);
		usleep(500000);
	}
}

//Константы для азбуки морзе
int morze[26] = {
21, 1112, 1212, 112, 1, 1211, 122,
1111, 11, 2221, 212, 1121, 22, 12,
222, 1221, 2122, 121, 111, 2, 211,
2111, 221, 2112, 2212, 1122  
};

// Тире
void dash(int *fb_copy)
{
	ioctl(*fb_copy, KDSETLED, 7);
	usleep(1500000);
	ioctl(*fb_copy, KDSETLED, 0);
	usleep(500000);
}

// Точка
void dot(int *fb_copy)
{
	ioctl(*fb_copy, KDSETLED, 7);
	usleep(500000);
	ioctl(*fb_copy, KDSETLED, 0);
	usleep(500000);
}


/**
* @brief Translate to morze
* @param fd_copy  keyboard descriptor
* @param sentence  text to translate 
* @return void 
*/
void Task_1(int *fb_copy, char* sentence)
{
	int code;
	for (int i = 0; sentence[i] != '\0'; i++)
	{
		code = morze[sentence[i] - 'a'];
		while (code)
		{
			if (code%10 == 2)
				dash(fb_copy);
			else
				dot(fb_copy);
				 
			code /= 10;
		}		
	}


}

int main(){
	int fd = open("/dev/console", O_WRONLY);
	int taskId;


	cout << "input task number 1 or 2:\n>> ";
    cin << taskId;
    cout << endl;

	if (taskId == 1)
	{
        char *sen;
		printf("Sentence: ");
		scanf("%s", sen);
		Task_1(&fd, sen);
	}
	else
    {
        int val;
        cout << "Value: ";
        cin >> val;
		Task_2(&fd, val);
	}
	close(fd);
	return 0;
}