f <- file("stdin")
open(f)
#while(length(line <- readLines(f,n=1)) > 0) {
firstline <- readLines(f,n=1)
firstparam <- as.numeric(firstline)
print(firstparam)
line <- readLines(f,n=1)
  #write(line, stdout())
  #write(typeof(line), stdout())
  test <- strsplit(line, " ")
  #print(test)
  #print(typeof(test))
  test2 <- unlist(test)
  result <- mean(as.numeric(test2))*firstparam
  #write(test, stdout())
  # process line
  list(result=result)
#}