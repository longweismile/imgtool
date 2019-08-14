#!/bin/bash
echo "encode script"
echo Script Name:"$0"
pwd
cd ..
cd afbcutil/afbcutil
pwd
./afbcenc $1 $2 $3 $4 $5 $6 $7 $8
echo $1
echo $2
echo $3
echo $4
echo $5
echo $6
echo $7
echo $8
