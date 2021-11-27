#include "RemoteSensor.hpp"
namespace Remote
{
    RemoteSensor sensors[NUMBEROFSENSORS] = {RemoteSensor(), RemoteSensor(), RemoteSensor(), RemoteSensor(), RemoteSensor(), RemoteSensor()};

    RemoteSensor *getSensor(int index)
    {
        return &sensors[index];
    }

    RemoteSensor *getSensor(IPAddress ip)
    {
        for (int i = 0; i < NUMBEROFSENSORS; i++)
        {
            if (sensors[i].getIP() == ip)
            {
                return &sensors[i];
            }
        }
        return nullptr;
    }

    RemoteSensor *getMaster()
    {
        for (int i = 0; i < 6; i++)
        {
            if (sensors[i].getIsMaster())
            {
                return &sensors[i];
            }
        }
    }
}