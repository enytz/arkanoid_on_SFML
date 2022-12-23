#ifndef tty_h
#define tty_h

#include <fcntl.h>      // Contains file control like O_RDWR
#include <errno.h>      // Error integer
#include <termios.h>    // Contains POSIX terminal control definitions
#include <unistd.h>     // write(), read(), close()

#include <memory>
#include <atomic>
#include <thread>

#include <iostream>

#define TIME_REQUEST 30  // time (ms) request in buf_int 

struct TTY
{
    public:
    	TTY();
    	~TTY();
    	void read_data(std::atomic<bool>& state,std::atomic<bool>& quitTheGame);
    	int get_value_sensor() const;
		void write_log_sensor_data(const char* buf);
    private:
        int serial_port;
        termios tty,oldtty;
        char buf[3];            // max bit depth for sensor (~300 cm)
        int buf_int;
        

};

int char_to_int(const char* buf);

#endif