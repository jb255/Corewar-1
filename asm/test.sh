./asm file.s
touch file
mv file.cor file
./asm2 file.s
diff file.cor file
