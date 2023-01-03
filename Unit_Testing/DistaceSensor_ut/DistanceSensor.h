




class DistanceSensor
{


public:

	DistanceSensor(void);
	~DistanceSensor(void);

	void Init();
	void StartMeasure();
	float GetResult();
	
	
private:
	float LastDistace;
	
	
}