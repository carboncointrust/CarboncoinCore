#!/bin/bash

echo 'NOTE: THIS SHOULD BE RUN FROM GIT ROOT'
echo 'NOTE: FOLLOW UP WITH ./autogen.sh && configure && make'

grep -rl bitcoin . | grep -v '.git/' | grep -v bitcoinToCarboncoin | xargs sed -i "s/bitcoin/carboncoin/g"
grep -rl Bitcoin . | grep -v '.git/' | grep -v bitcoinToCarboncoin | xargs sed -i "s/Bitcoin/Carboncoin/g"
grep -rl BITCOIN . | grep -v '.git/' | grep -v bitcoinToCarboncoin | xargs sed -i "s/BITCOIN/CARBONCOIN/g"
grep -rl BTC . | grep -v '.git/' | grep -v bitcoinToCarboncoin | xargs sed -i "s/BTC/CARBON/g"
grep -rl btc . | grep -v '.git/' | grep -v bitcoinToCarboncoin | xargs sed -i "s/btc/carbon/g"

for f in $(find . -type f -name '*bitcoin*'); do git mv $f $(echo $f | sed "s/bitcoin/carboncoin/"); done
for f in $(find . -type f -name '*Bitcoin*'); do git mv $f $(echo $f | sed "s/Bitcoin/Carboncoin/"); done



