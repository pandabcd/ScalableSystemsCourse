# LOAD TEST ARRAY
# for i in 2 3 4 5 6 7 8 9 10 11 12
# do
# 	command="./a.out load array Test_Files/Test/matrix_$i.tsv Test_Files/Result/result_array_load_$i.tsv" 
# 	echo "Running command: $command"
# 	eval $command
# 	echo 
# done

# # LOAD TEST CSR
# for i in 2 3 4 5 6 7 8 9 10 11 12
# do
# 	command="./a.out load csr Test_Files/Test/matrix_$i.tsv Test_Files/Result/result_csr_load_$i.tsv" 
# 	echo "Running command: $command"
# 	eval $command
# 	echo 
# done

# # TRANSPOSE TEST ARRAY
# for i in 2 3 4 5 6 7 8 9 10 11 12
# do
# 	command="./a.out transpose array Test_Files/Test/matrix_$i.tsv Test_Files/Result/result_array_transpose_$i.tsv" 
# 	echo "Running command: $command"
# 	eval $command
# 	echo 
# done

# # TRANSPOSE TEST CSR
# for i in 2 3 4 5 6 7 8 9 10 11 12
# do
# 	command="./a.out transpose csr Test_Files/Test/matrix_$i.tsv Test_Files/Result/result_csr_transpose_$i.tsv" 
# 	echo "Running command: $command"
# 	eval $command
# 	echo 
# done


# MULTIPLICATION TEST ARRAY
for i in 2 3 4 5 6 7 8 9 10 11
do
	command="./a.out multiply array Test_Files/Test/matrix_$i.tsv Test_Files/Test/matrix_$i.tsv Test_Files/Result/result_array_multiplication_$i.tsv" 
	echo "Running command: $command"
	eval $command
	echo 
done

# MULTIPLICATION TEST CSR
for i in 2 3 4 5 6 7 8 9 10 11
do
	command="./a.out multiply csr Test_Files/Test/matrix_$i.tsv Test_Files/Test/matrix_$i.tsv Test_Files/Result/result_csr_multiplication_$i.tsv" 
	echo "Running command: $command"
	eval $command
	echo 
done


#BLOCK MULTIPLICATION ARRAY
for i in 2 3 4 5 6 7 8 9 10 11
do
	command="./a.out bmultiply array Test_Files/Test/matrix_$i.tsv Test_Files/Test/matrix_$i.tsv Test_Files/Result/result_array_multiplication_$i.tsv" 
	echo "Running command: $command"
	eval $command
	echo 
done

#BLOCK MULTIPLICATION TEST CSR
for i in 2 3 4 5 6 7 8 9 10 11
do
	command="./a.out bmultiply csr Test_Files/Test/matrix_$i.tsv Test_Files/Test/matrix_$i.tsv Test_Files/Result/result_csr_multiplication_$i.tsv" 
	echo "Running command: $command"
	eval $command
	echo 
done
