######################################
#  Portmanteau test for the squares  #
######################################
statstd<-function(q, resid) {
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
}

statstd(1, c(1, 2, 3))