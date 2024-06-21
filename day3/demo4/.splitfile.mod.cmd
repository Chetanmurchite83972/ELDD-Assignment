cmd_/home/chetan/ELDD/day3/demo2/splitfile.mod := printf '%s\n'   day3_2.o day3_2b.o | awk '!x[$$0]++ { print("/home/chetan/ELDD/day3/demo2/"$$0) }' > /home/chetan/ELDD/day3/demo2/splitfile.mod
