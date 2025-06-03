#include <DNSServer.h>

class CustomDNS {
private:
    DNSServer dnsServer;
    const byte DNS_PORT = 53;

public:
    CustomDNS(IPAddress redirectIP, const String& domain);
    void tick();
};
