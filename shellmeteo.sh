#!/bin/bash


#sort meteo_filtered_data_v1.csv > meteo_filtered_data_v1_fil.csv

#grep filtre les données
#egrep 'd [0-9][0-9][0-9][0-9]_[0-9][0-9]_[0-9][0-9] [0-9][0-9][0-9][0-9]_[0-9][0-9]_[0-9][0-9]' $* > oui.csv
#function main(){

# la chaîne de caractère qui contient tous les arguments
arguments=$*


#variable qui montre trop d'option sélectionner ou d'erreur d'option
erreur=0
zone=0
tri=0

#non du fichier
file=0

#option activé ou non
mindate=0
maxdate=0
t1=0
t2=0
t3=0
p1=0
p2=0
p3=0
w=0
h=0
m=0
d=0
avl=0
abr=0
tab=0
#reg pour région des sation elle permet de connaître la zone spécifié
reg=0

help=0
nbr=$#
echo $nbr
echo $#
echo $@
	for (( i=1 ; i<$nbr ; i++ )) ; do
		echo $1
		case $1 in
			-t2 )
			t2=1
			shift;;
			
			-t1 )
			t1=1
			shift;;
			
			-t3 )
			t3=1
			shift;;
			
			-p1 )
			p1=1
			shift;;
			
			-p2 )
			p2=1
			shift;;
			
			-p3 )
			p3=1
			shift;;
			
			-w )
			w=1
			shift;;
			
			-h ) 
			h=1
			shift;;
			
			-m )
			 m=1
			shift;;
			
			--avl )
			avl=1
			tri=$(( tri + 1 ))
			shift;;
			
			--abr )
			abr=1
			tri=$(( tri + 1 ))
			shift;;
			
			--tab )
			tab=1
			tri=$(( tri + 1 ))
			shift;;
			
			-d )
			d=1
			shift
			mindate=$1
			shift
			maxdate=$1
			if (( mindate > maxdate )) ; then
				erreur=$(( erreur + 1 ))
			fi
			shift;;
			 
			-F )
			reg=F
			zone=$zone+1			
			shift;; 
			
			-G )
			reg=G
			zone=$zone+1
			shift;;
			
			-S )
			reg=S
			zone=$zone+1
			shift;;
			
			-A )
			reg=A
			zone=$zone+1
			shift;;
			
			-Q )
			reg=Q
			zone=$zone+1
			shift;;
			
			-O )
			reg=O
			zone=$zone+1
			shift;;
			
			-f )
			shift
			echo $1
			file=$1
			echo $file
			shift;;
			
			-help )
			help=1
			shift;;
			 
			*) 
			erreur=$(( erreur + 1 ))
			shift;;
		esac
	done
	
	echo $mindate
	echo $maxdate
	
	if (( $zone > 1 )) ; then
		echo "il y a trop d'option zone"
		erreur=$(( erreur + 1 ))
	fi
	
	if (( $tri > 1 )) ; then
		echo "il y a trop d'option de tri"
		erreur=$(( erreur + 1 ))
	fi
	
	
if (( $help == 1 )) ; then

	echo "Le programme nécessite quelques opt ion nécessaire. La première est l'option -f soit '' -f nom_fichier.csv ''."
	echo " Puis il y a des option -p et -t il nécessité absolument un mode soit 1, 2, 3. par exemple -p2. "
	echo " p correspont à la pression et t à la température. De plus le mode per met de sortir certaine donné."
	echo "1 permet de sortir la moyenne par station minimale et maximal. trier dans l'ordre croissant des ID de station"
	echo " le mode 2 permet de prduire moyenne par date/heure trié dans l'ordre chronologique." 
	echo " Le 3 permet de sortir les donné en ordre chronologique puis par station."
	echo " l'option -w permet de connaître l'orientation du vent moyen"
	echo " l'option -h permet de connaitre l'altitude "
	echo " permet de connaitre les zone les plus humides"	
	exit
fi

	if (( $erreur > 3 )) ; then
		exit
	fi

#egrep '2010-05-10' $file > meteo_filtered_data_v1_fil.csv
#partie où l'option d est activé
maxdate=${maxdate}T22:00:00+01:00
mindate=${mindate}T00:00:00+01:00


#	awk -F ';' '$2 > $mindate' $file > datefil.csv
#awk { if[ $2 >= $mindate ] && [ $2 <= $maxdate ] print $0;}
#awk '{ if[ "$2" < "$maxdate" ] print $0 }' FS=";" $file > datef.csv
#awk '{ if[ "$2" > "$mindate" ] print $0 }' FS=";" datef.csv > datefil.csv

#sed -n '/2019-02-24/,/2019-03-24/p' $file > datefil.csv

				file=datefil.csv
#egrep ';9;' meteo_filtered_data_v1_fil.csv > meteo_fil2.csv
#partie où l'option zone est choisi


if (( $reg != 0 )) ; then	
	case $reg in
	
		"F") echo files for france
		     awk -F ';' '$1 < 8000' $file > FinalWeather.csv	
		     ;;
		     
		"O") echo file for Indian ocean
			awk -F ';' '$1 < 68000' && '$1 > 61000' $file > FinalWeather.csv	
			;;
		
		"A") echo file for Antilles
			awk -F ';' '$1 < 78000' && '$1 > 79000' $file > FinalWeather.csv	
			;;
			
		"S") echo file for St pierre
			awk -F ';' '$1 < 72000' && '$1 > 71000' $file > FinalWeather.csv	
			;;
	
		"Q") echo file for Antartic
			awk -F ';' '$1 < 89000' && '$1 > 90000' $file > FinalWeather.csv	
			;;

	esac
fi





# partie où -t la température est demandé
if (( t1 == 1 )) ; then
	
	cut -d ';' -f 1,2,10,11,12 FinalWeather.csv > Temperature.csv
	id=7027
	total=0
	min=0
	max=0
	#id=$(awk -F ';' 'NR == 1 {print $1; exit}' "Temperature.csv")
	max=$(awk -F ';' 'NR == 1 {print $5; exit}' "Temperature.csv")
	min==$(awk -F ';' 'NR == 1 {print $3; exit}' "Temperature.csv")
	average=$(awk -F ';' "{if(\$1 == \""$id"\") {sum+=$"4"; count++}} END {print sum/count}" "Temperature.csv")
	
	
	cat "$id;$min;$average;$max" >> meteo_t1.csv

	
fi

if (( t2 == 1 )) ; then
	
	cut -d ';' -f 1,2,10,11,12 $file > meteo_filt.csv

fi

if (( t3 == 1 )) ; then
	
	cut -d ';' -f 1,2,10 $file > meteo_filt.csv

fi

# partie où -p la pression est demandé
if (( p1 == 1 )) ; then


	cut -d ';' -f 1,2,7 $file > meteo_filp.csv

	

fi

if (( p2 == 1 )) ; then


cut -d ';' -f 1,2,7 $file > meteo_filp.csv



fi


echo $p3
if (( p3 == 1 )) ; then

echo $file
cut -d ';' -f 1,2,7 $file > meteo_filp.csv



fi




if (( w == 1 )) ; then

cut -d ';' -f 1,2,6 $file > meteo_filw.csv

fi


if (( h == 1 )) ; then

cut -d ';' -f 1,2,14 $file > meteo_filh.csv

fi
