// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2015 The Carboncoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef CARBONCOIN_RPCCLIENT_H
#define CARBONCOIN_RPCCLIENT_H

#include <univalue.h>

UniValue RPCConvertValues(const std::string& strMethod, const std::vector<std::string>& strParams);
/** Non-RFC4627 JSON parser, accepts internal values (such as numbers, true, false, null)
 * as well as objects and arrays.
 */
UniValue ParseNonRFCJSONValue(const std::string& strVal);

#endif // CARBONCOIN_RPCCLIENT_H
