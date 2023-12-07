#ifndef TCP_H
#define TCP_H

#include <cstdint>
#include <vector>

namespace Tcp
{
    void Initialize();
    void Shutdown();

    bool IsInitialized();

    bool IsValidPort(int nPort);

    bool IsConnected();

    bool Receive(int nPort, std::vector<uint8_t>& vecBufferOut);

    bool Send(int nPort, const std::vector<uint8_t>& vecBufferIn);

    bool Reply(int nPort, const std::vector<uint8_t>& vecBufferIn);
}

#endif //TCP_H
