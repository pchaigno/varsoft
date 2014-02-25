class Importator
{
private:
	IStrategieImport* strategy;

public:
	Importator(IStrategieImport* strategy): strategy(strategy){}

	void execute()
	{
		strategie->execute();
	}

};
