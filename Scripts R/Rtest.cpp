#include <RInside.h>
#include "Rtest.h"

std::vector<double> correlationCarre(int q, std::vector<double> residus) {

	RInside R;
	std::vector<double> result;
	
	R["q"] = q;
	R["resid"] = residus;

	std::string str = 
		"n<-length(resid);"

		"rescarre = resid * resid;"
		"moy = sum(rescarre) / n;"
		"resmoy = rescarre - moy;"

		"gamzero = t(resmoy) %*% resmoy;"

		"gamcarre<-matrix(0, q);"

		"for(j in 1:q) {"
			"for(i in (j+1):n) {"
			"gamcarre[j] = gamcarre[j] + resmoy[i] * resmoy[i-j] }};"

		"rcarre<-matrix(0, q);"
		"for(j in 1:q) {"
			"rcarre[j] = gamcarre[j] / gamzero };"

		"qstat = 0;"
		"for(j in 1:q) {"
			"qstat = qstat + (rcarre[j]^2) / (n-j) };" 
		"qstat = qstat * n * (n+2);"
		"portstd = qstat;"

		"ststdport = portstd ;"

		//#####standard portmanteau test###
		"pvportcarre = 1 - pchisq(qstat, df = q);"

		"print(rescarre);"
		"print(ststdport);"
		"print(pvportcarre);"
		"result<-c(ststdport, pvportcarre);";

		result = R.parseEval(str);

		return result;
}

int main(int argc, char *argv[]) {

	std::vector<double> residus;
	residus.push_back(1.0);
	residus.push_back(2.0);
	residus.push_back(3.0);

	std::vector<double> test1 = correlationCarre(1, residus);
	//std::vector<double> test2 = correlationCarre(2, residus);

   	//std::cout << test1.at(0) << " " << test1.at(1);


	exit(0);
	
}