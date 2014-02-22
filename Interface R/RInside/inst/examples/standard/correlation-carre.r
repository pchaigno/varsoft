# Modified R script made compatible with RInside.
# 
n<-length(resid);

rescarre = resid^2;
moy = mean(rescarre);
resmoy = rescarre - moy;

gamzero = t(resmoy) %*% resmoy;

# q rows matrix
gamcarre<-matrix(0, q);

for(j in 1:q) {
	for(i in (j+1):n) {
		gamcarre[j] = gamcarre[j] + resmoy[i] * resmoy[i-j]
	}
}

rcarre<-matrix(0, q);

for(j in 1:q) {
	rcarre[j] = gamcarre[j] / gamzero
}

qstat = 0;
for(j in 1:q) {
	qstat = qstat + (rcarre[j]^2) / (n-j)
}
qstat = qstat * n * (n+2);
portstd = qstat;

ststdport = portstd;

#####standard portmanteau test###
pvportcarre = 1 - pchisq(qstat, df = q);

print(rescarre);
print(ststdport);
print(pvportcarre);

result<-c(ststdport, pvportcarre)
