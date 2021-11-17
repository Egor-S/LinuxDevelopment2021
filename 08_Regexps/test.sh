SED=$(/bin/echo "$3" | sed -E "s/$1/$2/")
ESUB=$($4 "$1" "$2" "$3")

echo " sed: $SED"
echo "esub: $ESUB"

[ "$SED" = "$ESUB" ]