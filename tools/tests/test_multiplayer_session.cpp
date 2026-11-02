#include "../../PSP Project/Include/MultiplayerSession.h"
#include <cassert>

int main()
{
    MultiplayerSession host(true, "icarusfalls", 1234, 42);
    MultiplayerSession client(false, "olympus", 999, 0);
    MultiplayerPacket packet = host.outgoing();
    assert(!client.receive(&packet, sizeof(packet) - 1));
    packet.version++;
    assert(!client.receive(&packet, sizeof(packet)));
    packet = host.outgoing();
    strcpy(packet.map, "../secret");
    assert(!client.receive(&packet, sizeof(packet)));
    packet = host.outgoing();
    assert(client.receive(&packet, sizeof(packet)));
    assert(client.phase() == MultiplayerSession::LoadingMap);
    assert(!strcmp(client.map(), "icarusfalls")); // Host overrides the client's selection.
    assert(client.ready(1234));
    packet = client.outgoing();
    packet.session++;
    assert(!host.receive(&packet, sizeof(packet))); // Ignore stale/other sessions.
    packet = client.outgoing();
    host.receive(&packet, sizeof(packet));
    assert(host.phase() == MultiplayerSession::Starting);
    packet = host.outgoing();
    client.receive(&packet, sizeof(packet));
    assert(client.phase() == MultiplayerSession::Playing);
    packet = client.outgoing();
    host.receive(&packet, sizeof(packet));
    assert(host.phase() == MultiplayerSession::Playing);
    packet = host.outgoing();
    client.receive(&packet, sizeof(packet));
    assert(client.phase() == MultiplayerSession::Playing); // Duplicate packets do not restart.
    MultiplayerSession incompatible(false, "olympus", 0, 0);
    MultiplayerSession offer(true, "icarusfalls", 1234, 43);
    packet = offer.outgoing();
    incompatible.receive(&packet, sizeof(packet));
    assert(!incompatible.ready(999));
    assert(incompatible.phase() == MultiplayerSession::Failed);
}
