filename="addbook"
opt=5
while [ $opt -lt  6 ]
do
	echo -e "\nEnter your choice:\n1 : create address book\n2 : insert records\n3 : delete records\n4 : modify records\n5 : View Records\n6 : exit "
	read opt

	case "$opt"  in
		1)
			if [ -e $filename ]; then
				rm $filename
			fi
			echo -e "\tNAME\tADDRESS\tNUMBER\n===========================================\n" | cat >> $filename
			cont=1
			while [ $cont -ne 0 ] 
			do
				echo -e "\nEnter name :\t"
				read name
				echo -e "\nEnter address :\t"
				read add
				echo -e "\nEnter number :\t"
				read num
				echo -e "\t$name\t$add\t$num" | cat >> $filename 
				echo -e "\nenter more records ? 0>no 1>yes"
				read cont
			done
			;;

		2)
			cnt=1
			while [ $cnt -ne 0 ] 
			do
				echo -e "\nEnter name :\t"
				read name
				echo -e "\nEnter address :\t"
				read add
				echo -e "\nEnter number :\t"
				read num
				echo -e "\t$name\t$add\t$num"|cat >> $filename 
				echo -e "\nenter more records ? 0>no 1>yes"
				read cnt
			done
			;;

		3)
			echo -e "\nEnter number to delete"
			read pattern
			temp="temp"
			grep -v $pattern $filename | cat >> $temp
			rm $filename
			cat $temp | cat >> $filename
			rm $temp
			;;


		4)
			echo -e "\nEnter number to modify"
			read pattern
			temp="temp"
			grep -v $pattern $filename | cat >> $temp
			rm $filename
			echo -e "\nEnter name :\t"
			read name
			echo -e "\nEnter address :\t"
			read add
			echo -e "\nEnter number :\t"
			read num
			echo -e "\t$name\t$add\t$num"|cat >> $temp
			cat $temp | cat >> $filename
			rm $temp
			;;
	
		5)
			cat $filename
			;;
	
	esac
done 

