#include "tty.h"

struct FileDeleter {
	void operator() (FILE* file)
	{
		std::fclose(file);
	}
};

void TTY::write_log_sensor_data(const char* buf)
{
	std::unique_ptr<FILE,FileDeleter> file(std::fopen("data_sensor.txt","a+"));
	fputs("\n",file.get());
	fputs(std::to_string(buf_int).c_str(),file.get());
}

void TTY::set_settings_tty()
{
    // https://blog.mbedded.ninja/programming/operating-systems/linux/linux-serial-ports-using-c-cpp/
    if (tcgetattr(serial_port,&tty) !=0)
    {
        perror("Error ");
        return;
    }

    tty.c_cflag &= ~PARENB; // clear parity bit, disabling parity
    tty.c_cflag &= ~CSTOPB; // clear stop field, 1 stop bit
    tty.c_cflag &= ~CSIZE;  // clear all bits for set data size
    tty.c_cflag |= CS8;     // set data size  = 8 bit
    tty.c_cflag &= ~CRTSCTS;    // disable RTS/CTS hardware flow control
    tty.c_cflag |= CREAD | CLOCAL;  // turn on read& ignore ctrl lines

    tty.c_iflag &= ~ICANON;
    tty.c_iflag &= ~ECHO;   // disable echo
    tty.c_iflag &= ~ECHOE;  // disable earsure
    tty.c_iflag &= ~ECHONL; // disable new-line echo
    tty.c_iflag &= ~ISIG;   // disable interpretation of INTR, QUIT and SUSP
    tty.c_iflag &= ~(IXON | IXOFF | IXANY); //turn off s/w flow ctrl
    tty.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL);

    tty.c_oflag &= ~OPOST;  // prevent special interpretator of output bytes
    tty.c_oflag &= ~ONLCR;  // prevent conversion of newline to carriage return/line feed

    // setting time delay for waiting data
    tty.c_cc[VTIME] = 10;      // wait for up 1s (10*100ms)
    tty.c_cc[VMIN] = 0;

    cfsetispeed(&tty,B9600);
    cfsetospeed(&tty,B9600);

    if (tcsetattr(serial_port,TCSANOW,&tty) !=0)
    {
        perror("Error from tcsetattr ");
        return;
    }
}

void TTY::read_data(std::atomic<bool>& state)
{
    while (state)
    {
        //Simple_timer st;
        tcflush(serial_port,TCIFLUSH);
        int num_bytes = read(serial_port,&buf,sizeof(buf));
        if (num_bytes <0)
            {
                perror("Error reading ");
				state = false;
                return;
            }
        buf_int = char_to_int(buf);
        //write_log_sensor_data(buf);
        std::this_thread::sleep_for(std::chrono::milliseconds(TIME_REQUEST));     // request every delta time
    }
    std::cout<<"State = "<<state<<std::endl;
    std::cout.flush();
};

int TTY::get_value_sensor() const
{
	return buf_int;
}

int char_to_int(const char* buf)
{
    int ans=0;
    int n =1;
    for (int i=2; i>=0;--i)
    {
        if (buf[i]>=48)
        {
            ans += (buf[i]-'0')*n;
            n *=10;
        }
    }
    return ans; 
}