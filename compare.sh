#!/bin/bash

# Compare script to test the validity of bin/main.out against ./test.txt
#   by Tim Müller (11774606)



# Remove the old output file if there is any
rm -f ./output.txt

# Simply run the main the appropriate number of times
for i in 0 1 2 5 10 20 50 100 200 500 1000 2000 5000
do
	bin/main.out $i >> ./output.txt
done

# Report if they are equal or not
(cmp ./output.txt ./test.txt && echo "Test success!") || echo "Test failure..."
