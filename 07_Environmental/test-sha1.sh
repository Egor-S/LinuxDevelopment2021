MY=$(echo "SHA1 Makefile.am" | ./rhasher | tail -1)
GT=$(sha1sum Makefile.am)

MY="${MY,,}"
GT="${GT%%[[:space:]]*}"

echo "$GT"
echo "$MY"

[ "$MY" = "$GT" ]
