#include <iostream>
#include <unistd.h>
#include <thread>
#include <mutex>

/**
 * @brief Релаизация D защелки
 * 
 * @param d вход в защелку
 * @param mtx исключение гонуи данных 
 */
void dLatch(int &d, std::mutex &mtx) 
{
	bool c, q = 1, not_q = 0;

	while(true) {
		c = true;
		not_q = !((c && d) || q);
		mtx.lock();
		q = !((c && !d) || not_q);
		not_q = !((c && d) || q);
		mtx.unlock();

        system("clear");
		std::cout << "q = " << q << "\t!q = " << not_q << std::endl;
        if (d == 2)
            return;
        sleep(1);
	}
}

/**
 * @brief Поток для ввода значения d в асинхронном формате
 *  
 * @param d ссылка на значение которое нужно изменить
 * @param mtx исключает гонку данных
 */
void GetD(int &d, std::mutex &mtx)
{
	int newD;
	while(true)
    {
		std::cin >> newD;
		mtx.lock();
		d = newD;
		mtx.unlock();
        if (newD == 2)
            return;
	}
}

void Task_4()
{
	int d;
	std::cout << "if d == 2 completion of the program\nPlease input d: " << std::endl;
	std::cin >> d;
	std::mutex mtx;

	auto thread_d_latch = std::thread(dLatch, std::ref(d), std::ref(mtx));
	auto thread1 = std::thread(GetD, std::ref(d), std::ref(mtx));

	thread_d_latch.join();
	thread1.join();
}

int main(int argc, char const **argv) 
{
	return 0;
}