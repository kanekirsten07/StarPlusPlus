#pragma once

namespace ServerAdmin
{
    class ServerStats
    {
    private:
        static bool m_StarboundServerRunning;
 
        static void checkStarboundServerRunning();

    public:

        static bool getIsStarboundServerRunning();
    };
} // namespace ServerAdmin