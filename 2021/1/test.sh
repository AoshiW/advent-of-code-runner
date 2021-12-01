#!/usr/bin/env bash
set -euo pipefail

D=$(dirname $(realpath $0))

echo "-- Day 1 --"
printf "%-10s %-20s %-8s %-10s %-10s \n" "language" "author" "total" "average" "status"
$D/../../lang/node.sh   "$D/solutions/node/stelar7/*.mjs"  "$D/io/*"

echo ""