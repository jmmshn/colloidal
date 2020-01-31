for file in d_*.dat
do
    echo $file $(tail -1 $file|awk '{print $2}')

done
