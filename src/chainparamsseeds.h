#ifndef BITCOIN_CHAINPARAMSSEEDS_H
#define BITCOIN_CHAINPARAMSSEEDS_H
/**
 * List of fixed seed nodes for the bitcoin network
 * AUTOGENERATED by contrib/seeds/generate-seeds.py
 *
 * Each line contains a 16-byte IPv6 address and a port.
 * IPv4 as well as onion addresses are wrapped inside a IPv6 address accordingly.
 */
static SeedSpec6 pnSeed6_main[] = {
    {{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xff,0x2e,0xfd,0xcb,0x71}, 9350},
    {{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xff,0xcc,0x1b,0x3a,0xd6}, 9350},
    {{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xff,0xad,0xa7,0x71,0x49}, 9350},
};

static SeedSpec6 pnSeed6_test[] = {
    {{0xfd,0x87,0xd8,0x7e,0xeb,0x43,0xa0,0x60,0x9e,0x46,0x54,0xdb,0x61,0x3b,0xb2,0x6f}, 19350}
};
#endif // BITCOIN_CHAINPARAMSSEEDS_H
