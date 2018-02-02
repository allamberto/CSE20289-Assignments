#!/bin/sh
#Ana Luisa Lamberto

if [ $# -eq "0" ]; then
	echo "Usage: extract.sh archive1 archive2..."
	exit 1
fi
for file in $@; do
	case $file in
		*.tar.gz)
			tar xzvf $file
			;;
		*.tgz)
      tar xzvf $file
			;;
		*.tbz)
			tar xjvf $file
			;;
		*.tar.bz2)
			tar xjvf $file
			;;
		*.txz)
			tar xvf $file
			;;
		*.tar.xz)
			tar xvf $file
			;;
		*.zip)
			unzip $file
			;;
		*.jar)
			unzip $file
			;;
		*)
			echo "Unknown archive format: $file"
			exit 1
		esac
shift
done
