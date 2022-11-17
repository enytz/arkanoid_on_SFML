#ifndef tty_h
#define tty_h

#include <fcntl.h>      // Contains file control like O_RDWR
#include <errno.h>      // Error integer
#include <termios.h>    // Contains POSIX terminal control definitions
#include <unistd.h>     // write(), read(), close()

#include <memory>
#include <atomic>
#include <thread>

#define TIME_REQUEST 30  // time (ms) request in buf_int 

#include <iostream>

struct TTY
{
    public:
    	TTY()
    		:buf_int(0)
     		{serial_port = open("/dev/ttyACM0",O_RDWR);}
    	~TTY() {std::cout<<"~tty"; /*std::cout.flush();*/ close(serial_port);}
    	void set_settings_tty();
    	void read_data(std::atomic<bool>& state);
    	int get_value_sensor() const;
		void write_log_sensor_data(const char* buf);
    private:
        int serial_port;
        termios tty;
        char buf[3];            // max bit depth for sensor (~300 cm)
        int buf_int;
        

};

int char_to_int(const char* buf);

#endif