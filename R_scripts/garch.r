f <- file("stdin")
open(f)

# Parse the input line
firstline <- readLines(f,n=1)
tmp <- strsplit(firstline, " ")
logreturns <- as.numeric(unlist(tmp))

# Load the library with garch function
library(tseries)

# Remove warnings to be sure about the output format
options(warn=-1)

# Prevents the garch function to produce a massive and
# variable in length output
capture.output(res <- garch(logreturns), file='NUL')

# Outputs the coefficients
res$coef
# Outputs the residuals  without the first uninitialized value (eta)
print("residuals")
res$residuals[2:length(res$residuals)]

# Outputs the latest standard deviation value (sigma)
print("stddev")
res$fitted.values[,1][length(res$fitted.values[,1])]