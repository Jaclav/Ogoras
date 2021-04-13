if [ ! -e $1 ]
then
	cd $1
fi
rm *.hpp 2> /dev/null
for x in *
do
	if [ ! -d $x ]
	then
		echo `echo "#ifndef $x" | cut --delimiter='.' --fields=1`_hpp > "$x.hpp"
		echo `echo "#define $x" | cut --delimiter='.' --fields=1`_hpp >> "$x.hpp"
		xxd -i $x >> "$x.hpp"
		echo "#endif" >> "$x.hpp"
		sed -i 's/\<unsigned\>/unsigned const/' "$x.hpp"
		#astyle -p -z2 -n "$x.hpp"
	fi
done
rm $0.hpp 2> /dev/null
