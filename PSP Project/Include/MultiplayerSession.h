#ifndef MULTIPLAYER_SESSION_H
#define MULTIPLAYER_SESSION_H

#include <cstdint>
#include <cstring>

// Both endpoints are PSPs: fixed-width fields, no pointers or native bools on the wire.
struct MultiplayerPacket
{
    uint32_t magic, version, session, type, mapHash, score, finished, survived, resultSeen;
    char map[64];
};

class MultiplayerSession
{
public:
    enum Phase { WaitingMap, LoadingMap, WaitingReady, WaitingStart, Starting, Playing, Failed };
    enum Type { Map = 1, Ready, Start, PlayingAck };
    enum Result { Pending, Lost, Draw, Won };
    MultiplayerSession(bool host, const char *map, uint32_t hash, uint32_t nonce)
        : mHost(host), mPhase(host ? WaitingReady : WaitingMap), mRemoteFinished(false),
          mRemoteScore(0), mRemoteSurvived(false), mPeerAcknowledged(false)
    {
        memset(&mPacket, 0, sizeof(mPacket));
        mPacket.magic = 0x47444d50;
        mPacket.version = 2;
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
    bool localFinished() const { return mPacket.finished != 0; }
    bool peerAcknowledged() const { return mPeerAcknowledged; }
    uint32_t remoteScore() const { return mRemoteScore; }
    void finish(uint32_t score, bool survived)
    {
        if (mPhase != Playing || localFinished()) return;
        mPacket.score = score;
        mPacket.survived = survived;
        mPacket.finished = 1;
    }
    Result result() const
    {
        if (!localFinished() || !mRemoteFinished) return Pending;
        if (bool(mPacket.survived) != mRemoteSurvived) return mPacket.survived ? Won : Lost;
        if (mPacket.score == mRemoteScore) return Draw;
        return mPacket.score > mRemoteScore ? Won : Lost;
    }
    bool ready(uint32_t localHash)
    {
        if (mPhase != LoadingMap) return false;
        mPhase = localHash && localHash == mPacket.mapHash ? WaitingStart : Failed;
        return mPhase != Failed;
    }
    MultiplayerPacket outgoing() const
    {
        MultiplayerPacket packet = mPacket;
        packet.resultSeen = localFinished() && mRemoteFinished;
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
            !memchr(packet.map, 0, sizeof(packet.map)) || !packet.map[0] ||
            packet.score > 0x7fffffffu || packet.finished > 1 || packet.survived > 1 || packet.resultSeen > 1) return false;
        for (const char *p = packet.map; *p; ++p)
            if (!((*p >= 'a' && *p <= 'z') || (*p >= '0' && *p <= '9') || *p == '_')) return false;
        if (!mHost && mPhase == WaitingMap && packet.type == Map)
        {
            mPacket.session = packet.session;
            mPacket.mapHash = packet.mapHash;
            memcpy(mPacket.map, packet.map, sizeof(mPacket.map));
            mPhase = LoadingMap;
            return true;
        }
        if (packet.session != mPacket.session || packet.mapHash != mPacket.mapHash ||
            strcmp(packet.map, mPacket.map)) return false;
        if (mHost && mPhase == WaitingReady && packet.type == Ready) mPhase = Starting;
        if (!mHost && mPhase == WaitingStart && packet.type == Start) mPhase = Playing;
        if (mHost && mPhase == Starting && packet.type == PlayingAck) mPhase = Playing;
        if (mPhase == Playing && packet.type == PlayingAck && packet.finished)
        {
            if (mRemoteFinished && (packet.score != mRemoteScore || bool(packet.survived) != mRemoteSurvived)) return false;
            mRemoteFinished = true;
            mRemoteScore = packet.score;
            mRemoteSurvived = packet.survived != 0;
            mPeerAcknowledged = packet.resultSeen != 0;
        }
        return packet.type >= Map && packet.type <= PlayingAck;
    }
private:
    bool mHost;
    Phase mPhase;
    MultiplayerPacket mPacket;
    bool mRemoteFinished;
    uint32_t mRemoteScore;
    bool mRemoteSurvived, mPeerAcknowledged;
};
#endif
