#ifndef __LOG__
#define __LOG__

#include <string>
#include <fstream>
#include <ctime>

class Log 
{
public:
    static Log* get_log_instance()
    {
        static Log log;
        return &log;
    }

    void write(int lvl, const std::string& txt) {
        if(logfile.is_open() && lvl < loglevel) 
        {
            time_t now{time(0)};
            char* header = ctime(&now); 
            if (header[strlen(header) - 1] == '\n') 
            {
                header[strlen(header) - 1] = '\0';
            }
            logfile << header << " " << txt << std::endl;
        }
    }

    void write(int lvl, const char* txt) {
        if(logfile.is_open() && lvl < loglevel) 
        {
            time_t now{time(0)};
            char* header = ctime(&now); 
            if (header[strlen(header) - 1] == '\n') 
            {
                header[strlen(header) - 1] = '\0';
            }
            logfile << header << " " << txt << std::endl;
        }
    }

private:
    Log() : filename("log.txt"), loglevel(5) 
    {
        logfile.open(filename, std::ofstream::app);
    }

    Log(const std::string& fn, int loglvl) : filename(fn), loglevel(loglvl)
    {
        logfile.open(filename, std::ofstream::app);
    }

    ~Log() 
    {
        logfile.close();
    }

    std::string     filename;
    std::ofstream   logfile;
    int             loglevel;
};
#endif

