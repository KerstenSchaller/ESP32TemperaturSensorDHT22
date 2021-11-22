#include "RemoteSensor.hpp"
namespace Remote
{
    RemoteSensor sensors[6] = {RemoteSensor(), RemoteSensor(), RemoteSensor(), RemoteSensor(), RemoteSensor(), RemoteSensor()};

    RemoteSensor *getSensor(int index)
    {
        return &sensors[index];
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