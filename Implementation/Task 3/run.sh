#
# suffix tests (using Test_hahaa.txt)
java -ea -cp dist Launcher Test_hahaa.txt suffix
echo "Expected: Yes"
echo
java -ea -cp dist Launcher Test_hahaa.txt suffix h
echo "Expected: No"
echo
java -ea -cp dist Launcher Test_hahaa.txt suffix ha
echo "Expected: No"
echo
java -ea -cp dist Launcher Test_hahaa.txt suffix hah
echo "Expected: No"
echo
java -ea -cp dist Launcher Test_hahaa.txt suffix haha
echo "Expected: No"
echo
java -ea -cp dist Launcher Test_hahaa.txt suffix hahaa
echo "Expected: Yes"
echo
java -ea -cp dist Launcher Test_hahaa.txt suffix ahaa
echo "Expected: Yes"
echo
java -ea -cp dist Launcher Test_hahaa.txt suffix haa
echo "Expected: Yes"
echo
java -ea -cp dist Launcher Test_hahaa.txt suffix aa
echo "Expected: Yes"
echo
java -ea -cp dist Launcher Test_hahaa.txt suffix a
echo "Expected: Yes"
echo
java -ea -cp dist Launcher Test_hahaa.txt suffix aha
echo "Expected: No"
echo
java -ea -cp dist Launcher Test_hahaa.txt substr bahaha
echo "Expected: No"
echo
#
# substring tests (using Test_hahaa.txt)
java -ea -cp dist Launcher Test_hahaa.txt substr
echo "Expected: Yes"
echo
java -ea -cp dist Launcher Test_hahaa.txt substr h
echo "Expected: Yes"
echo
java -ea -cp dist Launcher Test_hahaa.txt substr ha
echo "Expected: Yes"
echo
java -ea -cp dist Launcher Test_hahaa.txt substr hah
echo "Expected: Yes"
echo
java -ea -cp dist Launcher Test_hahaa.txt substr haha
echo "Expected: Yes"
echo
java -ea -cp dist Launcher Test_hahaa.txt substr hahaa
echo "Expected: Yes"
echo
java -ea -cp dist Launcher Test_hahaa.txt substr ahaa
echo "Expected: Yes"
echo
java -ea -cp dist Launcher Test_hahaa.txt substr haa
echo "Expected: Yes"
echo
java -ea -cp dist Launcher Test_hahaa.txt substr aa
echo "Expected: Yes"
echo
java -ea -cp dist Launcher Test_hahaa.txt substr a
echo "Expected: Yes"
echo
java -ea -cp dist Launcher Test_hahaa.txt substr aha
echo "Expected: Yes"
echo
java -ea -cp dist Launcher Test_hahaa.txt substr bahaha
echo "Expected: No"
echo
#
# count tests (using Test_hahaa.txt)
java -ea -cp dist Launcher Test_hahaa.txt count
echo "Expected: 6"
echo
java -ea -cp dist Launcher Test_hahaa.txt count h
echo "Expected: 2"
echo
java -ea -cp dist Launcher Test_hahaa.txt count ha
echo "Expected: 2"
echo
java -ea -cp dist Launcher Test_hahaa.txt count hah
echo "Expected: 1"
echo
java -ea -cp dist Launcher Test_hahaa.txt count haha
echo "Expected: 1"
echo
java -ea -cp dist Launcher Test_hahaa.txt count hahaa
echo "Expected: 1"
echo
java -ea -cp dist Launcher Test_hahaa.txt count ahaa
echo "Expected: 1"
echo
java -ea -cp dist Launcher Test_hahaa.txt count haa
echo "Expected: 1"
echo
java -ea -cp dist Launcher Test_hahaa.txt count aa
echo "Expected: 1"
echo
java -ea -cp dist Launcher Test_hahaa.txt count a
echo "Expected: 3"
echo
java -ea -cp dist Launcher Test_hahaa.txt count aha
echo "Expected: 1"
echo
java -ea -cp dist Launcher Test_hahaa.txt count bahaha
echo "Expected: 0"
echo
#
# longest repeat test (using Test_hahaa.txt)
java -ea -cp dist Launcher Test_hahaa.txt lonrep
echo "Expected: ha"
echo
#
# longest substring test (using Test_hahaa.txt)
java -ea -cp dist Launcher Test_hahaa.txt lonsub
echo "Expected: (blank string)"
echo
java -ea -cp dist Launcher Test_hahaa.txt lonsub bahaha
echo "Expected: haha"
echo
#
# show test (using Test_hahaa.txt)
java -ea -cp dist Launcher Test_hahaa.txt show
echo
#
# show test (using Test_blank.txt)
java -ea -cp dist Launcher Test_blank.txt show
echo
#
# show test (using Test_endsWith#.txt)
java -ea -cp dist Launcher Test_endsWith#.txt show
echo
#
# no arguments test
java -ea -cp dist Launcher
echo
#
# no function test
java -ea -cp dist Launcher Test_hahaa.txt
echo
#
# invalid file test
java -ea -cp dist Launcher Test_invalidFile.txt show
echo
#
# invalid function test
java -ea -cp dist Launcher Test_hahaa.txt display
echo
#
# Tester tests
java -ea -cp dist Tester
