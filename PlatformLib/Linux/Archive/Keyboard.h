#pragma once

#include <iostream>
#include <fcntl.h>
#include <pthread.h>
#include <linux/input.h>

class Keyboard
{
  private:
	pthread_t thread;
	bool active;
	int keyboard_fd;
	input_event *keyboard_ev;
	short keys[KEY_CNT];
	char name[256];

  protected:
  public:
	Keyboard();
	~Keyboard();
	static void* loop(void* obj);
	void readEv();
	const short *getKeyboardState() {return keys;}
};
