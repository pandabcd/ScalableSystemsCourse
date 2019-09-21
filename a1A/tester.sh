folder_add="dense"

# LOAD TEST ARRAY
echo "LOAD ARRAY:"
for i in 2 3
do
	j=$((2**$i))
	command="./Runner.o load array $folder_add/$j.tsv $folder_add/result/result_array_load_$j.tsv" 
	# echo "Running command: $command"
	eval $command
	echo 
done

echo "LOAD CSR:"
# LOAD TEST CSR
for i in 2 3 
do
	j=$((2**$i))
	command="./Runner.o load csr $folder_add/$j.tsv $folder_add/result/result_array_load_$j.tsv" 
	# echo "Running command: $command"
	eval $command
	echo 
done

echo "TRANSPOSE ARRAY:"
# TRANSPOSE TEST ARRAY
for i in 2 3
do
	j=$((2**$i))
	command="./Runner.o transpose array $folder_add/$j.tsv $folder_add/result/result_array_load_$j.tsv" 
	# echo "Running command: $command"
	eval $command
	echo 
done

echo "TRANSPOSE CSR"
# TRANSPOSE TEST CSR
for i in 2 3
do
	j=$((2**$i))
	command="./Runner.o transpose csr $folder_add/$j.tsv $folder_add/result/result_array_load_$j.tsv" 
	# echo "Running command: $command"
	eval $command
	echo 
done

echo "MULT ARRAY"
# MULTIPLICATION TEST ARRAY
for i in 2 3
do
	j=$((2**$i))
	command="./Runner.o multiply array $folder_add/$j.tsv $folder_add/$j.tsv $folder_add/result/result_array_load_$j.tsv" 
	# echo "Running command: $command"
	eval $command
	echo 
done

echo "MULT CSR"
# MULTIPLICATION TEST CSR
for i in 2 3
do
	j=$((2**$i))
	command="./Runner.o multiply csr $folder_add/$j.tsv $folder_add/$j.tsv $folder_add/result/result_array_load_$j.tsv" 
	# echo "Running command: $command"
	eval $command
	echo 
done

echo "BMUL ARRAY:"
#BLOCK MULTIPLICATION ARRAY
for i in 2 3
do
	j=$((2**$i))
	command="./Runner.o bmultiply array $folder_add/$j.tsv $folder_add/$j.tsv $folder_add/result/result_array_load_$j.tsv" 
	# echo "Running command: $command"
	eval $command
	echo 
done

echo "BMUL CSR:"
#BLOCK MULTIPLICATION TEST CSR
for i in 2 3
do
	j=$((2**$i))
	command="./Runner.o bmultiply csr $folder_add/$j.tsv $folder_add/$j.tsv $folder_add/result/result_array_load_$j.tsv" 
	# echo "Running command: $command"
	eval $command
	echo 
done
