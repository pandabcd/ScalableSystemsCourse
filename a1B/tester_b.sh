# LBST
for i in 1 2 3 4 5
do
	command="./a.out lbst -data Test_Files/TestB/tree_$i.tsv -query Test_Files/TestB/tree_query_3.tsv -output Test_Files/ResultB/lbst_$i_query_$i.tsv"
	echo "Running: $command"
	eval $command
	echo
done

#ABT
for i in 1 2 3 4 5
do
	command="./a.out abt -data Test_Files/TestB/tree_$i.tsv -query Test_Files/TestB/tree_query_3.tsv -output Test_Files/ResultB/abt_$i_query_$i.tsv"
	echo "Running: $command"
	eval $command
	echo
done

#LBT
for i in 1 2 3 4 5
do
	command="./a.out lbt -data Test_Files/TestB/tree_$i.tsv -query Test_Files/TestB/tree_query_3.tsv -output Test_Files/ResultB/lbt_$i_query_$i.tsv"
	echo "Running: $command"
	eval $command
	echo
done

#ABST
for i in 1 2 3 4 5
do
	command="./a.out abst -data Test_Files/TestB/tree_$i.tsv -query Test_Files/TestB/tree_query_3.tsv -output Test_Files/ResultB/abst_$i_query_$i.tsv"
	echo "Running: $command"
	eval $command
	echo
done