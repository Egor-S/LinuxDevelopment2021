MY=$(echo "MD5 Makefile.am" | ./rhasher | tail -1)
GT=$(md5sum Makefile.am)

MY="${MY,,}"
GT="${GT%%[[:space:]]*}"

echo "$GT"
echo "$MY"

[ "$MY" = "$GT" ]
