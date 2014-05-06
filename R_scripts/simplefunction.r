args <- commandArgs(TRUE)

x = as.numeric(args[1])
y = as.numeric(args[2])
sum <- x + y
list(sum = sum)