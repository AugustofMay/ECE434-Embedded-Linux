temp1=`i2cget -y 2 0x48`
temp2=`i2cget -y 2 0x4a`

temp1=$(($temp1 * 9 / 5 + 32))
temp2=$(($temp2 * 9 / 5 + 32))

echo "$temp1"
echo "$temp2"
