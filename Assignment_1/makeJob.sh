i=2
j=33333

while [ $i -lt 9 ]; do
	mkdir $i
	sed "s,myN,$i,g" SingleJob.sh > $i/SingleJob.sh_T
	sed "s,mySeed,$j,g" $i/SingleJob.sh_T > $i/SingleJob.sh
	rm $i/SingleJob.sh_T
        cp prog1.cpp $i
	cd $i
	qsub SingleJob.sh
	cd ..
	i=$(($i+2))
done

