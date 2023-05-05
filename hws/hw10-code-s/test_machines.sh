#!/bin/bash

machines="
csel-kh1250-01
csel-kh1250-02
csel-kh1250-03
csel-kh1250-04
csel-kh1250-05
csel-kh1250-06
csel-kh1250-07
csel-kh1250-08
csel-kh1250-09
csel-kh1250-10
csel-kh1250-11
csel-kh1250-12
csel-kh1250-13
csel-kh1250-14
csel-kh1250-15
csel-kh1250-16
csel-kh1250-17
csel-kh1250-18
csel-kh1250-19
csel-kh1250-20
csel-kh1250-21
csel-kh1250-22
csel-kh1250-23
csel-kh1250-24
csel-kh1250-25
csel-kh1250-26
csel-kh1250-27
csel-kh1250-28
csel-kh1250-29
csel-kh1250-30
csel-kh1250-31
csel-kh1250-32
csel-kh1250-33
csel-kh1250-34
csel-kh1250-35
csel-kh1250-36
csel-kh1250-37
"
for m in $machines; do
    echo $m
    ssh -o StrictHostKeyChecking=no $m "cd 2021/hw09-superscalar/solution-hw09-2021 && ./runall.sh > result_${m}.txt" &
done

# ssh -o StrictHostKeyChecking=no $machine
