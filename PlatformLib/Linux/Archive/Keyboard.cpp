#include <fcntl.h>
#include <unistd.h>

#include "Keyboard.h"

static const char*	gsc_szKeyboardDevice	= "/dev/input/event3";

Keyboard::Keyboard()
{
	active = true;
	keyboard_ev = new input_event();
	keyboard_fd	= open(gsc_szKeyboardDevice, O_RDONLY | O_NONBLOCK);
	
	if (keyboard_fd > 0) {
		ioctl(keyboard_fd, EVIOCGNAME(256), name);
		std::cout << "   Name: " << name << std::endl;
		active = true;
		pthread_create(&thread, 0, &Keyboard::loop, this);
	}
}

Keyboard::~Keyboard() {
	if (keyboard_fd > 0) {
		active = false;
		pthread_join(thread, 0);
		close(keyboard_fd);
	}
	delete keyboard_ev;
	keyboard_fd = 0;
}

void* Keyboard::loop(void *obj)
{
	if (reinterpret_cast<Keyboard *>(obj)->active)
	{
		reinterpret_cast<Keyboard *>(obj)->readEv();
	}
	
	return	NULL;
}

void Keyboard::readEv()
{
	int bytes	= read(keyboard_fd, keyboard_ev, sizeof(*keyboard_ev));
	
	if (bytes > 0)
	{
		if (keyboard_ev->type & EV_KEY)
		{
			keys[keyboard_ev->code] = keyboard_ev->value;
		}
	}
}
