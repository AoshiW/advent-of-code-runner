#!/usr/bin/env bash
set -uo pipefail
D=$(dirname $(realpath $0))

SOLUTION_FILES=$1
IO_FILES=$2

for SOLUTION in $SOLUTION_FILES
do
    START=$($D/util/start.sh)

    while read INPUT OUTPUT; do
        CURRENT=$($D/util/start.sh)

        cat $INPUT | node --harmony-top-level-await $SOLUTION | diff $OUTPUT -
        if [ $? -ne 0 ]; then
            $D/util/error.sh "node" "$SOLUTION" "$INPUT"
            break 2
        fi

        TIMES+=($($D/util/stop.sh $CURRENT))
    done < <(echo $IO_FILES | xargs -n2)

    TOTAL=$($D/util/stop.sh $START)

    $D/util/success.sh "node" "$TOTAL" "$SOLUTION" "$TIMES"
done