#!/bin/bash

chars=("é")

for ((i=32; i<=126; i++)); do
    char=$(printf \\$(printf '%03o' "$i"))
    chars+=("$char")
done

font="smascii12"

for char in "${chars[@]}"; do
    filename="GeneratedFont/char_[${char//\//slash}].ch"
    toilet "$char" -f "$font" -S > "$filename"
done
