f <- file("stdin")
open(f)

# Parse the line
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
# Outputs the residuals (eta)
res$residuals
# Outputs the standard deviation (sigma)
res$fitted.values[,1]