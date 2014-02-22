#include <RInside.h>
#include <string>
#include <fstream>
#include <streambuf>
#include "Rtest.h"

//TODO clean variables R session maybe
//DOXYgen
//Cleaner tests.
// TODO lire le code R a depuis un fichier ext.
// voir quand ca bug.
std::vector<double> Rtest::correlationCarre(int q, std::vector<double> & residus) {

	try {
		//RInside R;
		std::vector<double> result;
		
		R["q"] = q;
		R["resid"] = residus;

		/*std::string str = 
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
			"result<-c(ststdport, pvportcarre);";*/

			// TODO: Coder un chemin de fichier est dur, c'est pas super ?
			// a gerer probablement dans un fichier de configuration
			std::ifstream t("correlation-carre.r");
			std::string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
			t.close();

			std::cout << str;

			result = R.parseEval(str);

			return result;
		} catch(std::exception& ex) {
        	std::cerr << "Exception caught: " << ex.what() << std::endl;
    	} catch(...) {
        	std::cerr << "Unknown exception caught" << std::endl;
    }
}

std::vector<double> Rtest::correlationNiveau(int m, std::vector<double> residus) {

	std::vector<double> result;

	R["m"] = m;
	R["resid"] = residus;

	/*std::string str =
	"n<-length(resid);"

	"autocov<-matrix(0, m+1);"

	"for(j in 1:(m+1)) {"
		"for(i in (j+1):n) {"
			"autocov[j] = autocov[j] + resid[i] * resid[i-(j-1)]"
		"}"
	"};"

	"autocorr<-matrix(0,m);"

	"for(j in 2:(m+1)) {"
		"autocorr[j-1] = autocov[j] / autocov[1]"
	"};"

	"Qstat = t(autocorr) %*% autocorr;"
	"Qstat = n * Qstat;"

	"pvportm = 1 - pchisq(Qstat, df = m);"

	"print(Qstat);"
	"print(pvportm);"
	"result<-c(Qstat, pvportm);";*/

	std::ifstream t("correlation-niveau.r");
	std::string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
	t.close();

	result = R.parseEval(str);

	return result;
}

int main(int argc, char *argv[]) {

	Rtest r = Rtest::getInstance();

	std::vector<double> residus;
	residus.push_back(1.0);
	residus.push_back(2.0);
	residus.push_back(3.0);

	std::vector<double> test1 = r.correlationCarre(1, residus);
	std::cout << test1.at(0) << ' ' << test1.at(1) << std::endl;
	//std::vector<double> test2 = r.correlationCarre(2, residus);

	//std::vector<double> test3 = r.correlationNiveau(1, residus);
	//std::cout << test3.at(0) << ' ' << test3.at(1) << std::endl;

   	//std::cout << test1.at(0) << " " << test1.at(1);

	exit(0);
}