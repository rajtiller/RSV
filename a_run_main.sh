make clean
rm main output.csv output.rsv
make
./main
rm -rf *dSYM
# g++ -o rsv_to_csv_converter rsv_to_csv_converter.cpp
./rsv_to_csv_converter
diff -y output.csv output_2.csv