folder_add="test"
result_folder="result"
# LBST
echo "LBST:"
for i in 4 5 6 
do
	command="./BTRunner.o abt -data $folder_add/tree_$i.tsv -query $folder_add/tree_query_4.tsv -output $folder_add/$result_folder/lbst_$i_query_$i.tsv"
	# echo "Running: $command"
	eval $command
	echo
done

#ABT
# echo "ABT:"
# for i in 1 2 3
# do
# 	command="./BTRunner.o abt -data Test_Files/TestB/tree_$i.tsv -query Test_Files/TestB/tree_query_3.tsv -output Test_Files/ResultB/abt_$i_query_$i.tsv"
# 	# echo "Running: $command"
# 	eval $command
# 	echo
# done

# #LBT
# echo "LBT:"
# for i in 1 2 3
# do
# 	command="./BTRunner.o lbt -data Test_Files/TestB/tree_$i.tsv -query Test_Files/TestB/tree_query_3.tsv -output Test_Files/ResultB/lbt_$i_query_$i.tsv"
# 	# echo "Running: $command"
# 	eval $command
# 	echo
# done

# #ABST
# echo "ABST:"
# for i in 1 2 3
# do
# 	command="./BTRunner.o abst -data Test_Files/TestB/tree_$i.tsv -query Test_Files/TestB/tree_query_3.tsv -output Test_Files/ResultB/abst_$i_query_$i.tsv"
# 	# echo "Running: $command"
# 	eval $command
# 	echo
# done