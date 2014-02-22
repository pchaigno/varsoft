n<-length(resid);

autocov<-matrix(0, m+1);

for(j in 1:(m+1)) {
		for(i in (j+1):n) {
			autocov[j] = autocov[j] + resid[i] * resid[i-(j-1)]
		}
	};

	autocorr<-matrix(0,m);

	for(j in 2:(m+1)) {
		autocorr[j-1] = autocov[j] / autocov[1]
	}

	Qstat = t(autocorr) %*% autocorr;
	Qstat = n * Qstat;

	pvportm = 1 - pchisq(Qstat, df = m);

	print(Qstat);
	print(pvportm);
	result<-c(Qstat, pvportm);