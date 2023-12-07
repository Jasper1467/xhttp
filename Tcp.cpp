#include "Tcp.h"

#ifdef WIN32
#include <winsock2.h>
#elif defined(__linux__)
#include <sys/socket.h>
#include <netinet/in.h>
#endif

bool g_bInitialized = false;

void Tcp::Initialize()
{
    g_bInitialized = true;
}

void Tcp::Shutdown()
{
    g_bInitialized = false;
}

bool Tcp::IsInitialized()
{
    return g_bInitialized;
}

bool Tcp::IsValidPort(const int nPort)
{
    return nPort > 0 && nPort < 65535;
}

bool Tcp::Receive(const int nPort, std::vector<uint8_t>& vecBufferOut)
{
    if (!IsInitialized())
        return false;

    if (!IsValidPort(nPort))
        return false;

    vecBufferOut.clear();

#ifdef WIN32
    SOCKET nSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (nSocket == INVALID_SOCKET)
        return false;
#elif defined(__linux__)
    int nSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (nSocket < 0)
        return false;
#endif

    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(nPort);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(nSocket, (sockaddr*)&addr, sizeof(addr)) < 0)
        return false;

    if (listen(nSocket, 1) < 0)
        return false;

    sockaddr_in addrClient;
    socklen_t nSize = sizeof(addrClient);

    const int nClient = accept(nSocket, reinterpret_cast<sockaddr*>(&addrClient), &nSize);
    if (nClient < 0)
        return false;

    char szBuffer[1024];
    const ssize_t nRead = recv(nClient, szBuffer, 1024, 0);
    if (nRead < 0)
        return false;

    vecBufferOut.assign(szBuffer, szBuffer + nRead);

    return true;
}

bool Tcp::Send(const int nPort, const std::vector<uint8_t>& vecBufferIn)
{
    if (!IsInitialized())
        return false;

    if (!IsValidPort(nPort))
        return false;

    if (vecBufferIn.empty())
        return false;

#ifdef WIN32
    SOCKET nSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (nSocket == INVALID_SOCKET)
        return false;
#elif defined(__linux__)
    int nSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (nSocket < 0)
        return false;
#endif

    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(nPort);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (connect(nSocket, (sockaddr*)&addr, sizeof(addr)) < 0)
        return false;

    if (const ssize_t nWrite = send(nSocket, vecBufferIn.data(), vecBufferIn.size(), 0); nWrite < 0)
        return false;

    return true;
}

bool Tcp::Reply(int nPort, const std::vector<uint8_t>& vecBufferIn)
{
    if (!IsInitialized())
        return false;

    if (!IsValidPort(nPort))
        return false;

    if (vecBufferIn.empty())
        return false;

    return Send(nPort, vecBufferIn);
}
