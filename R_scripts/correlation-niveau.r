####################################
#  Portmanteau test for the level  #
####################################
# Modified script made compatible with
# Rscript calls using standard input

# Read parameters from the standard input
f <- file("stdin")
open(f)

# Parse the first line
firstline <- readLines(f,n=1)
m <- as.numeric(firstline)
#print(m)

# Parse the second line
secondline <- readLines(f,n=1)
tmp <- strsplit(secondline, " ")
resid <- as.numeric(unlist(tmp))
#print(resid)
#resid <- c(1, 2, 3)
#print(resid)

#portmanteau<-function(m, resid) {
	n<-length(resid)

	autocov<-matrix(0, m+1)

	for(j in 1:(m+1)) {
		for(i in (j+1):n) {
			autocov[j] = autocov[j] + resid[i] * resid[i-(j-1)]
		}
	}

	autocorr<-matrix(0,m)

	for(j in 2:(m+1)) {
		autocorr[j-1] = autocov[j] / autocov[1]
	}

	Qstat = t(autocorr) %*% autocorr
	Qstat = n * Qstat

	pvportm = 1 - pchisq(Qstat, df = m)

	list(qstat=Qstat, pvportm = pvportm)