#include "util/ServerStats.h"

#include <dirent.h>
#include <string>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

bool ServerAdmin::ServerStats::m_StarboundServerRunning = false;

void ServerAdmin::ServerStats::checkStarboundServerRunning()
{
    string serverExec = "./starbound_server";
    DIR *dp = opendir("/proc");
    struct dirent *dirp;
    if(dp != NULL)
    {
        while (dirp = readdir(dp))
        {
            int id = atoi(dirp->d_name);
            if(id > 0)
            {
                string cmdPath = string("/proc/") + dirp->d_name + "/cmdline";
                ifstream cmdFile(cmdPath.c_str());
                string cmdLine;
                getline(cmdFile, cmdLine);
                if(!cmdLine.empty() && (serverExec == cmdLine))
                {
                    ServerAdmin::ServerStats::m_StarboundServerRunning = true;
                }
            }
        }
    }
}

bool ServerAdmin::ServerStats::getIsStarboundServerRunning()
{
    ServerAdmin::ServerStats::checkStarboundServerRunning();
    return ServerAdmin::ServerStats::m_StarboundServerRunning;
}