#include "include/passerine.h"
#include <QApplication>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <array>

void executeTimidity(void);

int main(int argc, char *argv[])
{
    executeTimidity();

    QApplication a(argc, argv);
    Passerine w;
    w.show();

    return a.exec();
}

void executeTimidity(void)
{
    std::array<char, 1024> buffer;
    std::string aconnectOutput;

//    We get a pipe from aconnect output
    std::shared_ptr<FILE> pipe(popen("aconnect -o", "r"), pclose);

    if (!pipe)
        throw std::runtime_error("popen() failed!");

    while (!feof(pipe.get())) {
        if (fgets(buffer.data(), 1024, pipe.get()) != NULL)
            aconnectOutput += buffer.data();
    }

//    If TiMidity isn't turned on, then the following system command
//    will do that and make TiMidity run in background
    if (aconnectOutput.find("TiMidity") == std::string::npos)
        system("timidity -iA &");
}
