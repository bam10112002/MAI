#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/kd.h>
#include <stdio.h>

void flashing(int *fd_copy, int val)
{
	int f = 0;
	for (;val > 0; val--)
	{
		f = val;
		if (val == 2)
			f = 4;
		else if (val == 3)
			f = 5;
		else if (val == 4)
			f = 2;
		else if (val == 5)
			f = 3;
			
		ioctl(*fd_copy, KDSETLED, f);
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

int morze[26] = {
21, 1112, 1212, 112, 1, 1211, 122,
1111, 11, 2221, 212, 1121, 22, 12,
222, 1221, 2122, 121, 111, 2, 211,
2111, 221, 2112, 2212, 1122  
};

void dash(int *fb_copy)
{
	ioctl(*fb_copy, KDSETLED, 7);
	usleep(1500000);
	ioctl(*fb_copy, KDSETLED, 0);
	usleep(500000);
}

void dot(int *fb_copy)
{
	ioctl(*fb_copy, KDSETLED, 7);
	usleep(500000);
	ioctl(*fb_copy, KDSETLED, 0);
	usleep(500000);
}

void trans_morze(int *fb_copy, char*sentence)
{
	int f;
	for (int i = 0; sentence[i] != '\0'; i++)
	{
		f = morze[sentence[i] - 'a'];
		while (f)
		{
			if (f%10 == 2)
				dash(fb_copy);
			else
				dot(fb_copy);
				 
			f /= 10;
		}		
	}


}

int main(){
	int fd = open("/dev/console", O_WRONLY);
	int sk_value;
	char *sen;
	scanf("%d", &sk_value);
	if (sk_value == 1)
	{
		printf("Value: ");
		scanf("%d", &sk_value);
		flashing(&fd, sk_value);
	}
	else{
		printf("Sentence: ");
		scanf("%s", sen);
		trans_morze(&fd, sen);
	}
	close(fd);
	return 0;
}