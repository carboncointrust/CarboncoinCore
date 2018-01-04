// Copyright (c) 2009-2014 The Carboncoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "checkpoints.h"

#include "main.h"
#include "uint256.h"

#include <stdint.h>

#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/foreach.hpp>

namespace Checkpoints
{
    typedef std::map<int, uint256> MapCheckpoints;

    // How many times we expect transactions after the last checkpoint to
    // be slower. This number is a compromise, as it can't be accurate for
    // every system. When reindexing from a fast disk with a slow CPU, it
    // can be up to 20, while when downloading from a slow network with a
    // fast multicore CPU, it won't be much higher than 1.
    static const double SIGCHECK_VERIFICATION_FACTOR = 5.0;

    struct CCheckpointData {
        const MapCheckpoints *mapCheckpoints;
        int64_t nTimeLastCheckpoint;
        int64_t nTransactionsLastCheckpoint;
        double fTransactionsPerDay;
    };

    bool fEnabled = true;

    // What makes a good checkpoint block?
    // + Is surrounded by blocks with reasonable timestamps
    //   (no blocks before with a timestamp after, none after with
    //    timestamp before)
    // + Contains no strange transactions
    static MapCheckpoints mapCheckpoints =
        boost::assign::map_list_of
        (      0, uint256("0xa94f1aae8c409a0bd1e53cbca92d7e506b61c51d955cf56f76da501718d48d6c"))
        (      1, uint256("0x27fe28d8f814805c20aa2a2b31f629cb8a52d7016894541c5e424c18d6810559"))
        (      2, uint256("0x763ce0b24417ea00b642ba2e9980189d7c6d5f2cd0fd1574ac35e0e8d27fb405"))
        (  10000, uint256("0x12697138ac647bec1ad807dd45827e67d7ed334bb47d823849e3dbbb48eebf64"))
        (  20000, uint256("0x66099425a0ed2c3899e85e015e06f52a6138574d983829390e667ef4b5a9c89a"))
        (  30000, uint256("0x1a49a6076a25f7e2ba68f39131f0788b3dda5ac504c59b24f6182be1247cf65a"))
        (  40000, uint256("0x10d2e04152bf5c21b585a8c9720de6dc2c9f8440b70560cb9c796ccedd0b0ac3"))
        (  50000, uint256("0x80c232bc7ca8ea6905fda51b017d9d4fe37523953d840765e96540ece0f2f3ba"))
        (  60000, uint256("0x3913df09d0715aa54e1e44c5308dc475d1371f25029b619c609de2241d3c83e6"))
        (  70000, uint256("0x345877d805e44fd1573dac836096ff1f3fd6a6604f0e51c665f2e7aea27f912b"))
        ( 100000, uint256("0xd6fccdd775246ca400c35fbd4ad2275b31a44f40efbf5cc45048abb77fde8be5"))
        ( 250000, uint256("0x7997350321ba0cf566bbb986e78091b659792beb8836741b000c4c768874333a"))
        ( 350000, uint256("0xc49473306a4a0a53d89c4bde317512dd08e15071c3885726ff303a5a70a06a1b"))
        ( 500000, uint256("0xc9d6a919c20d3d63d85891bbef85b0e88d44dcc741daa3c4f948213bd0440806"))
        ( 750000, uint256("0x1b5cbc3dfefca593228b26e5c50ff53c9a199d238db43902f3f9918e083c35d7"))
        (1000000, uint256("0x3deaea4f0a8e29d144662ef493e2065461572f86876228346255fa61bfdfd2fd"))
        ;
    static const CCheckpointData data = {
        &mapCheckpoints,
        1511459387, // * UNIX timestamp of last checkpoint block
        1252933,   // * total number of transactions between genesis and last checkpoint
                    //   (the tx=... number in the SetBestChain debug.log lines)
        300.0     // * estimated number of transactions per day after checkpoint
    };

