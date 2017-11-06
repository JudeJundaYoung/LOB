#include<iostream>
#include<vector>
#include<string>

#define TM 30 //total Mile
#define WH 8  //work hour
#define WD 5  //work days
#define R  4  //output rate
#define MBT 2 //minimum buffer time

struct Activity
{
	std::string Name;
	int Manhours_Per_Mile;	//2
	int Men_Per_Gang;		//3
	float Theoretical_Gang_Size;	//4
	int Actual_Gang_Size;		//5
	float Actual_Output_Rate;	//6
	float Activity_Duration_Per_Mile;	//7
	float Time_From_Start_to_Last;		//8
	int Min_Buffer_Time = MBT;		//9

	Activity(std::string N, int MPM, int MPG):Name(N),Manhours_Per_Mile(MPM),Men_Per_Gang(MPG)
	{
		Theoretical_Gang_Size = Manhours_Per_Mile * R / (WH * WD);
		Actual_Gang_Size = get_Actual(Theoretical_Gang_Size);
		Actual_Output_Rate = R * Actual_Gang_Size / Men_Per_Gang;
		Activity_Duration_Per_Mile = Manhours_Per_Mile / (WH * Men_Per_Gang);
		Time_From_Start_to_Last = ((TM - 1) * Manhours_Per_Mile) / (WH * Actual_Gang_Size);
	}

	int get_Actual(float TGS)
	{
		float MultipleF = Theoretical_Gang_Size / Men_Per_Gang;
		int MultipleI = MultipleF;
		float Positive = (MultipleI+1) * Men_Per_Gang - Theoretical_Gang_Size;
		float Negative = (MultipleI * Men_Per_Gang - Theoretical_Gang_Size) * (-1);
		if (Positive >= Negative)
		{
			int Actual = MultipleI * Men_Per_Gang;
			if (Actual == Men_Per_Gang)
			{
				Actual *= 2;
			}
			return Actual;
		}
		else
		{
			int Actual = (MultipleI+1) * Men_Per_Gang;
			if (Actual == Men_Per_Gang)
			{
				Actual *= 2;
			}
			return Actual;
		}


	}

	void Print() const
	{
		std::cout << Name << " " << Manhours_Per_Mile << " " << Men_Per_Gang << " " << Theoretical_Gang_Size
			<< " " << Actual_Gang_Size << " " << Actual_Output_Rate << " " << Activity_Duration_Per_Mile
			<< " " << Time_From_Start_to_Last << " " << Min_Buffer_Time;
		std::cout << std::endl;
	}
};


int main()
{
	std::vector<Activity> LOB;
	Activity A("Excavation", 384, 8);
	Activity B("String Pipe", 128, 4);
	Activity C("Lay Pipe", 168, 3);
	Activity D("Test", 48, 2);
	Activity E("Backfill", 240, 6);
	LOB.emplace_back(A);
	LOB.emplace_back(B);
	LOB.emplace_back(C);
	LOB.emplace_back(D);
	LOB.emplace_back(E);
	for (const auto &a : LOB)
	{
		a.Print();
	}
}