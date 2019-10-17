// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2017 The PIVX developers
// Copyright (c) 2018-2019 The HCA developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "libzerocoin/Params.h"
#include "chainparams.h"
#include "random.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

using namespace std;
using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

/**
 * Main network
 */

//! Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress>& vSeedsOut, const SeedSpec6* data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int i = 0; i < count; i++) {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

//   What makes a good checkpoint block?
// + Is surrounded by blocks with reasonable timestamps
//   (no blocks before with a timestamp after, none after with
//    timestamp before)
// + Contains no strange transactions
static Checkpoints::MapCheckpoints mapCheckpoints =
    boost::assign::map_list_of
    (0, uint256("00000bb41fe2a8567d01a00eed09dd84255ea521588854f9a782cfb81eb03240"))
	(10, uint256("000009c99b9c7f4375ca5a93205ebe0faaa3c1b62717fea094ce57abdd663fc4"))
	(50, uint256("000008c408553a5dd493e36f385abe3a5f2999e7e8d10f56e8e966a306a7d04d"))
	(100, uint256("0000007ec329e47413be159c0d872e8d1f440dde68fe9c9e16dd2c5c088d9d99"))
	(150, uint256("000000d72d6fedadeb0e1f259929df89b1c4332097840ccce0b5984a9d4e4b96"))
	(200, uint256("0000002b0284d79b9984695343b6226b8cc08d8361f467285a481dca8aeba728"))
	(250, uint256("ae5b3fa1aeebd34219dd3d4c59e4d3bf53d43f588eca494f7681cffd77909f4d"))
	(500, uint256("21aefb618c0012680b10862811ce35953cd2968661dc8668eeb631701d630637"))
	(1000, uint256("97e695acce20c8793ba7769e5f5a735ad4532ed33a15e19ea9c6aca61d162e39"))
	(1464, uint256("dfab4cd5c4d790d3b54fc242efe8f28d4d1bc0acdaafd1656e2d41a595e6d9e3"))
	;
static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1571213108, // * UNIX timestamp of last checkpoint block
    2739,    	// * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the SetBestChain debug.log lines)
    3000        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of(0, uint256("00000bb41fe2a8567d01a00eed09dd84255ea521588854f9a782cfb81eb03240"));
static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1571025600,
    0,
    250};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of(0, uint256("00000bb41fe2a8567d01a00eed09dd84255ea521588854f9a782cfb81eb03240"));
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1571025600,
    0,
    100};

libzerocoin::ZerocoinParams* CChainParams::Zerocoin_Params() const
{
    assert(this);
    static CBigNum bnTrustedModulus(zerocoinModulus);
    static libzerocoin::ZerocoinParams ZCParams = libzerocoin::ZerocoinParams(bnTrustedModulus);

    return &ZCParams;
}

