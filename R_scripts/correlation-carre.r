######################################
#  Portmanteau test for the squares  #
######################################
# R script made compatible with
# Rscript calls using standard input

# Read parameters from the standard input
f <- file("stdin")
open(f)

# Parse the first line
firstline <- readLines(f,n=1)
q <- as.numeric(firstline)

# Parse the second line
secondline <- readLines(f,n=1)
tmp <- strsplit(secondline, " ")
resid <- as.numeric(unlist(tmp))

# Actual function
	n<-length(resid)

	rescarre = resid * resid
	moy = sum(rescarre) / n
	resmoy = rescarre - moy

	gamzero = t(resmoy) %*% resmoy

	gamcarre<-matrix(0, q)
	for(j in 1:q) {
		for(i in (j+1):n) {
			gamcarre[j] = gamcarre[j] + resmoy[i] * resmoy[i-j]
		}
	}

	rcarre<-matrix(0, q)
	for(j in 1:q) {
		rcarre[j] = gamcarre[j] / gamzero
	}

	qstat = 0
	for(j in 1:q) {
		qstat = qstat + (rcarre[j]^2) / (n-j)
	}
	qstat = qstat * n * (n+2)
	portstd = qstat

	ststdport = portstd
	#####standard portmanteau test###

	pvportcarre = 1 - pchisq(qstat, df = q)

	list(ststdport = ststdport, pvportcarre = pvportcarre)