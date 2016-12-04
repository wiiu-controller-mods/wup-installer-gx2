#! /bin/bash
#
rev_new_raw=$(svnversion -n . 2>/dev/null | tr '\n' ' ' | tr -d '\r')
[ -n "$rev_new_raw" ] || rev_new_raw=$(SubWCRev . 2>/dev/null | tr '\n' ' ' | tr -d '\r')

rev_new_raw=$(echo $rev_new_raw | sed 's/[^0-9]*\([0-9]*\)\(.*\)/\1 \2/')
rev_new=0
a=$(echo $rev_new_raw | sed 's/\([0-9]*\).*/\1/')
let "a+=0"
#find max rev
while [ "$a" ]; do
	[ "$a" -gt "$rev_new" ] && rev_new=$a
	rev_new_raw=$(echo -n $rev_new_raw | sed 's/[0-9]*[^0-9]*\([0-9]*\)\(.*\)/\1 \2/')
	a=$(echo $rev_new_raw | sed 's/\([0-9]*\).*/\1/') 
done

rev_old=$(cat ./src/common/svnrev.c 2>/dev/null | tr -d '\n' | sed 's/[^0-9]*\([0-9]*\).*/\1/')

rev_new=`expr $rev_new + 1`

if [ "$rev_new" != "$rev_old" ] || [ ! -f ./src/common/svnrev.c ]; then
	
	cat <<EOF > ./src/common/svnrev.c
#include <stdlib.h>

#define SVN_REV "$rev_new"

const char *GetRev()
{
	return SVN_REV;
}

int GetIntRev()
{
	return atoi(SVN_REV);
}
EOF

	if [ -n "$rev_old" ]; then
		echo "Changed Rev $rev_old to $rev_new" >&2
	else
		echo "svnrev.c created at Rev $rev_new" >&2
	fi
fi

rev_date=`date -u +%Y%m%d%H%M%S`
	
cat <<EOF > ./meta/meta.xml
<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<app version="1">
  <name>WUP Installer GX2</name>
  <coder>Dj_Skual</coder>
  <version>v0.1 rev$rev_new</version>
  <release_date>$rev_date</release_date>
  <short_description>WiiU public title installer.</short_description> 
  <long_description>This application can install public titles such as game updates to your system memory (NAND) or the WiiU formatted USB.
This application is based on "WUP Installer y Mod" by Yardape and the GUI on "Loadiine GX2" sources.

Thanks to:
  Loadiine GX2 team for GUI sources.
  Yardape for installer sources.

Links:
  https://sourceforge.net/projects/wup-installer-gx2/
  </long_description> 
</app>
EOF
