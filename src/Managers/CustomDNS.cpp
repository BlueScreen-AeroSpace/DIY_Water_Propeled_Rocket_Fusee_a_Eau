#include "Managers/CustomDNS.h"

CustomDNS::CustomDNS(IPAddress redirectIP, const String& domain) {
    dnsServer.start(DNS_PORT, domain, redirectIP);
}

void CustomDNS::tick() {
    dnsServer.processNextRequest();
}
