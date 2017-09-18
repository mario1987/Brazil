// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"

#include "chainparams.h"
#include "main.h"
#include "util.h"
#include "checkpoints.h"

#include <boost/assign/list_of.hpp>

using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"
//
// Main network
//

// Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress> &vSeedsOut, const SeedSpec6 *data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int i = 0; i < count; i++)
    {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xa6;
        pchMessageStart[1] = 0x7d;
        pchMessageStart[2] = 0x62;
        pchMessageStart[3] = 0x7f;
        vAlertPubKey = ParseHex("04b9fd13c016ed91528241bcf3bd55023679be17f0bd3a16e6fbeba2f222989769417eb053cd9f16a9a2894ad5ebbd551be1a4bd2d10cdb679228c91e26e26900e");
        nDefaultPort = 17645;
        nRPCPort = 17646;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);
		
        const char* pszTimestamp = "https://www.ft.com/content/75ce67da-9c53-11e7-8cd4-932067fbf946"; // Investors’ high hopes for Brazil likely to remain a dream
        std::vector<CTxIn> vin;
        vin.resize(1);
        vin[0].scriptSig = CScript() << 4861235 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        std::vector<CTxOut> vout;
        vout.resize(1);
        vout[0].SetEmpty();
        CTransaction txNew(1, 1505765340, vin, vout, 0);
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1505765340;
        genesis.nBits    = 0x1f00ffff; 
        genesis.nNonce   = 497458;

        hashGenesisBlock = genesis.GetHash();

        assert(hashGenesisBlock == uint256("0xcc02b76f5777a461cc6c8677cf8972eb9c4563d2358509d8f777f7a2ef1aeb47"));
        assert(genesis.hashMerkleRoot == uint256("0xe4bb360813baa6baa89e8c653b27d3dc8f070076792bb8664c0e3102be9f7c2a"));

        
        base58Prefixes[PUBKEY_ADDRESS] = list_of(24);
        base58Prefixes[SCRIPT_ADDRESS] = list_of(48);
        base58Prefixes[SECRET_KEY] =     list_of(96);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x77)(0x7B)(0x2A);
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x77)(0x4E)(0x4C);

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        nPOSStartBlock = 1000;
    }

    virtual const CBlock& GenesisBlock() const { return genesis; }
    virtual Network NetworkID() const { return CChainParams::MAIN; }

    virtual const vector<CAddress>& FixedSeeds() const {
        return vFixedSeeds;
    }
protected:
    CBlock genesis;
    vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;


//
// Testnet
//

class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0x5d;
        pchMessageStart[1] = 0x8a;
        pchMessageStart[2] = 0x22;
        pchMessageStart[3] = 0xe7;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);
        vAlertPubKey = ParseHex("04b9fd13c016ed91528241bcf3bd55023679be17f0bd3a16e6fbeba2f222989769417eb053cd9f16a9a2894ad5ebbd551be1a4bd2d10cdb679228c91e26e26900e");
        nDefaultPort = 27645;
        nRPCPort = 27646;
        strDataDir = "testnet";

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nBits  = 520649337; 
        genesis.nNonce = 76431;

        //assert(hashGenesisBlock == uint256(""));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = list_of(35);
        base58Prefixes[SCRIPT_ADDRESS] = list_of(70);
        base58Prefixes[SECRET_KEY]     = list_of(140);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0xd1)(0x88)(0x3B)(0xE5);
        base58Prefixes[EXT_SECRET_KEY] = list_of(0xd1)(0x88)(0x6D)(0xFC);


        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        nPOSStartBlock = 1000;

    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;


static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
    return *pCurrentParams;
}

void SelectParams(CChainParams::Network network) {
    switch (network) {
        case CChainParams::MAIN:
            pCurrentParams = &mainParams;
            break;
        case CChainParams::TESTNET:
            pCurrentParams = &testNetParams;
            break;
        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {
    
    bool fTestNet = GetBoolArg("-testnet", false);
    
    if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}