class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0xc1;
        pchMessageStart[1] = 0xac;
        pchMessageStart[2] = 0x01;
        pchMessageStart[3] = 0x0c;
        vAlertPubKey = ParseHex("0475d964dc3e2d2076641089f9f7043d2e076d7ff8175c2822b70313234571145258029cd9df1b37f5b45b8ff884af43008d19360f52a782d18f74df838d4ec697");
        nDefaultPort = 16518;
        bnProofOfWorkLimit = ~uint256(0) >> 20; // HCA starting difficulty is 1 / 2^12
        nSubsidyHalvingInterval = 4000000;
        nMaxReorganizationDepth = 100;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60;
        nTargetSpacing = 1 * 60;
        nMaturity = 60;
        nMasternodeCountDrift = 20;
        nMaxMoneyOut = 5000000 * COIN;

        /** Height or Time Based Activations **/
        nLastPOWBlock = 200;
        nModifierUpdateBlock = 1;
        nZerocoinStartHeight = 101;
        nAccumulatorStartHeight = 50;
        nZerocoinStartTime = 1529726034; // 20:30pm
        nBlockEnforceSerialRange = 1; //Enforce serial range starting this block
        nBlockRecalculateAccumulators = ~1; //Trigger a recalculation of accumulators
        nBlockFirstFraudulent = ~1; //First block that bad serials emerged
        nBlockLastGoodCheckpoint = ~1; //Last valid accumulator checkpoint

        const char* pszTimestamp = "October 14 2019 - Harcomia CRYO Launch";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 0 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("04678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5f") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime = 1571025600; // UTC Monday 14 October 2019 04:00:00
        genesis.nBits = 0x1E0FFFF0;
        genesis.nNonce = 1761074;

		hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("00000bb41fe2a8567d01a00eed09dd84255ea521588854f9a782cfb81eb03240"));
        assert(genesis.hashMerkleRoot == uint256("cc8ecf8500c9a1605eda8ad4b1385c823ddcc290d1413ed62b461c68d0ddf206"));

		vSeeds.push_back(CDNSSeedData("167.86.104.232", "167.86.104.232"));
		vSeeds.push_back(CDNSSeedData("164.68.110.103", "164.68.110.103"));
		vSeeds.push_back(CDNSSeedData("164.68.111.75", "164.68.111.75"));
		vSeeds.push_back(CDNSSeedData("116.203.156.64", "116.203.156.64"));
		vSeeds.push_back(CDNSSeedData("159.69.190.7", "159.69.190.7"));
		vSeeds.push_back(CDNSSeedData("95.216.164.118", "95.216.164.118"));
		vSeeds.push_back(CDNSSeedData("116.202.26.146", "116.202.26.146"));
		vSeeds.push_back(CDNSSeedData("164.68.106.143", "164.68.106.143"));
		
		// vSeeds.push_back(CDNSSeedData("68.183.6.219", "68.183.6.219"));
        // vSeeds.push_back(CDNSSeedData("104.248.195.155", "104.248.195.155"));
        // vSeeds.push_back(CDNSSeedData("142.93.40.174", "142.93.40.174"));
        // vSeeds.push_back(CDNSSeedData("134.209.238.96", "134.209.238.96"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 100);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 87);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 202);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x02)(0x25)(0x2D)(0x73).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x02)(0x31)(0x21)(0x2B).convert_to_container<std::vector<unsigned char> >();
        // 	BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x1d)(0xf0).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false;

        nPoolMaxTransactions = 3;
        strSporkKey = "04088bc099806c1559c7922ee856eb9c9fb9a6bf5b41ed66efc2986470a7ebfa77f0611ffb84e56106726f31f67c27338148529b25bdc16d3876abfc3dfd1136d9";
        strObfuscationPoolDummyAddress = "hTZah4snB3J2ptE8g1RuVXWHReBibMxxWA";
        nStartMasternodePayments = 1516371317; //Wed, 25 Jun 2014 20:36:16 GMT

        /** Zerocoin */
        zerocoinModulus = "09701225841875862781602011211432931360494778999216315640272611413082972701609200049371483999333740"
            "7122199140533232341811416699361221994104159230123921310219563085769373899444934151245854337057240079927900278965"
            "3886527527470294659057871190550419170649169971439432716099746456163484435030634301482437990052446135841334526680"
            "2083454951195876117931577959413088661521891853143942241426929896483761990862902964098877395091333151366270044883"
            "2442770464494707412407014678169300438076502778879938090170901723521467810070041967610852836397601157803677621223"
            "83337018492642333955246069177545823641383713513027542539001131825081270";
        nMaxZerocoinSpendsPerTransaction = 7; // Assume about 20kb each
        nMinZerocoinMintFee = 1 * ZCENT; //high fee required for zerocoin mints
        nMintRequiredConfirmations = 20; //the maximum amount of confirmations until accumulated in 19
        nRequiredAccumulation = 1;
        nDefaultSecurityLevel = 100; //full security level for accumulators
        nZerocoinHeaderVersion = 4; //Block headers must be this version once zerocoin is active
        nBudget_Fee_Confirmations = 6; // Number of confirmations for the finalization fee

        nStakeMinConfirmations = 720;   // Required number of confirmations
        nStakeMinAmount = 50 * COIN;    // Minimum required staking amount
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams
{
public:
    CTestNetParams()
    {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
        pchMessageStart[0] = 0xfa;
        pchMessageStart[1] = 0xfb;
        pchMessageStart[2] = 0xfc;
        pchMessageStart[3] = 0xfd;
        vAlertPubKey = ParseHex("04bb6495d4a192f1f262177f32e757ad33acac9ac97d09fc69ef7d7185ff0b022fb7b33ad9177e9bdd9aaf042e8a434e10278672600aa773387f36f14dc6ce9111");
        nDefaultPort = 11310;
        nEnforceBlockUpgradeMajority = 51;
        nRejectBlockOutdatedMajority = 75;
        nToCheckBlockUpgradeMajority = 100;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // HCA: 1 day
        nTargetSpacing = 1 * 60;  // HCA: 1 minute
        nLastPOWBlock = 200;
        nBTChangeBlock = 1000;
        nMaturity = 15;
        nMasternodeCountDrift = 4;
        nModifierUpdateBlock = 51197; //approx Mon, 17 Apr 2017 04:00:00 GMT
        nMaxMoneyOut = 43199500 * COIN;
        nZerocoinStartHeight = 50;
        nZerocoinStartTime = 1529726039;
        nBlockEnforceSerialRange = 1; //Enforce serial range starting this block
        nBlockRecalculateAccumulators = 9908000; //Trigger a recalculation of accumulators
        nBlockFirstFraudulent = 9891737; //First block that bad serials emerged
        nBlockLastGoodCheckpoint = 9891730; //Last valid accumulator checkpoint
        genesis.nTime = 1571025600;
        genesis.nNonce = 1761074;

	    hashGenesisBlock = genesis.GetHash();
		
		assert(hashGenesisBlock == uint256("00000bb41fe2a8567d01a00eed09dd84255ea521588854f9a782cfb81eb03240"));		

        vFixedSeeds.clear();
        vSeeds.clear();
        vSeeds.push_back(CDNSSeedData("testnet.harcomia.com", "testnet.harcomia.com"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 95);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 105);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 214);
        // Testnet hca BIP32 pubkeys
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x2a)(0x12)(0x11).convert_to_container<std::vector<unsigned char> >();
        // Testnet hca BIP32 prvkeys
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x41)(0x11)(0x1a).convert_to_container<std::vector<unsigned char> >();
        // Testnet hca BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x01).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 2;
        strSporkKey = "04088bc099806c1559c7922ee856eb9c9fb9a6bf5b41ed66efc2986470a7ebfa77f0611ffb84e56106726f31f67c27338148529b25bdc16d3876abfc3dfd1136d9";
        strObfuscationPoolDummyAddress = "hTZah4snB3J2ptE8g1RuVXWHReBibMxxWA";
        nStartMasternodePayments = 1420837558; //Fri, 09 Jan 2015 21:05:58 GMT
        nBudget_Fee_Confirmations = 3; // Number of confirmations for the finalization fee. We have to make this very short
                                       // here because we only have a 8 block finalization window on testnet

        nStakeMinConfirmations = 30;    // Required number of confirmations
        nStakeMinAmount = 1000 * COIN;  // Minimum required staking amount
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams
{
public:
    CRegTestParams()
    {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        strNetworkID = "regtest";
        pchMessageStart[0] = 0xf1;
        pchMessageStart[1] = 0xf2;
        pchMessageStart[2] = 0xf3;
        pchMessageStart[3] = 0xf4;
        nSubsidyHalvingInterval = 150;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        nTargetTimespan = 24 * 60 * 60; // HCA: 1 day
        nTargetSpacing = 1 * 60;        // HCA: 1 minute
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        genesis.nTime = 1571025600;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 1761074;

        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 36210;
        assert(hashGenesisBlock == uint256("00000bb41fe2a8567d01a00eed09dd84255ea521588854f9a782cfb81eb03240"));

        vFixedSeeds.clear(); //! Testnet mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Testnet mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;

/**
 * Unit test
 */
class CUnitTestParams : public CMainParams, public CModifiableParams
{
public:
    CUnitTestParams()
    {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 51478;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Unit test mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }

    //! Published setters to allow changing values in unit test cases
    virtual void setSubsidyHalvingInterval(int anSubsidyHalvingInterval) { nSubsidyHalvingInterval = anSubsidyHalvingInterval; }
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority) { nEnforceBlockUpgradeMajority = anEnforceBlockUpgradeMajority; }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority) { nRejectBlockOutdatedMajority = anRejectBlockOutdatedMajority; }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority) { nToCheckBlockUpgradeMajority = anToCheckBlockUpgradeMajority; }
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks) { fDefaultConsistencyChecks = afDefaultConsistencyChecks; }
    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) { fAllowMinDifficultyBlocks = afAllowMinDifficultyBlocks; }
    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};

static CChainParams* pCurrentParams = 0;

const CChainParams& Params()
{
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(CBaseChainParams::Network network)
{
    switch (network) {
    case CBaseChainParams::MAIN:
        return mainParams;
    case CBaseChainParams::TESTNET:
        return testNetParams;
    case CBaseChainParams::REGTEST:
        return regTestParams;
    default:
        assert(false && "Unimplemented network");
        return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}
