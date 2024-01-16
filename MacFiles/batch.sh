#!/bin/sh
gun=$1
ener=$2
nparticles=$3
#for i in {200..1000..200}
for i in {1..10}
do
#echo $i
outfile=$gun'_'$ener'_'$i
sed 's/ENER/'$ener'/g' shielding.mac > $outfile 
sed 's/GUN/'$gun'/g' -i $outfile
sed 's/NPARTICLES/'$nparticles'/g' -i $outfile
echo $outfile
./main $outfile &
done