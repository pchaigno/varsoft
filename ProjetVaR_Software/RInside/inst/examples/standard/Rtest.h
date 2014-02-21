class Rtest
{
	public:
		// Rtest is a singleton because a RInside instance at a time is allowed
		static Rtest & getInstance() {
			static Rtest instance;

			return instance;
		}

		std::vector<double> correlationCarre(int q, std::vector<double> & residus);
		std::vector<double> correlationNiveau(int m, std::vector<double> & residus);

	private:
		RInside R;
		Rtest() {};
};

