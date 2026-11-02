#ifndef MULTIPLAYER_SESSION_H
#define MULTIPLAYER_SESSION_H

#include <cstdint>
#include <cstring>

// Both endpoints are PSPs: fixed-width fields, no pointers or native bools on the wire.
struct MultiplayerPacket
{
    uint32_t magic, version, session, type, mapHash;
    char map[64];
};

class MultiplayerSession
{
public:
    enum Phase { WaitingMap, LoadingMap, WaitingReady, WaitingStart, Starting, Playing, Failed };
    enum Type { Map = 1, Ready, Start, PlayingAck };
    MultiplayerSession(bool host, const char *map, uint32_t hash, uint32_t nonce)
        : mHost(host), mPhase(host ? WaitingReady : WaitingMap)
    {
        memset(&mPacket, 0, sizeof(mPacket));
        mPacket.magic = 0x47444d50;
        mPacket.version = 1;
        if (host)
        {
            mPacket.session = nonce ? nonce : 1;
            mPacket.mapHash = hash;
            strncpy(mPacket.map, map, sizeof(mPacket.map) - 1);
        }
    }
    Phase phase() const { return mPhase; }
    const char *map() const { return mPacket.map; }
    uint32_t mapHash() const { return mPacket.mapHash; }
    bool ready(uint32_t localHash)
    {
        if (mPhase != LoadingMap) return false;
        mPhase = localHash && localHash == mPacket.mapHash ? WaitingStart : Failed;
        return mPhase != Failed;
    }
    MultiplayerPacket outgoing() const
    {
        MultiplayerPacket packet = mPacket;
        packet.type = mHost ? (mPhase == WaitingReady ? Map : Start) : Ready;
        if (mPhase == Playing) packet.type = PlayingAck;
        return packet;
    }
    bool receive(const void *data, unsigned int size)
    {
        if (size != sizeof(MultiplayerPacket)) return false;
        MultiplayerPacket packet;
        memcpy(&packet, data, sizeof(packet));
        if (packet.magic != mPacket.magic || packet.version != mPacket.version || !packet.session ||
            !memchr(packet.map, 0, sizeof(packet.map)) || !packet.map[0]) return false;
        for (const char *p = packet.map; *p; ++p)
            if (!((*p >= 'a' && *p <= 'z') || (*p >= '0' && *p <= '9') || *p == '_')) return false;
        if (!mHost && mPhase == WaitingMap && packet.type == Map)
        {
            mPacket = packet;
            mPhase = LoadingMap;
            return true;
        }
        if (packet.session != mPacket.session || packet.mapHash != mPacket.mapHash ||
            strcmp(packet.map, mPacket.map)) return false;
        if (mHost && mPhase == WaitingReady && packet.type == Ready) mPhase = Starting;
        if (!mHost && mPhase == WaitingStart && packet.type == Start) mPhase = Playing;
        if (mHost && mPhase == Starting && packet.type == PlayingAck) mPhase = Playing;
        return packet.type >= Map && packet.type <= PlayingAck;
    }
private:
    bool mHost;
    Phase mPhase;
    MultiplayerPacket mPacket;
};
#endif