    static MapCheckpoints mapCheckpointsTestnet =
        boost::assign::map_list_of
        ( 0, uint256("0x027c03874be8e8c1ead6518fd37f5c416e0eb02d5982919a21a2a7f8b86c80c8"))
        ;
    static const CCheckpointData dataTestnet = {
        &mapCheckpointsTestnet,
        1389199887,
        1,
        300.0
    };

    static MapCheckpoints mapCheckpointsRegtest =
        boost::assign::map_list_of
        ( 0, uint256("0xdeb6129ee5fbbf3ae8ca75e4650b5df2ba4241ff4b568506b2b3bff40b0c8a12"))
        ;
    static const CCheckpointData dataRegtest = {
        &mapCheckpointsRegtest,
        0,
        0,
        0.0
    };

    const CCheckpointData &Checkpoints() {
        if (Params().NetworkID() == CChainParams::TESTNET)
            return dataTestnet;
        else if (Params().NetworkID() == CChainParams::MAIN)
            return data;
        else
            return dataRegtest;
    }

    bool CheckBlock(int nHeight, const uint256& hash)
    {
        if (!fEnabled)
            return true;

        const MapCheckpoints& checkpoints = *Checkpoints().mapCheckpoints;

        MapCheckpoints::const_iterator i = checkpoints.find(nHeight);
        if (i == checkpoints.end()) return true;
        return hash == i->second;
    }

    // Guess how far we are in the verification process at the given block index
    double GuessVerificationProgress(CBlockIndex *pindex, bool fSigchecks) {
        if (pindex==NULL)
            return 0.0;

        int64_t nNow = time(NULL);

        double fSigcheckVerificationFactor = fSigchecks ? SIGCHECK_VERIFICATION_FACTOR : 1.0;
        double fWorkBefore = 0.0; // Amount of work done before pindex
        double fWorkAfter = 0.0;  // Amount of work left after pindex (estimated)
        // Work is defined as: 1.0 per transaction before the last checkpoint, and
        // fSigcheckVerificationFactor per transaction after.

        const CCheckpointData &data = Checkpoints();

        if (pindex->nChainTx <= data.nTransactionsLastCheckpoint) {
            double nCheapBefore = pindex->nChainTx;
            double nCheapAfter = data.nTransactionsLastCheckpoint - pindex->nChainTx;
            double nExpensiveAfter = (nNow - data.nTimeLastCheckpoint)/86400.0*data.fTransactionsPerDay;
            fWorkBefore = nCheapBefore;
            fWorkAfter = nCheapAfter + nExpensiveAfter*fSigcheckVerificationFactor;
        } else {
            double nCheapBefore = data.nTransactionsLastCheckpoint;
            double nExpensiveBefore = pindex->nChainTx - data.nTransactionsLastCheckpoint;
            double nExpensiveAfter = (nNow - pindex->nTime)/86400.0*data.fTransactionsPerDay;
            fWorkBefore = nCheapBefore + nExpensiveBefore*fSigcheckVerificationFactor;
            fWorkAfter = nExpensiveAfter*fSigcheckVerificationFactor;
        }

        return fWorkBefore / (fWorkBefore + fWorkAfter);
    }

    int GetTotalBlocksEstimate()
    {
        if (!fEnabled)
            return 0;

        const MapCheckpoints& checkpoints = *Checkpoints().mapCheckpoints;

        return checkpoints.rbegin()->first;
    }

    CBlockIndex* GetLastCheckpoint(const std::map<uint256, CBlockIndex*>& mapBlockIndex)
    {
        if (!fEnabled)
            return NULL;

        const MapCheckpoints& checkpoints = *Checkpoints().mapCheckpoints;

        BOOST_REVERSE_FOREACH(const MapCheckpoints::value_type& i, checkpoints)
        {
            const uint256& hash = i.second;
            std::map<uint256, CBlockIndex*>::const_iterator t = mapBlockIndex.find(hash);
            if (t != mapBlockIndex.end())
                return t->second;
        }
        return NULL;
    }
}
